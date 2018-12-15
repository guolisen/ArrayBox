#ifndef SWARMINFO_H
#define SWARMINFO_H
#include <string>
#include "iswarmreply.h"

namespace swarm
{

class SwarmReply : public ISwarmReply
{
public:
    SwarmReply(const std::string& relpyMsg);
    virtual ~SwarmReply(){}
    static SwarmReplyPtr createSwarmReply(const std::string& relyMsg)
    {
        return std::make_shared<SwarmReply>(relyMsg);
    }

    virtual std::string getRawMessage() const
    {
        return rawRelpyMsg_;
    }

private:
    std::string rawRelpyMsg_;
};

}
#endif // SWARMINFO_H
