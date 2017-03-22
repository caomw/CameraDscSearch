#ifndef LIB_QTHELPER_H
#define LIB_QTHELPER_H

#include <QtGui>
#include <cv.h>
#include <highgui.h>

//////////////////////////////////////////////////////
QImage mat2Image(const cv::Mat& img, bool isNormalized=false);
QPixmap mat2Pixmap(const cv::Mat& img, bool isNormalized=false);

//////////////////////////////////////////////////////
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

//////////////////////////////////////////////////////
void showImageDialog(const QPixmap& pxm);
void showImageDialog(const QImage& img);
void showImageDialog(const cv::Mat& m);


#endif // LIB_QTHELPER_H
