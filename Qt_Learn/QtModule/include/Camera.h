#ifndef CAMERA_H
#define CAMERA_H

#include <QMutex>
#include <QQueue>
#include <QCamera>
#include <QObject>
#include <QVideoSink>
#include <QImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QWaitCondition>
#include <QMediaCaptureSession>
class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();
    ~Camera();
    void start();
    void stop();
    bool findCamera(QString cameraName);
    void configureCamera(QVideoFrameFormat::PixelFormat pixelFormat, QSize size);

    bool initialize();
    QByteArray getVideoFrame();

private:
    QScopedPointer<QCamera> m_camera;

    QMediaCaptureSession m_captureSession;
    QScopedPointer<QVideoSink> m_videoSink;
    QScopedPointer<QImageCapture> m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;
    
    QByteArray frameBuffer;
    QMutex m_frameQueueMutex;
    QQueue<QByteArray> m_frameQueue;
    QWaitCondition m_frameAvailableCondition; // 帧可用条件变量
private slots:
    void processCapturedImage(int requestId, const QImage &img);
    void processVideoFrame(const QVideoFrame &frame);
};
#endif // CAMERA_H