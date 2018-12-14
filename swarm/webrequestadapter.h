#ifndef WEBREQUESTWRAPPER_H
#define WEBREQUESTWRAPPER_H

#include <memory>
#include "iwebrequestadapter.h"
#include "qtwebrequestimpl.h"

namespace swarm
{

class WebRequestAdapter : public IWebRequestAdapter
{
public:
    explicit WebRequestAdapter(ResultFunc resFunc);
    virtual ~WebRequestAdapter(){}
    static WebRequestAdapterPtr createWebRequest(ResultFunc resultFunc)
    {
        return std::make_shared<WebRequestAdapter>(resultFunc);
    }

    virtual bool startRequest(std::string url) override;


private:
    QtWebRequestImpl impl_;
};
}

#endif // WEBREQUESTWRAPPER_H
