#include "swarmimpl.h"
#include "swarmreply.h"
#include <iostream>
namespace swarm {


bool SwarmImpl::search(const std::string& targetStr, ArrayInfoFunc func)
{
    if (isWorking_)
        return false;
    isWorking_ = true;
    infoFunc_ = func;
    return swarmTools_->request(targetStr, std::bind(&SwarmImpl::resultFunction, this,
                                std::placeholders::_1, std::placeholders::_2));
}
void SwarmImpl::resultFunction(bool result, const std::string& retMsg)
{
    std::cout << "Test!!!: " << retMsg.c_str();
    infoFunc_(result, std::make_shared<SwarmReply>(retMsg));
}

} // namespace swarm
