#include "mainwindow.h"

#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("soap-klient");

    QCommandLineParser parser;
    parser.process(app);

    MainWindow w;
    w.show();
    return app.exec();
}
