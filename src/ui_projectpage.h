#ifndef UI_PROJECTPAGE_H
#define UI_PROJECTPAGE_H

#include <KCollapsibleGroupBox>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui
{
struct ProjectPage
{
    QLabel *projectPathLabel;
    QFormLayout *interfaceSummaryFormLayout;

    void setupUi(QWidget *implementation)
    {
        implementation->setLayout(new QVBoxLayout(implementation));
        auto contentTabWidget = new QTabWidget(implementation);

        auto overviewPage = new QWidget(contentTabWidget);
        overviewPage->setLayout(new QVBoxLayout(overviewPage));
        auto overviewPageScrollArea = new QScrollArea(overviewPage);
        auto overviewPageScrollAreaContentWidget = new QWidget(overviewPageScrollArea);
        overviewPageScrollAreaContentWidget->setLayout(new QVBoxLayout(overviewPageScrollAreaContentWidget));
        auto projectSummaryCollapsibleGroupBox = new KCollapsibleGroupBox(overviewPageScrollAreaContentWidget);
        projectSummaryCollapsibleGroupBox->setTitle(i18n("Project Summary"));
        auto projectSummaryFormLayout = new QFormLayout(projectSummaryCollapsibleGroupBox);
        projectSummaryFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        projectSummaryCollapsibleGroupBox->setLayout(projectSummaryFormLayout);
        projectSummaryFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("File Path"), projectSummaryCollapsibleGroupBox));
        projectPathLabel = new QLabel(projectSummaryCollapsibleGroupBox);
        projectSummaryFormLayout->setWidget(0, QFormLayout::FieldRole, projectPathLabel);
        overviewPageScrollAreaContentWidget->layout()->addWidget(projectSummaryCollapsibleGroupBox);
        auto interfaceSummaryCollapsibleGroupBox = new KCollapsibleGroupBox(overviewPageScrollAreaContentWidget);
        interfaceSummaryCollapsibleGroupBox->setTitle(i18n("Interface Summary"));
        interfaceSummaryFormLayout = new QFormLayout(interfaceSummaryCollapsibleGroupBox);
        interfaceSummaryFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        interfaceSummaryCollapsibleGroupBox->setLayout(interfaceSummaryFormLayout);
        overviewPageScrollAreaContentWidget->layout()->addWidget(interfaceSummaryCollapsibleGroupBox);
        overviewPageScrollArea->setWidget(overviewPageScrollAreaContentWidget);
        overviewPage->layout()->addWidget(overviewPageScrollArea);
        contentTabWidget->addTab(overviewPage, i18n("Overview"));

        implementation->layout()->addWidget(contentTabWidget);
    }
};
}

#endif // UI_PROJECTPAGE_H
