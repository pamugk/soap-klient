#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <KFile>
#include <KFontRequester>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <KUrlRequester>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QRadioButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QStackedWidget>
#include <QTableWidget>
#include <QToolButton>

namespace Ui
{
struct PreferencesDialog
{
    QComboBox *httpVersionComboBox;
    QLineEdit *httpUserAgentHeaderLineEdit;
    QComboBox *httpRequestCompressionComboBox;
    QCheckBox *httpResponseCompressionCheckBox;
    QCheckBox *httpResponseDecompressionCheckBox;
    QCheckBox *httpCloseConnectionCheckBox;
    QSpinBox *httpChunkingThresholdSpinBox;
    QCheckBox *httpAuthenticateCheckBox;
    QCheckBox *httpExpectContinueCheckBox;
    QCheckBox *httpPreEncodedEndpointsCheckBox;
    QCheckBox *httpNormalizeSlashesCheckBox;
    QLineEdit *httpBindAddressLineEdit;
    QCheckBox *httpIncludeRequestTimeCheckBox;
    QCheckBox *httpIncludeResponseTimeCheckBox;
    QSpinBox *httpSocketTimeoutSpinBox;
    QSpinBox *httpMaxResponseSizeSpinBox;
    QSpinBox *httpMaxConnectionsPerHostSpinBox;
    QSpinBox *httpMaxConnectionsTotalSpinBox;
    QCheckBox *httpLeaveMockCheckBox;
    QCheckBox *httpMockLogCheckBox;
    QCheckBox *httpStartMockCheckBox;

    QButtonGroup *proxyModeButtonGroup;
    QRadioButton *proxyAutomaticRadioButton;
    QRadioButton *proxyNoneRadioButton;
    QRadioButton *proxyManualRadioButton;
    QLineEdit *proxyHostLineEdit;
    QSpinBox *proxyPortSpinBox;
    QLineEdit *proxyExcludesLineEdit;
    QLineEdit *proxyUsernameLineEdit;
    KPasswordLineEdit *proxyPasswordLineEdit;

    KUrlRequester *sslKeyStoreUrlRequester;
    KPasswordLineEdit *sslKeyStorePasswordLineEdit;
    QCheckBox *sslMockCheckBox;
    QSpinBox *sslMockPortSpinBox;
    KUrlRequester *sslMockKeyStoreUrlRequester;
    KPasswordLineEdit *sslMockPasswordLineEdit;
    KPasswordLineEdit *sslMockKeyPasswordLineEdit;
    KUrlRequester *sslMockTrustStoreUrlRequester;
    KPasswordLineEdit *sslMockTrustStorePasswordLineEdit;
    QCheckBox *sslClientAuthenticationCheckBox;

    QCheckBox *wsdlCacheCheckBox;
    QCheckBox *wsdlSampleValuesCheckBox;
    QCheckBox *wsdlTypeCommentCheckBox;
    QCheckBox *wsdlIncludeOptionalCheckBox;
    QCheckBox *wsdlPrettyPrintCheckBox;
    QCheckBox *wsdlAttachmentPartsCheckBox;
    KUrlRequester *wsdlSchemaDirectoryUrlRequester;
    QCheckBox *wsdlBindingNameCheckBox;
    QCheckBox *wsdlStrictSchemaTypesCheckBox;
    QSpinBox *wsdlCompressionSpinBox;
    QCheckBox *wsdlPrettyPrintProjectFilesCheckBox;
    QCheckBox *wsdlTrimCheckBox;
    QCheckBox *wsdlNoContentTypeValidationCheckBox;
    KEditListWidget *wsdlExcludedTypesEditListWidget;

    QCheckBox *uiCloseProjectsCheckBox;
    QCheckBox *uiOrderProjectsCheckBox;
    QCheckBox *uiOrderServicesCheckBox;
    QCheckBox *uiOrderRequestsCheckBox;
    QCheckBox *uiShowDescriptionsCheckBox;
    QCheckBox *uiSaveProjectCheckBox;
    QCheckBox *uiCreatBackupCheckBox;
    KUrlRequester *uiBackupFolderUrlRequester;
    QSpinBox *uiAutosaveIntervalSpinBox;
    QComboBox *uiDesktopTypeComboBox;
    QCheckBox *uiMostRecentPanelCheckBox;
    QCheckBox *uiNativeLookCheckBox;
    QCheckBox *uiGroovyLogCheckBox;
    QCheckBox *uiLogTabsCheckBox;
    QCheckBox *uiShowStartupPageCheckBox;
    QCheckBox *uiDisableTooltipsCheckBox;
    QCheckBox *uiNormalizeLinebreakCheckBox;
    QSpinBox *uiGargabeCollectionIntervalSpinBox;
    QSpinBox *uiRawResponseSizeSpinBox;
    QSpinBox *uiRawRequestSizeSpinBox;
    QCheckBox *uiWrapRawContentCheckBox;
    QCheckBox *uiDisableUsageStatisticsCheckBox;

    KFontRequester *editorFontFontRequester;
    QCheckBox *editorXmlLinesCheckBox;
    QCheckBox *editorGroovyLinesCheckBox;
    QCheckBox *editorAutoResizeCheckBox;
    QCheckBox *editorTabbedCheckBox;
    QCheckBox *editorValidateRequestCheckBox;
    QCheckBox *editorAbortInvalidCheckBox;
    QCheckBox *editorValidateResponseCheckBox;

    KUrlRequester *toolsJbossUrlRequester;
    KUrlRequester *toolsJaxRpcUrlRequester;
    KUrlRequester *toolsJaxWsUrlRequester;
    KUrlRequester *toolsAxis1UrlRequester;
    KUrlRequester *toolsAxis2UrlRequester;
    KUrlRequester *toolsDotnetWsdlUrlRequester;
    KUrlRequester *toolsXfireUrlRequester;
    KUrlRequester *toolsCxfUrlRequester;
    KUrlRequester *toolsAntUrlRequester;
    KUrlRequester *toolsGsoapUrlRequester;
    KUrlRequester *toolsJaxbUrlRequester;
    KUrlRequester *toolsXmlBeansUrlRequester;
    KUrlRequester *toolsJavacUrlRequester;
    KUrlRequester *toolsTcpMonUrlRequester;
    KUrlRequester *toolsWsaUrlRequester;
    KUrlRequester *toolsWadl2JavaUrlRequester;
    KUrlRequester *toolsHermesJmsUrlRequester;

    QCheckBox *wsiVerboseCheckBox;
    QComboBox *wsiProfileComboBox;
    QComboBox *wsiCorrelationComboBox;
    QCheckBox *wsiMessageEntryCheckBox;
    QCheckBox *wsiFailureMessageCheckBox;
    QCheckBox *wsiAssertionDescriptionCheckBox;
    KUrlRequester *wsiToolLocationUrlRequester;
    QCheckBox *wsiShowLogCheckBox;
    KUrlRequester *wsiOutputFolderUrlRequester;

    QCheckBox *globalPropertiesEnableOverrideCheckBox;
    QToolButton *globalPropertiesAddButton;
    QToolButton *globalPropertiesRemoveButton;
    QToolButton *globalPropertiesUpButton;
    QToolButton *globalPropertiesDownButton;
    QToolButton *globalPropertiesClearButton;
    QToolButton *globalPropertiesImportButton;
    QToolButton *globalPropertiesExportButton;
    QTableWidget *globalPropertiesTableWidget;

    KPasswordLineEdit *globalSecurityPasswordLineEdit;
    QCheckBox *globalSecurityDisableScriptsCheckBox;

    QCheckBox *wsaSoapOverrideCheckBox;
    QCheckBox *wsaDefaultRelationshipTypeCheckBox;
    QCheckBox *wsaDefaultRelatesToCheckBox;
    QCheckBox *wsaOverrideHeadersCheckBox;
    QCheckBox *wsaAddressingPolicyCheckBox;

    QToolButton *globalSensitiveInformationTokensAddButton;
    QToolButton *globalSensitiveInformationTokensRemoveButton;
    QToolButton *globalSensitiveInformationTokensUpButton;
    QToolButton *globalSensitiveInformationTokensDownButton;
    QToolButton *globalSensitiveInformationTokensClearButton;
    QToolButton *globalSensitiveInformationTokensImportButton;
    QToolButton *globalSensitiveInformationTokensExportButton;
    QTableWidget *globalSensitiveInformationTokensTableWidget;

    void setupUi(QDialog *implementation)
    {
        implementation->resize(800, 600);
        implementation->setWindowTitle(i18n("SOAP Klient Preferences"));

        auto gridLayout = new QGridLayout(implementation);
        implementation->setLayout(gridLayout);

        auto pagesListWidget = new QListWidget(implementation);
        pagesListWidget->addItems({
                                      i18n("HTTP Settings"),
                                      i18n("Proxy Settings"),
                                      i18n("SSL Settings"),
                                      i18n("WSDL Settings"),
                                      i18n("UI Settings"),
                                      i18n("Editor Settings"),
                                      i18n("Tools"),
                                      i18n("WS-I Settings"),
                                      i18n("Global Properties"),
                                      i18n("Global Security Settings"),
                                      i18n("WS-A Settings"),
                                      i18n("Global Sensitive Information Tokens"),
                                  });
        pagesListWidget->setMaximumSize(QSize(300, 16777215));
        gridLayout->addWidget(pagesListWidget, 0, 0, 1, 1);

        auto pagesStackedWidget = new QStackedWidget(implementation);

        auto httpSettingsPage = new QWidget(pagesStackedWidget);
        httpSettingsPage->setLayout(new QVBoxLayout(httpSettingsPage));
        auto httpSettingsPageScrollArea = new QScrollArea(httpSettingsPage);
        httpSettingsPageScrollArea->setWidgetResizable(true);
        auto httpSettingsPageScrollAreaWidgetContents = new QWidget(httpSettingsPage);
        auto httpSettingsPageFormLayout = new QFormLayout(httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        httpSettingsPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("HTTP Version:"), httpSettingsPageScrollAreaWidgetContents));
        httpVersionComboBox = new QComboBox(httpSettingsPageScrollAreaWidgetContents);
        httpVersionComboBox->addItem(QStringLiteral("1.0"));
        httpVersionComboBox->addItem(QStringLiteral("1.1"));
        httpSettingsPageFormLayout->setWidget(0, QFormLayout::FieldRole, httpVersionComboBox);
        httpSettingsPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("User-Agent Header:"), httpSettingsPageScrollAreaWidgetContents));
        httpUserAgentHeaderLineEdit = new QLineEdit(httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(1, QFormLayout::FieldRole, httpUserAgentHeaderLineEdit);
        httpSettingsPageFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Request compression:"), httpSettingsPageScrollAreaWidgetContents));
        httpRequestCompressionComboBox = new QComboBox(httpSettingsPageScrollAreaWidgetContents);
        httpRequestCompressionComboBox->addItem(i18n("None"), QStringLiteral("None"));
        httpRequestCompressionComboBox->addItem(i18n("gzip"), QStringLiteral("gzip"));
        httpRequestCompressionComboBox->addItem(i18n("deflate"), QStringLiteral("deflate"));
        httpSettingsPageFormLayout->setWidget(2, QFormLayout::FieldRole, httpRequestCompressionComboBox);
        httpSettingsPageFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Response compression:"), httpSettingsPageScrollAreaWidgetContents));
        httpResponseCompressionCheckBox = new QCheckBox(i18n("Accept compressed responses from host"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(3, QFormLayout::FieldRole, httpResponseCompressionCheckBox);
        httpSettingsPageFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Disable Response Decompression:"), httpSettingsPageScrollAreaWidgetContents));
        httpResponseDecompressionCheckBox = new QCheckBox(i18n("Disable decompression of compressed responses"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(4, QFormLayout::FieldRole, httpResponseDecompressionCheckBox);
        httpSettingsPageFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Close connections after request:"), httpSettingsPageScrollAreaWidgetContents));
        httpCloseConnectionCheckBox = new QCheckBox(i18n("Close the HTTP connection after each SOAP request"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(5, QFormLayout::FieldRole, httpCloseConnectionCheckBox);
        httpSettingsPageFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("Chunking Threshold:"), httpSettingsPageScrollAreaWidgetContents));
        httpChunkingThresholdSpinBox = new QSpinBox(httpSettingsPageScrollAreaWidgetContents);
        httpChunkingThresholdSpinBox->setMaximum(2147483647);
        httpSettingsPageFormLayout->setWidget(6, QFormLayout::FieldRole, httpChunkingThresholdSpinBox);
        httpSettingsPageFormLayout->setWidget(7, QFormLayout::LabelRole,  new QLabel(i18n("Authenticate Preemptively:"), httpSettingsPageScrollAreaWidgetContents));
        httpAuthenticateCheckBox = new QCheckBox(i18n("Adds authentication information to outgoing request"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(7, QFormLayout::FieldRole, httpAuthenticateCheckBox);
        httpSettingsPageFormLayout->setWidget(8, QFormLayout::LabelRole, new QLabel(i18n("Expect-Continue:"), httpSettingsPageScrollAreaWidgetContents));
        httpExpectContinueCheckBox = new QCheckBox(i18n("Adds Expect-Continue header to outgoing request"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(8, QFormLayout::FieldRole, httpExpectContinueCheckBox);
        httpSettingsPageFormLayout->setWidget(9, QFormLayout::LabelRole, new QLabel(i18n("Pre-encoded Endpoints:"), httpSettingsPageScrollAreaWidgetContents));
        httpPreEncodedEndpointsCheckBox = new QCheckBox(i18n("URI contains encoded endpoints, don't try to re-encode"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(9, QFormLayout::FieldRole, httpPreEncodedEndpointsCheckBox);
        httpSettingsPageFormLayout->setWidget(10, QFormLayout::LabelRole, new QLabel(i18n("Normalize Forward Slashes:"), httpSettingsPageScrollAreaWidgetContents));
        httpNormalizeSlashesCheckBox = new QCheckBox(i18n("Replaces duplicate forward slashes in HTTP request endpoints with a single slash"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(10, QFormLayout::FieldRole, httpNormalizeSlashesCheckBox);
        httpSettingsPageFormLayout->setWidget(11, QFormLayout::LabelRole, new QLabel(i18n("Bind Address:"), httpSettingsPageScrollAreaWidgetContents));
        httpBindAddressLineEdit = new QLineEdit(httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(11, QFormLayout::FieldRole, httpBindAddressLineEdit);
        httpSettingsPageFormLayout->setWidget(12, QFormLayout::LabelRole, new QLabel(i18n("Include request in time taken:"), httpSettingsPageScrollAreaWidgetContents));
        httpIncludeRequestTimeCheckBox = new QCheckBox(i18n("Includes the time it took to write the request in time-taken"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(12, QFormLayout::FieldRole, httpIncludeRequestTimeCheckBox);
        httpSettingsPageFormLayout->setWidget(13, QFormLayout::LabelRole, new QLabel(i18n("Include response in time taken:"), httpSettingsPageScrollAreaWidgetContents));
        httpIncludeResponseTimeCheckBox = new QCheckBox(i18n("Includes the time it took to read the entire response in time-taken"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(13, QFormLayout::FieldRole, httpIncludeResponseTimeCheckBox);
        httpSettingsPageFormLayout->setWidget(14, QFormLayout::LabelRole, new QLabel(i18n("Socket timeout (ms):"), httpSettingsPageScrollAreaWidgetContents));
        httpSocketTimeoutSpinBox = new QSpinBox(httpSettingsPageScrollAreaWidgetContents);
        httpSocketTimeoutSpinBox->setMaximum(3600);
        httpSettingsPageFormLayout->setWidget(14, QFormLayout::FieldRole, httpSocketTimeoutSpinBox);
        httpSettingsPageFormLayout->setWidget(15, QFormLayout::LabelRole, new QLabel(i18n("Max response size:"), httpSettingsPageScrollAreaWidgetContents));
        httpMaxResponseSizeSpinBox = new QSpinBox(httpSettingsPageScrollAreaWidgetContents);
        httpMaxResponseSizeSpinBox->setMaximum(2147483647);
        httpSettingsPageFormLayout->setWidget(15, QFormLayout::FieldRole, httpMaxResponseSizeSpinBox);
        httpSettingsPageFormLayout->setWidget(16, QFormLayout::LabelRole, new QLabel(i18n("Max Connections Per Host:"), httpSettingsPageScrollAreaWidgetContents));
        httpMaxConnectionsPerHostSpinBox = new QSpinBox(httpSettingsPageScrollAreaWidgetContents);
        httpMaxConnectionsPerHostSpinBox->setMaximum(2147483647);
        httpSettingsPageFormLayout->setWidget(16, QFormLayout::FieldRole, httpMaxConnectionsPerHostSpinBox);
        httpSettingsPageFormLayout->setWidget(17, QFormLayout::LabelRole, new QLabel(i18n("Max Total Connections:"), httpSettingsPageScrollAreaWidgetContents));
        httpMaxConnectionsTotalSpinBox = new QSpinBox(httpSettingsPageScrollAreaWidgetContents);
        httpMaxConnectionsTotalSpinBox->setMaximum(2147483647);
        httpSettingsPageFormLayout->setWidget(17, QFormLayout::FieldRole, httpMaxConnectionsTotalSpinBox);
        httpSettingsPageFormLayout->setWidget(18, QFormLayout::LabelRole, new QLabel(i18n("Leave MockEngine:"), httpSettingsPageScrollAreaWidgetContents));
        httpLeaveMockCheckBox = new QCheckBox(i18n("Leave MockEngine running when stopping MockService"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(18, QFormLayout::FieldRole, httpLeaveMockCheckBox);
        httpSettingsPageFormLayout->setWidget(19, QFormLayout::LabelRole, new QLabel(i18n("Enable Mock HTTP Log:"), httpSettingsPageScrollAreaWidgetContents));
        httpMockLogCheckBox = new QCheckBox(i18n("Logs wire content of all mock requests"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(19, QFormLayout::FieldRole, httpMockLogCheckBox);
        httpSettingsPageFormLayout->setWidget(20, QFormLayout::LabelRole, new QLabel(i18n("Start REST MockService:"), httpSettingsPageScrollAreaWidgetContents));
        httpStartMockCheckBox = new QCheckBox(i18n("Start REST MockService after creation"), httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPageFormLayout->setWidget(20, QFormLayout::FieldRole, httpStartMockCheckBox);
        httpSettingsPageScrollArea->setWidget(httpSettingsPageScrollAreaWidgetContents);
        httpSettingsPage->layout()->addWidget(httpSettingsPageScrollArea);
        pagesStackedWidget->addWidget(httpSettingsPage);

        auto proxySettingsPage = new QWidget(pagesStackedWidget);
        proxySettingsPage->setLayout(new QVBoxLayout(proxySettingsPage));
        auto proxySettingsPageScrollArea = new QScrollArea(proxySettingsPage);
        proxySettingsPageScrollArea->setWidgetResizable(true);
        auto proxySettingsPageScrollAreaWidgetContents = new QWidget(proxySettingsPageScrollArea);
        auto proxySettingsPageFormLayout = new QFormLayout(proxySettingsPageScrollAreaWidgetContents);
        proxySettingsPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        proxySettingsPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Proxy Setting:"), proxySettingsPageScrollAreaWidgetContents));
        proxyModeButtonGroup = new QButtonGroup(implementation);
        auto proxyModeGroup = new QWidget(proxySettingsPageScrollAreaWidgetContents);
        proxyModeGroup->setLayout(new QVBoxLayout(proxyModeGroup));
        proxyAutomaticRadioButton = new QRadioButton(i18n("Automatic"), proxyModeGroup);
        proxyModeButtonGroup->addButton(proxyAutomaticRadioButton);
        proxyModeGroup->layout()->addWidget(proxyAutomaticRadioButton);
        proxyNoneRadioButton = new QRadioButton(i18n("None"), proxyModeGroup);
        proxyModeButtonGroup->addButton(proxyNoneRadioButton);
        proxyModeGroup->layout()->addWidget(proxyNoneRadioButton);
        proxyManualRadioButton = new QRadioButton(i18n("Manual"), proxyModeGroup);
        proxyModeButtonGroup->addButton(proxyManualRadioButton);
        proxyModeGroup->layout()->addWidget(proxyManualRadioButton);
        proxySettingsPageFormLayout->setWidget(0, QFormLayout::FieldRole, proxyModeGroup);
        proxyHostLineEdit = new QLineEdit(proxySettingsPageScrollAreaWidgetContents);
        proxySettingsPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Host:"), proxySettingsPageScrollAreaWidgetContents));
        proxySettingsPageFormLayout->setWidget(1, QFormLayout::FieldRole, proxyHostLineEdit);
        proxySettingsPageFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Port:"), proxySettingsPageScrollAreaWidgetContents));
        proxyPortSpinBox = new QSpinBox(proxySettingsPageScrollAreaWidgetContents);
        proxyPortSpinBox->setMaximum(65535);
        proxySettingsPageFormLayout->setWidget(2, QFormLayout::FieldRole, proxyPortSpinBox);
        proxySettingsPageFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Excludes:"), proxySettingsPageScrollAreaWidgetContents));
        proxyExcludesLineEdit = new QLineEdit(proxySettingsPageScrollAreaWidgetContents);
        proxySettingsPageFormLayout->setWidget(3, QFormLayout::FieldRole, proxyExcludesLineEdit);
        proxySettingsPageFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Username:"), proxySettingsPageScrollAreaWidgetContents));
        proxyUsernameLineEdit = new QLineEdit(proxySettingsPageScrollAreaWidgetContents);
        proxySettingsPageFormLayout->setWidget(4, QFormLayout::FieldRole, proxyUsernameLineEdit);
        proxySettingsPageFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Password:"), proxySettingsPageScrollAreaWidgetContents));
        proxyPasswordLineEdit = new KPasswordLineEdit(proxySettingsPageScrollAreaWidgetContents);
        proxySettingsPageFormLayout->setWidget(5, QFormLayout::FieldRole, proxyPasswordLineEdit);
        proxySettingsPageScrollArea->setWidget(proxySettingsPageScrollAreaWidgetContents);
        proxySettingsPage->layout()->addWidget(proxySettingsPageScrollArea);
        pagesStackedWidget->addWidget(proxySettingsPage);

        auto sslSettingsPage = new QWidget(pagesStackedWidget);
        sslSettingsPage->setLayout(new QVBoxLayout(sslSettingsPage));
        auto sslSettingsPageScrollArea = new QScrollArea(sslSettingsPage);
        sslSettingsPageScrollArea->setWidgetResizable(true);
        auto sslSettingsPageScrollAreaWidgetContents = new QWidget(sslSettingsPageScrollArea);
        auto sslSettingsPageFormLayout = new QFormLayout(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        sslSettingsPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("KeyStore:"), sslSettingsPageScrollAreaWidgetContents));
        sslKeyStoreUrlRequester = new KUrlRequester(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(0, QFormLayout::FieldRole, sslKeyStoreUrlRequester);
        sslSettingsPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("KeyStore Password:"), sslSettingsPageScrollAreaWidgetContents));
        sslKeyStorePasswordLineEdit = new KPasswordLineEdit(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(1, QFormLayout::FieldRole, sslKeyStorePasswordLineEdit);
        sslSettingsPageFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Enable Mock SSL:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockCheckBox = new QCheckBox(i18n("enable SSL for Mock Services"), sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(2, QFormLayout::FieldRole, sslMockCheckBox);
        sslSettingsPageFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Mock Port:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockPortSpinBox = new QSpinBox(sslSettingsPageScrollAreaWidgetContents);
        sslMockPortSpinBox->setMaximum(65535);
        sslSettingsPageFormLayout->setWidget(3, QFormLayout::FieldRole, sslMockPortSpinBox);
        sslSettingsPageFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Mock KeyStore:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockKeyStoreUrlRequester = new KUrlRequester(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(4, QFormLayout::FieldRole, sslMockKeyStoreUrlRequester);
        sslSettingsPageFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Mock Password:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockPasswordLineEdit = new KPasswordLineEdit(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(5, QFormLayout::FieldRole, sslMockPasswordLineEdit);
        sslSettingsPageFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("Mock Key Password:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockKeyPasswordLineEdit = new KPasswordLineEdit(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(6, QFormLayout::FieldRole, sslMockKeyPasswordLineEdit);
        sslSettingsPageFormLayout->setWidget(7, QFormLayout::LabelRole, new QLabel(i18n("Mock TrustStore:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockTrustStoreUrlRequester = new KUrlRequester(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(7, QFormLayout::FieldRole, sslMockTrustStoreUrlRequester);
        sslSettingsPageFormLayout->setWidget(8, QFormLayout::LabelRole, new QLabel(i18n("Mock TrustStore Password:"), sslSettingsPageScrollAreaWidgetContents));
        sslMockTrustStorePasswordLineEdit = new KPasswordLineEdit(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(8, QFormLayout::FieldRole, sslMockTrustStorePasswordLineEdit);
        sslSettingsPageFormLayout->setWidget(9, QFormLayout::LabelRole, new QLabel(i18n("Client Authentication:"), sslSettingsPageScrollAreaWidgetContents));
        sslClientAuthenticationCheckBox = new QCheckBox(i18n("requires client authentication"), sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPageFormLayout->setWidget(9, QFormLayout::FieldRole, sslClientAuthenticationCheckBox);
        sslSettingsPageScrollArea->setWidget(sslSettingsPageScrollAreaWidgetContents);
        sslSettingsPage->layout()->addWidget(sslSettingsPageScrollArea);
        pagesStackedWidget->addWidget(sslSettingsPage);

        auto wsdlSettingsPage = new QWidget(pagesStackedWidget);
        wsdlSettingsPage->setLayout(new QVBoxLayout(wsdlSettingsPage));
        auto wsdlSettingsPageScrollArea = new QScrollArea(wsdlSettingsPage);
        wsdlSettingsPageScrollArea->setWidgetResizable(true);
        auto wsdlSettingsPageScrollAreaWidgetContents = new QWidget(wsdlSettingsPageScrollArea);
        auto wsdlSettingsFormLayout = new QFormLayout(wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        wsdlSettingsFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Cache WSDLs:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlCacheCheckBox = new QCheckBox(i18n("caches and associates WSDLs locally for offline access and improved performance"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(0, QFormLayout::FieldRole, wsdlCacheCheckBox);
        wsdlSettingsFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Sample Values:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlSampleValuesCheckBox = new QCheckBox(i18n("generate example values in new requests"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(1, QFormLayout::FieldRole, wsdlSampleValuesCheckBox);
        wsdlSettingsFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Type Comment:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlTypeCommentCheckBox = new QCheckBox(i18n("generate comments with type information in new requests"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(2, QFormLayout::FieldRole, wsdlTypeCommentCheckBox);
        wsdlSettingsFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Include Optional:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlIncludeOptionalCheckBox = new QCheckBox(i18n("always include optional schema elements when creating requests"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(3, QFormLayout::FieldRole, wsdlIncludeOptionalCheckBox);
        wsdlSettingsFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Pretty Print:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlPrettyPrintCheckBox = new QCheckBox(i18n("pretty print response messages"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(4, QFormLayout::FieldRole, wsdlPrettyPrintCheckBox);
        wsdlSettingsFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Attachment Parts:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlAttachmentPartsCheckBox = new QCheckBox(i18n("generate rpc message parts for attachments"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(5, QFormLayout::FieldRole, wsdlAttachmentPartsCheckBox);
        wsdlSettingsFormLayout->setWidget(7, QFormLayout::LabelRole, new QLabel(i18n("Schema Directory:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlSchemaDirectoryUrlRequester = new KUrlRequester(wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(7, QFormLayout::FieldRole, wsdlSchemaDirectoryUrlRequester);
        wsdlSettingsFormLayout->setWidget(8, QFormLayout::LabelRole, new QLabel(i18n("Name with Binding:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlBindingNameCheckBox = new QCheckBox(i18n("uses the WSDL binding name (instead of portType) for imported interfaces"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(8, QFormLayout::FieldRole, wsdlBindingNameCheckBox);
        wsdlSettingsFormLayout->setWidget(10, QFormLayout::LabelRole, new QLabel(i18n("Strict schema types:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlStrictSchemaTypesCheckBox = new QCheckBox(i18n("fails schema imports if type/particles are redefined"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(10, QFormLayout::FieldRole, wsdlStrictSchemaTypesCheckBox);
        wsdlSettingsFormLayout->setWidget(11, QFormLayout::LabelRole, new QLabel(i18n("Compression Limit:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlCompressionSpinBox = new QSpinBox(wsdlSettingsPageScrollAreaWidgetContents);
        wsdlCompressionSpinBox->setMaximum(2147483647);
        wsdlSettingsFormLayout->setWidget(11, QFormLayout::FieldRole, wsdlCompressionSpinBox);
        wsdlSettingsFormLayout->setWidget(12, QFormLayout::LabelRole, new QLabel(i18n("Pretty Print Project Files:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlPrettyPrintProjectFilesCheckBox = new QCheckBox(i18n("pretty prints project files"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(12, QFormLayout::FieldRole, wsdlPrettyPrintProjectFilesCheckBox);
        wsdlSettingsFormLayout->setWidget(13, QFormLayout::LabelRole, new QLabel(i18n("Trim WSDL:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlTrimCheckBox = new QCheckBox(i18n("Trims leading and trailing whitespaces from WSDL file (might not work on non 8 bit encoding)"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(13, QFormLayout::FieldRole, wsdlTrimCheckBox);
        wsdlSettingsFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("No Content-Type Validation:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlNoContentTypeValidationCheckBox = new QCheckBox(i18n("allow incorrect content-types in mime-attachments"), wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsFormLayout->setWidget(6, QFormLayout::FieldRole, wsdlNoContentTypeValidationCheckBox);
        wsdlSettingsFormLayout->setWidget(9, QFormLayout::LabelRole, new QLabel(i18n("Excluded types:"), wsdlSettingsPageScrollAreaWidgetContents));
        wsdlExcludedTypesEditListWidget = new KEditListWidget(wsdlSettingsPageScrollAreaWidgetContents);
        wsdlExcludedTypesEditListWidget->setButtons(KEditListWidget::Button::Add|KEditListWidget::Button::Remove);
        wsdlSettingsFormLayout->setWidget(9, QFormLayout::FieldRole, wsdlExcludedTypesEditListWidget);
        wsdlSettingsPageScrollArea->setWidget(wsdlSettingsPageScrollAreaWidgetContents);
        wsdlSettingsPage->layout()->addWidget(wsdlSettingsPageScrollArea);
        pagesStackedWidget->addWidget(wsdlSettingsPage);

        auto uiSettingsPage = new QWidget(pagesStackedWidget);
        uiSettingsPage->setLayout(new QVBoxLayout(uiSettingsPage));
        auto uiSettingsPageScrollArea = new QScrollArea(uiSettingsPage);
        uiSettingsPageScrollArea->setWidgetResizable(true);
        auto uiSettingsPageScrollAreaWidgetContents = new QWidget(uiSettingsPageScrollArea);
        auto uiSettingsFormLayout = new QFormLayout(uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        uiSettingsFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Close Projects:"), uiSettingsPageScrollAreaWidgetContents));
        uiCloseProjectsCheckBox = new QCheckBox(i18n("Close all projects on startup"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(0, QFormLayout::FieldRole, uiCloseProjectsCheckBox);
        uiSettingsFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Order Projects:"), uiSettingsPageScrollAreaWidgetContents));
        uiOrderProjectsCheckBox = new QCheckBox(i18n("Order Projects alphabetically in tree"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(1, QFormLayout::FieldRole, uiOrderProjectsCheckBox);
        uiSettingsFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Order Services:"), uiSettingsPageScrollAreaWidgetContents));
        uiOrderServicesCheckBox = new QCheckBox(i18n("Order Services alphabetically in tree"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(2, QFormLayout::FieldRole, uiOrderServicesCheckBox);
        uiSettingsFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Order Requests:"), uiSettingsPageScrollAreaWidgetContents));
        uiOrderRequestsCheckBox = new QCheckBox(i18n("Order Requests alphabetically in tree"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(3, QFormLayout::FieldRole, uiOrderRequestsCheckBox);
        uiSettingsFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Show Descriptions:"), uiSettingsPageScrollAreaWidgetContents));
        uiShowDescriptionsCheckBox = new QCheckBox(i18n("Show description content when available"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(4, QFormLayout::FieldRole, uiShowDescriptionsCheckBox);
        uiSettingsFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Save projects on exit:"), uiSettingsPageScrollAreaWidgetContents));
        uiSaveProjectCheckBox = new QCheckBox(i18n("Save all projects on exit"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(5, QFormLayout::FieldRole, uiSaveProjectCheckBox);
        uiSettingsFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("Create Backup:"), uiSettingsPageScrollAreaWidgetContents));
        uiCreatBackupCheckBox = new QCheckBox(i18n("Backup project files before they are saved"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(6, QFormLayout::FieldRole, uiCreatBackupCheckBox);
        uiSettingsFormLayout->setWidget(7, QFormLayout::LabelRole, new QLabel(i18n("Backup Folder:"), uiSettingsPageScrollAreaWidgetContents));
        uiBackupFolderUrlRequester = new KUrlRequester(uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(7, QFormLayout::FieldRole, uiBackupFolderUrlRequester);
        uiSettingsFormLayout->setWidget(8, QFormLayout::LabelRole, new QLabel(i18n("AutoSave Interval:"), uiSettingsPageScrollAreaWidgetContents));
        uiAutosaveIntervalSpinBox = new QSpinBox(uiSettingsPageScrollAreaWidgetContents);
        uiAutosaveIntervalSpinBox->setMaximum(2147483647);
        uiSettingsFormLayout->setWidget(8, QFormLayout::FieldRole, uiAutosaveIntervalSpinBox);
        uiSettingsFormLayout->setWidget(9, QFormLayout::LabelRole, new QLabel(i18n("Desktop Type:"), uiSettingsPageScrollAreaWidgetContents));
        uiDesktopTypeComboBox = new QComboBox(uiSettingsPageScrollAreaWidgetContents);
        uiDesktopTypeComboBox->addItem(i18n("Default"), QStringLiteral("Default"));
        uiSettingsFormLayout->setWidget(9, QFormLayout::FieldRole, uiDesktopTypeComboBox);
        uiSettingsFormLayout->setWidget(10, QFormLayout::LabelRole, new QLabel(i18n("Select most recently used desktop panel on close:"), uiSettingsPageScrollAreaWidgetContents));
        uiMostRecentPanelCheckBox = new QCheckBox(i18n("Show most recently used panel on close (requires restart)"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(10, QFormLayout::FieldRole, uiMostRecentPanelCheckBox);
        uiSettingsFormLayout->setWidget(11, QFormLayout::LabelRole, new QLabel(i18n("Native LF:"), uiSettingsPageScrollAreaWidgetContents));
        uiNativeLookCheckBox = new QCheckBox(i18n("Use native Look & Feel (requires restart)"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(11, QFormLayout::FieldRole, uiNativeLookCheckBox);
        uiSettingsFormLayout->setWidget(12, QFormLayout::LabelRole, new QLabel(i18n("Do not disable Groovy Log:"), uiSettingsPageScrollAreaWidgetContents));
        uiGroovyLogCheckBox = new QCheckBox(i18n("Do not disable the groovy log when running load tests"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(12, QFormLayout::FieldRole, uiGroovyLogCheckBox);
        uiSettingsFormLayout->setWidget(13, QFormLayout::LabelRole, new QLabel(i18n("Show Log Tabs:"), uiSettingsPageScrollAreaWidgetContents));
        uiLogTabsCheckBox = new QCheckBox(i18n("Shows log tabs when starting"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(13, QFormLayout::FieldRole, uiLogTabsCheckBox);
        uiSettingsFormLayout->setWidget(14, QFormLayout::LabelRole, new QLabel(i18n("Show Startup Page:"), uiSettingsPageScrollAreaWidgetContents));
        uiShowStartupPageCheckBox = new QCheckBox(i18n("Open startup web page when starting"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(14, QFormLayout::FieldRole, uiShowStartupPageCheckBox);
        uiSettingsFormLayout->setWidget(15, QFormLayout::LabelRole, new QLabel(i18n("Disable Tooltips:"), uiSettingsPageScrollAreaWidgetContents));
        uiDisableTooltipsCheckBox = new QCheckBox(i18n("Disables all tooltips"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(15, QFormLayout::FieldRole, uiDisableTooltipsCheckBox);
        uiSettingsFormLayout->setWidget(16, QFormLayout::LabelRole, new QLabel(i18n("Normalize line-break:"), uiSettingsPageScrollAreaWidgetContents));
        uiNormalizeLinebreakCheckBox = new QCheckBox(i18n("Normalize line-breaks when saving project"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(16, QFormLayout::FieldRole, uiNormalizeLinebreakCheckBox);
        uiSettingsFormLayout->setWidget(17, QFormLayout::LabelRole, new QLabel(i18n("Garbage Collection Interval (s):"), uiSettingsPageScrollAreaWidgetContents));
        uiGargabeCollectionIntervalSpinBox = new QSpinBox(uiSettingsPageScrollAreaWidgetContents);
        uiGargabeCollectionIntervalSpinBox->setMaximum(2147483647);
        uiSettingsFormLayout->setWidget(17, QFormLayout::FieldRole, uiGargabeCollectionIntervalSpinBox);
        uiSettingsFormLayout->setWidget(18, QFormLayout::LabelRole, new QLabel(i18n("Size of Raw Response Message to Show:"), uiSettingsPageScrollAreaWidgetContents));
        uiRawResponseSizeSpinBox = new QSpinBox(uiSettingsPageScrollAreaWidgetContents);
        uiRawResponseSizeSpinBox->setMaximum(2147483647);
        uiSettingsFormLayout->setWidget(18, QFormLayout::FieldRole, uiRawResponseSizeSpinBox);
        uiSettingsFormLayout->setWidget(19, QFormLayout::LabelRole, new QLabel(i18n("Size of Raw Request Message to Show:"), uiSettingsPageScrollAreaWidgetContents));
        uiRawRequestSizeSpinBox = new QSpinBox(uiSettingsPageScrollAreaWidgetContents);
        uiRawRequestSizeSpinBox->setMaximum(2147483647);
        uiSettingsFormLayout->setWidget(19, QFormLayout::FieldRole, uiRawRequestSizeSpinBox);
        uiSettingsFormLayout->setWidget(20, QFormLayout::LabelRole, new QLabel(i18n("Wrap content in Raw Message Viewers:"), uiSettingsPageScrollAreaWidgetContents));
        uiWrapRawContentCheckBox = new QCheckBox(i18n("Wraps content in Raw Message Viewers"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(20, QFormLayout::FieldRole, uiWrapRawContentCheckBox);
        uiSettingsFormLayout->setWidget(21, QFormLayout::LabelRole, new QLabel(i18n("Disable Usage Statistics:"), uiSettingsPageScrollAreaWidgetContents));
        uiDisableUsageStatisticsCheckBox = new QCheckBox(i18n("Do not send usage statistics"), uiSettingsPageScrollAreaWidgetContents);
        uiSettingsFormLayout->setWidget(21, QFormLayout::FieldRole, uiDisableUsageStatisticsCheckBox);
        uiSettingsPageScrollArea->setWidget(uiSettingsPageScrollAreaWidgetContents);
        uiSettingsPage->layout()->addWidget(uiSettingsPageScrollArea);
        pagesStackedWidget->addWidget(uiSettingsPage);

        auto editorSettingsPage = new QWidget(pagesStackedWidget);
        editorSettingsPage->setLayout(new QVBoxLayout(editorSettingsPage));
        auto editorSettingsPageScrollArea = new QScrollArea(editorSettingsPage);
        editorSettingsPageScrollArea->setWidgetResizable(true);
        auto editorSettingsPageScrollAreaWidgetContents = new QWidget(editorSettingsPageScrollArea);
        auto editorSettingsFormLayout = new QFormLayout(editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        editorSettingsFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Editor Font:"), editorSettingsPageScrollAreaWidgetContents));
        editorFontFontRequester = new KFontRequester(editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(0, QFormLayout::FieldRole, editorFontFontRequester);
        editorSettingsFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("XML Line Numbers:"), editorSettingsPageScrollAreaWidgetContents));
        editorXmlLinesCheckBox = new QCheckBox(i18n("Show line numbers in XML editors by default"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(1, QFormLayout::FieldRole, editorXmlLinesCheckBox);
        editorSettingsFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Groovy Line Numbers:"), editorSettingsPageScrollAreaWidgetContents));
        editorGroovyLinesCheckBox = new QCheckBox(i18n("Show line numbers in Groovy editors by default"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(2, QFormLayout::FieldRole, editorGroovyLinesCheckBox);
        editorSettingsFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Disable auto-resize:"), editorSettingsPageScrollAreaWidgetContents));
        editorAutoResizeCheckBox = new QCheckBox(i18n("Disables automatic resizing of Request editors"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(3, QFormLayout::FieldRole, editorAutoResizeCheckBox);
        editorSettingsFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Tabbed request view:"), editorSettingsPageScrollAreaWidgetContents));
        editorTabbedCheckBox = new QCheckBox(i18n("Defaults the request editor to the tabbed layout"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(4, QFormLayout::FieldRole, editorTabbedCheckBox);
        editorSettingsFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Validate Requests:"), editorSettingsPageScrollAreaWidgetContents));
        editorValidateRequestCheckBox = new QCheckBox(i18n("Always validate request messages before they are send"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(5, QFormLayout::FieldRole, editorValidateRequestCheckBox);
        editorSettingsFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("Abort on invalid:"), editorSettingsPageScrollAreaWidgetContents));
        editorAbortInvalidCheckBox = new QCheckBox(i18n("Abort invalid requests"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(6, QFormLayout::FieldRole, editorAbortInvalidCheckBox);
        editorSettingsFormLayout->setWidget(7, QFormLayout::LabelRole, new QLabel(i18n("Validate Responses:"), editorSettingsPageScrollAreaWidgetContents));
        editorValidateResponseCheckBox = new QCheckBox(i18n("Always validate response messages"), editorSettingsPageScrollAreaWidgetContents);
        editorSettingsFormLayout->setWidget(7, QFormLayout::FieldRole, editorValidateResponseCheckBox);
        editorSettingsPageScrollArea->setWidget(editorSettingsPageScrollAreaWidgetContents);
        editorSettingsPage->layout()->addWidget(editorSettingsPageScrollArea);
        pagesStackedWidget->addWidget(editorSettingsPage);

        auto toolsPage = new QWidget(pagesStackedWidget);
        toolsPage->setLayout(new QVBoxLayout(toolsPage));
        auto toolsPageScrollArea = new QScrollArea(toolsPage);
        toolsPageScrollArea->setWidgetResizable(true);
        auto toolsPageScrollAreaWidgetContents = new QWidget(toolsPageScrollArea);
        auto toolsPageFormLayout = new QFormLayout(toolsPageScrollAreaWidgetContents);
        toolsPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        toolsPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("JBossWS wstools:"), toolsPageScrollAreaWidgetContents));
        toolsJbossUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsJbossUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(0, QFormLayout::FieldRole, toolsJbossUrlRequester);
        toolsPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("JAX-RPC WSCompile:"), toolsPageScrollAreaWidgetContents));
        toolsJaxRpcUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsJaxRpcUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(1, QFormLayout::FieldRole, toolsJaxRpcUrlRequester);
        toolsPageFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("JAX-WS WSImport:"), toolsPageScrollAreaWidgetContents));
        toolsJaxWsUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsJaxWsUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(2, QFormLayout::FieldRole, toolsJaxWsUrlRequester);
        toolsPageFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Axis 1.X:"), toolsPageScrollAreaWidgetContents));
        toolsAxis1UrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsAxis1UrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(3, QFormLayout::FieldRole, toolsAxis1UrlRequester);
        toolsPageFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Axis 2:"), toolsPageScrollAreaWidgetContents));
        toolsAxis2UrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsAxis2UrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(4, QFormLayout::FieldRole, toolsAxis2UrlRequester);
        toolsPageFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n(".NET 2.0 wsdl.exe:"), toolsPageScrollAreaWidgetContents));
        toolsDotnetWsdlUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsDotnetWsdlUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(5, QFormLayout::FieldRole, toolsDotnetWsdlUrlRequester);
        toolsPageFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("XFire 1.X:"), toolsPageScrollAreaWidgetContents));
        toolsXfireUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsXfireUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(6, QFormLayout::FieldRole, toolsXfireUrlRequester);
        toolsPageFormLayout->setWidget(7, QFormLayout::LabelRole, new QLabel(i18n("CXF 2.X:"), toolsPageScrollAreaWidgetContents));
        toolsCxfUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsCxfUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(7, QFormLayout::FieldRole, toolsCxfUrlRequester);
        toolsPageFormLayout->setWidget(8, QFormLayout::LabelRole, new QLabel(i18n("ANT 1.6+"), toolsPageScrollAreaWidgetContents));
        toolsAntUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsAntUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(8, QFormLayout::FieldRole, toolsAntUrlRequester);
        toolsPageFormLayout->setWidget(9, QFormLayout::LabelRole, new QLabel(i18n("GSoap:"), toolsPageScrollAreaWidgetContents));
        toolsGsoapUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsGsoapUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(9, QFormLayout::FieldRole, toolsGsoapUrlRequester);
        toolsPageFormLayout->setWidget(10, QFormLayout::LabelRole, new QLabel(i18n("JAXB xjc:"), toolsPageScrollAreaWidgetContents));
        toolsJaxbUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsJaxbUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(10, QFormLayout::FieldRole, toolsJaxbUrlRequester);
        toolsPageFormLayout->setWidget(11, QFormLayout::LabelRole, new QLabel(i18n("XmlBeans 2.X:"), toolsPageScrollAreaWidgetContents));
        toolsXmlBeansUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsXmlBeansUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(11, QFormLayout::FieldRole, toolsXmlBeansUrlRequester);
        toolsPageFormLayout->setWidget(12, QFormLayout::LabelRole, new QLabel(i18n("JDK 1.5 javac:"), toolsPageScrollAreaWidgetContents));
        toolsJavacUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsJavacUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(12, QFormLayout::FieldRole, toolsJavacUrlRequester);
        toolsPageFormLayout->setWidget(13, QFormLayout::LabelRole, new QLabel(i18n("Apache TcpMon:"), toolsPageScrollAreaWidgetContents));
        toolsTcpMonUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsTcpMonUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(13, QFormLayout::FieldRole, toolsTcpMonUrlRequester);
        toolsPageFormLayout->setWidget(14, QFormLayout::LabelRole, new QLabel(i18n("Oracle wsa.jar:"), toolsPageScrollAreaWidgetContents));
        toolsWsaUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsWsaUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(14, QFormLayout::FieldRole, toolsWsaUrlRequester);
        toolsPageFormLayout->setWidget(15, QFormLayout::LabelRole, new QLabel(i18n("WADL2Java:"), toolsPageScrollAreaWidgetContents));
        toolsWadl2JavaUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsWadl2JavaUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(15, QFormLayout::FieldRole, toolsWadl2JavaUrlRequester);
        toolsPageFormLayout->setWidget(16, QFormLayout::LabelRole, new QLabel(i18n("Hermes JMS:"), toolsPageScrollAreaWidgetContents));
        toolsHermesJmsUrlRequester = new KUrlRequester(toolsPageScrollAreaWidgetContents);
        toolsHermesJmsUrlRequester->setMode(KFile::Mode::Directory|KFile::Mode::ExistingOnly|KFile::Mode::LocalOnly);
        toolsPageFormLayout->setWidget(16, QFormLayout::FieldRole, toolsHermesJmsUrlRequester);
        toolsPageScrollArea->setWidget(toolsPageScrollAreaWidgetContents);
        toolsPage->layout()->addWidget(toolsPageScrollArea);
        pagesStackedWidget->addWidget(toolsPage);

        auto wsiSettingsPage = new QWidget(pagesStackedWidget);
        wsiSettingsPage->setLayout(new QVBoxLayout(wsiSettingsPage));
        auto wsiSettingsPageScrollArea = new QScrollArea(wsiSettingsPage);
        wsiSettingsPageScrollArea->setWidgetResizable(true);
        auto wsiSettingsPageScrollAreaWidgetContents = new QWidget(wsiSettingsPageScrollArea);
        auto wsiSettingsPageFormLayout = new QFormLayout(wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        wsiSettingsPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Verbose:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiVerboseCheckBox = new QCheckBox(i18n("Verbose output of WSI tools"), wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(0, QFormLayout::FieldRole, wsiVerboseCheckBox);
        wsiSettingsPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Profile:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiProfileComboBox = new QComboBox(wsiSettingsPageScrollAreaWidgetContents);
        wsiProfileComboBox->addItem(QStringLiteral("BasicSecurityProfile-1.0-TAD.xml"));
        wsiProfileComboBox->addItem(QStringLiteral("BasicSecurityProfile-1.1-TAD.xml"));
        wsiSettingsPageFormLayout->setWidget(1, QFormLayout::FieldRole, wsiProfileComboBox);
        wsiSettingsPageFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Correlation:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiCorrelationComboBox = new QComboBox(wsiSettingsPageScrollAreaWidgetContents);
        wsiCorrelationComboBox->addItem(i18n("endpoint"), QStringLiteral("endpoint"));
        wsiCorrelationComboBox->addItem(i18n("namespace"), QStringLiteral("namespace"));
        wsiCorrelationComboBox->addItem(i18n("operation"), QStringLiteral("operation"));
        wsiSettingsPageFormLayout->setWidget(2, QFormLayout::FieldRole, wsiCorrelationComboBox);
        wsiSettingsPageFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Message entry:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiMessageEntryCheckBox = new QCheckBox(i18n("Message entriies should be included in the report"), wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(3, QFormLayout::FieldRole, wsiMessageEntryCheckBox);
        wsiSettingsPageFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Failure message:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiFailureMessageCheckBox = new QCheckBox(i18n("Failure message defined for each test assertion should be included in the report"), wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(4, QFormLayout::FieldRole, wsiFailureMessageCheckBox);
        wsiSettingsPageFormLayout->setWidget(5, QFormLayout::LabelRole, new QLabel(i18n("Assertion description:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiAssertionDescriptionCheckBox = new QCheckBox(i18n("Description of each test assertion should be included in the report"), wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(5, QFormLayout::FieldRole, wsiAssertionDescriptionCheckBox);
        wsiSettingsPageFormLayout->setWidget(6, QFormLayout::LabelRole, new QLabel(i18n("Tool location:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiToolLocationUrlRequester = new KUrlRequester(wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(6, QFormLayout::FieldRole, wsiToolLocationUrlRequester);
        wsiSettingsPageFormLayout->setWidget(7, QFormLayout::LabelRole, new QLabel(i18n("Show log:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiShowLogCheckBox = new QCheckBox(i18n("Show console-log for ws-i analyzer"), wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(7, QFormLayout::FieldRole, wsiShowLogCheckBox);
        wsiSettingsPageFormLayout->setWidget(8, QFormLayout::LabelRole, new QLabel(i18n("Output folder:"), wsiSettingsPageScrollAreaWidgetContents));
        wsiOutputFolderUrlRequester = new KUrlRequester(wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPageFormLayout->setWidget(8, QFormLayout::FieldRole, wsiOutputFolderUrlRequester);
        wsiSettingsPageScrollArea->setWidget(wsiSettingsPageScrollAreaWidgetContents);
        wsiSettingsPage->layout()->addWidget(wsiSettingsPageScrollArea);
        pagesStackedWidget->addWidget(wsiSettingsPage);

        auto listAddIcon = QIcon::fromTheme(QString::fromUtf8("list-add"));
        auto listRemoveIcon = QIcon::fromTheme(QString::fromUtf8("list-remove"));
        auto goUpIcon = QIcon::fromTheme(QString::fromUtf8("go-up"));
        auto goDownIcon = QIcon::fromTheme(QString::fromUtf8("go-down"));
        auto editClearIcon = QIcon::fromTheme(QString::fromUtf8("edit-clear"));
        auto documentOpenIcon = QIcon::fromTheme(QString::fromUtf8("document-open"));
        auto documentSaveAsIcon = QIcon::fromTheme(QString::fromUtf8("document-save-as"));

        auto globalPropertiesPage = new QWidget(pagesStackedWidget);
        globalPropertiesPage->setLayout(new QVBoxLayout(globalPropertiesPage));
        globalPropertiesEnableOverrideCheckBox = new QCheckBox(i18n("Enables overriding of any property-reference with global properties"), globalPropertiesPage);
        globalPropertiesPage->layout()->addWidget(globalPropertiesEnableOverrideCheckBox);
        auto globalPropertiesTableActionsWidget = new QWidget(globalPropertiesPage);
        globalPropertiesTableActionsWidget->setLayout(new QHBoxLayout(globalPropertiesTableActionsWidget));
        globalPropertiesAddButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesAddButton->setIcon(listAddIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesAddButton);
        globalPropertiesRemoveButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesRemoveButton->setIcon(listRemoveIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesRemoveButton);
        globalPropertiesUpButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesUpButton->setIcon(goUpIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesUpButton);
        globalPropertiesDownButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesDownButton->setIcon(goDownIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesDownButton);
        globalPropertiesClearButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesClearButton->setIcon(editClearIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesClearButton);
        globalPropertiesImportButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesImportButton->setIcon(documentOpenIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesImportButton);
        globalPropertiesExportButton = new QToolButton(globalPropertiesTableActionsWidget);
        globalPropertiesExportButton->setIcon(documentSaveAsIcon);
        globalPropertiesTableActionsWidget->layout()->addWidget(globalPropertiesExportButton);
        globalPropertiesTableActionsWidget->layout()->addItem(new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum));
        globalPropertiesPage->layout()->addWidget(globalPropertiesTableActionsWidget);
        globalPropertiesTableWidget = new QTableWidget(0, 2, globalPropertiesPage);
        globalPropertiesTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(i18n("Name")));
        globalPropertiesTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(i18n("Value")));
        globalPropertiesTableWidget->horizontalHeader()->setStretchLastSection(true);
        globalPropertiesPage->layout()->addWidget(globalPropertiesTableWidget);
        pagesStackedWidget->addWidget(globalPropertiesPage);

        auto globalSecurityPage = new QWidget(pagesStackedWidget);
        globalSecurityPage->setLayout(new QVBoxLayout(globalSecurityPage));
        auto globalSecurityPageScrollArea = new QScrollArea(globalSecurityPage);
        globalSecurityPageScrollArea->setWidgetResizable(true);
        auto globalSecurityPageScrollAreaWidgetContents = new QWidget(globalSecurityPageScrollArea);
        auto globalSecurityPageFormLayout = new QFormLayout(globalSecurityPageScrollAreaWidgetContents);
        globalSecurityPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        globalSecurityPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Password:"), globalSecurityPageScrollAreaWidgetContents));
        globalSecurityPasswordLineEdit = new KPasswordLineEdit(globalSecurityPageScrollAreaWidgetContents);
        globalSecurityPageFormLayout->setWidget(0, QFormLayout::FieldRole, globalSecurityPasswordLineEdit);
        globalSecurityPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Disable the Load and Save scripts:"), globalSecurityPageScrollAreaWidgetContents));
        globalSecurityDisableScriptsCheckBox = new QCheckBox(i18n("Do not run the Load and Save scripts on opening and saving projects"), globalSecurityPageScrollAreaWidgetContents);
        globalSecurityPageFormLayout->setWidget(1, QFormLayout::FieldRole, globalSecurityDisableScriptsCheckBox);
        globalSecurityPageScrollArea->setWidget(globalSecurityPageScrollAreaWidgetContents);
        globalSecurityPage->layout()->addWidget(globalSecurityPageScrollArea);
        pagesStackedWidget->addWidget(globalSecurityPage);

        auto wsaSettingsPage = new QWidget(pagesStackedWidget);
        wsaSettingsPage->setLayout(new QVBoxLayout(wsaSettingsPage));
        auto wsaSettingsPageScrollArea = new QScrollArea(wsaSettingsPage);
        wsaSettingsPageScrollArea->setWidgetResizable(true);
        auto wsaSettingsPageScrollAreaWidgetContents = new QWidget();
        auto wsaSettingsPageFormLayout = new QFormLayout(wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPageFormLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        wsaSettingsPageFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel(i18n("Soap action overrides wsa action:"), wsaSettingsPageScrollAreaWidgetContents));
        wsaSoapOverrideCheckBox = new QCheckBox(i18n("Soap action if present overrides wsa action"), wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPageFormLayout->setWidget(0, QFormLayout::FieldRole, wsaSoapOverrideCheckBox);
        wsaSettingsPageFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel(i18n("Use default Relationship Type:"), wsaSettingsPageScrollAreaWidgetContents));
        wsaDefaultRelationshipTypeCheckBox = new QCheckBox(i18n("Use default 'reply' for RelationshipType"), wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPageFormLayout->setWidget(1, QFormLayout::FieldRole, wsaDefaultRelationshipTypeCheckBox);
        wsaSettingsPageFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel(i18n("Use default RelatesTo:"), wsaSettingsPageScrollAreaWidgetContents));
        wsaDefaultRelatesToCheckBox = new QCheckBox(i18n("Use default 'unspecified' for Relates To"), wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPageFormLayout->setWidget(2, QFormLayout::FieldRole, wsaDefaultRelatesToCheckBox);
        wsaSettingsPageFormLayout->setWidget(3, QFormLayout::LabelRole, new QLabel(i18n("Override existing headers:"), wsaSettingsPageScrollAreaWidgetContents));
        wsaOverrideHeadersCheckBox = new QCheckBox(i18n("Replaces existing WS-A headers (or skips them if unchecked)"), wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPageFormLayout->setWidget(3, QFormLayout::FieldRole, wsaOverrideHeadersCheckBox);
        wsaSettingsPageFormLayout->setWidget(4, QFormLayout::LabelRole, new QLabel(i18n("Enable for optional Addressing policy:"), wsaSettingsPageScrollAreaWidgetContents));
        wsaAddressingPolicyCheckBox = new QCheckBox(i18n("Enables WS-Addressing for Addressing Optional='true'"), wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPageFormLayout->setWidget(4, QFormLayout::FieldRole, wsaAddressingPolicyCheckBox);
        wsaSettingsPageScrollArea->setWidget(wsaSettingsPageScrollAreaWidgetContents);
        wsaSettingsPage->layout()->addWidget(wsaSettingsPageScrollArea);
        pagesStackedWidget->addWidget(wsaSettingsPage);

        auto globalSensitiveInformationTokensPage = new QWidget(pagesStackedWidget);
        globalSensitiveInformationTokensPage->setLayout(new QVBoxLayout(globalSensitiveInformationTokensPage));
        auto globalSensitiveInformationTokensTableActionsWidget = new QWidget(globalSensitiveInformationTokensPage);
        auto globalSensitiveInformationTokensTableActionsLayout = new QHBoxLayout(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensAddButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensAddButton->setIcon(listAddIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensAddButton);
        globalSensitiveInformationTokensRemoveButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensRemoveButton->setIcon(listRemoveIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensRemoveButton);
        globalSensitiveInformationTokensUpButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensUpButton->setIcon(goUpIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensUpButton);
        globalSensitiveInformationTokensDownButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensDownButton->setIcon(goDownIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensDownButton);
        globalSensitiveInformationTokensClearButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensClearButton->setIcon(editClearIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensClearButton);
        globalSensitiveInformationTokensImportButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensImportButton->setIcon(documentOpenIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensImportButton);
        globalSensitiveInformationTokensExportButton = new QToolButton(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensExportButton->setIcon(documentSaveAsIcon);
        globalSensitiveInformationTokensTableActionsLayout->addWidget(globalSensitiveInformationTokensExportButton);
        globalSensitiveInformationTokensTableActionsLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum));
        globalSensitiveInformationTokensPage->layout()->addWidget(globalSensitiveInformationTokensTableActionsWidget);
        globalSensitiveInformationTokensTableWidget = new QTableWidget(0, 2, globalSensitiveInformationTokensPage);
        globalSensitiveInformationTokensTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(i18n("Token")));
        globalSensitiveInformationTokensTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(i18n("Description")));
        globalSensitiveInformationTokensTableWidget->horizontalHeader()->setStretchLastSection(true);
        globalSensitiveInformationTokensPage->layout()->addWidget(globalSensitiveInformationTokensTableWidget);
        pagesStackedWidget->addWidget(globalSensitiveInformationTokensPage);

        gridLayout->addWidget(pagesStackedWidget, 0, 1, 1, 1);

        auto dialogButtonBox = new QDialogButtonBox(implementation);
        dialogButtonBox->setOrientation(Qt::Orientation::Horizontal);
        dialogButtonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        gridLayout->addWidget(dialogButtonBox, 1, 0, 1, 2);
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, implementation, qOverload<>(&QDialog::accept));
        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, implementation, qOverload<>(&QDialog::reject));

        QObject::connect(pagesListWidget, &QListWidget::currentRowChanged,
                         pagesStackedWidget, &QStackedWidget::setCurrentIndex);
        pagesListWidget->setCurrentRow(0);

#if QT_CONFIG(tooltip)
        globalPropertiesAddButton->setToolTip(i18n("Adds a property to the property list"));
        globalPropertiesRemoveButton->setToolTip(i18n("Removes the selected property from the property list"));
        globalPropertiesUpButton->setToolTip(i18n("Moves the selected property up one list"));
        globalPropertiesDownButton->setToolTip(i18n("Moves the selected property down one item"));
        globalPropertiesClearButton->setToolTip(i18n("Clears all current property values"));
        globalPropertiesImportButton->setToolTip(i18n("Loads property values from an external file"));
        globalPropertiesExportButton->setToolTip(i18n("Saves current property-values to a file"));
        globalSensitiveInformationTokensAddButton->setToolTip(i18n("Adds a property to the property list"));
        globalSensitiveInformationTokensRemoveButton->setToolTip(i18n("Removes the selected property from the property list"));
        globalSensitiveInformationTokensUpButton->setToolTip(i18n("Moves the selected property up one list"));
        globalSensitiveInformationTokensDownButton->setToolTip(i18n("Moves the selected property down one item"));
        globalSensitiveInformationTokensClearButton->setToolTip(i18n("Clears all current property values"));
        globalSensitiveInformationTokensImportButton->setToolTip(i18n("Loads property values from an external file"));
        globalSensitiveInformationTokensExportButton->setToolTip(i18n("Saves current property-values to a file"));
#endif
    }
};
}

#endif // UI_PREFERENCESDIALOG_H
