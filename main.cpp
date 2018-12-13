#include <functional>
#include "abmainwindow.h"
#include <QApplication>
#include "swarm/swarmimpl.h"
#include "swarm/swarminfo.h"
#include "swarm/swarmtools.h"
#include "swarm/webrequestadapter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    swarm::SwarmPtr swarmVar = std::make_shared<swarm::SwarmImpl>(
                std::make_shared<swarm::SwarmInfoFactory>(),
                std::make_shared<swarm::SwarmTools>(
                    std::bind(swarm::WebRequestAdapter::createWebRequest, std::placeholders::_1)));
    ABMainWindow w(nullptr, swarmVar);
    if(!w.init())
    {
        printf("ABMainWindow init error!\n");
        return 1;
    }
    w.show();

    return a.exec();
}
