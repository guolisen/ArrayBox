#include <memory>
#include <QtNetwork>
#include <QUrl>
#include <QSslConfiguration>
#include "webrequestadapter.h"


namespace swarm
{
WebRequestAdapter::WebRequestAdapter(ResultFunc resFunc):
    //networkAccessMgr_(std::make_shared<QNetworkAccessManager>()),
    reply_(nullptr),
    resFunc_(resFunc) {}

bool WebRequestAdapter::startRequest(std::string url)
{
    const QString urlSpec = QString::fromStdString(url);

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
        return false;
    }

    QNetworkRequest request;
    QSslConfiguration config;

    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::AnyProtocol);
    request.setSslConfiguration(config);
    request.setUrl(newUrl);

    QList<QNetworkCookie> * listcookie = new QList<QNetworkCookie>();
    listcookie->push_back(QNetworkCookie("Ticket","UmVhZE9ubHlUb2tlbg=="));

    QVariant var;
    var.setValue(*listcookie);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setHeader(QNetworkRequest::CookieHeader,var);

    reply_ = networkAccessMgr_.get(request);
    QMetaObject::Connection t = connect(reply_, &QNetworkReply::finished, this, &WebRequestAdapter::finished);

    return true;
}

void WebRequestAdapter::finished()
{
#if 0
    if (httpRequestAborted) {
        reply->deleteLater();
        reply = nullptr;
        return;
    }
#endif

    if (reply_->error()) {
        std::string errStr = reply_->errorString().toStdString();
        resFunc_(false, errStr);
        reply_->deleteLater();
        reply_ = nullptr;

        return;
    }


}

}
