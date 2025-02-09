#ifndef PROJECT_H
#define PROJECT_H

#include "interface.h"
#include "testsuite.h"

#include <QList>
#include <QString>

namespace data
{
struct Project
{
    QString id;
    QString activeEnvironment;
    QString name;
    QString resourceRoot;
    QString appVersion;
    bool abortOnError;
    QString runType;
    QList<Interface> interfaces;
    QList<TestSuite> testSuites;
};
}

#endif // PROJECT_H
