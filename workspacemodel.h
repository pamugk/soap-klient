#ifndef WORKSPACEMODEL_H
#define WORKSPACEMODEL_H

#include "project.h"
#include "workspace.h"

#include <optional>
#include <QAbstractItemModel>
#include <QObject>

class WorkspaceModel : public QAbstractItemModel
{
    Q_OBJECT

    class Node;

public:
    explicit WorkspaceModel(QObject *parent = nullptr);
    virtual ~WorkspaceModel() override;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setWorkspace(const data::Workspace &workspace);

    struct NodeData
    {
        enum
        {
            PROJECT,
            INTERFACE,
            OPERATION,
            OPERATION_CALL,
            TEST_SUITE,
            TEST_CASE,
            TEST_STEP,
        } kind;
        const std::optional<data::Project> * project;
        const data::Interface *interface;
        const data::Operation *operation;
        const data::OperationCall *operationCall;
    };

private:
    QList<Node*> projectNodes;
    data::Workspace workspace;

};

#endif // WORKSPACEMODEL_H
