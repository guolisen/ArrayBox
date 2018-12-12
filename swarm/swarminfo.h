#ifndef SWARMINFO_H
#define SWARMINFO_H

#include "iswarminfo.h"

namespace swarm
{
class SwarmInfo : public ISwarmInfo
{
public:
    SwarmInfo();
    virtual ~SwarmInfo(){}
};

class SwarmInfoFactory : public ISwarmInfoFactory
{
public:
    virtual ~SwarmInfoFactory(){}
    SwarmInfoPtr createSwarmInfo();
};

}
#endif // SWARMINFO_H
