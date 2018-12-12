#ifndef SWARMIMPL_H
#define SWARMIMPL_H

#include "iswarm.h"
#include "iswarminfo.h"
#include "iswarmtools.h"

namespace swarm {

class SwarmImpl : public ISwarm
{
public:
    SwarmImpl(SwarmInfoFactoryPtr factory, SwarmToolsPtr swarmTools):
        swarmInfoFactory_(factory), swarmTools_(swarmTools) {}
    virtual ~SwarmImpl(){}
    virtual SwarmInfoPtr search(const std::string& targetStr) override;

private:
    SwarmInfoFactoryPtr swarmInfoFactory_;
    SwarmToolsPtr swarmTools_;
};

} // namespace swarm
#endif // SWARMIMPL_H
