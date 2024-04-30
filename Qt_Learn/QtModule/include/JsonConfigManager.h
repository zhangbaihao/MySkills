#ifndef JSONCONFIGMANAGER_HPP
#define JSONCONFIGMANAGER_HPP

// 头文件的内容
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>

class JsonConfigManager
{
public:
    JsonConfigManager(const QString &filePath)
        : m_filePath(filePath)
    {
        loadConfig();
    }

    QVariantMap getCommandParameters(const QString &command) const
    {
        if (m_configObject.contains("commands"))
        {
            QJsonArray commandsArray = m_configObject["commands"].toArray();
            for (const QJsonValue &commandValue : commandsArray)
            {
                if (commandValue.isObject())
                {
                    QJsonObject commandObj = commandValue.toObject();
                    QString cmd = commandObj["cmd"].toString();
                    if (cmd == command)
                    {
                        QVariantMap parameters;
                        parameters["id"] = commandObj["id"].toInt();
                        parameters["cmd"] = cmd;
                        parameters["rows"] = commandObj["rows"].toInt();
                        parameters["cols"] = commandObj["cols"].toInt();
                        parameters["channel"] = commandObj["channel"].toInt();
                        parameters["dataSize"] = commandObj["dataSize"].toInt();
                        return parameters;
                    }
                }
            }
        }
        return QVariantMap();
    }
    QVariantMap getInitCommandLists(const QString &deviceModel) const
    {
        if (m_configObject.contains("initCommandsList"))
        {
            QJsonArray commandsArray = m_configObject["initCommandsList"].toArray();
            for (const QJsonValue &commandValue : commandsArray)
            {
                if (commandValue.isObject())
                {
                    QJsonObject commandObj = commandValue.toObject();
                    QString m_deviceModel = commandObj["deviceModel"].toString();
                    if (m_deviceModel == deviceModel)
                    {

                        QVariantMap parameters;
                        parameters["deviceModel"] = m_deviceModel;

                        QJsonArray cmdArray = commandObj["cmd"].toArray();
                        QStringList cmdList;
                        for (const QJsonValue &cmdValue : cmdArray)
                        {
                            if (cmdValue.isString())
                            {
                                cmdList.append(cmdValue.toString());
                            }
                        }
                        parameters["cmd"] = cmdList;
                        return parameters;
                    }
                }
            }
        }
        return QVariantMap();
    }

private:
    void loadConfig()
    {
        QFile file(m_filePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Failed to open the JSON file.";
            return;
        }

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (jsonDoc.isNull())
        {
            qDebug() << "Failed to parse the JSON document.";
            return;
        }

        m_configObject = jsonDoc.object();
    }

private:
    QString m_filePath;
    QJsonObject m_configObject;
};
#endif // JSONCONFIGMANAGER_HPP