#include <memory>
#include <QtNetwork>
#include <QUrl>
#include <QSslConfiguration>
#include "webrequestadapter.h"


namespace swarm
{
WebRequestAdapter::WebRequestAdapter(ResultFunc resFunc):
    impl_(resFunc)
{}

bool WebRequestAdapter::startRequest(std::string url)
{
    return impl_.startRequest(url);
}

}
