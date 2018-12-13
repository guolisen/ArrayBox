#ifndef ISWARMTOOLS_H
#define ISWARMTOOLS_H

#include <memory>
#include <string>

namespace swarm {

class ISwarmTools
{
public:
    virtual ~ISwarmTools(){}

    virtual bool request() = 0;
};

typedef std::shared_ptr<ISwarmTools> SwarmToolsPtr;

}




#endif // ISWARMTOOLS_H
