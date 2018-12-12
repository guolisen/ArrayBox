#ifndef IWEBREQUESTWRAPPER_H
#define IWEBREQUESTWRAPPER_H

#include <memory>

namespace swarm
{
class IWebRequestAdapter
{
public:
    virtual ~IWebRequestAdapter(){}
};

typedef std::shared_ptr<IWebRequestAdapter> WebRequestAdapterPtr;

}
#endif // IWEBREQUESTWRAPPER_H
