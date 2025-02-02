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
            auto project = &workspace.projects[path[3]].data;
            if (path[2] >= project->value().interfaces.size())
            {
                auto testSuiteIndex = path[2] - project->value().interfaces.size();
                auto testStep = &project->value().testSuites[testSuiteIndex].testCases[path[1]].testSteps[0];
                if (role == Qt::DisplayRole)
                {
                    return testStep->name;
                }
                else if (role == Qt::UserRole)
                {
                    return QVariant::fromValue<NodeData>(
                                {
                                    NodeData::TEST_STEP,
                                    &workspace.projects[path[0]].data,
                                    nullptr,
                                    nullptr,
                                    nullptr,
                                });
                }
            }
            else
            {
                auto operationCall = &project->value().interfaces[path[2]].operations[path[1]].calls[path[0]];
                if (role == Qt::DisplayRole)
                {
                    return operationCall->name;
                }
                else if (role == Qt::UserRole)
                {
                    auto interface = &project->value().interfaces[path[2]];
                    auto operation = &interface->operations[path[1]];
                    return QVariant::fromValue<NodeData>(
                                {
                                    NodeData::OPERATION_CALL,
                                    project,
                                    interface,
                                    operation,
                                    operationCall,
                                });
                }
            }
        }
        else if (path[2] != -1)
        {
            auto project = &workspace.projects[path[2]].data;
            if (path[1] >= project->value().interfaces.size())
            {
                auto testSuiteIndex = path[1] - project->value().interfaces.size();
                auto testCase = &project->value().testSuites[testSuiteIndex].testCases[path[0]];
                if (role == Qt::DisplayRole)
                {
                    return testCase->name;
                }
                else if (role == Qt::DecorationRole)
                {
                    return QIcon::fromTheme(QStringLiteral("emblem-ok-symbolic"));
                }
                else if (role == Qt::UserRole)
                {
                    return QVariant::fromValue<NodeData>(
                                {
                                    NodeData::TEST_CASE,
                                    &workspace.projects[path[0]].data,
                                    nullptr,
                                    nullptr,
                                    nullptr,
                                });
                }
            }
            else
            {
                auto operation = &project->value().interfaces[path[1]].operations[path[0]];
                if (role == Qt::DisplayRole)
                {
                    return operation->name;
                }
                else if (role == Qt::DecorationRole)
                {
                    return QIcon::fromTheme(QStringLiteral("emblem-synchronizing-symbolic"));
                }
                else if (role == Qt::UserRole)
                {
                    auto interface = &project->value().interfaces[path[1]];
                    return QVariant::fromValue<NodeData>(
                                {
                                    NodeData::OPERATION,
                                    project,
                                    interface,
                                    operation,
                                    nullptr,
                                });
                }
            }
        }
        else if (path[1] != -1)
        {
            auto project = &workspace.projects[path[1]].data;
            if (path[0] >= project->value().interfaces.size())
            {
                auto testSuiteIndex = path[0] - project->value().interfaces.size();
                auto testSuite = &project->value().testSuites[testSuiteIndex];
                if (role == Qt::DisplayRole)
                {
                    return testSuite->name;
                }
                else if (role == Qt::DecorationRole)
                {
                    return QIcon::fromTheme(QStringLiteral("view-grid-symbolic"));
                }
                else if (role == Qt::UserRole)
                {
                    return QVariant::fromValue<NodeData>(
                                {
                                    NodeData::TEST_SUITE,
                                    &workspace.projects[path[0]].data,
                                    nullptr,
                                    nullptr,
                                    nullptr,
                                });
                }
            }
            else
            {
                auto interface = &project->value().interfaces[path[0]];
                if (role == Qt::DisplayRole)
                {
                    return interface->name;
                }
                else if (role == Qt::DecorationRole)
                {
                    return QIcon::fromTheme(QStringLiteral("network-transmit-symbolic"));
                }
                else if (role == Qt::UserRole)
                {
                    return QVariant::fromValue<NodeData>(
                                {
                                    NodeData::INTERFACE,
                                    project,
                                    interface,
                                    nullptr,
                                    nullptr,
                                });
                }
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
                return QVariant::fromValue<NodeData>(
                            {
                                NodeData::PROJECT,
                                &workspace.projects[path[0]].data,
                                nullptr,
                                nullptr,
                                nullptr,
                            });
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

void WorkspaceModel::setWorkspace(const data::Workspace &workspace)
{
    beginResetModel();

    this->workspace = workspace;

    qDeleteAll(projectNodes);
    projectNodes.resize(workspace.projects.size());
    for (qsizetype i = 0; i < workspace.projects.size(); i++)
    {
        auto projectNode = new WorkspaceModel::Node(i);
        projectNodes[i] = projectNode;
        if (workspace.projects[i].data.has_value())
        {
            auto project = &workspace.projects[i].data.value();
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
            for (qsizetype j = 0; j < project->testSuites.size(); j++)
            {
                auto testSuiteNode = new WorkspaceModel::Node(project->interfaces.size() + j);
                projectNode->addChild(testSuiteNode);
                auto testSuite = &project->testSuites[j];
                for (qsizetype k = 0; k < testSuite->testCases.size(); k++)
                {
                    auto testCaseNode = new WorkspaceModel::Node(k);
                    testSuiteNode->addChild(testCaseNode);
                    auto testCase = &testSuite->testCases[k];
                    for (qsizetype l = 0; l < testCase->testSteps.size(); l++)
                    {
                        testCaseNode->addChild(new WorkspaceModel::Node(l));
                    }
                }
            }
        }
    }

    endResetModel();
}
