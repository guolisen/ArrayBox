#include "swarminfo.h"


namespace swarm
{

SwarmInfo::SwarmInfo()
{

}

SwarmInfoPtr SwarmInfoFactory::createSwarmInfo()
{
    //return std::make_shared<ISwarmInfo>();
    return SwarmInfoPtr();
}

}
