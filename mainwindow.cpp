#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "workspacemodel.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->projectsTreeView->setModel(new WorkspaceModel());

    auto defaultWorkspacePath = QStandardPaths::locate(QStandardPaths::HomeLocation, "default-soapui-workspace.xml", QStandardPaths::LocateFile);
    static_cast<WorkspaceModel*>(ui->projectsTreeView->model())->setWorkspacePath(defaultWorkspacePath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

