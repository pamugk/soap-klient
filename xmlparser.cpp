#include "xmlparser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QXmlStreamReader>

namespace xml {

const auto DEFAULT_NAMESPACE = QStringLiteral("");
const auto SOAPUI_CONFIG_NAMESPACE = QStringLiteral("http://eviware.com/soapui/config");

const auto DEFINITION_CACHE_ELEMENT = QStringLiteral("definitionCache");
const auto ENDPOINT_ELEMENT = QStringLiteral("endpoint");
const auto INTERFACE_ELEMENT = QStringLiteral("interface");
const auto OPERATION_ELEMENT = QStringLiteral("operation");

bool parseBoolean(const QStringView &booleanValue)
{
    return booleanValue == QStringLiteral("true");
}

void parseProjectInterfaceDefinitionCache(QXmlStreamReader &projectReader,
                                          data::DefinitionCache &definitionCache)
{
    const auto CONTENT_ELEMENT = QStringLiteral("content");
    const auto PART_ELEMENT = QStringLiteral("part");
    const auto TYPE_ELEMENT = QStringLiteral("type");
    const auto URL_ELEMENT = QStringLiteral("url");

    const auto definitionCacheAttributes = projectReader.attributes();
    definitionCache.type = QString(definitionCacheAttributes.value(DEFAULT_NAMESPACE, "type"));
    definitionCache.rootPart = QString(definitionCacheAttributes.value(DEFAULT_NAMESPACE, "rootPart"));
    do
    {
        projectReader.readNext();

        if (projectReader.isStartElement()
                && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                && projectReader.name() == PART_ELEMENT)
        {
            data::DefinitionCachePart part;
            do
            {
                projectReader.readNext();

                if (projectReader.isStartElement()
                        && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE)
                {
                    auto const elementName = projectReader.name();
                    if (elementName == URL_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                part.url = QString(projectReader.text());
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == URL_ELEMENT));
                    }
                    else if (elementName == CONTENT_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                part.content = QString(projectReader.text());
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == CONTENT_ELEMENT));
                    }
                    else if (elementName == TYPE_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                part.type = QString(projectReader.text());
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == TYPE_ELEMENT));
                    }
                }
            } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                 && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                 && projectReader.name() == PART_ELEMENT));
            definitionCache.parts.append(part);
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == DEFINITION_CACHE_ELEMENT));
}

data::Operation parseProjectInterfaceOperation(QXmlStreamReader &projectReader)
{
    const auto CALL_ELEMENT = QStringLiteral("call");
    const auto ENCODING_ELEMENT = QStringLiteral("encoding");
    const auto REQUEST_ELEMENT = QStringLiteral("request");
    const auto WSA_CONFIG_ELEMENT = QStringLiteral("wsaConfig");

    const auto operationAttributes = projectReader.attributes();
    data::Operation operation;
    operation.id = QString(operationAttributes.value(DEFAULT_NAMESPACE, "id"));
    operation.isOneWay = parseBoolean(operationAttributes.value(DEFAULT_NAMESPACE, "isOneWay"));
    operation.action = QString(operationAttributes.value(DEFAULT_NAMESPACE, "action"));
    operation.name = QString(operationAttributes.value(DEFAULT_NAMESPACE, "name"));
    operation.bindingOperationName = QString(operationAttributes.value(DEFAULT_NAMESPACE, "bindingOperationName"));
    operation.type = QString(operationAttributes.value(DEFAULT_NAMESPACE, "type"));
    operation.outputName = QString(operationAttributes.value(DEFAULT_NAMESPACE, "outputName"));
    operation.inputName = QString(operationAttributes.value(DEFAULT_NAMESPACE, "inputName"));
    operation.receivesAttachments = parseBoolean(operationAttributes.value(DEFAULT_NAMESPACE, "receivesAttachments"));
    operation.sendsAttachments = parseBoolean(operationAttributes.value(DEFAULT_NAMESPACE, "sendsAttachments"));
    operation.anonymous = QString(operationAttributes.value(DEFAULT_NAMESPACE, "anonymous"));
    do
    {
        projectReader.readNext();

        if (projectReader.isStartElement()
                && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                && projectReader.name() == CALL_ELEMENT)
        {
            const auto callAttributes = projectReader.attributes();
            data::OperationCall call;
            call.id = QString(callAttributes.value(DEFAULT_NAMESPACE, "id"));
            call.name = QString(callAttributes.value(DEFAULT_NAMESPACE, "name"));
            do
            {
                projectReader.readNext();

                if (projectReader.isStartElement()
                        && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE)
                {
                    auto const elementName = projectReader.name();
                    if (elementName == ENCODING_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                call.encoding = QString(projectReader.text());
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == ENCODING_ELEMENT));
                    }
                    else if (elementName == ENDPOINT_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                call.endpoint = QString(projectReader.text());
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == ENDPOINT_ELEMENT));
                    }
                    else if (elementName == REQUEST_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                call.request = QString(projectReader.text());
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == REQUEST_ELEMENT));
                    }
                    else if (elementName == WSA_CONFIG_ELEMENT)
                    {
                        const auto wsaConfigAttributes = projectReader.attributes();
                        call.wsaConfig.mustUnderstand = QString(wsaConfigAttributes.value(DEFAULT_NAMESPACE, "mustUnderstand"));
                        call.wsaConfig.version = QString(wsaConfigAttributes.value(DEFAULT_NAMESPACE, "version"));
                        call.wsaConfig.action = QString(wsaConfigAttributes.value(DEFAULT_NAMESPACE, "action"));
                    }
                }
            } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                 && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                 && projectReader.name() == CALL_ELEMENT));
            operation.calls.append(call);
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == OPERATION_ELEMENT));
    return operation;
}

data::Interface parseProjectInterface(QXmlStreamReader &projectReader)
{
    const auto ENDPOINTS_ELEMENT = QStringLiteral("endpoints");

    const auto interfaceAttributes = projectReader.attributes();
    data::Interface interfaceEntry;
    interfaceEntry.id = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "id"));
    interfaceEntry.wsaVersion = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "wsaVersion"));
    interfaceEntry.name = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "name"));
    interfaceEntry.type = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "type"));
    interfaceEntry.bindingName = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "bindingName"));
    interfaceEntry.soapVersion = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "soapVersion"));
    interfaceEntry.anonymous = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "anonymous"));
    interfaceEntry.definition = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, "definition"));
    do
    {
        projectReader.readNext();

        if (projectReader.isStartElement()
                && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE)
        {
            auto const elementName = projectReader.name();
            if (elementName == DEFINITION_CACHE_ELEMENT)
            {
                parseProjectInterfaceDefinitionCache(projectReader, interfaceEntry.definitionCache);
            }
            else if (elementName == ENDPOINTS_ELEMENT)
            {
                do
                {
                    projectReader.readNext();

                    if (projectReader.isStartElement()
                            && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                            && projectReader.name() == ENDPOINT_ELEMENT)
                    {
                        do
                        {
                            projectReader.readNext();

                            if (projectReader.isCharacters())
                            {
                                interfaceEntry.endpoints.append(QString(projectReader.text()));
                            }
                        } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                             && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                             && projectReader.name() == ENDPOINT_ELEMENT));
                    }
                } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                     && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                     && projectReader.name() == ENDPOINTS_ELEMENT));
            }
            else if (elementName == OPERATION_ELEMENT)
            {
                interfaceEntry.operations.append(parseProjectInterfaceOperation(projectReader));
            }
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == INTERFACE_ELEMENT));
    return interfaceEntry;
}

std::optional<data::Project> parseProjectFile(const QString &projectFilePath)
{
    std::optional<data::Project> result = std::nullopt;
    QFile projectFile(projectFilePath);

    const auto PROJECT_ELEMENT = QStringLiteral("soapui-project");

    if (projectFile.open(QIODeviceBase::ReadOnly | QIODevice::Text))
    {
        data::Project project;
        QXmlStreamReader projectReader(&projectFile);
        while (!projectReader.atEnd())
        {
            projectReader.readNext();

            if (projectReader.isStartElement()
                    && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                    && projectReader.name() == PROJECT_ELEMENT)
            {
                const auto projectAttributes = projectReader.attributes();
                project.id = QString(projectAttributes.value(DEFAULT_NAMESPACE, "id"));
                project.activeEnvironment = QString(projectAttributes.value(DEFAULT_NAMESPACE, "activeEnvironment"));
                project.name = QString(projectAttributes.value(DEFAULT_NAMESPACE, "name"));
                project.resourceRoot = QString(projectAttributes.value(DEFAULT_NAMESPACE, "resourceRoot"));
                project.appVersion = QString(projectAttributes.value(DEFAULT_NAMESPACE, "soapui-version"));
                project.abortOnError = parseBoolean(projectAttributes.value(DEFAULT_NAMESPACE, "abortOnError"));
                project.runType = QString(projectAttributes.value(DEFAULT_NAMESPACE, "runType"));
                do
                {
                    projectReader.readNext();

                    if (projectReader.isStartElement()
                            && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                            && projectReader.name() == INTERFACE_ELEMENT)
                    {
                        project.interfaces.append(parseProjectInterface(projectReader));
                    }
                } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                      && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                      && projectReader.name() == PROJECT_ELEMENT));
            }
        }
        projectFile.close();
        result = project;
    }
    return result;
}

QList<QPair<QString, QString>> parseSettingsKeyValueList(const QStringView &xml)
{
    QList<QPair<QString, QString>> result;

    const QLatin1StringView ENTRY_ELEMENT = QLatin1StringView("entry");

    QXmlStreamReader xmlReader(xml);
    while (!xmlReader.atEnd())
    {
        xmlReader.readNext();
        if (xmlReader.isStartElement()
                && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                && xmlReader.name() == ENTRY_ELEMENT)
        {
            auto entryAttributes = xmlReader.attributes();
            result.append(QPair<QString, QString>(QString(entryAttributes.value(DEFAULT_NAMESPACE, "key")),
                                                  QString(entryAttributes.value(DEFAULT_NAMESPACE, "value"))));
        }
    }

    return result;
}

QList<QPair<QString, QString>> parseSettingsPropertyList(const QStringView &xml)
{
    QList<QPair<QString, QString>> result;

    const auto NAME_ELEMENT = QStringLiteral("name");
    const auto PROPERTY_ELEMENT = QStringLiteral("property");
    const auto VALUE_ELEMENT = QStringLiteral("value");

    QXmlStreamReader xmlReader(xml);
    while (!xmlReader.atEnd())
    {
        xmlReader.readNext();
        if (xmlReader.isStartElement()
                && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                && xmlReader.name() == PROPERTY_ELEMENT)
        {
            QString name;
            QString value;

            do
            {
                xmlReader.readNext();

                if (xmlReader.isStartElement()
                        && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE)
                {
                    auto const elementName = xmlReader.name();
                    if (elementName == NAME_ELEMENT)
                    {
                        do
                        {
                            xmlReader.readNext();
                            if (xmlReader.isCharacters())
                            {
                                name = QString(xmlReader.text());
                            }
                        } while (!xmlReader.atEnd() && !(xmlReader.isEndElement()
                                                         && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                         && xmlReader.name() == NAME_ELEMENT));
                    }
                    else if (elementName == VALUE_ELEMENT)
                    {
                        do
                        {
                            xmlReader.readNext();
                            if (xmlReader.isCharacters())
                            {
                                value = QString(xmlReader.text());
                            }
                        } while (!xmlReader.atEnd() && !(xmlReader.isEndElement()
                                                         && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                         && xmlReader.name() == VALUE_ELEMENT));
                    }
                }
            } while (!xmlReader.atEnd() && !(xmlReader.isEndElement()
                                             && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                             && xmlReader.name() == PROPERTY_ELEMENT));
            result.append(QPair<QString, QString>(name, value));
        }
    }

    return result;
}

QStringList parseSettingsValueList(const QStringView &xml)
{
    QStringList result;

    const auto ENTRY_ELEMENT = QStringLiteral("entry");

    QXmlStreamReader xmlReader(xml);
    while (!xmlReader.atEnd())
    {
        xmlReader.readNext();
        if (xmlReader.isStartElement()
                && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                && xmlReader.name() == ENTRY_ELEMENT)
        {
            do
            {
                xmlReader.readNext();
                if (xmlReader.isCharacters())
                {
                    result.append(QString(xmlReader.text()));
                }
            } while (!xmlReader.atEnd() && !(xmlReader.isEndElement()
                                             && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                             && xmlReader.name() == ENTRY_ELEMENT));
        }
    }

    return result;
}

std::optional<data::Preferences> parseSettingsFile(const QString &settingsFilePath)
{
    std::optional<data::Preferences> result = std::nullopt;
    QFile settinsgFile(settingsFilePath);

    const auto SETTING_ELEMENT = QStringLiteral("setting");
    const auto SETTINGS_ELEMENT = QStringLiteral("soapui-settings");
    if (settinsgFile.open(QIODeviceBase::ReadOnly | QIODevice::Text))
    {
        data::Preferences preferences;
        QXmlStreamReader settingsReader(&settinsgFile);
        while (!settingsReader.atEnd())
        {
            settingsReader.readNext();

            if (settingsReader.isStartElement()
                    && settingsReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                    && settingsReader.name() == SETTINGS_ELEMENT)
            {
                do
                {
                    settingsReader.readNext();

                    if (settingsReader.isStartElement()
                            && settingsReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                            && settingsReader.name() == SETTING_ELEMENT)
                    {
                        auto settingsEntryAttributes = settingsReader.attributes();
                        QString id = QString(settingsEntryAttributes.value(DEFAULT_NAMESPACE, QStringLiteral("id")));
                        QVariant value;

                        do
                        {
                            settingsReader.readNext();

                            if (settingsReader.isCharacters())
                            {
                                if (id == QLatin1StringView("WsdlSettings@excluded-types") || id == QLatin1StringView("RecentAssertionSettings@recent-assertions"))
                                {
                                    value = parseSettingsValueList(settingsReader.text());
                                }
                                else if (id == QLatin1StringView("RecentProjects") || id == QLatin1StringView("RecentWorkspaces"))
                                {
                                    value = QVariant::fromValue(parseSettingsKeyValueList(settingsReader.text()));
                                }
                                else if (id == QLatin1StringView("GlobalPropertySettings@properties") || id == QLatin1StringView("GlobalPropertySettings@security_scans_properties"))
                                {
                                    value = QVariant::fromValue(parseSettingsPropertyList(settingsReader.text()));
                                }
                                else
                                {
                                    value = QString(settingsReader.text());
                                }
                            }
                        } while(!settingsReader.atEnd() && !(settingsReader.isEndElement()
                                                              && settingsReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                              && settingsReader.name() == SETTING_ELEMENT));

                        preferences.insert(id, value);
                    }
                } while (!settingsReader.atEnd() && !(settingsReader.isEndElement()
                                                      && settingsReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                      && settingsReader.name() == SETTINGS_ELEMENT));
            }
        }
        settinsgFile.close();

        result = preferences;
    }

    return result;
}

std::optional<data::Workspace> parseWorkspaceFile(const QString &workspaceFilePath)
{
    std::optional<data::Workspace> result = std::nullopt;
    QFile workspaceFile(workspaceFilePath);

    const auto PROJECT_ELEMENT = QStringLiteral("project");
    const auto WORKSPACE_ELEMENT = QStringLiteral("soapui-workspace");
    if (workspaceFile.open(QIODeviceBase::ReadOnly | QIODevice::Text))
    {
        data::Workspace workspace;
        QXmlStreamReader workspaceReader(&workspaceFile);
        while (!workspaceReader.atEnd())
        {
            workspaceReader.readNext();

            if (workspaceReader.isStartElement()
                    && workspaceReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                    && workspaceReader.name() == WORKSPACE_ELEMENT)
            {
                auto workspaceAttributes = workspaceReader.attributes();
                workspace.name = QString(workspaceAttributes.value(DEFAULT_NAMESPACE, QStringLiteral("name")));
                workspace.appVersion = QString(workspaceAttributes.value(DEFAULT_NAMESPACE, QStringLiteral("soapui-version")));

                do
                {
                    workspaceReader.readNext();

                    if (workspaceReader.isStartElement()
                            && workspaceReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                            && workspaceReader.name() == PROJECT_ELEMENT)
                    {
                        data::ProjectEntry projectEntry;
                        auto projectAttributes = workspaceReader.attributes();
                        projectEntry.name = QString(projectAttributes.value(DEFAULT_NAMESPACE, QStringLiteral("name")));
                        projectEntry.closed = projectAttributes.value(DEFAULT_NAMESPACE, QStringLiteral("status")) == QStringLiteral("CLOSED");
                        projectEntry.remote = projectAttributes.value(DEFAULT_NAMESPACE, QStringLiteral("type")) == QStringLiteral("REMOTE");

                        do
                        {
                            workspaceReader.readNext();

                            if (workspaceReader.isCharacters())
                            {
                                projectEntry.path = QString(workspaceReader.text());
                            }
                        } while(!workspaceReader.atEnd() && !(workspaceReader.isEndElement()
                                                              && workspaceReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                              && workspaceReader.name() == PROJECT_ELEMENT));

                        workspace.projects << projectEntry;
                    }
                } while (!workspaceReader.atEnd() && !(workspaceReader.isEndElement()
                                                       && workspaceReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                       && workspaceReader.name() == WORKSPACE_ELEMENT));
            }
        }
        if (workspaceReader.hasError())
        {
            qDebug() << "An error occurred during workspace file parsing: " << workspaceReader.errorString();
        }
        workspaceFile.close();

        result = workspace;
    }

    return result;
}

} // namespace xml
