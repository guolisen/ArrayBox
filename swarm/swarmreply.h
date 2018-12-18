#ifndef SWARMINFO_H
#define SWARMINFO_H
#include <map>
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

    //virtual bool result();

    virtual bool getMessagePairs(std::map<std::string, std::string>& jsonMap);

private:
    std::string rawRelpyMsg_;
};

}
#endif // SWARMINFO_H
