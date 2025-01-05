#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "preferencesdialog.h"
#include "workspacemodel.h"
#include "xmlparser.h"
#include <KLocalizedString>
#include <QLatin1StringView>
#include <QList>
#include <QPair>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->projectsTreeView->setModel(new WorkspaceModel());

    connect(ui->actionPreferences, &QAction::triggered,
            this, &MainWindow::showPreferencesDialog);

    auto defaultWorkspacePath = QStandardPaths::locate(QStandardPaths::HomeLocation, QLatin1StringView("default-soapui-workspace.xml"), QStandardPaths::LocateFile);
    static_cast<WorkspaceModel*>(ui->projectsTreeView->model())->setWorkspace(xml::parseWorkspaceFile(defaultWorkspacePath));

    auto defaultSettingsPath = QStandardPaths::locate(QStandardPaths::HomeLocation, QLatin1StringView("soapui-settings.xml"), QStandardPaths::LocateFile);
    this->preferences = xml::parseSettingsFile(defaultSettingsPath);

    auto menuRecentEditors = new QMenu();
    menuRecentEditors->addAction(i18n("empty"))->setEnabled(false);
    menuRecentEditors->addSeparator();
    menuRecentEditors->addAction(i18n("Clear items"))->setEnabled(false);
    ui->actionRecentEditors->setMenu(menuRecentEditors);

    auto menuRecentProjects = new QMenu();
    auto recentProjects = this->preferences.value(QLatin1StringView("RecentProjects")).value<QList<QPair<QString, QString>>>();
    if (recentProjects.isEmpty())
    {
        menuRecentProjects->addAction(i18n("empty"))->setEnabled(false);
    }
    else
    {
        for (const auto &entry: recentProjects)
        {
            menuRecentProjects->addAction(entry.second);
        }
    }
    menuRecentProjects->addSeparator();
    menuRecentProjects->addAction(i18n("Clear items"))->setEnabled(!recentProjects.empty());
    ui->actionRecentProjects->setMenu(menuRecentProjects);

    auto menuRecentWorkspaces = new QMenu();
    auto recentWorkspaces = this->preferences.value(QLatin1StringView("RecentWorkspaces")).value<QList<QPair<QString, QString>>>();
    if (recentWorkspaces.isEmpty())
    {
        menuRecentWorkspaces->addAction(i18n("empty"))->setEnabled(false);
    }
    else
    {
        for (const auto &entry: recentWorkspaces)
        {
            menuRecentWorkspaces->addAction(entry.second);
        }
    }
    menuRecentWorkspaces->addSeparator();
    menuRecentWorkspaces->addAction(i18n("Clear items"))->setEnabled(!recentWorkspaces.empty());
    ui->actionRecentWorkspaces->setMenu(menuRecentWorkspaces);
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
