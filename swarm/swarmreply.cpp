#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "swarmreply.h"


namespace swarm
{

SwarmReply::SwarmReply(const std::string& relpyMsg): rawRelpyMsg_(relpyMsg)
{
    //getMessagePairs();
}

bool SwarmReply::getMessagePairs(std::map<std::string, std::string>& jsonMap)
{
    QJsonParseError jsonError;
    QByteArray rawMsgAssay = QByteArray::fromStdString(rawRelpyMsg_);
    QJsonDocument doucment = QJsonDocument::fromJson(rawMsgAssay, &jsonError);

    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return false;
    }

    QJsonObject rootObj = doucment.object();
    if(rootObj.contains("content"))
    {
        QJsonArray contentArray = rootObj.value("content").toArray();
        QJsonObject contentObj = contentArray[0].toObject();

        auto iter = contentObj.constBegin();
        for (;iter!= contentObj.end(); ++iter)
        {
            QString key = iter.key();
            QString value = iter.value().toString();

            qDebug() << "content obj: " << key <<" : "<< value << "\n";
            jsonMap.insert(std::make_pair(key.toStdString(), value.toStdString()));
        }
    }
    else if(rootObj.contains("entries"))
    {
        QJsonArray contentArray = rootObj.value("entries").toArray();
        QJsonObject contentObj = contentArray[0].toObject();

        auto iter = contentObj.constBegin();
        for (;iter!= contentObj.end(); ++iter)
        {
            QString key = iter.key();
            QString value = iter.value().toString();

            qDebug() << "entries obj: " << key <<" : "<< value << "\n";
            jsonMap.insert(std::make_pair(key.toStdString(), value.toStdString()));
        }
    }

    return true;

}

}
