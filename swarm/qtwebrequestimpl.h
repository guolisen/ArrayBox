#ifndef QTWEBREQUESTIMPL_H
#define QTWEBREQUESTIMPL_H

#include <string>
#include <QObject>
#include <QNetworkAccessManager>
#include "iswarmtools.h"
#include "iwebrequestadapter.h"

namespace swarm {

class QtWebRequestImpl : public QObject
{
    Q_OBJECT
public:
    QtWebRequestImpl(ResultFunc resFunc, QObject *parent = nullptr);

    virtual bool startRequest(std::string url);
signals:

public slots:
    void finished();

private:
    QNetworkAccessManager networkAccessMgr_;
    QNetworkReply* reply_;
    ResultFunc resFunc_;
};

}
#endif // QTWEBREQUESTIMPL_H
