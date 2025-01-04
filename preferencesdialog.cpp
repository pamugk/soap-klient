#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <QList>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    connect(ui->pagesListWidget, &QListWidget::currentRowChanged,
            this, &PreferencesDialog::setSelectedPage);
    ui->pagesListWidget->setCurrentRow(0);

    ui->httpVersionComboBox->addItem("1.0");
    ui->httpVersionComboBox->addItem("1.1");

    ui->httpRequestCompressionComboBox->addItem(tr("None"), "None");
    ui->httpRequestCompressionComboBox->addItem(tr("gzip"), "gzip");
    ui->httpRequestCompressionComboBox->addItem(tr("deflate"), "deflate");

    ui->uiDesktopTypeComboBox->addItem(tr("Default"), "Default");

    ui->wsiProfileComboBox->addItem("BasicSecurityProfile-1.0-TAD.xml");
    ui->wsiProfileComboBox->addItem("BasicSecurityProfile-1.1-TAD.xml");

    ui->wsiCorrelationComboBox->addItem(tr("endpoint"), "endpoint");
    ui->wsiCorrelationComboBox->addItem(tr("namespace"), "namespace");
    ui->wsiCorrelationComboBox->addItem(tr("operation"), "operation");
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::setPreferences(const data::Preferences &preferences)
{
    this->preferences = preferences;

    ui->httpVersionComboBox->setCurrentText(this->preferences.value(QLatin1StringView("HttpSettings@http_version")).toString());
    ui->httpUserAgentHeaderLineEdit->setText(this->preferences.value(QLatin1StringView("HttpSettings@user-agent")).toString());
    auto requestCompression = this->preferences.value(QLatin1StringView("HttpSettings@request-compression")).toString();
    int selectedRequestCompression;
    if (requestCompression == "None")
    {
        selectedRequestCompression = 0;
    }
    else if (requestCompression == "gzip")
    {
        selectedRequestCompression = 1;
    }
    else if (requestCompression == "deflate")
    {
        selectedRequestCompression = 2;
    }
    else
    {
        selectedRequestCompression = -1;
    }
    ui->httpRequestCompressionComboBox->setCurrentIndex(selectedRequestCompression);
    ui->httpResponseCompressionCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@response-compression")).toBool());
    ui->httpResponseDecompressionCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@disable_response_decompression")).toBool());
    ui->httpCloseConnectionCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@close-connections")).toBool());
    ui->httpChunkingThresholdSpinBox->setValue(this->preferences.value(QLatin1StringView("HttpSettings@chunking_threshold")).toInt());
    ui->httpAuthenticateCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@authenticate-preemptively")).toBool());
    ui->httpExpectContinueCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@expect-continue")).toBool());
    ui->httpPreEncodedEndpointsCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@encoded_urls")).toBool());
    ui->httpNormalizeSlashesCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@forward_slashes")).toBool());
    ui->httpBindAddressLineEdit->setText(this->preferences.value(QLatin1StringView("HttpSettings@bind_address")).toString());
    ui->httpIncludeRequestTimeCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@include_request_in_time_taken")).toBool());
    ui->httpIncludeResponseTimeCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@include_response_in_time_taken")).toBool());
    ui->httpSocketTimeoutSpinBox->setValue(this->preferences.value(QLatin1StringView("HttpSettings@socket_timeout")).toInt());
    ui->httpMaxResponseSizeSpinBox->setValue(this->preferences.value(QLatin1StringView("HttpSettings@max_response_size")).toInt());
    ui->httpMaxConnectionsPerHostSpinBox->setValue(this->preferences.value(QLatin1StringView("HttpSettings@max_connections_per_host")).toInt());
    ui->httpMaxConnectionsTotalSpinBox->setValue(this->preferences.value(QLatin1StringView("HttpSettings@max_total_connections")).toInt());
    ui->httpLeaveMockCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@leave_mockengine")).toBool());
    ui->httpMockLogCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@enable_mock_wire_log")).toBool());
    ui->httpStartMockCheckBox->setChecked(this->preferences.value(QLatin1StringView("HttpSettings@start_mock_service")).toBool());

    bool proxyEnabled = this->preferences.value(QLatin1StringView("ProxySettings@enableProxy")).toBool();
    bool proxyAutoMode = this->preferences.value(QLatin1StringView("ProxySettings@autoProxy")).toBool();
    ui->proxyAutomaticRadioButton->setChecked(proxyEnabled && proxyAutoMode);
    ui->proxyNoneRadioButton->setChecked(!proxyEnabled);
    ui->proxyManualRadioButton->setChecked(proxyEnabled && !proxyAutoMode);
    ui->proxyHostLineEdit->setText(this->preferences.value(QLatin1StringView("ProxySettings@host")).toString());
    ui->proxyPortSpinBox->setValue(this->preferences.value(QLatin1StringView("ProxySettings@port")).toInt());
    ui->proxyExcludesLineEdit->setText(this->preferences.value(QLatin1StringView("ProxySettings@excludes")).toString());
    ui->proxyUsernameLineEdit->setText(this->preferences.value(QLatin1StringView("ProxySettings@username")).toString());
    ui->proxyPasswordLineEdit->setPassword(this->preferences.value(QLatin1StringView("ProxySettings@password")).toString());

    ui->sslKeyStoreUrlRequester->setUrl(this->preferences.value(QLatin1StringView("SSLSettings@keyStore")).toString());
    ui->sslKeyStorePasswordLineEdit->setPassword(this->preferences.value(QLatin1StringView("SSLSettings@keyStorePassword")).toString());
    ui->sslMockCheckBox->setChecked(this->preferences.value(QLatin1StringView("SSLSettings@enableMockSSL")).toBool());
    ui->sslMockPortSpinBox->setValue(this->preferences.value(QLatin1StringView("SSLSettings@mockPort")).toInt());
    ui->sslMockKeyStoreUrlRequester->setUrl(this->preferences.value(QLatin1StringView("SSLSettings@mockKeyStore")).toString());
    ui->sslMockPasswordLineEdit->setPassword(this->preferences.value(QLatin1StringView("SSLSettings@mockPassword")).toString());
    ui->sslMockKeyPasswordLineEdit->setPassword(this->preferences.value(QLatin1StringView("SSLSettings@mockKeyStorePassword")).toString());
    ui->sslMockTrustStoreUrlRequester->setUrl(this->preferences.value(QLatin1StringView("SSLSettings@mockTrustStore")).toString());
    ui->sslMockTrustStorePasswordLineEdit->setPassword(this->preferences.value(QLatin1StringView("SSLSettings@mockTrustStorePassword")).toString());
    ui->sslClientAuthenticationCheckBox->setChecked(this->preferences.value(QLatin1StringView("SSLSettings@needClientAuthentication")).toBool());

    ui->wsdlCacheCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@cache-wsdls")).toBool());
    ui->wsdlSampleValuesCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@xml-generation-type-example-value")).toBool());
    ui->wsdlTypeCommentCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@xml-generation-type-comment-type")).toBool());
    ui->wsdlIncludeOptionalCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@xml-generation-always-include-optional-elements")).toBool());
    ui->wsdlPrettyPrintCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@pretty-print-response-xml")).toBool());
    ui->wsdlAttachmentPartsCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@attachment-parts")).toBool());
    ui->wsdlNoContentTypeValidationCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@allow-incorrect-contenttype")).toBool());
    ui->wsdlSchemaDirectoryUrlRequester->setUrl(this->preferences.value(QLatin1StringView("WsdlSettings@schema-directory")).toString());
    ui->wsdlBindingNameCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@name-with-binding")).toBool());
    ui->wsdlExcludedTypesEditListWidget->setItems(this->preferences.value(QLatin1StringView("WsdlSettings@excluded-types")).toStringList());
    ui->wsdlStrictSchemaTypesCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@strict-schema-types")).toBool());
    ui->wsdlCompressionSpinBox->setValue(this->preferences.value(QLatin1StringView("WsdlSettings@compression-limit")).toInt());
    ui->wsdlPrettyPrintProjectFilesCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@pretty-print-project-files")).toBool());
    ui->wsdlTrimCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsdlSettings@trim-wsdl")).toBool());

    ui->uiCloseProjectsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@close-projects")).toBool());
    ui->uiOrderProjectsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@order-projects")).toBool());
    ui->uiOrderServicesCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@order-services")).toBool());
    ui->uiOrderRequestsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@order-requests")).toBool());
    ui->uiShowDescriptionsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@show_descriptions")).toBool());
    ui->uiSaveProjectCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@auto_save_projects_on_exit")).toBool());
    ui->uiCreatBackupCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@create_backup")).toBool());
    ui->uiBackupFolderUrlRequester->setUrl(this->preferences.value(QLatin1StringView("UISettings@backup_folder")).toString());
    ui->uiAutosaveIntervalSpinBox->setValue(this->preferences.value(QLatin1StringView("UISettings@auto_save_interval")).toInt());
    auto uiDesktopType = this->preferences.value(QLatin1StringView("UISettings@desktop-type")).toString();
    int selectedDesktopType;
    if (uiDesktopType == "Default")
    {
        selectedDesktopType = 0;
    }
    else
    {
        selectedDesktopType = -1;
    }
    ui->uiDesktopTypeComboBox->setCurrentIndex(selectedDesktopType);
    ui->uiMostRecentPanelCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@mru_panel_selector")).toBool());
    ui->uiNativeLookCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@native-laf")).toBool());
    ui->uiGroovyLogCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@dont-disable-groovy-log")).toBool());
    ui->uiLogTabsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@show_logs_at_startup")).toBool());
    ui->uiShowStartupPageCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@show_startup_page")).toBool());
    ui->uiDisableTooltipsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@disable_tooltips")).toBool());
    ui->uiNormalizeLinebreakCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@normalize_line-breaks")).toBool());
    ui->uiGargabeCollectionIntervalSpinBox->setValue(this->preferences.value(QLatin1StringView("UISettings@gc_interval")).toInt());
    ui->uiRawResponseSizeSpinBox->setValue(this->preferences.value(QLatin1StringView("UISettings@raw_response_message_size_show")).toInt());
    ui->uiRawRequestSizeSpinBox->setValue(this->preferences.value(QLatin1StringView("UISettings@UISettings@raw_request_message_size_show")).toInt());
    ui->uiWrapRawContentCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@wrap_raw_messages")).toBool());
    ui->uiDisableUsageStatisticsCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@disable_analytics")).toBool());

    auto editorFontText = this->preferences.value(QLatin1StringView("UISettings@editor-font")).toString();
    if (editorFontText.isEmpty())
    {
        ui->editorFontFontRequester->setFont(QFont());
    }
    else
    {
        QRegularExpression fontRegexp("^(.+)\\s+(\\d+)$");
        QRegularExpressionMatch fontMatch = fontRegexp.match(editorFontText);
        if (fontMatch.hasMatch())
        {
            QString editorFontFamily = fontMatch.captured(1);
            int editorFontSize = fontMatch.captured(2).toInt();
            ui->editorFontFontRequester->setFont(QFont(editorFontFamily, editorFontSize));
        }
        else
        {
            ui->editorFontFontRequester->setFont(QFont());
        }
    }
    ui->editorXmlLinesCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@show_xml_line_numbers")).toBool());
    ui->editorGroovyLinesCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@show_groovy_line_numbers")).toBool());
    ui->editorAutoResizeCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@no_resize_request_editor")).toBool());
    ui->editorTabbedCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@start_with_request_tabs")).toBool());
    ui->editorValidateRequestCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@auto_validate_request")).toBool());
    ui->editorAbortInvalidCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@abort_on_invalid_request")).toBool());
    ui->editorValidateResponseCheckBox->setChecked(this->preferences.value(QLatin1StringView("UISettings@auto_validate_response")).toBool());

    ui->toolsJbossUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@jbossws_wstools")).toString());
    ui->toolsJaxRpcUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@jwsdp_wscompile")).toString());
    ui->toolsJaxWsUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@jwsdp_wsimport")).toString());
    ui->toolsAxis1UrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@axis_1_X")).toString());
    ui->toolsAxis2UrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@axis_2")).toString());
    ui->toolsDotnetWsdlUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@dotnet_wsdl")).toString());
    ui->toolsXfireUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@xfire")).toString());
    ui->toolsCxfUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@cxf")).toString());
    ui->toolsAntUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@ant")).toString());
    ui->toolsGsoapUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@gsoap")).toString());
    ui->toolsJaxbUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@jaxb")).toString());
    ui->toolsXmlBeansUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@xmlbeans")).toString());
    ui->toolsJavacUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@javac")).toString());
    ui->toolsTcpMonUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@tcpmon")).toString());
    ui->toolsWsaUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@wsa")).toString());
    ui->toolsWadl2JavaUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@wadl2java")).toString());
    ui->toolsHermesJmsUrlRequester->setUrl(this->preferences.value(QLatin1StringView("ToolsSettings@hermesjms")).toString());

    ui->wsiVerboseCheckBox->setChecked(this->preferences.value(QLatin1StringView("WSISettings@verbose")).toBool());
    ui->wsiProfileComboBox->setCurrentText(this->preferences.value(QLatin1StringView("WSISettings@profile_type")).toString());
    auto wsiCorrelation = this->preferences.value(QLatin1StringView("WSISettings@correlation_type")).toString();
    int selectedWsiCorrelation;
    if (wsiCorrelation == "endpoint")
    {
        selectedWsiCorrelation = 0;
    }
    else if (wsiCorrelation == "namespace")
    {
        selectedWsiCorrelation = 1;
    }
    else if (wsiCorrelation == "operation")
    {
        selectedWsiCorrelation = 2;
    }
    else
    {
        selectedWsiCorrelation = -1;
    }
    ui->wsiCorrelationComboBox->setCurrentIndex(selectedWsiCorrelation);
    ui->wsiMessageEntryCheckBox->setChecked(this->preferences.value(QLatin1StringView("WSISettings@messageEntry")).toBool());
    ui->wsiFailureMessageCheckBox->setChecked(this->preferences.value(QLatin1StringView("WSISettings@failureMessage")).toBool());
    ui->wsiAssertionDescriptionCheckBox->setChecked(this->preferences.value(QLatin1StringView("WSISettings@assertionDescription")).toBool());
    ui->wsiToolLocationUrlRequester->setUrl(this->preferences.value(QLatin1StringView("WSISettings@location")).toString());
    ui->wsiShowLogCheckBox->setChecked(this->preferences.value(QLatin1StringView("WSISettings@showLog")).toBool());
    ui->wsiOutputFolderUrlRequester->setUrl(this->preferences.value(QLatin1StringView("WSISettings@outputFolder")).toString());

    ui->globalPropertiesEnableOverrideCheckBox->setChecked(this->preferences.value(QLatin1StringView("GlobalPropertySettings@enableOverride")).toBool());
    auto globalProperties = this->preferences.value(QLatin1StringView("GlobalPropertySettings@properties")).value<QList<QPair<QString, QString>>>();
    ui->globalPropertiesTableWidget->clearContents();
    ui->globalPropertiesTableWidget->setRowCount(globalProperties.size());
    for (int row = 0; row < globalProperties.size(); row++)
    {
        const auto &entry = globalProperties[row];
        ui->globalPropertiesTableWidget->setItem(row, 0, new QTableWidgetItem(entry.first));
        ui->globalPropertiesTableWidget->setItem(row, 1, new QTableWidgetItem(entry.second));
    }

    ui->globalSecurityPasswordLineEdit->setPassword(this->preferences.value(QLatin1StringView("SecuritySettings@shadowProxyPassword")).toString());
    ui->globalSecurityDisableScriptsCheckBox->setChecked(this->preferences.value(QLatin1StringView("SecuritySettings@disable_project_load_save_scripts")).toBool());

    auto sensitiveInformationTokens = this->preferences.value(QLatin1StringView("GlobalPropertySettings@security_scans_properties")).value<QList<QPair<QString, QString>>>();
    ui->globalSensitiveInformationTokensTableWidget->clearContents();
    ui->globalSensitiveInformationTokensTableWidget->setRowCount(sensitiveInformationTokens.size());
    for (int row = 0; row < sensitiveInformationTokens.size(); row++)
    {
        const auto &entry = sensitiveInformationTokens[row];
        ui->globalSensitiveInformationTokensTableWidget->setItem(row, 0, new QTableWidgetItem(entry.first));
        ui->globalSensitiveInformationTokensTableWidget->setItem(row, 1, new QTableWidgetItem(entry.second));
    }

    ui->wsaSoapOverrideCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsaSettings@soapActionOverridesWsaAction")).toBool());
    ui->wsaDefaultRelationshipTypeCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsaSettings@useDefaultRelationshipType")).toBool());
    ui->wsaDefaultRelatesToCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsaSettings@useDefaultRelatesTo")).toBool());
    ui->wsaOverrideHeadersCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsaSettings@overrideExistingHeaders")).toBool());
    ui->wsaAddressingPolicyCheckBox->setChecked(this->preferences.value(QLatin1StringView("WsaSettings@enableForOptional")).toBool());
}

void PreferencesDialog::setSelectedPage(int selectedPageIndex)
{
    ui->pagesStackedWidget->setCurrentIndex(selectedPageIndex);
}
