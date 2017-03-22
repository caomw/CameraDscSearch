#ifndef DSCCOOMATRIX_H
#define DSCCOOMATRIX_H

#include "lib_descriptor2sl.h"
#include "dscplugininterface.h"
#include "dscplugincoomatrix_global.h"

#include <QObject>
#include <iostream>
#include <sstream>

#define     DEF_IMAGE_BASESIZE  128

static const char* default_dscCooTypesCodes[] = {
    // gray:
    "g1p4b1g1r1d",
    "g1p4b3g1r1d",
    //
    "g2p3b1g1r1d",
    "g2p3b1g1rmd",
    "g2p3b3g1r1d",
    //
    "g3p2b1g1r1d",
    "g3p2b1g1rmd",
    "g3p2b3g1r1d",
    // color:
    "c1p3b1g1r1d",
    "c1p3b3g1r1d",
    //
    "c2p3b1g1r1d",
    "c2p3b1g1rmd",
    "c2p3b3g1r1d",
    //
    "c3p2b1g1r1d",
    "c3p2b1g1rmd",
    "c3p2b3g1r1d"
};

static const int    default_numDscCooTypes  = sizeof(default_dscCooTypesCodes)/sizeof(default_dscCooTypesCodes[0]);
const QString       default_codeType        = "coomat";

using namespace dscv2sl;

class DSCPLUGIN_COOMATRIX_LIBRARY DscPluginCooMatrix : public QObject, DscPluginInterface
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "by.basnet.uiip.lab225.DscPluginInterface" FILE "simpletestplugin.json")
    Q_PLUGIN_METADATA(IID "by.basnet.uiip.lab225.DscPluginInterface")
    Q_INTERFACES(DscPluginInterface)
public:
    DscPluginCooMatrix() {}
    DscPluginCooMatrix(const std::string& strCode);
//    std::string toString() const;
    void    buildDscFromPath(const std::string &imgPath);
    void    buildDscFromMat (const cv::Mat &imgin);
    double  calcDscDistance(const DscPluginInterface *d) const;
    void    saveToStream(std::ofstream &ofs);
    void    loadFromStream(std::ifstream &ifs);
    void    clear();
    //
    void                init(const QString& pathToLoadedLibrary="");
    DscPluginInterface* createObject(const std::string& dscCode="") const;
    QString             getCodeType() const;
    QStringList         getCodeSubTypes() const;
    //
    QString getSuffix() const;
    QString getShortInfo() const;

    SDescriptorP dsc;
private:
    void initDefault();
    void setStrCode(const std::string& strCode);
    QString suffix;
    static QString      codeType;
    static QStringList  codeSubTypes;
    //
    int  dscType;
    int  dscGridSize;
    int  dscNBin;
    bool isColor;
    bool isMultiDst;
    int  dscDst;
    bool isRotateInvariant;
};

#endif // DSCCOOMATRIX_H
