//#include <QCoreApplication>
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include <QDebug>

#include "dscplugin_meanch.h"

using namespace std;

int main(int argc, char *argv[])
{
    cv::Mat img = cv::imread("/home/ar/img/lena.png", CV_LOAD_IMAGE_COLOR);
    DscPluginMeanCh dscBuilder;
    dscBuilder.init();
    DscPluginInterface* dsc = dscBuilder.createObject(dscBuilder.getCodeSubTypes().at(0).toStdString());
    dsc->buildDscFromMat(img);
    qDebug() << "dsc1: " << dsc->getShortInfo();

    string fileTest    = "test_dsc_meanch.bin";
    ofstream ofs(fileTest.c_str(), std::ofstream::binary);
    dsc->saveToStream(ofs);
    ofs.close();

    DscPluginInterface* dsc2    = dscBuilder.createObject("");
    ifstream ifs(fileTest.c_str(), std::ifstream::binary);
    dsc2->loadFromStream(ifs);
    ifs.close();
    qDebug() << "dsc2: " << dsc->getShortInfo();

    delete dsc2;
    delete dsc;
/*
    QCoreApplication a(argc, argv);
    return a.exec();
*/
}
