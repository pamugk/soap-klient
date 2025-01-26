#ifndef TESTSTEP_H
#define TESTSTEP_H

#include <QList>
#include <QString>
#include <variant>

namespace data
{
struct Assertion
{
    QString type;
    QString id;
    QString name;
};

struct TestPropertyTransfersStep
{
    struct Transfer
    {
        bool setNullOnMissingSource;
        bool transferTextContent;
        bool failOnError;
        bool ignoreEmpty;
        bool transferToAll;
        bool transferChildNodes;
        QString name;
        QString sourceType;
        QString sourceStep;
        QString sourcePath;
        QString targetType;
        QString targetStep;
        QString targetPath;
        bool upgraded;
    };

    QList<Transfer> transfers;
};

struct TestRequestStep
{
    QString interface;
    QString operation;
    struct
    {
        QString name;
        QString id;
        QString encoding;
        QString endpoint;
        QString request;
        QList<Assertion> assertions;
    } request;
};

struct TestStep
{
    QString type;
    QString name;
    QString id;
    std::variant<TestPropertyTransfersStep, TestRequestStep> config;
};
}

#endif // TESTSTEP_H
