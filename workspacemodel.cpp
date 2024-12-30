#include "workspacemodel.h"

#include "xmlparser.h"
#include <QIcon>

WorkspaceModel::WorkspaceModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    this->workspace.appVersion = QString();
    this->workspace.name = QString();
    this->workspace.projects = QList<data::ProjectEntry>();
}

int WorkspaceModel::columnCount(const QModelIndex &parent) const
{

    return 1;
}

QVariant WorkspaceModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        auto project = static_cast<data::ProjectEntry*>(index.internalPointer());

        if (role == Qt::DisplayRole)
        {
            return project->name;
        }
        else if (role == Qt::DecorationRole)
        {
            return QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen);
        }
        return QVariant();
    }

    return role == Qt::DisplayRole ? workspace.name : QVariant();
}

QModelIndex WorkspaceModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return {};
    }

    if (!parent.isValid())
    {
        return createIndex(row, column, &(workspace.projects[row]));
    }

    return {};
}

QModelIndex WorkspaceModel::parent(const QModelIndex &index) const
{
    return {};
}

int WorkspaceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    return parent.isValid() ? 0 : workspace.projects.size();
}

void WorkspaceModel::setWorkspacePath(const QString &workspacePath)
{
    beginResetModel();
    this->workspacePath = workspacePath;
    this->workspace = xml::parseWorkspaceFile(workspacePath);
    endResetModel();
}
