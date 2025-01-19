#ifndef SOAPCLIENT_H
#define SOAPCLIENT_H

#include <QNetworkAccessManager>
#include <QObject>

class SoapClient : public QObject
{
    Q_OBJECT
public:
    explicit SoapClient(QObject *parent = nullptr);

    QNetworkReply *sendRequest(const QUrl &url,
                               const QString &request);

Q_SIGNALS:
    void soapRequestFinished(QNetworkReply *reply);
    void soapRequestStarted();

private:
    QNetworkAccessManager *networkManager;
};

#endif // SOAPCLIENT_H
