#ifndef SWARMIMPL_H
#define SWARMIMPL_H

#include "iswarm.h"
#include "iswarmreply.h"
#include "iswarmtools.h"

namespace swarm {

class SwarmImpl : public ISwarm
{
public:
    SwarmImpl(ISwarmReply::Factory factory, SwarmToolsPtr swarmTools):
        swarmReplyFactory_(factory), swarmTools_(swarmTools), isWorking_(false), step_(0) {}
    virtual ~SwarmImpl(){}
    virtual bool search(const std::string& targetStr, ArrayInfoFunc func) override;
    virtual void resultFunction(bool result, const std::string& retMsg);

private:
    ISwarmReply::Factory swarmReplyFactory_;
    SwarmToolsPtr swarmTools_;
    ArrayInfoFunc infoFunc_;
    bool isWorking_;
    int step_;
};

} // namespace swarm
#endif // SWARMIMPL_H
