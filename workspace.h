#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "project.h"

#include <optional>
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

    std::optional<data::Project> data;
};

struct Workspace
{
    QString name;
    QString appVersion;
    QList<ProjectEntry> projects;
};
}

#endif // WORKSPACE_H
