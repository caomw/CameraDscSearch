#ifndef DSCINTERFACE_H
#define DSCINTERFACE_H

#include <iostream>
#include <fstream>
#include <cv.h>

#include <QString>
#include <QtPlugin>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QDebug>

#define DEF_CFG_GROUP_DSCCODE_STR       "config"
#define DEF_CFG_KEYS_DSCCODE_STR        "codeType"
#define DEF_CFG_KEYS_DSCSUBCODES_STR    "codeSubTypes"

#define DEF_PLUGIN_DIR                  "dsc"

class DscPluginInterface
{
public:

    virtual void    buildDscFromPath(const std::string& imgPath)    = 0;
    virtual void    buildDscFromMat (const cv::Mat&     img    )    = 0;
    virtual double  calcDscDistance(const DscPluginInterface* dsc) const  = 0;
    virtual void    saveToStream  (std::ofstream& ofs)              = 0;
    virtual void    loadFromStream(std::ifstream& ifs)              = 0;
    virtual void    clear() = 0;
    virtual QString getSuffix() const       = 0;
    virtual QString getShortInfo() const    = 0;
    //
    virtual void                init(const QString& pathToLoadedLibrary="")     = 0;
    virtual DscPluginInterface* createObject(const std::string& dscCode="") const  = 0;
    virtual QString             getCodeType()       const = 0;
    virtual QStringList         getCodeSubTypes()   const = 0;
//    virtual std::string         toString()          const = 0;
    //
    virtual ~DscPluginInterface() {}
};

Q_DECLARE_INTERFACE(DscPluginInterface, "by.basnet.uiip.lab225.DscPluginInterface")

static bool loadBaseConfig(const QString pathToLoadedLibrary, QString& baseCode, QStringList& baseSubCodes) {
    bool ret    = false;
    baseSubCodes.clear();
    if(!pathToLoadedLibrary.isEmpty()) {
        QFileInfo fileInfo(pathToLoadedLibrary);
        if(fileInfo.exists()) {
            QString path    = fileInfo.absolutePath();
            QString name    = fileInfo.completeBaseName();
            QString fileCfg = QDir(path).absoluteFilePath(QString("%1.cfg").arg(name));
            QFileInfo infoCfg(fileCfg);
            if(infoCfg.exists()) {
                QSettings cfg(infoCfg.absoluteFilePath(), QSettings::IniFormat);
                cfg.beginGroup(DEF_CFG_GROUP_DSCCODE_STR);
                baseCode    = cfg.value(DEF_CFG_KEYS_DSCCODE_STR).toString();
                if(!baseCode.isEmpty()) {
                    baseSubCodes    = cfg.value(DEF_CFG_KEYS_DSCSUBCODES_STR).toStringList();
                    if(baseSubCodes.size()>0) {
                        ret = true;
                    }
                }
                cfg.endGroup();
            } else {
                qDebug() << "cfg-file [" << infoCfg.absoluteFilePath() << "] not found";
            }
        }
    }
    return ret;
}


#endif // DSCINTERFACE_H
