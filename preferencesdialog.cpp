#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <KLocalizedString>
#include <QList>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::setPreferences(const data::Preferences &preferences)
{
    this->preferences = preferences;

    ui->httpVersionComboBox->setCurrentText(this->preferences.value(QStringLiteral("HttpSettings@http_version")).toString());
    ui->httpUserAgentHeaderLineEdit->setText(this->preferences.value(QStringLiteral("HttpSettings@user-agent")).toString());
    auto requestCompression = this->preferences.value(QStringLiteral("HttpSettings@request-compression")).toString();
    int selectedRequestCompression;
    if (requestCompression == QStringLiteral("None"))
    {
        selectedRequestCompression = 0;
    }
    else if (requestCompression == QStringLiteral("gzip"))
    {
        selectedRequestCompression = 1;
    }
    else if (requestCompression == QStringLiteral("deflate"))
    {
        selectedRequestCompression = 2;
    }
    else
    {
        selectedRequestCompression = -1;
    }
    ui->httpRequestCompressionComboBox->setCurrentIndex(selectedRequestCompression);
    ui->httpResponseCompressionCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@response-compression")).toBool());
    ui->httpResponseDecompressionCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@disable_response_decompression")).toBool());
    ui->httpCloseConnectionCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@close-connections")).toBool());
    ui->httpChunkingThresholdSpinBox->setValue(this->preferences.value(QStringLiteral("HttpSettings@chunking_threshold")).toInt());
    ui->httpAuthenticateCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@authenticate-preemptively")).toBool());
    ui->httpExpectContinueCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@expect-continue")).toBool());
    ui->httpPreEncodedEndpointsCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@encoded_urls")).toBool());
    ui->httpNormalizeSlashesCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@forward_slashes")).toBool());
    ui->httpBindAddressLineEdit->setText(this->preferences.value(QStringLiteral("HttpSettings@bind_address")).toString());
    ui->httpIncludeRequestTimeCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@include_request_in_time_taken")).toBool());
    ui->httpIncludeResponseTimeCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@include_response_in_time_taken")).toBool());
    ui->httpSocketTimeoutSpinBox->setValue(this->preferences.value(QStringLiteral("HttpSettings@socket_timeout")).toInt());
    ui->httpMaxResponseSizeSpinBox->setValue(this->preferences.value(QStringLiteral("HttpSettings@max_response_size")).toInt());
    ui->httpMaxConnectionsPerHostSpinBox->setValue(this->preferences.value(QStringLiteral("HttpSettings@max_connections_per_host")).toInt());
    ui->httpMaxConnectionsTotalSpinBox->setValue(this->preferences.value(QStringLiteral("HttpSettings@max_total_connections")).toInt());
    ui->httpLeaveMockCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@leave_mockengine")).toBool());
    ui->httpMockLogCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@enable_mock_wire_log")).toBool());
    ui->httpStartMockCheckBox->setChecked(this->preferences.value(QStringLiteral("HttpSettings@start_mock_service")).toBool());

    bool proxyEnabled = this->preferences.value(QStringLiteral("ProxySettings@enableProxy")).toBool();
    bool proxyAutoMode = this->preferences.value(QStringLiteral("ProxySettings@autoProxy")).toBool();
    ui->proxyAutomaticRadioButton->setChecked(proxyEnabled && proxyAutoMode);
    ui->proxyNoneRadioButton->setChecked(!proxyEnabled);
    ui->proxyManualRadioButton->setChecked(proxyEnabled && !proxyAutoMode);
    ui->proxyHostLineEdit->setText(this->preferences.value(QStringLiteral("ProxySettings@host")).toString());
    ui->proxyPortSpinBox->setValue(this->preferences.value(QStringLiteral("ProxySettings@port")).toInt());
    ui->proxyExcludesLineEdit->setText(this->preferences.value(QStringLiteral("ProxySettings@excludes")).toString());
    ui->proxyUsernameLineEdit->setText(this->preferences.value(QStringLiteral("ProxySettings@username")).toString());
    ui->proxyPasswordLineEdit->setPassword(this->preferences.value(QStringLiteral("ProxySettings@password")).toString());

    ui->sslKeyStoreUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("SSLSettings@keyStore")).toString()));
    ui->sslKeyStorePasswordLineEdit->setPassword(this->preferences.value(QStringLiteral("SSLSettings@keyStorePassword")).toString());
    ui->sslMockCheckBox->setChecked(this->preferences.value(QStringLiteral("SSLSettings@enableMockSSL")).toBool());
    ui->sslMockPortSpinBox->setValue(this->preferences.value(QStringLiteral("SSLSettings@mockPort")).toInt());
    ui->sslMockKeyStoreUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("SSLSettings@mockKeyStore")).toString()));
    ui->sslMockPasswordLineEdit->setPassword(this->preferences.value(QStringLiteral("SSLSettings@mockPassword")).toString());
    ui->sslMockKeyPasswordLineEdit->setPassword(this->preferences.value(QStringLiteral("SSLSettings@mockKeyStorePassword")).toString());
    ui->sslMockTrustStoreUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("SSLSettings@mockTrustStore")).toString()));
    ui->sslMockTrustStorePasswordLineEdit->setPassword(this->preferences.value(QStringLiteral("SSLSettings@mockTrustStorePassword")).toString());
    ui->sslClientAuthenticationCheckBox->setChecked(this->preferences.value(QStringLiteral("SSLSettings@needClientAuthentication")).toBool());

    ui->wsdlCacheCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@cache-wsdls")).toBool());
    ui->wsdlSampleValuesCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@xml-generation-type-example-value")).toBool());
    ui->wsdlTypeCommentCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@xml-generation-type-comment-type")).toBool());
    ui->wsdlIncludeOptionalCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@xml-generation-always-include-optional-elements")).toBool());
    ui->wsdlPrettyPrintCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@pretty-print-response-xml")).toBool());
    ui->wsdlAttachmentPartsCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@attachment-parts")).toBool());
    ui->wsdlNoContentTypeValidationCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@allow-incorrect-contenttype")).toBool());
    ui->wsdlSchemaDirectoryUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("WsdlSettings@schema-directory")).toString()));
    ui->wsdlBindingNameCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@name-with-binding")).toBool());
    ui->wsdlExcludedTypesEditListWidget->setItems(this->preferences.value(QStringLiteral("WsdlSettings@excluded-types")).toStringList());
    ui->wsdlStrictSchemaTypesCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@strict-schema-types")).toBool());
    ui->wsdlCompressionSpinBox->setValue(this->preferences.value(QStringLiteral("WsdlSettings@compression-limit")).toInt());
    ui->wsdlPrettyPrintProjectFilesCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@pretty-print-project-files")).toBool());
    ui->wsdlTrimCheckBox->setChecked(this->preferences.value(QStringLiteral("WsdlSettings@trim-wsdl")).toBool());

    ui->uiCloseProjectsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@close-projects")).toBool());
    ui->uiOrderProjectsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@order-projects")).toBool());
    ui->uiOrderServicesCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@order-services")).toBool());
    ui->uiOrderRequestsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@order-requests")).toBool());
    ui->uiShowDescriptionsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@show_descriptions")).toBool());
    ui->uiSaveProjectCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@auto_save_projects_on_exit")).toBool());
    ui->uiCreatBackupCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@create_backup")).toBool());
    ui->uiBackupFolderUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("UISettings@backup_folder")).toString()));
    ui->uiAutosaveIntervalSpinBox->setValue(this->preferences.value(QStringLiteral("UISettings@auto_save_interval")).toInt());
    auto uiDesktopType = this->preferences.value(QStringLiteral("UISettings@desktop-type")).toString();
    int selectedDesktopType;
    if (uiDesktopType == QStringLiteral("Default"))
    {
        selectedDesktopType = 0;
    }
    else
    {
        selectedDesktopType = -1;
    }
    ui->uiDesktopTypeComboBox->setCurrentIndex(selectedDesktopType);
    ui->uiMostRecentPanelCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@mru_panel_selector")).toBool());
    ui->uiNativeLookCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@native-laf")).toBool());
    ui->uiGroovyLogCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@dont-disable-groovy-log")).toBool());
    ui->uiLogTabsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@show_logs_at_startup")).toBool());
    ui->uiShowStartupPageCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@show_startup_page")).toBool());
    ui->uiDisableTooltipsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@disable_tooltips")).toBool());
    ui->uiNormalizeLinebreakCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@normalize_line-breaks")).toBool());
    ui->uiGargabeCollectionIntervalSpinBox->setValue(this->preferences.value(QStringLiteral("UISettings@gc_interval")).toInt());
    ui->uiRawResponseSizeSpinBox->setValue(this->preferences.value(QStringLiteral("UISettings@raw_response_message_size_show")).toInt());
    ui->uiRawRequestSizeSpinBox->setValue(this->preferences.value(QStringLiteral("UISettings@UISettings@raw_request_message_size_show")).toInt());
    ui->uiWrapRawContentCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@wrap_raw_messages")).toBool());
    ui->uiDisableUsageStatisticsCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@disable_analytics")).toBool());

    auto editorFontText = this->preferences.value(QStringLiteral("UISettings@editor-font")).toString();
    if (editorFontText.isEmpty())
    {
        ui->editorFontFontRequester->setFont(QFont());
    }
    else
    {
        QRegularExpression fontRegexp(QLatin1String("^(.+)\\s+(\\d+)$"));
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
    ui->editorXmlLinesCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@show_xml_line_numbers")).toBool());
    ui->editorGroovyLinesCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@show_groovy_line_numbers")).toBool());
    ui->editorAutoResizeCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@no_resize_request_editor")).toBool());
    ui->editorTabbedCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@start_with_request_tabs")).toBool());
    ui->editorValidateRequestCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@auto_validate_request")).toBool());
    ui->editorAbortInvalidCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@abort_on_invalid_request")).toBool());
    ui->editorValidateResponseCheckBox->setChecked(this->preferences.value(QStringLiteral("UISettings@auto_validate_response")).toBool());

    ui->toolsJbossUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@jbossws_wstools")).toString()));
    ui->toolsJaxRpcUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@jwsdp_wscompile")).toString()));
    ui->toolsJaxWsUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@jwsdp_wsimport")).toString()));
    ui->toolsAxis1UrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@axis_1_X")).toString()));
    ui->toolsAxis2UrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@axis_2")).toString()));
    ui->toolsDotnetWsdlUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@dotnet_wsdl")).toString()));
    ui->toolsXfireUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@xfire")).toString()));
    ui->toolsCxfUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@cxf")).toString()));
    ui->toolsAntUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@ant")).toString()));
    ui->toolsGsoapUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@gsoap")).toString()));
    ui->toolsJaxbUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@jaxb")).toString()));
    ui->toolsXmlBeansUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@xmlbeans")).toString()));
    ui->toolsJavacUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@javac")).toString()));
    ui->toolsTcpMonUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@tcpmon")).toString()));
    ui->toolsWsaUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@wsa")).toString()));
    ui->toolsWadl2JavaUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@wadl2java")).toString()));
    ui->toolsHermesJmsUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("ToolsSettings@hermesjms")).toString()));

    ui->wsiVerboseCheckBox->setChecked(this->preferences.value(QStringLiteral("WSISettings@verbose")).toBool());
    ui->wsiProfileComboBox->setCurrentText(this->preferences.value(QStringLiteral("WSISettings@profile_type")).toString());
    auto wsiCorrelation = this->preferences.value(QStringLiteral("WSISettings@correlation_type")).toString();
    int selectedWsiCorrelation;
    if (wsiCorrelation == QStringLiteral("endpoint"))
    {
        selectedWsiCorrelation = 0;
    }
    else if (wsiCorrelation == QStringLiteral("namespace"))
    {
        selectedWsiCorrelation = 1;
    }
    else if (wsiCorrelation == QStringLiteral("operation"))
    {
        selectedWsiCorrelation = 2;
    }
    else
    {
        selectedWsiCorrelation = -1;
    }
    ui->wsiCorrelationComboBox->setCurrentIndex(selectedWsiCorrelation);
    ui->wsiMessageEntryCheckBox->setChecked(this->preferences.value(QStringLiteral("WSISettings@messageEntry")).toBool());
    ui->wsiFailureMessageCheckBox->setChecked(this->preferences.value(QStringLiteral("WSISettings@failureMessage")).toBool());
    ui->wsiAssertionDescriptionCheckBox->setChecked(this->preferences.value(QStringLiteral("WSISettings@assertionDescription")).toBool());
    ui->wsiToolLocationUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("WSISettings@location")).toString()));
    ui->wsiShowLogCheckBox->setChecked(this->preferences.value(QStringLiteral("WSISettings@showLog")).toBool());
    ui->wsiOutputFolderUrlRequester->setUrl(QUrl(this->preferences.value(QStringLiteral("WSISettings@outputFolder")).toString()));

    ui->globalPropertiesEnableOverrideCheckBox->setChecked(this->preferences.value(QStringLiteral("GlobalPropertySettings@enableOverride")).toBool());
    auto globalProperties = this->preferences.value(QStringLiteral("GlobalPropertySettings@properties")).value<QList<QPair<QString, QString>>>();
    ui->globalPropertiesTableWidget->clearContents();
    ui->globalPropertiesTableWidget->setRowCount(globalProperties.size());
    for (int row = 0; row < globalProperties.size(); row++)
    {
        const auto &entry = globalProperties[row];
        ui->globalPropertiesTableWidget->setItem(row, 0, new QTableWidgetItem(entry.first));
        ui->globalPropertiesTableWidget->setItem(row, 1, new QTableWidgetItem(entry.second));
    }

    ui->globalSecurityPasswordLineEdit->setPassword(this->preferences.value(QStringLiteral("SecuritySettings@shadowProxyPassword")).toString());
    ui->globalSecurityDisableScriptsCheckBox->setChecked(this->preferences.value(QStringLiteral("SecuritySettings@disable_project_load_save_scripts")).toBool());

    auto sensitiveInformationTokens = this->preferences.value(QStringLiteral("GlobalPropertySettings@security_scans_properties")).value<QList<QPair<QString, QString>>>();
    ui->globalSensitiveInformationTokensTableWidget->clearContents();
    ui->globalSensitiveInformationTokensTableWidget->setRowCount(sensitiveInformationTokens.size());
    for (int row = 0; row < sensitiveInformationTokens.size(); row++)
    {
        const auto &entry = sensitiveInformationTokens[row];
        ui->globalSensitiveInformationTokensTableWidget->setItem(row, 0, new QTableWidgetItem(entry.first));
        ui->globalSensitiveInformationTokensTableWidget->setItem(row, 1, new QTableWidgetItem(entry.second));
    }

    ui->wsaSoapOverrideCheckBox->setChecked(this->preferences.value(QStringLiteral("WsaSettings@soapActionOverridesWsaAction")).toBool());
    ui->wsaDefaultRelationshipTypeCheckBox->setChecked(this->preferences.value(QStringLiteral("WsaSettings@useDefaultRelationshipType")).toBool());
    ui->wsaDefaultRelatesToCheckBox->setChecked(this->preferences.value(QStringLiteral("WsaSettings@useDefaultRelatesTo")).toBool());
    ui->wsaOverrideHeadersCheckBox->setChecked(this->preferences.value(QStringLiteral("WsaSettings@overrideExistingHeaders")).toBool());
    ui->wsaAddressingPolicyCheckBox->setChecked(this->preferences.value(QStringLiteral("WsaSettings@enableForOptional")).toBool());
}

