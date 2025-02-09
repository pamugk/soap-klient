#ifndef SOAPCLIENT_H
#define SOAPCLIENT_H

#include <QNetworkAccessManager>
#include <QObject>

enum class SoapVersion
{
    UNKNOWN,
    VERSION_1_0,
    VERSION_1_1,
    VERSION_1_2,
};

struct SoapRequest
{
    const QString &action;
    const QString &body;
    SoapVersion soapVersion;
    const QUrl &url;
};

class SoapClient : public QObject
{
    Q_OBJECT
public:
    explicit SoapClient(QObject *parent = nullptr);

    QNetworkReply *sendRequest(const SoapRequest &request);

Q_SIGNALS:
    void soapRequestFinished(QNetworkReply *reply);
    void soapRequestStarted();

private:
    QNetworkAccessManager *networkManager;
};

#endif // SOAPCLIENT_H
