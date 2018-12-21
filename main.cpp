#include <functional>
#include "abmainwindow.h"
#include <QApplication>
#include "swarm/swarmimpl.h"
#include "swarm/swarmreply.h"
#include "swarm/swarmtools.h"
#include "swarm/webrequestadapter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    swarm::IWebRequestAdapter::Factory webFactory = std::bind(swarm::WebRequestAdapter::createWebRequest, std::placeholders::_1);
    swarm::SwarmPtr swarmVar = std::make_shared<swarm::SwarmImpl>(
                std::bind(&swarm::SwarmReply::createSwarmReply, std::placeholders::_1),
                std::bind(&swarm::SwarmTools::createSwarmTools,
                          std::placeholders::_1, webFactory));

    ABMainWindow w(nullptr, swarmVar);
    if(!w.init())
    {
        printf("ABMainWindow init error!\n");
        return 1;
    }
    w.show();

    return a.exec();
}
