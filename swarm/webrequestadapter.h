#ifndef WEBREQUESTWRAPPER_H
#define WEBREQUESTWRAPPER_H

#include <memory>
#include "iwebrequestadapter.h"
#include <QNetworkAccessManager>

class QNetworkAccessManager;
class QNetworkReply;
namespace swarm
{

class WebRequestAdapter : public QObject, public IWebRequestAdapter
{
    Q_OBJECT
public:
    explicit WebRequestAdapter(ResultFunc resFunc);
    virtual ~WebRequestAdapter(){}
    static WebRequestAdapterPtr createWebRequest(ResultFunc resultFunc)
    {
        return std::make_shared<WebRequestAdapter>(resultFunc);
    }

    virtual bool startRequest(std::string url) override;

private slots:
    void finished();

private:
    QNetworkAccessManager networkAccessMgr_;
    QNetworkReply* reply_;
    ResultFunc resFunc_;
};
}

#endif // WEBREQUESTWRAPPER_H
