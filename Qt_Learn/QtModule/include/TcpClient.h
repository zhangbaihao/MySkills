#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>

class TcpClient : public QTcpSocket
{
    Q_OBJECT

public:
    TcpClient(QObject *parent = nullptr);
    ~TcpClient() override;
    void setIpAndPort(const QString &ip, const int port);
    QByteArray sendDataAndGetResponse(const QByteArray &data);

private:
    bool isJsonValid(const QByteArray &jsonData)
    {
        QJsonParseError error;
        QJsonDocument::fromJson(jsonData, &error);
        return (error.error == QJsonParseError::NoError);
    }
    bool isJsonValid(const QString &jsonData)
    {
        return isJsonValid(jsonData.toUtf8());
    }
    QByteArray jsonProtocolPackaging(const QByteArray &cmd);
    QByteArray jsonProtocolUnpackaging(const QByteArray &data);
    int serverPort;
    QString serverAddress;

};