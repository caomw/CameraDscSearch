#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QThread>
#include <QMutex>

#include <QPixmap>
#include <QImage>
#include <QColor>

#include <QList>
#include <QVector>
#include <QList>
#include <QStringList>
#include <QMap>

#include <cv.h>
#include <highgui.h>

#include "lib_utils.h"
#include "dscplugininterface.h"


#include <iostream>
#include <vector>
#include <map>
#include <set>

//////////////////////////////////////////////
#define DEF_MAX_FRAME_SIZ       128
#define DEF_TIMER_DELAY         50
#define DEF_MAX_DB_FRASIZE      100

//////////////////////////////////////////////
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage matToQImage(const cv::Mat& mat);

public:
    static const bool   paramIsColored;
    static const int    paramNumberOfBin;

private:
    QString             currentDir;
    // camera:
    QTimer             *timer;
    cv::Mat             frame;
    cv::VideoCapture    capture;
    QImage              frameImage;
    int                 currCamerIndex;
    int                 frameCounter;
    QStringList         cameraListNames;
    QVector<int>        cameraListIdx;
    QMutex              mtxCaptureLocker;

    QStringList                 dscTypesNames;
    QVector<int>                dscTypesIdx;

//    bool                        isProcessDscState;
//    int                         currentClassIdxCounter;
    bool                            isNeedToRefreshFrameDscList;
    bool                            isAtLeastOneDscLoaded;
    QVector<DscPluginInterface*>    dscPlugins;
    QList<cv::Mat>                  listFrameMatForDsc;
    QList<int>                      listFrameIndex;
    QList<QPixmap>                  listFramePixmaps;
    QList<DscPluginInterface*>      listFrameDsc;
    QVector<SortedIndex>            dscSortIndex;

    void clearDscData();

protected:
    void checkCameraList();

private slots:
    int   getCurrentCameraIdx();

    void slotCaptureFrame();

    void on_pushButtonCameraRefresh_clicked();
    void on_pushButtonCameraStart_clicked();
    void on_pushButtonCameraStop_clicked();
    void on_checkBox_toggled(bool checked);
    void on_checkBoxVideoScaled_clicked(bool checked);
    void on_action_Quit_triggered();

    //TODO: delete methods
    // pass

    void on_pushButtonCameraImages_clicked();

    void on_comboBoxDscSubtypes_currentIndexChanged(int index);

    void on_comboBoxDscTypes_currentIndexChanged(int index);

    void on_pushButton_Search_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    void                loadDescriptorsToApplication();
    void                refreshCodeSubTypesCombobox();
    DscPluginInterface* getCurrentDscBuilder() const;
    QString             getCurrentDscCode() const;
};

#endif // MAINWINDOW_H
