
#include <QApplication>

#include <opencv2/opencv.hpp>
#include "Camera.h"
#include "tcpClient.h"
#include "JsonConfigManager.h"
//测试TCP 发送命令
int main(int argc, char *argv[])
{
// 添加以下代码进行TCP资源的初始化
    QApplication a(argc, argv);
    TcpClient tcpClient;
    tcpClient.setIpAndPort("192.168.4.100", 50660);
    QByteArray requestData = "getCalibrate";
    //QByteArray requestData = "getCalibrate";
    QElapsedTimer timer;
    while (1)
    {
        timer.start();
        QByteArray recvData = tcpClient.sendDataAndGetResponse(requestData);
        qDebug() << "recvData：" << recvData;
        qDebug() << recvData.size() << " bytes received";
        // 输出耗时计算耗时（毫秒）
        qDebug()
            << "Elapsed time:" << timer.elapsed() << "ms";
    }
    QByteArray datax;
    datax.
    return a.exec();
}

void doProcessDepthAndAmp(QByteArray &data, cv::Mat &depth, cv::Mat &amp)
{
    uint16_t *depthSrc = reinterpret_cast<uint16_t *>(data.data());
    uint16_t *ampSrc = depthSrc + depth.cols * depth.rows;

    double maxAmp = 1000;
    for (int i = 0; i < amp.rows; i++)
    {
        for (int j = 0; j < amp.cols; j++)
        {
            uint16_t ampValue = ampSrc[i * amp.cols + j];
            if (ampValue > 20 && ampValue < maxAmp)
            {
                amp.at<cv::Vec3b>(i, j)[0] = amp.at<cv::Vec3b>(i, j)[1] = amp.at<cv::Vec3b>(i, j)[2] = ampValue * 255 / maxAmp;
            }
            else
            {
                // amp.at<cv::Vec3b>(i, j)[0] = amp.at<cv::Vec3b>(i, j)[1] = amp.at<cv::Vec3b>(i, j)[2] = 0;
            }
        }
    }
}
//测试NS15 UVC TOF和RGB 发送命令以及图像获取OPENCV显示
int main02(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpClient tcpClient;
    tcpClient.setIpAndPort("192.168.4.100", 50660);
    QByteArray requestData = "setAutoExposure 0";
    QByteArray recvData = tcpClient.sendDataAndGetResponse(requestData);
    qDebug() << recvData.size() << " bytes received";

    Camera rgbCamera;
    Camera tofCamera;
    bool flag = rgbCamera.findCamera("UVC Camera RGB");
    if (flag)
    {
        rgbCamera.configureCamera(QVideoFrameFormat::Format_Jpeg, QSize(1920, 1080));
        rgbCamera.initialize();
    }

    flag = tofCamera.findCamera("UVC Camera TOF");
    if (flag)
    {
        tofCamera.configureCamera(QVideoFrameFormat::Format_NV12, QSize(640, 480));
        tofCamera.initialize();
    }

    std::thread thread1([&]
                        {
                            while (1)
                            {
                                QByteArray rgbData = rgbCamera.getVideoFrame();
                                if(rgbData.size() == 1920*1080*3)
                                {
                                    cv::Mat rgb = cv::Mat::zeros(1080, 1920, CV_8UC3);
                                    rgb.data = reinterpret_cast<uchar *>(rgbData.data());
                                    cv::resize(rgb, rgb, cv::Size(640, 480));
                                    cv::imshow("rgb", rgb);
                                    cv::waitKey(2);
                                }

                                QByteArray tofData = tofCamera.getVideoFrame();
                                if(tofData.size() == 320*240*4)
                                {
                                    cv::Mat depth = cv::Mat::zeros(240, 320, CV_8UC3);
                                    cv::Mat amp = cv::Mat::zeros(240, 320, CV_8UC3);
                                    doProcessDepthAndAmp(tofData,depth,amp);
                                    cv::imshow("amp", amp);
                                    cv::waitKey(2);
                                }            
                                
                            } });
    thread1.detach();

    return a.exec();
}
//测试JSON 读取命令参数和对应类型设备的初始化命令列表
int main03(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建 JsonConfigManager 对象并传入配置文件路径
    JsonConfigManager configManager("./config.json");

    // 查询命令的参数
    QVariantMap commandParams = configManager.getCommandParameters("getDistanceAndAmplitudeSorted");

    // 检查是否找到了对应的命令
    if (!commandParams.isEmpty())
    {
        int id = commandParams["id"].toInt();
        QString cmd = commandParams["cmd"].toString();
        int rows = commandParams["rows"].toInt();
        int cols = commandParams["cols"].toInt();
        int channel = commandParams["channel"].toInt();
        int dataSize = commandParams["dataSize"].toInt();
        // 使用命令的参数进行后续操作
        qDebug() << "Command ID:" << id;
        qDebug() << "Command:" << cmd;
        qDebug() << "Rows:" << rows;
        qDebug() << "Cols:" << cols;
        qDebug() << "Channel:" << channel;
        qDebug() << "DataSize:" << dataSize;
    }
    else
    {
        qDebug() << "Command not found.";
    }

    QVariantMap initCommandLists = configManager.getInitCommandLists("C3202");

    // 检查是否找到了对应的命令
    if (!initCommandLists.isEmpty())
    {
        // 找到了对应的命令，可以访问相应的参数
        // 在这里访问和使用 commandLists 中的数据

        // 示例：获取设备型号
        QString deviceModel = initCommandLists["deviceModel"].toString();
        qDebug() << "Device Model: " << deviceModel;

        // 示例：获取命令列表
        QStringList commandList = initCommandLists["cmd"].toStringList();
        qDebug() << "Command List:";
        for (const QString &command : commandList)
        {
            qDebug() << command;
        }
    }
    else
    {
        qDebug() << "initCommandLists not found.";
    }

    return a.exec();
}