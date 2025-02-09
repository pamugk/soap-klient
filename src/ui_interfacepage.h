#ifndef UI_INTERFACEPAGE_H
#define UI_INTERFACEPAGE_H

#include <KCollapsibleGroupBox>
#include <KLocalizedString>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTableWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui
{
struct InterfacePage
{
    QLabel *wsdlUrlLabel;
    QLabel *wsdlNamespaceLabel;
    QLabel *wsdlBindingLabel;
    QLabel *wsdlSoapVersionLabel;
    QLabel *wsdlStyleLabel;
    QLabel *wsdlWsaVersionLabel;
    QFormLayout *definitionPartsFormLayout;
    QTableWidget *endpointsTableWidget;

    void setupUi(QWidget *implementation)
    {
        implementation->setLayout(new QVBoxLayout(implementation));
        auto contentTabWidget = new QTabWidget(implementation);

        auto overviewPage = new QWidget(contentTabWidget);
        overviewPage->setLayout(new QVBoxLayout(overviewPage));
        auto overviewPageScrollArea = new QScrollArea(overviewPage);
        auto overviewPageScrollAreaContentWidget = new QWidget(overviewPageScrollArea);
        overviewPageScrollAreaContentWidget->setLayout(new QVBoxLayout(overviewPageScrollArea));
        auto wsdlDefinitionCollapsibleGroupBox = new KCollapsibleGroupBox(overviewPageScrollAreaContentWidget);
        wsdlDefinitionCollapsibleGroupBox->setTitle(i18n("WSDL Definition"));
        auto wsdlDefinitionFormLayout = new QFormLayout(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        wsdlDefinitionCollapsibleGroupBox->setLayout(wsdlDefinitionFormLayout);
        wsdlDefinitionFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("WSDL URL"), wsdlDefinitionCollapsibleGroupBox));
        wsdlUrlLabel = new QLabel(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setWidget(0, QFormLayout::FieldRole, wsdlUrlLabel);
        wsdlDefinitionFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Namespace"), wsdlDefinitionCollapsibleGroupBox));
        wsdlNamespaceLabel = new QLabel(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setWidget(1, QFormLayout::FieldRole, wsdlNamespaceLabel);
        wsdlDefinitionFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Binding"), wsdlDefinitionCollapsibleGroupBox));
        wsdlBindingLabel = new QLabel(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setWidget(2, QFormLayout::FieldRole, wsdlBindingLabel);
        wsdlDefinitionFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("SOAP Version"), wsdlDefinitionCollapsibleGroupBox));
        wsdlSoapVersionLabel = new QLabel(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setWidget(3, QFormLayout::FieldRole, wsdlSoapVersionLabel);
        wsdlDefinitionFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Style"), wsdlDefinitionCollapsibleGroupBox));
        wsdlStyleLabel = new QLabel(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setWidget(4, QFormLayout::FieldRole, wsdlStyleLabel);
        wsdlDefinitionFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("WS-A version"), wsdlDefinitionCollapsibleGroupBox));
        wsdlWsaVersionLabel = new QLabel(wsdlDefinitionCollapsibleGroupBox);
        wsdlDefinitionFormLayout->setWidget(5, QFormLayout::FieldRole, wsdlWsaVersionLabel);
        overviewPageScrollAreaContentWidget->layout()->addWidget(wsdlDefinitionCollapsibleGroupBox);
        auto definitionPartsCollapsibleGroupBox = new KCollapsibleGroupBox(overviewPageScrollAreaContentWidget);
        definitionPartsCollapsibleGroupBox->setTitle(i18n("Definition Parts"));
        definitionPartsFormLayout = new QFormLayout(definitionPartsCollapsibleGroupBox);
        definitionPartsFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        definitionPartsCollapsibleGroupBox->setLayout(definitionPartsFormLayout);
        overviewPageScrollAreaContentWidget->layout()->addWidget(definitionPartsCollapsibleGroupBox);
        auto operationsCollapsibleGroupBox = new KCollapsibleGroupBox(overviewPageScrollAreaContentWidget);
        operationsCollapsibleGroupBox->setTitle(i18n("Operations"));
        overviewPageScrollAreaContentWidget->layout()->addWidget(operationsCollapsibleGroupBox);
        contentTabWidget->addTab(overviewPage, i18n("Overview"));

        auto endpointsPage = new QWidget(contentTabWidget);
        endpointsPage->setLayout(new QVBoxLayout(endpointsPage));
        auto endpointsPageHeaderWidget = new QWidget(endpointsPage);
        endpointsPageHeaderWidget->setLayout(new QHBoxLayout(endpointsPageHeaderWidget));
        endpointsPage->layout()->addWidget(endpointsPageHeaderWidget);
        endpointsTableWidget = new QTableWidget(0, 9, endpointsPage);
        endpointsTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(i18n("Endpoint")));
        endpointsTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(i18n("Username")));
        endpointsTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(i18n("Password")));
        endpointsTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(i18n("Domain")));
        endpointsTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(i18n("WSS-Type")));
        endpointsTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(i18n("WSS-TimeTotal")));
        endpointsTableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem(i18n("Outgoing WSS")));
        endpointsTableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem(i18n("Incoming WSS")));
        endpointsTableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem(i18n("Mode")));
        endpointsPage->layout()->addWidget(endpointsTableWidget);
        contentTabWidget->addTab(endpointsPage, i18n("Service Endpoints"));

        auto wsdlPage = new QWidget(contentTabWidget);
        wsdlPage->setLayout(new QVBoxLayout(wsdlPage));
        contentTabWidget->addTab(wsdlPage, i18n("WSDL Content"));

        auto wsiPage = new QWidget(contentTabWidget);
        wsiPage->setLayout(new QVBoxLayout(wsiPage));
        contentTabWidget->addTab(wsiPage, i18n("WS-I Compliance"));

        implementation->layout()->addWidget(contentTabWidget);
    }
};
}

#endif // UI_INTERFACEPAGE_H
