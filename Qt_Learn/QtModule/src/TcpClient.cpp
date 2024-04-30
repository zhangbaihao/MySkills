#include "TcpClient.h"
// JSON 协议
#pragma pack(1)
typedef struct JsonProtocol
{
    uint16_t sync;               // (2 Bytes) 帧头    (0xA5A5)
    uint16_t type;               // (2 Bytes) 帧类型  0x00(CMD)、0x01(FRAME)、0x02(DATA/BINARY)、0x03(STATUS) 0x04(OldCmdType) 0x05(ComCmd)
    uint8_t timestamp[8];        // (8 Bytes) 时间戳  0x20210225143080  (2021/02/25 14:30.80) (80表示800ms)
    uint8_t extended[128];       // (128 Bytes) 拓展信息 拓展信息 8->128 （数据帧长宽）-> (数据帧 温度 积分时间 长宽）
    uint32_t payload_size;       // (4 Bytes) Payload帧长
    uint8_t payload_checksum[0]; // (TDB) Payload帧内容, 最后4字节为32bit和校验(可变长数组, 数组长 = payload_size + 4)
} JsonPacket;
#pragma pack()

// 省略拓展单元JSON类型
#pragma pack(1)
typedef struct FrameCom
{
    uint16_t sync;               // (2 Bytes) 帧头    (0xA5A5)
    uint16_t type;               // (2 Bytes) 帧类型  0x00(CMD)、0x01(FRAME)、0x02(DATA/BINARY)、0x03(STATUS) 0x04(OldCmdType) 0x05(ComCmd)
    uint8_t timestamp[8];        // (8 Bytes) 时间戳  0x20210225143080  (2021/02/25 14:30.80) (80表示800ms)
    uint32_t payload_size;       // (4 Bytes) Payload帧长
    uint8_t payload_checksum[0];  // (TDB) Payload帧内容, 最后4字节为32bit和校验(可变长数组, 数组长 = payload_size + 4)
} JsonPacketCom;
#pragma pack()

#pragma pack(1)
struct ExtendedInfo
{
    int32_t integration_time = 0;  // 积分时间
    int32_t gain = 0;              // 增益
    int32_t leddriver_temp_ul = 0; // 灯板温度 0.1°
    int32_t sensor_temp_ul = 0;    // 左上角温度
    int32_t sensor_temp_ur = 0;    // 右上角 温度
    int32_t sensor_temp_bl = 0;    // 左下角 温度
    int32_t sensor_temp_br = 0;    // 右下角温度
    int32_t resoulution_width = 0; // 分辨率 宽
    int32_t resoulution_high = 0;  // 分辨率 高
    uint8_t reserved[92];          // 保留
};
#pragma pack()
int makeSum4Byte(const char *com, int len)
{
    int jiao = 0;
    // 计算校验值
    for (int i = 0; i < len / 4; i++)
    {
        jiao += *((int *)com + i);
    }

    int remainstart = len - (len % 4);
    int remain;
    for (int i = 0; i < len % 4; i++)
    {
        remain |= (*(char *)(com + remainstart + i)) << (8 * i);
    }

    return jiao + remain;
}
TcpClient::TcpClient(QObject *parent) : QTcpSocket(parent)
{
    serverAddress = "";
    serverPort = 0;
}
TcpClient::~TcpClient()
{
    if (state() == QAbstractSocket::ConnectedState)
        disconnectFromHost();
}

void TcpClient::setIpAndPort(const QString &ip, const int port)
{
    this->serverAddress = ip;
    this->serverPort = port;
}

QByteArray TcpClient::jsonProtocolPackaging(const QByteArray &cmd)
{
    int cmdSize = cmd.size();
    int totalSize = sizeof(JsonProtocol);
    totalSize += cmdSize;

    // USB 发送协议需要4字节对齐
    //  int addSize = totalSize % 4;
    //  if (addSize != 0)
    //  {
    //      addSize = 4 - addSize;
    //      totalSize += addSize;
    //  }

    QByteArray jsonPacket = QByteArray(totalSize, 0).fill(0x00);
    QDataStream stream(&jsonPacket, QIODevice::WriteOnly);
    // 设置字节顺序，根据实际情况调整，可能需要与接收端保持一致
    stream.setByteOrder(QDataStream::LittleEndian);

    // 写入 JsonPacket 的字段
    stream << quint16(0xA5A5); // sync
    stream << quint16(0x0000); // type

    // 写入 时间戳
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QByteArray timestampData = currentDateTime.toString("yyyyMMddhhmmss").toLatin1();
    // 如果需要使用十六进制格式填充时间戳数据，请使用下面的代码
    // QByteArray timestampData = currentDateTime.toString("yyyyMMddhhmmss").toLatin1().toHex();

    // 如果 timestampData 的长度不足8个字节，可以根据需要进行填充
    if (timestampData.size() < 8)
    {
        timestampData = timestampData.rightJustified(8, '0');
    }
    stream.writeRawData(timestampData.data(), 8); // timestamp

    // 写入 扩展信息
    QByteArray extendedData = QByteArray(128, 0).fill(0x00);

    // 写入 Payload 帧长
    stream << quint32(cmdSize);

    // 写入 发送数据
    stream.writeRawData(reinterpret_cast<const char *>(cmd.data()), cmdSize); // payload_checksum

    // 计算校验和并写入
    int jsonChecksumValue = makeSum4Byte(jsonPacket.data(), sizeof(JsonPacket) + cmdSize);
    stream << quint32(jsonChecksumValue);

    return jsonPacket;
}

QByteArray TcpClient::jsonProtocolUnpackaging(const QByteArray &data)
{
    JsonPacket *head = (JsonPacket *)data.data();
    uint16_t  sync = head->sync;
    uint16_t  frameType = head->type;
    uint32_t  payloadSize = head->payload_size;
    const uint8_t *payloadChecksum = head->payload_checksum;
    ExtendedInfo *extInfo = reinterpret_cast<ExtendedInfo *>(head->extended);
    QByteArray rawData(reinterpret_cast<const char *>(payloadChecksum), payloadSize);
       // 提取校验和
    uint32_t jsonChecksumValue = *reinterpret_cast<const uint32_t *>(&payloadChecksum[payloadSize]);
    return rawData;
}
QByteArray TcpClient::sendDataAndGetResponse(const QByteArray &data)
{
    if (serverAddress == "" || serverPort == 0)
        return QByteArray();

    if (state() == QAbstractSocket::ConnectedState)
        disconnectFromHost();

    setProxy(QNetworkProxy::NoProxy);
    connectToHost(serverAddress, serverPort);

    bool useJsonProtocol = false;
    QByteArray receivedData;
    if (waitForConnected(2000))
    {
        if (isJsonValid(data))
        {
            QByteArray jsonData = jsonProtocolPackaging(data);
            qDebug() << "jsonData: " << jsonData << "size: " << jsonData.size();
            write(jsonData);
            useJsonProtocol = true;
        }
        else
        {
            write(data);
        }

        if (waitForBytesWritten(1000))
        {

            while (waitForReadyRead(2000) && bytesAvailable() > 0)
            {
                QByteArray temp = readAll();
                receivedData.append(temp);
            }
        }
        //TCP短连接
        disconnectFromHost();
    }
    else
    {
        qDebug() << "Failed to connect to server.";
        return QByteArray();
    }

    //使用了JSON协议则需要解析
    if (useJsonProtocol && receivedData.size() > sizeof(JsonPacket))
    {
        receivedData = jsonProtocolUnpackaging(receivedData);
    }

    return receivedData;
}