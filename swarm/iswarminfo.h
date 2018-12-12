#ifndef ISWARMINFO_H
#define ISWARMINFO_H

#include <memory>

namespace swarm
{
class ISwarmInfo
{
public:
    virtual ~ISwarmInfo(){}
};

typedef std::shared_ptr<ISwarmInfo> SwarmInfoPtr;

class ISwarmInfoFactory
{
public:
    virtual ~ISwarmInfoFactory(){}
    SwarmInfoPtr createSwarmInfo();
};

typedef std::shared_ptr<ISwarmInfoFactory> SwarmInfoFactoryPtr;

}
#endif // ISWARMINFO_H
