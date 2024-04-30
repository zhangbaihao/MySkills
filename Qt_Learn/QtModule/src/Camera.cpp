#include "Camera.h"

#include <QList>
#include <QMutexLocker>
#include <QByteArray>
#include <QCameraDevice>
#include <QMediaDevices>
#include <opencv2/opencv.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::start()
{
}

bool Camera::findCamera(QString cameraName)
{
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : cameras)
    {
        if (cameraDevice.description() == cameraName)
        {
            m_camera.reset(new QCamera(cameraDevice));
            return true;
        }
    }
    return false;
}

void Camera::configureCamera(QVideoFrameFormat::PixelFormat pixelFormat, QSize size)
{
    if (!m_camera)
        return;

    QCameraDevice m_cameraDevice = m_camera->cameraDevice();
    QList<QCameraFormat> formats = m_cameraDevice.videoFormats();

    for (const QCameraFormat &cameraFormat : formats)
    {
        qDebug() << "Format: " << cameraFormat.pixelFormat() << ", resolution: " << cameraFormat.resolution();

        if (cameraFormat.pixelFormat() == pixelFormat && cameraFormat.resolution() == size)
        {
            m_camera->setCameraFormat(cameraFormat);
            break;
        }
    }
}

bool Camera::initialize()
{
    if (!m_camera)
        return false;
    m_captureSession.setCamera(m_camera.data());

    // if (!m_imageCapture)
    // {
    //     m_imageCapture.reset(new QImageCapture);
    //     m_captureSession.setImageCapture(m_imageCapture.get());
    //     connect(m_imageCapture.get(), &QImageCapture::imageCaptured, this, &Camera::processCapturedImage);
    //     //connect(m_imageCapture.get(), &QImageCapture::readyForCaptureChanged, this,&Camera::readyForCapture);
    //     // connect(m_imageCapture.get(), &QImageCapture::imageSaved, this, &Camera::imageSaved);
    //     // connect(m_imageCapture.get(), &QImageCapture::errorOccurred, this,&Camera::displayCaptureError);
    // }

    if (!m_videoSink)
    {
        m_videoSink.reset(new QVideoSink);
        m_captureSession.setVideoSink(m_videoSink.data());
        connect(m_videoSink.data(), &QVideoSink::videoFrameChanged, this, &Camera::processVideoFrame);
    }
    m_camera->start();
    return true;
}

void Camera::processCapturedImage(int requestId, const QImage &img)
{
    Q_UNUSED(requestId);
    // QImage scaledImage =img.scaled(ui->viewfinder->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void Camera::processVideoFrame(const QVideoFrame &frame)
{
    QVideoFrame cloneFrame(frame);
    if (cloneFrame.isValid())
    {
        cloneFrame.map(QVideoFrame::ReadOnly);
        // 计算当前帧数据的大小

        QByteArray data;
        if (cloneFrame.pixelFormat() == QVideoFrameFormat::PixelFormat::Format_NV12)
        {   
            int planeCount = cloneFrame.planeCount();
            int targetSize = cloneFrame.width() * cloneFrame.height();
            for (int i = 0; i < 1; i++)
            {
                const int frameSize = cloneFrame.mappedBytes(i);//
                qDebug() << "i:" << i << "frameSize: " << frameSize;
                if(frameSize == targetSize)
                    data = QByteArray(reinterpret_cast<const char *>(cloneFrame.bits(i)), frameSize);
            }
            
        }
        else if (cloneFrame.pixelFormat() == QVideoFrameFormat::PixelFormat::Format_Jpeg)
        {
            // 使用OPENCV解码 MJPEG 成对应RGB CV::MAT
            const int frameSize = cloneFrame.mappedBytes(0);
            std::vector<uint8_t> frame(reinterpret_cast<const uint8_t *>(cloneFrame.bits(0)),
                                       reinterpret_cast<const uint8_t *>(cloneFrame.bits(0)) + frameSize);
            cv::Mat decodedImage = cv::imdecode(frame, cv::IMREAD_COLOR);
            if (decodedImage.empty())
            {
                qDebug() << "Failed to decode MJPEG frame";
            }
            else
            {
                int dataSize = decodedImage.rows * decodedImage.cols * decodedImage.channels();
                data = QByteArray(reinterpret_cast<const char *>(decodedImage.data), dataSize);
                // cv::imshow("rgb1", decodedImage);
                // cv::waitKey(1);
            }
            // 释放图像内存
            decodedImage.release();
        }
        cloneFrame.unmap();

        m_frameQueueMutex.lock();
        if (m_frameQueue.empty())
        {
            m_frameQueue.push_back(data);
            m_frameAvailableCondition.wakeAll();
        }
        m_frameQueueMutex.unlock();
    }
}

QByteArray Camera::getVideoFrame()
{
    m_frameQueueMutex.lock();
    while (m_frameQueue.empty())
    {
        // 等待条件变量的唤醒信号
        m_frameAvailableCondition.wait(&m_frameQueueMutex);
    }
    QByteArray data = m_frameQueue.takeFirst();
    m_frameQueueMutex.unlock();
    return data;
}