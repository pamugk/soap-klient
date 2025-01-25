#ifndef PROJECT_H
#define PROJECT_H

#include "interface.h"

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
};
}

#endif // PROJECT_H
