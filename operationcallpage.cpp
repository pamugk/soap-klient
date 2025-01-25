#include "operationcallpage.h"
#include "ui_operationcallpage.h"

#include <QDomDocument>
#include <QNetworkReply>

OperationCallPage::OperationCallPage(QWidget *parent)
    : QWidget{parent}
    , soapClient(QCoreApplication::instance()->property("soapClient").value<SoapClient*>())
    , ui(new Ui::OperationCallPage)
{
    ui->setupUi(this);

    connect(ui->sendRequestButton, &QToolButton::clicked,
            this, &OperationCallPage::sendRequest);
}

OperationCallPage::~OperationCallPage()
{
    delete ui;
}

void OperationCallPage::initialize(const data::Interface *interface,
                                   const data::Operation *operation,
                                   const data::OperationCall *operationCall)
{
    if (interface->soapVersion == QStringLiteral("1_0"))
    {
        this->interfaceSoapVersion = SoapVersion::VERSION_1_0;
    }
    else if (interface->soapVersion == QStringLiteral("1_1"))
    {
        this->interfaceSoapVersion = SoapVersion::VERSION_1_1;
    }
    else if (interface->soapVersion == QStringLiteral("1_2"))
    {
        this->interfaceSoapVersion = SoapVersion::VERSION_1_2;
    }
    else
    {
        this->interfaceSoapVersion = SoapVersion::UNKNOWN;
    }
    this->operationSoapAction = operation->action;
    ui->urlLineEdit->setText(operationCall->endpoint);
    ui->requestXmlDocument->setText(operationCall->request);
}

QString buildRequestDescription(const QNetworkRequest &request,
                                const QString &requestBody)
{
    auto newline = QChar::fromLatin1('\n');

    QString result;
    result.append(QStringLiteral("POST "));
    result.append(request.url().toDisplayString());
    result.append(QChar::fromLatin1(' '));
    if (request.attribute(QNetworkRequest::Http2WasUsedAttribute).toBool())
    {
        result.append(QStringLiteral("HTTP/2"));
    }
    else
    {
        result.append(QStringLiteral("HTTP/1.1"));
    }
    result.append(newline);
    for (const auto &headerEntry: request.headers().toListOfPairs())
    {
        result.append(QString::fromLatin1(headerEntry.first));
        result.append(QStringLiteral(": "));
        result.append(QString::fromLatin1(headerEntry.second));
        result.append(newline);
    }
    result.append(newline);
    result.append(requestBody);
    return result;
}

QString buildResponseDescription(const QNetworkReply *reply,
                                 const QByteArray &replyBody)
{
    if (reply->headers().isEmpty() && replyBody.isEmpty())
    {
        return i18n("<missing raw response data>");
    }

    QByteArray result;
    if (reply->attribute(QNetworkRequest::Http2WasUsedAttribute).toBool())
    {
        result.append("HTTP/2 ");
        result.append(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toByteArray());
    }
    else
    {
        result.append("HTTP/1.1 ");
        result.append(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toByteArray());
        result.append(' ');
        result.append(reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray());
    }
    result.append('\n');
    for (const auto &headerEntry: reply->headers().toListOfPairs())
    {
        result.append(headerEntry.first);
        result.append(": ");
        result.append(headerEntry.second);
        result.append('\n');
    }
    if (!replyBody.isEmpty())
    {
        result.append('\n');
        result += replyBody;
    }
    return QString::fromUtf8(result);
}

void OperationCallPage::sendRequest()
{
    ui->sendRequestButton->setEnabled(false);
    ui->abortRequestButton->setEnabled(true);

    SoapRequest request
    {
        operationSoapAction,
        ui->requestXmlDocument->text(),
        interfaceSoapVersion,
        QUrl(ui->urlLineEdit->text()),
    };
    auto reply = soapClient->sendRequest(request);
    ui->requestRawTextEdit->setText(buildRequestDescription(reply->request(), request.body));
    connect(this, &QObject::destroyed, reply, &QNetworkReply::abort);
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
    connect(reply, &QNetworkReply::finished,
            this, [this, reply]()
    {
        ui->sendRequestButton->setEnabled(true);
        ui->abortRequestButton->setEnabled(false);

        QByteArray replyBody = reply->readAll();
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::InternalServerError)
        {
            QDomDocument responseDocument;
            responseDocument.setContent(replyBody, QDomDocument::ParseOption::PreserveSpacingOnlyNodes);
            ui->responseXmlDocument->setReadWrite(true);
            ui->responseXmlDocument->setText(responseDocument.toString(4));
            ui->responseXmlDocument->setReadWrite(false);
        }
        else if (reply->error() != QNetworkReply::OperationCanceledError)
        {
            ui->responseXmlDocument->setReadWrite(true);
            ui->responseXmlDocument->clear();
            ui->responseXmlDocument->setReadWrite(false);
            qDebug() << reply->error()
                     << reply->errorString()
                     << QString::fromUtf8(reply->readAll());
        }
        ui->responseRawTextEdit->setText(buildResponseDescription(reply, replyBody));
    });
    connect(ui->abortRequestButton, &QToolButton::clicked,
            reply, &QNetworkReply::abort);
}
