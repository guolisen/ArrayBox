#ifndef ISWARM_H
#define ISWARM_H

#include <memory>
#include "iswarmreply.h"
namespace swarm {

typedef std::function<void(bool, SwarmReplyPtr)> ArrayInfoFunc;

class ISwarm {
public:
    virtual ~ISwarm(){}

    virtual bool search(const std::string& targetStr, ArrayInfoFunc func) = 0;


    //virtual bool getField() = 0;
};

typedef std::shared_ptr<ISwarm> SwarmPtr;

}

#endif // ISWARM_H
