#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QList>
#include <QStringView>

namespace data
{
struct ProjectEntry
{
    QString name;
    QString path;
    QString status;
    QString type;
};

struct Workspace
{
    QString name;
    QString appVersion;
    QList<ProjectEntry> projects;
};
}

#endif // DATASTRUCTURES_H
