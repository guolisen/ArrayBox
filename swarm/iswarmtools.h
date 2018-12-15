#ifndef ISWARMTOOLS_H
#define ISWARMTOOLS_H

#include <memory>
#include <string>

namespace swarm {

typedef std::function<void(bool, const std::string&)> ResultFunc;

class ISwarmTools
{
public:
    virtual ~ISwarmTools(){}

    virtual bool request(const std::string&, ResultFunc) = 0;
};

typedef std::shared_ptr<ISwarmTools> SwarmToolsPtr;

}




#endif // ISWARMTOOLS_H
