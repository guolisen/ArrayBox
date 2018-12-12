#ifndef ISWARM_H
#define ISWARM_H

#include <memory>

namespace swarm {

class ISwarm {
public:
    virtual ~ISwarm(){}

    virtual bool search() = 0;


    //virtual bool getField() = 0;
};

typedef std::shared_ptr<ISwarm> SwarmPtr;

}

#endif // ISWARM_H
