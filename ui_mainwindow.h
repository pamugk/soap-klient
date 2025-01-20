#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <KHelpMenu>
#include <KLocalizedString>
#include <KXmlGuiWindow>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStackedWidget>
#include <QProgressBar>
#include <QStatusBar>
#include <QTreeView>
#include <QVBoxLayout>

namespace Ui
{
struct MainWindow
{
    QAction *actionPreferences;
    QMenu *menuRecentProjects;
    QMenu *menuRecentWorkspaces;
    QWidget *mainContentWidget;
    QGridLayout *mainContentWidgetLayout;
    QTreeView *projectsTreeView;

    QWidget *progressWidget;

    void setupUi(KXmlGuiWindow *implementation)
    {
        implementation->resize(1024, 768);
        implementation->setWindowTitle(i18n("SOAP Klient"));

        auto menuBar = new QMenuBar(implementation);
        auto menuFile = menuBar->addMenu(i18n("File"));
        menuFile->addAction(i18n("Create empty project"));
        menuFile->addAction(i18n("New SOAP Project"), QKeySequence(Qt::CTRL | Qt::Key_N));
        menuFile->addSeparator();
        menuFile->addAction(i18n("Import Project"), QKeySequence(Qt::CTRL | Qt::Key_I));
        menuFile->addAction(i18n("Import Packed Project"));
        menuFile->addSeparator();
        menuFile->addAction(i18n("Save All Projects"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_S));
        menuFile->addAction(i18n("Open All Closed Projects"));
        menuFile->addAction(i18n("Close All Open Projects"));
        menuFile->addSeparator();
        menuFile->addAction(i18n("Rename Workspace"), QKeySequence(Qt::Key_F2));
        menuFile->addAction(i18n("New Workspace"));
        menuFile->addAction(i18n("Switch Workspace"));
        actionPreferences = menuFile->addAction(QIcon::fromTheme(QLatin1String("preferences-other")), i18n("Preferences"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_P));
        menuFile->addAction(i18n("Save Preferences"));
        menuFile->addAction(i18n("Import Preferences"));
        menuFile->addSeparator();

        auto menuRecent = menuFile->addMenu(i18n("Recent"));
        auto menuRecentEditors = menuFile->addMenu(i18n("Editors"));
        menuRecentEditors->addAction(i18n("empty"))->setEnabled(false);
        menuRecentEditors->addSeparator();
        menuRecentEditors->addAction(i18n("Clear items"))->setEnabled(false);
        menuRecentProjects = menuRecent->addMenu(i18n("Projects"));
        menuRecentWorkspaces = menuRecent->addMenu(i18n("Workspaces"));

        menuFile->addSeparator();
        menuFile->addAction(i18n("Exit"), QKeySequence(Qt::CTRL | Qt::Key_Q));
        menuFile->addAction(i18n("Exit Without Saving"), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q));

        auto menuProject = menuBar->addMenu(i18n("Project"));
        menuProject->addAction(i18n("Show Project View"));
        menuProject->addSeparator();
        menuProject->addAction(i18n("Add WSDL"));
        menuProject->addAction(i18n("Add WADL"));
        menuProject->addSeparator();
        menuProject->addAction(i18n("Rename"));
        menuProject->addAction(i18n("Remove"), QKeySequence(Qt::Key_Delete));
        menuProject->addAction(i18n("Reload Project"), QKeySequence(Qt::Key_F5));
        menuProject->addAction(i18n("Resolve"));
        menuProject->addAction(i18n("Close Project"));
        menuProject->addSeparator();
        menuProject->addAction(i18n("Save Project"), QKeySequence(Qt::CTRL | Qt::Key_S));
        menuProject->addAction(i18n("Save Project As"), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
        menuProject->addAction(i18n("Export Project"));

        auto menuHelp = new KHelpMenu(menuBar);
        menuBar->addMenu(menuHelp->menu());

        implementation->setMenuBar(menuBar);

        mainContentWidget = new QWidget(implementation);
        mainContentWidgetLayout = new QGridLayout(mainContentWidget);

        auto sidebarWidget = new QWidget(mainContentWidget);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidebarWidget->sizePolicy().hasHeightForWidth());
        sidebarWidget->setSizePolicy(sizePolicy);
        sidebarWidget->setMinimumSize(QSize(300, 0));
        sidebarWidget->setMaximumSize(QSize(300, 16777215));
        auto sidebarWidgetLayout = new QVBoxLayout(sidebarWidget);
        projectsTreeView = new QTreeView(sidebarWidget);
        projectsTreeView->setHeaderHidden(true);
        sidebarWidgetLayout->addWidget(projectsTreeView);
        mainContentWidgetLayout->addWidget(sidebarWidget, 0, 0);
        mainContentWidgetLayout->addWidget(new QWidget(mainContentWidget), 0, 1);
        implementation->setCentralWidget(mainContentWidget);

        implementation->setStatusBar(new QStatusBar(implementation));
        progressWidget = new QWidget(implementation->statusBar());
        progressWidget->setLayout(new QHBoxLayout(progressWidget));
        auto progressBar = new QProgressBar(progressWidget);
        progressBar->setMinimum(0);
        progressBar->setMinimumWidth(100);
        progressBar->setMaximum(0);
        progressBar->setMaximumWidth(100);
        progressWidget->layout()->addWidget(progressBar);
        auto progressLabel = new QLabel(i18n("Executing SOAP request…"), progressWidget);
        progressWidget->layout()->addWidget(progressLabel);
        progressWidget->hide();
    }
};
}

#endif // UI_MAINWINDOW_H
