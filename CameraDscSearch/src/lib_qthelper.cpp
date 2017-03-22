#include "lib_qthelper.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

//////////////////////////////////////////////////////
/*
from: http://code.google.com/p/qt-opencv-multithreaded/
*/
QImage mat2Image(const cv::Mat& img, bool isNormalized) {
    cv::Mat tmp;
    if(isNormalized) {
        CV_Assert(img.channels()==1);
        cv::normalize(img, tmp, 0,255, CV_MINMAX, CV_8UC1);
    } else {
        img.copyTo(tmp);
    }
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(tmp.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)tmp.data;
        // Create QImage with same dimensions as input Mat
        QImage ret(qImageBuffer, tmp.cols, tmp.rows, tmp.step1(), QImage::Format_Indexed8);
        ret.setColorTable(colorTable);
        return ret.copy();
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(img.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)tmp.data;
        // Create QImage with same dimensions as input Mat
        QImage ret(qImageBuffer, tmp.cols, tmp.rows, tmp.step1(), QImage::Format_RGB888);
        return ret.rgbSwapped().copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

QPixmap mat2Pixmap(const cv::Mat& img, bool isNormalized) {
    QPixmap ret;
    ret.convertFromImage(mat2Image(img, isNormalized));
    return ret;
}

//////////////////////////////////////////////////////
void showImageDialog(const QPixmap& pxm) {
    QDialog dlg;
    QVBoxLayout l;
    QLabel lb;
    lb.setPixmap(pxm);
    l.addWidget(&lb);
    dlg.setLayout(&l);
    //
    dlg.exec();
}

void showImageDialog(const QImage& img) {
    QPixmap pxm;
    pxm.fromImage(img);
    showImageDialog(pxm);
}

void showImageDialog(const cv::Mat& m) {
    QPixmap pxm;
    if(m.type()==CV_8UC1 || m.type()==CV_8UC3) {
        pxm = mat2Pixmap(m, false);
    } else {
        pxm = mat2Pixmap(m, true);
    }
    showImageDialog(pxm);
}


