#ifndef WEBREQUESTWRAPPER_H
#define WEBREQUESTWRAPPER_H

#include "iwebrequestadapter.h"

namespace swarm
{
class WebRequestAdapter : public IWebRequestAdapter
{
public:
    WebRequestAdapter();
    virtual ~WebRequestAdapter(){}
};
}

#endif // WEBREQUESTWRAPPER_H
