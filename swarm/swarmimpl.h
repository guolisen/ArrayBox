#ifndef SWARMIMPL_H
#define SWARMIMPL_H

#include "iswarm.h"
#include "iswarminfo.h"

namespace swarm {

class SwarmImpl : public ISwarm
{
public:
    SwarmImpl(SwarmInfoFactoryPtr factory):
        swarmInfoFactory_(factory){};
    virtual ~SwarmImpl(){}
    virtual SwarmInfoPtr search(const std::string& targetStr) override;

private:
    SwarmInfoFactoryPtr swarmInfoFactory_;
};

} // namespace swarm
#endif // SWARMIMPL_H
