#include "swarmimpl.h"

namespace swarm {


SwarmInfoPtr SwarmImpl::search(const std::string& targetStr)
{
    swarmTools_->request();
    return SwarmInfoPtr();
}

} // namespace swarm
