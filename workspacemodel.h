#ifndef WORKSPACEMODEL_H
#define WORKSPACEMODEL_H

#include "workspace.h"

#include <QAbstractItemModel>
#include <QObject>

class WorkspaceModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit WorkspaceModel(QObject *parent = nullptr);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setWorkspace(const data::Workspace &workspace);

private:
    data::Workspace workspace;

};

#endif // WORKSPACEMODEL_H
