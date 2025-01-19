#include "soapclient.h"

#include <QNetworkReply>

SoapClient::SoapClient(QObject *parent)
    : QObject{parent}
    , networkManager(new QNetworkAccessManager(this))
{

}

QNetworkReply * SoapClient::sendRequest(const QUrl &url,
                                        const QString &requestText)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1StringView("application/soap+xml;charset=UTF-8"));

    QNetworkReply *reply = networkManager->post(request, requestText.toUtf8());
    Q_EMIT soapRequestStarted();
    connect(reply, &QNetworkReply::finished,
            this, [this, reply]()
    {
        Q_EMIT soapRequestFinished(reply);
    });
    return reply;
}
