#ifndef CAMERAGET_H
#define CAMERAGET_H

#include <QDialog>
#include <QTimer>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include "face.h"
#include "checklist.h"

namespace Ui {
class CameraGet;
}

class CameraGet : public QDialog
{
    Q_OBJECT

public:
    explicit CameraGet(QWidget *parent = 0);
    ~CameraGet();

public slots:
    // Get the information and show it on the 'hint'
//    void inform(QString);

    // Start with arguments
    void start(int, QString);

signals:
    // When 'Back' clicked
    void back(int);

    // When face detected, emit with face image
    void getFace(cv::Mat);

    // When face matchs, emit with number
    void confirmed(QString);

    // When face matching failed, emit with number
    void refused(QString);

    // When 1 frame processed
    void camera(int);

private slots:
    void on_back_clicked();

    void on_cancel_clicked();

    // Show the feed back of camera
    void getCamera();

    // process the match
    void match();

private:
    Ui::CameraGet *ui;

    // Holds number got slot 'start (int, QString)'
    QString number;

    // Help to get & show the image
    QTimer *timer;

    // Camera Buffer
    cv::Mat cameraBuffer;

    // Color change Buffer
    cv::Mat colorBuffer;

    // Display Buffer
    QImage displayBuffer;

    // Face recognization related algorithms
    Face face;

    // Database checking related algorithm
    CheckList check;

    // Face image
    cv::Mat faceBuffer;

    // Camera cpture stream object
    cv::VideoCapture cap;




};

#endif // CAMERAGET_H