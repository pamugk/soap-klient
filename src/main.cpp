#include "mainwindow.h"

#include "soapclient.h"
#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>
#include <QNetworkAccessManager>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setProperty("soapClient", QVariant::fromValue(new SoapClient(&app)));
    KLocalizedString::setApplicationDomain("soap-klient");

    KAboutData aboutData(
            QStringLiteral("soap-klient"),
            i18n("SOAP Klient"),
            QStringLiteral("1.0"),
            i18n("Open-source GUI SOAP client, somewhat compatible with SoapUI"),
            KAboutLicense::GPL_V3,
            i18n("(c) 2024"),
            i18n("Simple application to test SOAP services"),
            QStringLiteral("https://github.com/pamugk/soap-klient/"),
            QString());

    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    MainWindow *w = new MainWindow();
    w->show();
    return app.exec();
}
