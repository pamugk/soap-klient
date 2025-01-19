#ifndef PROJECT_H
#define PROJECT_H

#include "operationcall.h"

#include <QList>
#include <QString>
#include <QStringList>

namespace data
{
struct DefinitionCachePart
{
    QString url;
    QString content;
    QString type;
};

struct DefinitionCache
{
    QString type;
    QString rootPart;
    QList<DefinitionCachePart> parts;
};

struct Operation
{
    QString id;
    bool isOneWay;
    QString action;
    QString name;
    QString bindingOperationName;
    QString type;
    QString outputName;
    QString inputName;
    bool receivesAttachments;
    bool sendsAttachments;
    QString anonymous;
    QList<OperationCall> calls;
};

struct Interface
{
    QString id;
    QString wsaVersion;
    QString name;
    QString type;
    QString bindingName;
    QString soapVersion;
    QString anonymous;
    QString definition;
    DefinitionCache definitionCache;
    QStringList endpoints;
    QList<Operation> operations;
};

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
