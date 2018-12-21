#ifndef SWARMTOOLS_H
#define SWARMTOOLS_H

#include "iswarmtools.h"
#include "iwebrequestadapter.h"

namespace swarm
{
class SwarmTools: public ISwarmTools
{
public:
    explicit SwarmTools(IWebRequestAdapter::Factory webAdapterFactory, ResultFunc resultFunc):
         webAdapterFactory_(webAdapterFactory),  web_(webAdapterFactory_(resultFunc)){}
    virtual ~SwarmTools(){}

    static SwarmToolsPtr createSwarmTools(ResultFunc resultFunc, IWebRequestAdapter::Factory webAdapterFactory)
    {
        return std::make_shared<SwarmTools>(webAdapterFactory, resultFunc);
    }
    virtual bool request(const std::string& requestType, const std::string& requestFilter,
                         const std::string& requestField) override;

    virtual std::string createRequestUrl(const std::string& requestType, const std::string& requestFilter,
                                         const std::string& requestField);
private:
    IWebRequestAdapter::Factory webAdapterFactory_;
    WebRequestAdapterPtr web_;
};
}


#endif // SWARMTOOLS_H
