#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPluginLoader>
#include <QListWidgetItem>

#include <math.h>
#include "model2.h"

#ifdef _WIN32
    double log2( double n )   {
        return log( n ) / log( 2.0 );
    }
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
//    isProcessDscState           = false;
    isNeedToRefreshFrameDscList = false;
    isAtLeastOneDscLoaded       = false;
    timer                       = new QTimer(this);
    currCamerIndex              = -1;
    checkCameraList();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotCaptureFrame()));
    currentDir  = QDir::currentPath();
    //
    loadDescriptorsToApplication();
    ui->listView->setModel(new Model(&listFramePixmaps, &listFrameIndex, this));
//    clearDscData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////
QImage MainWindow::matToQImage(const cv::Mat& mat) {
    if(mat.type()==CV_8UC1) {
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        const uchar *qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    } else if(mat.type()==CV_8UC3) {
        const uchar *qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    } else {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

///////////////////////////////////////////
void MainWindow::checkCameraList() {
    ui->comboBoxCameraList->clear();
    bool isNeedRestart  = false;
    mtxCaptureLocker.lock();
    if(capture.isOpened()) {
        capture.release();
        currCamerIndex  = -1;
        isNeedRestart   = true;
    }
    mtxCaptureLocker.unlock();
    if(timer->isActive()) {
        timer->stop();
    }
    //
    cv::VideoCapture tmpCap;
    cameraListIdx.clear();
    cameraListNames.clear();
    for(int ii=0; ii<10; ii++) {
        tmpCap  = cv::VideoCapture(ii);
        if(tmpCap.isOpened()) {
            cameraListIdx.push_back(ii);
            cameraListNames.push_back(QString("camera #%1").arg(ii));
            tmpCap.release();
        }
    }
    ui->comboBoxCameraList->addItems(cameraListNames);
    if(isNeedRestart) {
        on_pushButtonCameraStart_clicked();
    }
    //
    ui->labelMessageErrors->clear();
    if(cameraListIdx.size()<1) {
        ui->labelMessageErrors->setText(tr("Camera not found"));
    } else {
        ui->labelMessageErrors->setText(QString("found %1 webcams").arg(cameraListIdx.size()));
    }
}

void MainWindow::on_pushButtonCameraRefresh_clicked()
{
    checkCameraList();
}

int MainWindow::getCurrentCameraIdx()
{
    if(cameraListIdx.size()>0) {
        return ui->comboBoxCameraList->currentIndex();
    } else {
        return -1;
    }
}

void MainWindow::slotCaptureFrame()
{
    int                 sizeDB          = ui->spinBox_DBSize->value();
    DscPluginInterface* tmpDscBuilder   = NULL;
    QString             dscCodeSubType;
    if(isAtLeastOneDscLoaded) {
        tmpDscBuilder   = getCurrentDscBuilder();
        dscCodeSubType  = getCurrentDscCode();
    }
    timer->blockSignals(true); //FIXME: bad solution???
    //
    mtxCaptureLocker.lock();
    capture >> frame;
    mtxCaptureLocker.unlock();
    if(frame.data) {
        frameImage  = matToQImage(frame);
        int tw  = ui->labelCamera->width();
        int th  = ui->labelCamera->height();
        ui->labelCamera->setPixmap(QPixmap::fromImage(frameImage).scaled(tw,th, Qt::KeepAspectRatio));
        //
        if(isNeedToRefreshFrameDscList && isAtLeastOneDscLoaded) {
            // FIXME: force updote??? this is thread non-safe!?
            tmpDscBuilder   = getCurrentDscBuilder();
            dscCodeSubType  = getCurrentDscCode();
            setEnabled(false);
            ui->labelMessageErrors->setText(tr("update DSC-Index"));
            ui->progressBar->setValue(0);
            ui->progressBar->setMaximum(listFrameDsc.size());
            QApplication::processEvents();
            for(int ii=0; ii<listFrameDsc.size(); ii++) {
                DscPluginInterface* dscOld = listFrameDsc[ii];
                dscOld->clear();
                delete dscOld;
                DscPluginInterface* dscNew  = tmpDscBuilder->createObject(dscCodeSubType.toStdString());
                dscNew->buildDscFromMat(listFrameMatForDsc.at(ii));
                listFrameDsc[ii]    = dscNew;
                ui->progressBar->setValue(ii);
                QApplication::processEvents();
            }
            ui->progressBar->setValue(0);
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(1);
            ui->labelMessageErrors->setText(tr("..."));
            setEnabled(true);
            QApplication::processEvents();
            isNeedToRefreshFrameDscList = false;
        }
        //
        int nc  = frame.cols;
        int nr  = frame.rows;
        if(nc>nr) {
            cv::resize(frame, frame, cv::Size(DEF_MAX_FRAME_SIZ, (DEF_MAX_FRAME_SIZ*nr)/nc));
        } else {
            cv::resize(frame, frame, cv::Size((DEF_MAX_FRAME_SIZ*nc)/nr, DEF_MAX_FRAME_SIZ));
        }
        if(ui->pushButton_RecordFrames->isChecked()) {
            ui->label_DBInfo->setText(QString("%1").arg(listFramePixmaps.size()));
            listFrameIndex.push_front(frameCounter);
            listFramePixmaps.push_front(QPixmap::fromImage(matToQImage(frame)));
            if(isAtLeastOneDscLoaded) {
                DscPluginInterface* newDsc  = tmpDscBuilder->createObject(dscCodeSubType.toStdString());
                newDsc->buildDscFromMat(frame);
                listFrameDsc.push_front(newDsc);
            }
            listFrameMatForDsc.push_front(frame.clone()); //TODO: why clone()??
            //
            if(listFramePixmaps.size()<=sizeDB) {
                dscSortIndex.push_back(SortedIndex());
            } else {
                listFramePixmaps.removeLast();
                listFrameIndex.removeLast();
                listFrameMatForDsc.removeLast();
                if(isAtLeastOneDscLoaded) {
                    qDebug() << "remove dsc";
                    delete listFrameDsc.takeLast();
                }
            }
//            qDebug() << "sizes = " << listFrameDsc.size() << "/" << dscSortIndex.size();
            //
            ((Model*)ui->listView->model())->refreshListOfImages();
        }
        if(ui->pushButton_Search->isChecked()) {
            if(isAtLeastOneDscLoaded) {
                DscPluginInterface* currentDsc  = tmpDscBuilder->createObject(dscCodeSubType.toStdString());
                currentDsc->buildDscFromMat(frame);
                for(int ii=0; ii<dscSortIndex.size(); ii++) {
                    dscSortIndex[ii].idx    = ii;
                    dscSortIndex[ii].val    = currentDsc->calcDscDistance(listFrameDsc.at(ii));
                }
                qSort(dscSortIndex);
                ui->listWidget->clear();
                int sizRequest = ui->spinBox_SizeSearchRequest->value();
                for(int ii=0; ii<sizRequest; ii++) {
                    const SortedIndex& si   = dscSortIndex.at(ii);
                    ui->listWidget->addItem(
                                new QListWidgetItem(
                                        QIcon(listFramePixmaps.at(si.idx)),
                                        QString("dst: %1").arg(si.val),
                                        ui->listWidget));
                }
            }
        }
    } else {
        qDebug() << "Bad frame #" << frameCounter;
    }
    frameCounter++;
    ui->labelFrameCounter->setText(QString::number(frameCounter));
    //
    timer->blockSignals(false);
}


//////////////////////////////////////////////////
void MainWindow::clearDscData() {
    //FIXME: this is kostil!
    bool isNeedRefreshModel = listFramePixmaps.size()>0?true:false;
    while (!listFrameDsc.isEmpty()) {
        delete listFrameDsc.takeFirst();
    }
    listFrameDsc.clear();
    listFrameIndex.clear();
    listFrameMatForDsc.clear();
    listFramePixmaps.clear();
    dscSortIndex.clear();
    if(isNeedRefreshModel) {
        ((Model*)ui->listView->model())->refreshListOfImages();
    }
    ui->label_DBInfo->setText("...");
}

//////////////////////////////////////////////////
void MainWindow::on_pushButtonCameraStart_clicked()
{
    int camIdx  = getCurrentCameraIdx();
    if(currCamerIndex!=camIdx || currCamerIndex<0) {
        if(capture.isOpened()) {
            capture.release();
        }
        if(camIdx>-1) {
            capture = cv::VideoCapture(camIdx);
            if(!capture.isOpened()) {
                QMessageBox::critical(this, "Error", QString("Can't initialize camera #%1").arg(camIdx));
            } else {
                frameCounter    = 0;
                timer->start(DEF_TIMER_DELAY);
                ui->comboBoxCameraList->setEnabled(false);
            }
        }
    } else {
        if(camIdx<0) {
            ui->labelMessageErrors->setText("bad camera idx");
        } else {
            ui->labelMessageErrors->setText("This camera already selected, skip...");
        }
    }
}

void MainWindow::on_pushButtonCameraStop_clicked()
{
//    isProcessDscState   = false;
    timer->stop();
    mtxCaptureLocker.lock();
    if(capture.isOpened()) {
        capture.release();
    }
    mtxCaptureLocker.unlock();
    ui->labelCamera->clear();
    ui->comboBoxCameraList->setEnabled(true);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    qDebug() << checked;
}

void MainWindow::on_checkBoxVideoScaled_clicked(bool checked)
{
    ui->labelCamera->setScaledContents(checked);
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}

void MainWindow::on_pushButtonCameraImages_clicked()
{
    ui->listWidget->clear();
    ui->pushButton_Search->setChecked(false);
    clearDscData();
}

void MainWindow::loadDescriptorsToApplication()
{
    isAtLeastOneDscLoaded   = false;
    if(dscPlugins.size()>0) {
        for(int ii=0; ii<dscPlugins.size(); ii++) {
            DscPluginInterface* tmp = dscPlugins.at(ii);
            delete tmp;
            tmp = NULL;
        }
        dscPlugins.clear();
    }
    QStringList dscPliginNames;
    QDir dir(QDir(QApplication::applicationDirPath()).absoluteFilePath(DEF_PLUGIN_DIR));
    foreach (QString strFileName, dir.entryList(QDir::Files)) {
        QString pluginFileName  = dir.absoluteFilePath(strFileName);
        QPluginLoader loader(pluginFileName);
        QObject* tmpObj = qobject_cast<QObject*>(loader.instance());
		qDebug() << "[" << pluginFileName << "] obj={"  << tmpObj << "}";
        if(tmpObj!=NULL) {
            DscPluginInterface* tmpIFace = qobject_cast<DscPluginInterface*>(tmpObj);
            if(tmpIFace!=NULL) {
                tmpIFace->init(pluginFileName);
                dscPlugins.append(tmpIFace);
                dscPliginNames.append(tmpIFace->getCodeType());
            }
        }
    }
    if(dscPlugins.size()<1) {
        QMessageBox::information(this, tr("WARNING!"), tr("DSC-plugins not found!"));
    } else {
        isAtLeastOneDscLoaded   = true;
    }
    ui->comboBoxDscTypes->addItems(dscPliginNames);
    refreshCodeSubTypesCombobox();
    //
}

void MainWindow::refreshCodeSubTypesCombobox()
{
    if(dscPlugins.size()>0) {
        int idx = ui->comboBoxDscTypes->currentIndex();
        if(idx<dscPlugins.size()) {
            ui->comboBoxDscSubtypes->clear();
            ui->comboBoxDscSubtypes->addItems(dscPlugins.at(idx)->getCodeSubTypes());
        }
    }
}

DscPluginInterface *MainWindow::getCurrentDscBuilder() const
{
    int numDsc  = dscPlugins.size();
    int indx    = ui->comboBoxDscTypes->currentIndex();
    if(numDsc>0 && (indx<numDsc)) {
        return dscPlugins.at(indx);
    } else {
        return NULL;
    }
}

QString MainWindow::getCurrentDscCode() const
{
    return ui->comboBoxDscSubtypes->currentText();
}

void MainWindow::on_comboBoxDscSubtypes_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    if(timer->isActive()) {
        isNeedToRefreshFrameDscList = true;
    } else {
        clearDscData();
    }
}

void MainWindow::on_comboBoxDscTypes_currentIndexChanged(int index)
{
//    Q_UNUSED(index)
    if(isAtLeastOneDscLoaded) {
        ui->comboBoxDscSubtypes->clear();
        ui->comboBoxDscSubtypes->addItems(dscPlugins.at(index)->getCodeSubTypes());
    }
    if(timer->isActive()) {
        isNeedToRefreshFrameDscList = true;
    } else {
        clearDscData();
    }
}

void MainWindow::on_pushButton_Search_toggled(bool checked)
{
    if(checked && !isAtLeastOneDscLoaded) {
        QMessageBox::information(this, tr("Warning"), tr("DSC-plugin not found, Image search not working!"));
    }
}
