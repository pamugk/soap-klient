#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interfacepage.h"
#include "operationcallpage.h"
#include "projectpage.h"
#include "preferencesdialog.h"
#include "soapclient.h"
#include "workspacemodel.h"
#include "xmlparser.h"

#include <algorithm>
#include <KLocalizedString>
#include <QApplication>
#include <QList>
#include <QNetworkReply>
#include <QPair>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto soapClient = QCoreApplication::instance()->property("soapClient").value<SoapClient*>();
    connect(soapClient, &SoapClient::soapRequestStarted,
            this, [this]()
    {
        statusBar()->clearMessage();
        statusBar()->addWidget(ui->progressWidget);
        ui->progressWidget->show();
    });
    connect(soapClient, &SoapClient::soapRequestFinished,
            this, [this](QNetworkReply *reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            statusBar()->showMessage(i18n("Request completed successfully"), 2000);
        }
        else if (reply->error() == QNetworkReply::OperationCanceledError)
        {
            statusBar()->clearMessage();
        }
        else
        {
            statusBar()->showMessage(i18n("An error occured: %1").arg(reply->errorString()), 0);
        }
        statusBar()->removeWidget(ui->progressWidget);
    });

    connect(ui->actionPreferences, &QAction::triggered,
            this, &MainWindow::showPreferencesDialog);
    connect(ui->projectsTreeView, &QAbstractItemView::activated,
            this, &MainWindow::selectWorkspaceModelItem);

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
    for (auto &projectEntry: workspace.projects)
    {
        if (projectEntry.closed)
        {
            projectEntry.data = std::nullopt;
        }
        else
        {
            auto project = xml::parseProjectFile(projectEntry.path);
            projectEntry.closed = !project.has_value();
            projectEntry.remote = projectEntry.closed;
            for (auto &interface: project->interfaces)
            {
                std::sort(interface.operations.begin(), interface.operations.end(), [](data::Operation a, data::Operation b) { return a.name < b.name; });
            }
            std::sort(project->interfaces.begin(), project->interfaces.end(), [](data::Interface a, data::Interface b) { return a.name < b.name; });
            projectEntry.data = project;
        }
    }
    std::sort(workspace.projects.begin(), workspace.projects.end(), [](data::ProjectEntry a, data::ProjectEntry b) { return a.name < b.name; });
    projectsModel->setWorkspace(workspace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectWorkspaceModelItem(const QModelIndex &index)
{
    QWidget *previousPage = ui->mainContentWidgetLayout->itemAtPosition(0, 1)->widget();
    QWidget *nextPage;
    if (index.isValid())
    {
        const auto entryData = index.data(Qt::UserRole).value<WorkspaceModel::NodeData>();
        switch (entryData.kind)
        {
        case WorkspaceModel::NodeData::PROJECT:
            nextPage = new ProjectPage(ui->mainContentWidget);
            break;
        case WorkspaceModel::NodeData::INTERFACE:
            nextPage = new InterfacePage(ui->mainContentWidget);
            break;
        case WorkspaceModel::NodeData::OPERATION:
            nextPage = new QWidget(ui->mainContentWidget);
            break;
        case WorkspaceModel::NodeData::OPERATION_CALL:
        {
            nextPage = new OperationCallPage(ui->mainContentWidget);
            static_cast<OperationCallPage*>(nextPage)->initialize(
                        entryData.interface,
                        entryData.operation,
                        entryData.operationCall);
            break;
        }
        }
    }
    else
    {
        nextPage = new QWidget(ui->mainContentWidget);
    }

    QLayoutItem *replacedItem = ui->mainContentWidgetLayout->replaceWidget(previousPage, nextPage);
    delete replacedItem;
    previousPage->deleteLater();
    statusBar()->clearMessage();
}

void MainWindow::showPreferencesDialog()
{
    PreferencesDialog preferencesDialog(this);
    preferencesDialog.setPreferences(this->preferences);
    preferencesDialog.exec();
}
