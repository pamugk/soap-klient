#include "workspacemodel.h"

#include <QIcon>

class WorkspaceModel::Node
{
    QList<WorkspaceModel::Node*> _children;
    qsizetype _idx;
    Node *_parent;

public:
    Node(qsizetype idx)
    {
        this->_idx = idx;
        this->_parent = nullptr;
    }

    ~Node()
    {
        _parent = nullptr;
        qDeleteAll(_children);
        _children.clear();
    }

    void addChild(WorkspaceModel::Node* child)
    {
        child->_parent = this;
        _children.append(child);
    }

    const QList<WorkspaceModel::Node*> &children() const
    {
        return _children;
    }

    qsizetype index() const
    {
        return _idx;
    }

    Node *parent() const
    {
        return _parent;
    }
};

WorkspaceModel::WorkspaceModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    workspace.appVersion = QString();
    workspace.name = QString();
    workspace.projects = QList<data::ProjectEntry>();
}

WorkspaceModel::~WorkspaceModel()
{
    qDeleteAll(projectNodes);
    projectNodes.clear();
}

int WorkspaceModel::columnCount(const QModelIndex &_) const
{
    return 1;
}

QVariant WorkspaceModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        auto node = static_cast<WorkspaceModel::Node*>(index.internalPointer());
        std::array<qsizetype, 4> path = { -1, -1, -1, -1 };
        std::size_t i = 0;
        while(node != nullptr)
        {
            path[i] = node->index();
            node = node->parent();
            i++;
        }

        if (path[3] != -1)
        {
            auto operationCall = &projects[path[3]]->interfaces[path[2]].operations[path[1]].calls[path[0]];
            if (role == Qt::DisplayRole)
            {
                return operationCall->name;
            }
            else if (role == Qt::UserRole)
            {
                return QVariant::fromValue(NodeKind::OPERATION_CALL);
            }
        }
        else if (path[2] != -1)
        {
            auto operation = &projects[path[2]]->interfaces[path[1]].operations[path[0]];
            if (role == Qt::DisplayRole)
            {
                return operation->name;
            }
            else if (role == Qt::UserRole)
            {
                return QVariant::fromValue(NodeKind::OPERATION);
            }
        }
        else if (path[1] != -1)
        {
            auto interface = &projects[path[1]]->interfaces[path[0]];
            if (role == Qt::DisplayRole)
            {
                return interface->name;
            }
            else if (role == Qt::UserRole)
            {
                return QVariant::fromValue(NodeKind::INTERFACE);
            }
        }
        else
        {
            auto projectEntry = &workspace.projects[path[0]];
            if (role == Qt::DisplayRole)
            {
                return projectEntry->name;
            }
            else if (role == Qt::DecorationRole)
            {
                if (projectEntry->remote)
                {
                    return QIcon::fromTheme(QStringLiteral("folder-remote"));
                }
                else if (projectEntry->closed)
                {
                    return QIcon::fromTheme(QIcon::ThemeIcon::FolderVisiting);
                }
                else
                {
                    return QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen);
                }
            }
            else if (role == Qt::UserRole)
            {
                return QVariant::fromValue(NodeKind::PROJECT);
            }
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

    if (parent.isValid())
    {
        auto node = static_cast<WorkspaceModel::Node*>(parent.internalPointer());
        return createIndex(row, column, node->children()[row]);
    }

    return createIndex(row, column, projectNodes[row]);
}

QModelIndex WorkspaceModel::parent(const QModelIndex &index) const
{
    if (index.isValid())
    {
        auto node = static_cast<WorkspaceModel::Node*>(index.internalPointer());
        if (node->parent() != nullptr)
        {
            return createIndex(node->parent()->index(), 0, node->parent());
        }
    }

    return {};
}

int WorkspaceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    if (parent.isValid())
    {
        auto node = static_cast<WorkspaceModel::Node*>(parent.internalPointer());
        return node->children().size();
    }

    return projectNodes.size();
}

void WorkspaceModel::setWorkspace(const data::Workspace &workspace, const QList<std::optional<data::Project>> &projects)
{
    beginResetModel();

    this->workspace = workspace;
    this->projects = projects;

    qDeleteAll(projectNodes);
    projectNodes.resize(workspace.projects.size());
    for (qsizetype i = 0; i < workspace.projects.size(); i++)
    {
        auto projectNode = new WorkspaceModel::Node(i);
        projectNodes[i] = projectNode;
        if (projects[i].has_value())
        {
            auto project = &projects[i].value();
            for (qsizetype j = 0; j < project->interfaces.size(); j++)
            {
                auto interfaceNode = new WorkspaceModel::Node(j);
                projectNode->addChild(interfaceNode);
                auto interface = &project->interfaces[j];
                for (qsizetype k = 0; k < interface->operations.size(); k++)
                {
                    auto operationNode = new WorkspaceModel::Node(k);
                    interfaceNode->addChild(operationNode);
                    auto operation = &interface->operations[k];
                    for (qsizetype l = 0; l < operation->calls.size(); l++)
                    {
                        operationNode->addChild(new WorkspaceModel::Node(l));
                    }
                }
            }
        }
    }

    endResetModel();
}
