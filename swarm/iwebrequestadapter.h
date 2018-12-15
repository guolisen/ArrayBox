#ifndef IWEBREQUESTWRAPPER_H
#define IWEBREQUESTWRAPPER_H

#include <functional>
#include <string>
#include <memory>
#include "swarm/iswarmtools.h"

namespace swarm
{

class IWebRequestAdapter
{
public:
    typedef std::function<std::shared_ptr<IWebRequestAdapter>(ResultFunc)> Factory;

    virtual ~IWebRequestAdapter(){}
    virtual bool startRequest(std::string url) = 0;
};

typedef std::shared_ptr<IWebRequestAdapter> WebRequestAdapterPtr;
}
#endif // IWEBREQUESTWRAPPER_H
