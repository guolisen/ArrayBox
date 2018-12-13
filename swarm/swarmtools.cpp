#include <functional>
#include "swarmtools.h"
namespace swarm {

bool SwarmTools::request()
{
    WebRequestAdapterPtr web = webAdapterFactory_(std::bind(&SwarmTools::resultFunction, this,
                                 std::placeholders::_1, std::placeholders::_2));

    web->startRequest("ffff");
    return true;
}

void SwarmTools::resultFunction(bool, std::string)
{

}

} // namespace swarm


