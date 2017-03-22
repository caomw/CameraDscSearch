#include "dscplugin_meanch.h"

#include <cv.h>
#include <highgui.h>
#include <QFileInfo>

/*static */QString      DscPluginMeanCh::codeType/*        = ""*/;
/*static */QStringList  DscPluginMeanCh::codeSubTypes/*    = QStringList()*/;

DscPluginMeanCh::DscPluginMeanCh(const std::string& strCode) {
    setStrCode(strCode);
}

void DscPluginMeanCh::setStrCode(const std::string &strCode)
{
    if(strCode[0]=='c') {
        this->isColor   = true;
    } else {
        this->isColor   = false;
    }
}

void DscPluginMeanCh::buildDscFromPath(const std::string &imgPath)
{
    cv::Mat imgb;
    if(isColor) {
        imgb = cv::imread(imgPath, CV_LOAD_IMAGE_COLOR);
    } else {
        imgb = cv::imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
    }
    buildDscFromMat(imgb);
}

void DscPluginMeanCh::buildDscFromMat(const cv::Mat &imgin)
{
    dsc.clear();
    if(!imgin.data) {
        std::cerr << "!!! WARNING !!! image can't be loaded..." << std::endl;
        return;
    }
    cv::Mat timg = imgin;
    int nch = imgin.channels();
    if(nch<1) {
        std::cerr << "!!! WARNING !!! image has zero channels (::buildDscFromMat)!" << std::endl;
        return;
    }
    if(isColor && nch==1) {
        cv::cvtColor(imgin, timg, CV_GRAY2BGR);
    }
    if(!isColor && nch==3) {
        cv::cvtColor(imgin, timg, CV_BGR2GRAY);
    }
    nch = timg.channels();
    cv::Scalar mch  = cv::mean(timg);
    dsc.clear();
    for(int ii=0; ii<nch; ii++) {
        dsc.push_back(mch[ii]/(nch*255));
    }
}

double DscPluginMeanCh::calcDscDistance(const DscPluginInterface *d) const
{
    double ret  = 0.;
    DscPluginMeanCh* dm = (DscPluginMeanCh*)d;
    int num = std::min(dsc.size(), dm->dsc.size());
    if(num<1) {
        ret = -1.;
    } else {
        for(int ii=0; ii<num; ii++) {
            ret += fabs(dsc[ii] - dm->dsc[ii]);
        }
    }
    return ret;
}

void DscPluginMeanCh::saveToStream(std::ofstream &ofs)
{
    int siz = dsc.size();
    ofs.write((char*)&siz, sizeof(int));
    ofs.write((char*)dsc.data(), dsc.size()*sizeof(double));
}

void DscPluginMeanCh::loadFromStream(std::ifstream &ifs)
{
    dsc.clear();
    int siz = 0;
    ifs.read((char*)&siz, sizeof(int));
    if(siz>0) {
        double* tmp  = new double[siz];
        ifs.read((char*)tmp, siz*sizeof(double));
        dsc.assign(tmp, tmp+siz);
        delete [] tmp;
    }
}

void DscPluginMeanCh::clear()
{
    dsc.clear();
}

void DscPluginMeanCh::init(const QString &pathToLoadedLibrary/*=""*/)
{
    if(!loadBaseConfig(pathToLoadedLibrary, DscPluginMeanCh::codeType, DscPluginMeanCh::codeSubTypes)) {
        initDefault();
    }
}

DscPluginInterface *DscPluginMeanCh::createObject(const std::string &dscCode) const
{
    if(dscCode.empty()) {
        return new DscPluginMeanCh();
    } else {
        return new DscPluginMeanCh(dscCode);
    }
}

QString DscPluginMeanCh::getCodeType() const
{
    return DscPluginMeanCh::codeType;
}

QStringList DscPluginMeanCh::getCodeSubTypes() const
{
    return DscPluginMeanCh::codeSubTypes;
}

QString DscPluginMeanCh::getSuffix() const
{
    return QString("%1_%2").arg(DscPluginMeanCh::codeType).arg(suffix);
}

QString DscPluginMeanCh::getShortInfo() const
{
    QStringList lst;
    for(int ii=0; ii<dsc.size(); ii++) {
        lst.append(QString::number(dsc[ii]));
    }
    return QString("%1 : [%2]").arg(DscPluginMeanCh::codeType).arg(lst.join(", "));
}

void DscPluginMeanCh::initDefault()
{
    DscPluginMeanCh::codeType    = default_codeType;
    DscPluginMeanCh::codeSubTypes.clear();
    for(int ii=0; ii<default_numDscCooTypes; ii++) {
        codeSubTypes.append(QString(default_dscCooTypesCodes[ii]));
    }
}
