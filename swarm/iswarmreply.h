#ifndef ISWARMINFO_H
#define ISWARMINFO_H
#include <string>
#include <map>
#include <memory>

namespace swarm
{
class ISwarmReply
{
public:
    typedef std::function<std::shared_ptr<ISwarmReply>(const std::string&)> Factory;

    virtual ~ISwarmReply(){}
    virtual std::string getRawMessage() const = 0;
    virtual bool getMessagePairs(std::map<std::string, std::string>& jsonMap) = 0;
};

typedef std::shared_ptr<ISwarmReply> SwarmReplyPtr;

}
#endif // ISWARMINFO_H
