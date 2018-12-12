#include "abmainwindow.h"
#include <QApplication>
#include "swarm/swarmimpl.h"
#include "swarm/swarminfo.h"
#include "swarm/swarmtools.h"
#include "swarm/webrequestadapter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    swarm::WebRequestAdapterPtr webAdapter = std::make_shared<swarm::WebRequestAdapter>();
    swarm::SwarmPtr swarmVar = std::make_shared<swarm::SwarmImpl>(
                std::make_shared<swarm::SwarmInfoFactory>(),
                std::make_shared<swarm::SwarmTools>(webAdapter));
    ABMainWindow w(nullptr, swarmVar);
    if(!w.init())
    {
        printf("ABMainWindow init error!\n");
        return 1;
    }
    w.show();

    return a.exec();
}
