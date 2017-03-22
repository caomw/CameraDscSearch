#include "dscplugincoomatrix.h"

#include <QFileInfo>

/*static */QString      DscPluginCooMatrix::codeType/*        = ""*/;
/*static */QStringList  DscPluginCooMatrix::codeSubTypes/*    = QStringList()*/;

DscPluginCooMatrix::DscPluginCooMatrix(const std::string& strCode) {
    setStrCode(strCode);
}

//         |0    |1 |3  |5   |7  |9  |
//  str =  |color|Np|Bin|Grid|Rot|Dst|   min-length = 11
//  ex#1   = c1p3b1g1r2d --> Colored, 1-Point, 2^3 bin, 1-Grid, rot-inv, dst=2
//  ex#2   = g2p3b2g0rm  --> Gray, 2-Point, 2^3 bin, 2x2-Grid, rot-non-inv, dst=1-3-5
void DscPluginCooMatrix::setStrCode(const std::string &strCode)
{
    if(strCode.size()>10) {
        if(strCode[0]=='c') {
            this->isColor   = true;
        } else {
            this->isColor   = false;
        }
        dscType     = atoi(strCode.substr(1,1).c_str());
        dscNBin     = atoi(strCode.substr(3,1).c_str());
        dscGridSize = atoi(strCode.substr(5,1).c_str());
        if(strCode[9]=='m') {
            isMultiDst  = true;
            dscDst      = -1;
        } else  {
            dscDst      = atoi(strCode.substr(7,1).c_str())-1;
            isMultiDst  = false;
        }
        if(strCode[7]=='1') {
            isRotateInvariant   = true;
        } else {
            isRotateInvariant   = false;
        }
        suffix  = QString(strCode.c_str());
    } else {
        dscType = -1;
        std::cerr << "*** ERROR-DSC *** bad-dsc string-code" << std::endl;
    }
}

void DscPluginCooMatrix::buildDscFromPath(const std::string &imgPath)
{
    cv::Mat imgb;
    if(isColor) {
        imgb = cv::imread(imgPath, CV_LOAD_IMAGE_COLOR);
    } else {
        imgb = cv::imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
    }
    buildDscFromMat(imgb);
}

void DscPluginCooMatrix::buildDscFromMat(const cv::Mat &imgin)
{
    cv::Mat timg = imgin;
    int nch = imgin.channels();
    if(isColor && nch==1) {
        cv::cvtColor(imgin, timg, CV_GRAY2BGR);
    }
    if(!isColor && nch==3) {
        cv::cvtColor(imgin, timg, CV_BGR2GRAY);
    }
    if(timg.data) {
        cv::Mat img = resizeImageProportional(timg, DEF_IMAGE_BASESIZE);
        timg.release();
        if(dscType>0) {
            SDescriptorI tmpDsc;
            if(isMultiDst) {
                if(dscGridSize>1) {
                    buildCompoundDscGridFullImage(img, tmpDsc, dst_135, dst_135_siz, dscGridSize, dscType, dscNBin, isRotateInvariant);
                } else {
                    buildCompoundDscFullImage(img, tmpDsc, dst_135, dst_135_siz, dscType, dscNBin, isRotateInvariant);
                }
            } else {
                if(dscGridSize>1) {
                    int dst[1];
                    dst[0]      = dscDst;
                    buildCompoundDscGridFullImage(img, tmpDsc, dst, 1, dscGridSize, dscType, dscNBin, isRotateInvariant);
                } else {
                    recti roi   = getCorrectROIForFullImage(img, dscDst+1);
                    buildDescriptorFromMat(img, roi, dscType, dscNBin, tmpDsc, dscDst, isRotateInvariant);
                }
            }
//            std::cout << tmpDsc << std::endl;
            dsc.loadFromIntDsc(tmpDsc);
//            std::cout << dsc << std::endl;
//            dsc.applyThreshFloat(dsc.getThreshMinMax(0.1));
//            std::cout << dsc << std::endl;
        } else {
            std::cerr << "!!! ERROR incorrect parameters for build COO-descriptro..." << std::endl;
        }
    } else {
        std::cerr << "!!! WARNING !!! image can't be loaded..." << std::endl;
    }
}

double DscPluginCooMatrix::calcDscDistance(const DscPluginInterface *d) const
{
    return this->dsc.L1(((DscPluginCooMatrix*)d)->dsc);
}

void DscPluginCooMatrix::saveToStream(std::ofstream &ofs)
{
    dsc.bsave(ofs);
//    std::cout << "raw-save-dsc: " << dsc << std::endl;
}

void DscPluginCooMatrix::loadFromStream(std::ifstream &ifs)
{
    dsc.bload(ifs);
//    std::cout << "raw-load-dsc: " << dsc << std::endl;
}

void DscPluginCooMatrix::clear()
{
    dsc.clear();
}

void DscPluginCooMatrix::init(const QString &pathToLoadedLibrary/*=""*/)
{
    if(!loadBaseConfig(pathToLoadedLibrary, DscPluginCooMatrix::codeType, DscPluginCooMatrix::codeSubTypes)) {
        initDefault();
    }
}

DscPluginInterface *DscPluginCooMatrix::createObject(const std::string &dscCode) const
{
    if(dscCode.empty()) {
        return new DscPluginCooMatrix();
    } else {
        return new DscPluginCooMatrix(dscCode);
    }
}

QString DscPluginCooMatrix::getCodeType() const
{
    return DscPluginCooMatrix::codeType;
}

QStringList DscPluginCooMatrix::getCodeSubTypes() const
{
    return DscPluginCooMatrix::codeSubTypes;
}

QString DscPluginCooMatrix::getSuffix() const
{
    return QString("%1_%2").arg(DscPluginCooMatrix::codeType).arg(suffix);
}

QString DscPluginCooMatrix::getShortInfo() const
{
    return DscPluginCooMatrix::codeType;
}

void DscPluginCooMatrix::initDefault()
{
    DscPluginCooMatrix::codeType    = default_codeType;
    DscPluginCooMatrix::codeSubTypes.clear();
    for(int ii=0; ii<default_numDscCooTypes; ii++) {
        codeSubTypes.append(QString(default_dscCooTypesCodes[ii]));
    }
}
