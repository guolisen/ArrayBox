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

    virtual bool request(const std::string&, ResultFunc) override;
    virtual void resultFunction(bool, const std::string&);
private:
    IWebRequestAdapter::Factory webAdapterFactory_;
    ResultFunc resultFunc_;
    WebRequestAdapterPtr web_;
};
}


#endif // SWARMTOOLS_H
