#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "swarmreply.h"


namespace swarm
{

SwarmReply::SwarmReply(const std::string& relpyMsg): rawRelpyMsg_(relpyMsg)
{
    getMessagePairs();
}

bool SwarmReply::getMessagePairs()
{
    QJsonParseError jsonError;
    QByteArray rawMsgAssay = QByteArray::fromStdString(rawRelpyMsg_);
    QJsonDocument doucment = QJsonDocument::fromJson(rawMsgAssay, &jsonError);

    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return false;
    }

    QJsonObject obj = doucment.object();

    auto iter = obj.constBegin();
    for (;iter!= obj.end(); ++iter)
    {
        QString key = iter.key();
        QString value = iter.value().toString();

        qDebug() << "obj: " << key <<" : "<< value << "";

    }

    return true;

}

}
