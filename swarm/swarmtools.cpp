#include <functional>
#include <string>
#include "swarmtools.h"
#include <iostream>

namespace swarm {

bool SwarmTools::request(const std::string& url, ResultFunc resultFunc)
{
    resultFunc_ = resultFunc;
    web_ = webAdapterFactory_(std::bind(&SwarmTools::resultFunction, this,
                                 std::placeholders::_1, std::placeholders::_2));

    web_->startRequest(url);
    //web->startRequest("https://www.baidu.com");

    return true;
}


void SwarmTools::resultFunction(bool result, const std::string& retMsg)
{
    std::cout << "Test!!!: " << retMsg.c_str();
    resultFunc_(result, retMsg);
}

} // namespace swarm


