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

void OperationCallPage::initialize(const data::OperationCall *data)
{
    ui->urlLineEdit->setText(data->endpoint);
    ui->requestXmlDocument->setText(data->request);
    ui->requestXmlDocument->setReadWrite(false);
}

void OperationCallPage::sendRequest()
{
    ui->sendRequestButton->setEnabled(false);
    ui->abortRequestButton->setEnabled(true);

    auto reply = soapClient->sendRequest(QUrl(ui->urlLineEdit->text()),
                                         ui->requestXmlDocument->text());
    connect(this, &QObject::destroyed, reply, &QNetworkReply::abort);
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
    connect(reply, &QNetworkReply::finished,
            this, [this, reply]()
    {
        ui->sendRequestButton->setEnabled(true);
        ui->abortRequestButton->setEnabled(false);

        if (reply->error() == QNetworkReply::NoError)
        {
            QDomDocument responseDocument;
            responseDocument.setContent(reply, QDomDocument::ParseOption::PreserveSpacingOnlyNodes);
            ui->responseXmlDocument->setReadWrite(true);
            ui->responseXmlDocument->setText(responseDocument.toString(4));
            ui->responseXmlDocument->setReadWrite(false);
        }
        else if (reply->error() != QNetworkReply::OperationCanceledError)
        {
            ui->responseXmlDocument->setReadWrite(true);
            ui->responseXmlDocument->clear();
            ui->responseXmlDocument->setReadWrite(false);
            ui->responseRawTextEdit->setText(i18n("<missing raw response data>"));
            qDebug() << reply->error()
                     << reply->errorString()
                     << QString::fromUtf8(reply->readAll());
        }
    });
    connect(ui->abortRequestButton, &QToolButton::clicked,
            reply, &QNetworkReply::abort);
}
