#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "preferencesdialog.h"
#include "workspacemodel.h"
#include "xmlparser.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->projectsTreeView->setModel(new WorkspaceModel());

    connect(ui->actionPreferences, &QAction::triggered,
            this, &MainWindow::showPreferencesDialog);

    auto defaultWorkspacePath = QStandardPaths::locate(QStandardPaths::HomeLocation, "default-soapui-workspace.xml", QStandardPaths::LocateFile);
    static_cast<WorkspaceModel*>(ui->projectsTreeView->model())->setWorkspacePath(defaultWorkspacePath);

    auto defaultSettingsPath = QStandardPaths::locate(QStandardPaths::HomeLocation, "soapui-settings.xml", QStandardPaths::LocateFile);
    this->preferences = xml::parseSettingsFile(defaultSettingsPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPreferencesDialog()
{
    PreferencesDialog preferencesDialog(this);
    preferencesDialog.setPreferences(this->preferences);
    preferencesDialog.exec();
}
