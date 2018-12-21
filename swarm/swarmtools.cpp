#include <functional>
#include <string>
#include "swarmtools.h"
#include <iostream>

namespace swarm {

const std::string apiRootUrl = "https://swarm.usd.lab.emc.com/api/";

bool SwarmTools::request(const std::string& requestType, const std::string& requestFilter,
                         const std::string& requestField)
{
    return web_->startRequest(createRequestUrl(requestType, requestFilter, requestField));
}


void SwarmTools::resultFunction(bool result, const std::string& retMsg)
{
    printf("Test!!!: %s\n", retMsg.c_str());
    //resultFunc_(result, retMsg);
}

std::string SwarmTools::createRequestUrl(const std::string &requestType,
                                         const std::string &requestFilter,
                                         const std::string &requestField)
{
    std::string targetUrlStr = apiRootUrl;

    if (requestType.empty())
    {
        return "";
    }
    targetUrlStr += requestType + "?";

    if (!requestFilter.empty())
    {
        //QString urlEncode = QUrl::toPercentEncoding(QString::fromStdString(requestFilter));
        targetUrlStr += "filter=" + requestFilter + "&";
    }
    if (!requestField.empty())
    {
        //QString urlEncode = QUrl::toPercentEncoding(QString::fromStdString(requestField));
        targetUrlStr += "fields=" + requestField + "&";
    }

    targetUrlStr += "per_page=9999";
    return targetUrlStr;
}

} // namespace swarm


