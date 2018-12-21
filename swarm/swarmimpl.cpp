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

    //std::string idRequestUrl = "https://swarm.usd.lab.emc.com/api/types/storageSystem/instances?filter=name%20ilk%20%27"+ targetStr +"%27&fields=id&per_page=9999";

    //std::cout << "idRequestUrl!!!: " << idRequestUrl << std::endl;
    return swarmTools_->request("types/storageSystem/instances", "name ilk '" + targetStr + "'", "id");
}
void SwarmImpl::resultFunction(bool result, const std::string& retMsg)
{

    std::cout << "Test!!!: " << retMsg.c_str();
    if (step_ == 0)
    {
        SwarmReplyPtr idRequestReply = std::make_shared<SwarmReply>(retMsg);
        std::map<std::string, std::string> idMap;
        idRequestReply->getMessagePairs(idMap);

        std::string typeParam = std::string("instances/storageSysDetailView/") + idMap["id"];
        swarmTools_->request(typeParam, "", "");
        step_++;
        return;
    }

    infoFunc_(result, std::make_shared<SwarmReply>(retMsg));

}

} // namespace swarm
