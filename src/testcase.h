#ifndef TESTCASE_H
#define TESTCASE_H

#include "teststep.h"
#include <QList>
#include <QString>

namespace data
{
struct TestCase
{
    QString id;
    bool failOnError;
    bool failTestCaseOnErrors;
    bool keepSession;
    uint maxResults;
    QString name;
    bool searchProperties;
    QList<TestStep> testSteps;
};
}

#endif // TESTCASE_H
