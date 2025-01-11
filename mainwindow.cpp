#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "preferencesdialog.h"
#include "workspacemodel.h"
#include "xmlparser.h"

#include <KLocalizedString>
#include <QList>
#include <QPair>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionPreferences, &QAction::triggered,
            this, &MainWindow::showPreferencesDialog);

    auto defaultSettingsPath = QStandardPaths::locate(QStandardPaths::HomeLocation, QStringLiteral("soapui-settings.xml"), QStandardPaths::LocateFile);
    this->preferences = xml::parseSettingsFile(defaultSettingsPath).value();
    auto recentProjects = this->preferences.value(QStringLiteral("RecentProjects")).value<QList<QPair<QString, QString>>>();
    if (recentProjects.isEmpty())
    {
        ui->menuRecentProjects->addAction(i18n("empty"))->setEnabled(false);
    }
    else
    {
        for (const auto &entry: recentProjects)
        {
            ui->menuRecentProjects->addAction(entry.second);
        }
    }
    ui->menuRecentProjects->addSeparator();
    ui->menuRecentProjects->addAction(i18n("Clear items"))->setEnabled(!recentProjects.empty());
    auto recentWorkspaces = this->preferences.value(QStringLiteral("RecentWorkspaces")).value<QList<QPair<QString, QString>>>();
    if (recentWorkspaces.isEmpty())
    {
        ui->menuRecentWorkspaces->addAction(i18n("empty"))->setEnabled(false);
    }
    else
    {
        for (const auto &entry: recentWorkspaces)
        {
            ui->menuRecentWorkspaces->addAction(entry.second);
        }
    }
    ui->menuRecentWorkspaces->addSeparator();
    ui->menuRecentWorkspaces->addAction(i18n("Clear items"))->setEnabled(!recentWorkspaces.empty());

    auto projectsModel = new WorkspaceModel();
    ui->projectsTreeView->setModel(projectsModel);
    auto defaultWorkspacePath = QStandardPaths::locate(QStandardPaths::HomeLocation, QStringLiteral("default-soapui-workspace.xml"), QStandardPaths::LocateFile);
    auto workspace = xml::parseWorkspaceFile(defaultWorkspacePath).value();
    QList<std::optional<data::Project>> projects;
    for (auto &projectEntry: workspace.projects)
    {
        if (projectEntry.closed)
        {
            projects.append(std::nullopt);
        }
        else
        {
            auto project = xml::parseProjectFile(projectEntry.path);
            projectEntry.closed = !project.has_value();
            projectEntry.remote = projectEntry.closed;
            projects.append(project);
        }
    }
    projectsModel->setWorkspace(workspace, projects);
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
