#include <functional>
#include <string>
#include "swarmtools.h"
#include <iostream>

namespace swarm {

const std::string apiRootUrl = "https://swarm.usd.lab.emc.com/api/";

bool SwarmTools::request(const std::string& requestType, const std::string& requestFilter,
                         const std::string& requestField, ResultFunc resultFunc)
{
    resultFunc_ = resultFunc;
    web_ = webAdapterFactory_(std::bind(&SwarmTools::resultFunction, this,
                                 std::placeholders::_1, std::placeholders::_2));

    web_->startRequest(createRequestUrl(requestType, requestFilter, requestField));
    //web->startRequest("https://www.baidu.com");

    return true;
}


void SwarmTools::resultFunction(bool result, const std::string& retMsg)
{
    std::cout << "Test!!!: " << retMsg.c_str();
    resultFunc_(result, retMsg);
}

std::string SwarmTools::createRequestUrl(const std::string &requestType,
                                         const std::string &requestFilter,
                                         const std::string &requestField)
{
    std::string targetUrlStr = apiRootUrl;

    if (!requestType.empty())
    {
        targetUrlStr += "?" + requestType;
    }
    if (!requestFilter.empty())
    {

    }
    if (!requestField.empty())
    {

    }

    return "";
}

} // namespace swarm


