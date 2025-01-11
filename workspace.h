#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QList>
#include <QString>

namespace data
{

struct ProjectEntry
{
    QString name;
    QString path;
    bool closed;
    bool remote;
};

struct Workspace
{
    QString name;
    QString appVersion;
    QList<ProjectEntry> projects;
};
}

#endif // WORKSPACE_H
