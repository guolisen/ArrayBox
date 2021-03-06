#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtNetwork>
#include <QUrl>
#include <QSslConfiguration>
#include <QDebug>
#include "qtwebrequestimpl.h"

namespace swarm {

QtWebRequestImpl::QtWebRequestImpl(ResultFunc resFunc, QObject *parent) :
    QObject(parent), networkAccessMgr_(new QNetworkAccessManager), resFunc_(resFunc)
{

}

bool QtWebRequestImpl::startRequest(std::string url)
{
    qDebug() << "In Url:" << QString::fromStdString(url) << "\n";

    QUrl newUrl = QUrl::fromUserInput(QString::fromStdString(url));
    if (!newUrl.isValid()) {
        return false;
    }

    //QByteArray encodedUrlArray = newUrl.toEncoded();
    //qDebug() << "encodedUrlArray Url:" << encodedUrlArray << "\n";
    //QUrl encodedUrl(encodedUrlArray);
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

    reply_ = networkAccessMgr_->get(request);
    QMetaObject::Connection t = connect(reply_, &QNetworkReply::finished, this, &QtWebRequestImpl::finished);

    return true;
}

void QtWebRequestImpl::finished()
{
    if (reply_->error()) {
        std::string errStr = reply_->errorString().toStdString();
        resFunc_(false, errStr);
        reply_->deleteLater();
        reply_ = nullptr;

        return;
    }

    QByteArray array = reply_->readAll();
    std::string str = array.toStdString();
    resFunc_(true, str);
    QString qstr = array;
    //qDebug() << "!!!:" << qstr;
    //printf("!!!: %s\n", str.c_str());
    reply_->deleteLater();
    reply_ = nullptr;
    return;
}

}
