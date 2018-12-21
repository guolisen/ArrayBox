#ifndef ISWARMTOOLS_H
#define ISWARMTOOLS_H

#include <memory>
#include <string>


namespace swarm {

typedef std::function<void(bool, const std::string&)> ResultFunc;

class ISwarmTools
{
public:
    typedef std::function<std::shared_ptr<ISwarmTools>(ResultFunc)> Factory;

    virtual ~ISwarmTools(){}

    virtual bool request(const std::string& requestType, const std::string& requestFilter,
                         const std::string& requestField) = 0;
};

typedef std::shared_ptr<ISwarmTools> SwarmToolsPtr;

}




#endif // ISWARMTOOLS_H
