#ifndef ISWARM_H
#define ISWARM_H

namespace swarm {

class ISwarm {
public:
    virtual ~ISwarm(){}

    virtual bool search() = 0;

    virtual bool getField() = 0;
    virtual bool searchByName() = 0;
    virtual bool searchByIp() = 0;
};

}

#endif // ISWARM_H
