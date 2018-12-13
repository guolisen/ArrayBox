#ifndef SWARMTOOLS_H
#define SWARMTOOLS_H

#include "iswarmtools.h"
#include "iwebrequestadapter.h"

namespace swarm
{
class SwarmTools: public ISwarmTools
{
public:
    explicit SwarmTools(IWebRequestAdapter::Factory webAdapterFactory):
        webAdapterFactory_(webAdapterFactory){}
    virtual ~SwarmTools(){}

    virtual bool request() override;
    virtual void resultFunction(bool, std::string);
private:
    IWebRequestAdapter::Factory webAdapterFactory_;
};
}


#endif // SWARMTOOLS_H
