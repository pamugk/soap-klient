#include "soapclient.h"

#include <QNetworkReply>

SoapClient::SoapClient(QObject *parent)
    : QObject{parent}
    , networkManager(new QNetworkAccessManager(this))
{

}

QNetworkReply * SoapClient::sendRequest(const SoapRequest &request)
{
    QNetworkRequest networkRequest(request.url);
    switch (request.soapVersion)
    {
    case SoapVersion::VERSION_1_1:
    {
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1StringView("text/xml;charset=UTF-8"));
        networkRequest.setRawHeader("SOAPAction", request.action.toLatin1());
        break;
    }
    case SoapVersion::VERSION_1_2:
    {
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                                 QString::fromLatin1("application/soap+xml;charset=UTF-8;action=%1").arg(request.action));
        break;
    }
    default:
    {
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1StringView("application/soap+xml;charset=UTF-8"));
    }
    }


    QNetworkReply *reply = networkManager->post(networkRequest, request.body.toUtf8());
    Q_EMIT soapRequestStarted();
    connect(reply, &QNetworkReply::finished,
            this, [this, reply]()
    {
        Q_EMIT soapRequestFinished(reply);
    });
    return reply;
}
