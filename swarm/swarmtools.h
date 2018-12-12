#ifndef SWARMTOOLS_H
#define SWARMTOOLS_H

#include "iswarmtools.h"
#include "iwebrequestadapter.h"

namespace swarm
{
class SwarmTools: public ISwarmTools
{
public:
    SwarmTools(WebRequestAdapterPtr webAdapter):
        webAdapter_(webAdapter){}
    virtual ~SwarmTools(){}

private:
    WebRequestAdapterPtr webAdapter_;
};
}


#endif // SWARMTOOLS_H
