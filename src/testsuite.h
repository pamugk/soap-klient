#ifndef TESTSUITE_H
#define TESTSUITE_H

#include "testcase.h"
#include <QList>
#include <QString>

namespace data
{
struct TestSuite
{
    QString name;
    QString id;
    QString runType;
    QList<TestCase> testCases;
};
}

#endif // TESTSUITE_H
