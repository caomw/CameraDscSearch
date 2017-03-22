#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
/*
#include <lib_descriptor2s.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
using namespace dscv2;
*/

#include "lib_utils.h"
#include <QVector>
#include <QList>

template <typename T>
void printQList(const QList<T>& data) {
    foreach (int q, data) {
        qDebug() << q;
    }
    qDebug() << "-";
}

int main(int argc, char *argv[])
{
/*
    cv::Mat img = cv::imread("/home/ar/img/lena.png", CV_LOAD_IMAGE_GRAYSCALE);
    recti roi1(2,2,     100, 100);
    recti roi2(200,200, 100, 100);
    SDescriptorI dsc1, dsc2;
    buildDescriptorFromMat(img, roi1, DSC_TYPE_1P, 2, dsc1);
    buildDescriptorFromMat(img, roi2, DSC_TYPE_1P, 2, dsc2);
    cout << dsc1 << endl;
    cout << dsc2 << endl;
    dsc1.addDsc(dsc2);
    cout << dsc1 << endl;
    cout << dsc2 << endl;
*/

    QList<int> data;
    data.push_front(1);
    data.push_front(2);
    data.push_front(3);
    data.push_front(4);
    data[1] = 20;
    data[2] = 30;
    /*
    QList<int> data;
    for(int ii=0; ii<10; ii++) {
        data.push_back(qrand()%10);
    }
    printQList(data);
    qSort(data);
    printQList(data);
    data.takeFirst();
    data.takeFirst();
    printQList(data);
    */


/*
#include <iostream>
    for(int ii=0; ii<1; ii++) {
        for(int jj=ii+1; jj<1; jj++) {
            std::cout << ii << "," << jj << std::endl;
        }
    }
*/

/*
    QString fileName    = "/home/ar/img/lena.png";
    qDebug() << "path" << QFileInfo(fileName).absoluteDir().absolutePath();
*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
