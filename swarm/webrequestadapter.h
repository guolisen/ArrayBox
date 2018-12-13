#ifndef WEBREQUESTWRAPPER_H
#define WEBREQUESTWRAPPER_H

#include "iwebrequestadapter.h"

class QNetworkAccessManager;
class QNetworkReply;

namespace swarm
{

class WebRequestAdapter : public IWebRequestAdapter
{
public:
    explicit WebRequestAdapter(ResultFunc resFunc):
        resFunc_(resFunc){}
    virtual ~WebRequestAdapter(){}
    static WebRequestAdapterPtr createWebRequest(ResultFunc resultFunc)
    {
        return std::make_shared<WebRequestAdapter>(resultFunc);
    }

    virtual bool startRequest(std::string url) override;

private:
    QNetworkAccessManager* networkAccessMgr_;
    QNetworkReply* reply_;
    ResultFunc resFunc_;
};
}

#endif // WEBREQUESTWRAPPER_H
