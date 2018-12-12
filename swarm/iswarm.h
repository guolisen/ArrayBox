#ifndef ISWARM_H
#define ISWARM_H

#include <memory>
#include "iswarminfo.h"
namespace swarm {

class ISwarm {
public:
    virtual ~ISwarm(){}

    virtual SwarmInfoPtr search(const std::string& targetStr) = 0;


    //virtual bool getField() = 0;
};

typedef std::shared_ptr<ISwarm> SwarmPtr;

}

#endif // ISWARM_H
