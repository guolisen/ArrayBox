#include <functional>
#include <string>
#include "swarmtools.h"
#include <iostream>

namespace swarm {

bool SwarmTools::request()
{
    WebRequestAdapterPtr web = webAdapterFactory_(std::bind(&SwarmTools::resultFunction, this,
                                 std::placeholders::_1, std::placeholders::_2));

    web->startRequest("https://swarm.usd.lab.emc.com/api/instances/storageSysDetailView/FCNCH0972DDD9D?per_page=100");
    return true;
}


void SwarmTools::resultFunction(bool result, const std::string& retMsg)
{
    std::cout << "Test!!!: " << retMsg.c_str();
}

} // namespace swarm


