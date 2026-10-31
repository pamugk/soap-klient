#include "xmlparser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QXmlStreamReader>

namespace xml {

const auto DEFAULT_NAMESPACE = QLatin1StringView("");
const auto SOAPUI_CONFIG_NAMESPACE = QLatin1StringView("http://eviware.com/soapui/config");

const auto DEFINITION_CACHE_ELEMENT = QLatin1StringView("definitionCache");
const auto ENDPOINT_ELEMENT = QLatin1StringView("endpoint");
const auto INTERFACE_ELEMENT = QLatin1StringView("interface");
const auto OPERATION_ELEMENT = QLatin1StringView("operation");
const auto TEST_CASE_ELEMENT = QLatin1StringView("testCase");
const auto TEST_STEP_ELEMENT = QLatin1StringView("testStep");
const auto TEST_SUITE_ELEMENT = QLatin1StringView("testSuite");

void skipUnknownSection(QXmlStreamReader &projectReader)
{
    if (!projectReader.isStartElement())
    {
        return;
    }

    unsigned int nestedLevel = 1;
    do
    {
        projectReader.readNext();

        if (projectReader.isStartElement())
        {
            nestedLevel++;
        }
        else if (projectReader.isEndElement())
        {
            nestedLevel--;
        }
    } while (!projectReader.atEnd() && nestedLevel > 0);
}

bool parseBoolean(const QAnyStringView &booleanValue)
{
    return booleanValue == "true";
}

void parseProjectInterfaceDefinitionCache(QXmlStreamReader &projectReader,
                                          data::DefinitionCache &definitionCache)
{
    const auto CONTENT_ELEMENT = QLatin1StringView("content");
    const auto PART_ELEMENT = QLatin1StringView("part");
    const auto TYPE_ELEMENT = QLatin1StringView("type");
    const auto URL_ELEMENT = QLatin1StringView("url");

    const auto definitionCacheAttributes = projectReader.attributes();
    definitionCache.type = QString(definitionCacheAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("type")));
    definitionCache.rootPart = QString(definitionCacheAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("rootPart")));
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
                    else
                    {
                        skipUnknownSection(projectReader);
                    }
                }
                else
                {
                    skipUnknownSection(projectReader);
                }
            } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                 && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                 && projectReader.name() == PART_ELEMENT));
            definitionCache.parts.append(part);
        }
        else
        {
            skipUnknownSection(projectReader);
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == DEFINITION_CACHE_ELEMENT));
}

data::Operation parseProjectInterfaceOperation(QXmlStreamReader &projectReader)
{
    const auto CALL_ELEMENT = QLatin1StringView("call");
    const auto ENCODING_ELEMENT = QLatin1StringView("encoding");
    const auto REQUEST_ELEMENT = QLatin1StringView("request");
    const auto WSA_CONFIG_ELEMENT = QLatin1StringView("wsaConfig");

    const auto operationAttributes = projectReader.attributes();
    data::Operation operation;
    operation.id = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
    operation.isOneWay = parseBoolean(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("isOneWay")));
    operation.action = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("action")));
    operation.name = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
    operation.bindingOperationName = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("bindingOperationName")));
    operation.type = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("type")));
    operation.outputName = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("outputName")));
    operation.inputName = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("inputName")));
    operation.receivesAttachments = parseBoolean(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("receivesAttachments")));
    operation.sendsAttachments = parseBoolean(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("sendsAttachments")));
    operation.anonymous = QString(operationAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("anonymous")));
    do
    {
        projectReader.readNext();

        if (projectReader.isStartElement()
                && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                && projectReader.name() == CALL_ELEMENT)
        {
            const auto callAttributes = projectReader.attributes();
            data::OperationCall call;
            call.id = QString(callAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
            call.name = QString(callAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
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
                        call.wsaConfig.mustUnderstand = QString(wsaConfigAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("mustUnderstand")));
                        call.wsaConfig.version = QString(wsaConfigAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("version")));
                        call.wsaConfig.action = QString(wsaConfigAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("action")));
                    }
                    else
                    {
                        skipUnknownSection(projectReader);
                    }
                }
                else
                {
                    skipUnknownSection(projectReader);
                }
            } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                 && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                 && projectReader.name() == CALL_ELEMENT));
            operation.calls.append(call);
        }
        else
        {
            skipUnknownSection(projectReader);
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == OPERATION_ELEMENT));
    return operation;
}

data::Interface parseProjectInterface(QXmlStreamReader &projectReader)
{
    const auto ENDPOINTS_ELEMENT = QLatin1StringView("endpoints");

    const auto interfaceAttributes = projectReader.attributes();
    data::Interface interfaceEntry;
    interfaceEntry.id = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
    interfaceEntry.wsaVersion = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("wsaVersion")));
    interfaceEntry.name = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
    interfaceEntry.type = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("type")));
    interfaceEntry.bindingName = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("bindingName")));
    interfaceEntry.soapVersion = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("soapVersion")));
    interfaceEntry.anonymous = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("anonymous")));
    interfaceEntry.definition = QString(interfaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("definition")));
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
                    else
                    {
                        skipUnknownSection(projectReader);
                    }
                } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                     && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                     && projectReader.name() == ENDPOINTS_ELEMENT));
            }
            else if (elementName == OPERATION_ELEMENT)
            {
                interfaceEntry.operations.append(parseProjectInterfaceOperation(projectReader));
            }
            else
            {
                skipUnknownSection(projectReader);
            }
        }
        else
        {
            skipUnknownSection(projectReader);
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == INTERFACE_ELEMENT));
    return interfaceEntry;
}

data::TestStep parseTestStep(QXmlStreamReader &projectReader)
{
    const auto testStepAttributes = projectReader.attributes();
    data::TestStep testStep;
    testStep.id = QString(testStepAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
    testStep.name = QString(testStepAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
    do
    {
        projectReader.readNext();
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == TEST_STEP_ELEMENT));
    return testStep;
}

data::TestCase parseTestCase(QXmlStreamReader &projectReader)
{
    const auto testCaseAttributes = projectReader.attributes();
    data::TestCase testCase;
    testCase.id = QString(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
    testCase.failOnError = parseBoolean(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("failOnError")));
    testCase.failTestCaseOnErrors = parseBoolean(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("failTestCaseOnErrors")));
    testCase.keepSession = parseBoolean(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("keepSession")));
    testCase.maxResults = testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("maxResults")).toUInt();
    testCase.name = QString(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
    testCase.searchProperties = parseBoolean(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("searchProperties")));
    testCase.name = QString(testCaseAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
    do
    {
        if (projectReader.readNextStartElement())
        {
            if (projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                    && projectReader.name() == TEST_STEP_ELEMENT)
            {
                testCase.testSteps.append(parseTestStep(projectReader));
            }
            else
            {
                skipUnknownSection(projectReader);
            }
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == TEST_CASE_ELEMENT));
    return testCase;
}

data::TestSuite parseTestSuite(QXmlStreamReader &projectReader)
{
    const auto RUN_TYPE_ELEMENT = QLatin1StringView("runType");

    const auto testSuiteAttributes = projectReader.attributes();
    data::TestSuite testSuite;
    testSuite.id = QString(testSuiteAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
    testSuite.name = QString(testSuiteAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
    do
    {
        if (projectReader.readNextStartElement())
        {
            if (projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                && projectReader.name() == RUN_TYPE_ELEMENT)
            {
                do
                {
                    projectReader.readNext();

                    if (projectReader.isCharacters())
                    {
                        testSuite.runType = QString(projectReader.text());
                    }
                } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                     && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                     && projectReader.name() == RUN_TYPE_ELEMENT));
            }
            else if (projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                    && projectReader.name() == TEST_CASE_ELEMENT)
            {
                testSuite.testCases.append(parseTestCase(projectReader));
            }
            else
            {
                skipUnknownSection(projectReader);
            }
        }
    } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                         && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                         && projectReader.name() == TEST_SUITE_ELEMENT));
    return testSuite;
}

std::optional<data::Project> parseProjectFile(const QString &projectFilePath)
{
    std::optional<data::Project> result = std::nullopt;
    QFile projectFile(projectFilePath);

    const auto PROJECT_ELEMENT = QLatin1StringView("soapui-project");

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
                project.id = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
                project.activeEnvironment = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("activeEnvironment")));
                project.name = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
                project.resourceRoot = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("resourceRoot")));
                project.appVersion = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("soapui-version")));
                project.abortOnError = parseBoolean(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("abortOnError")));
                project.runType = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("runType")));
                do
                {
                    projectReader.readNext();

                    if (projectReader.isStartElement()
                            && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE)
                    {
                        if (projectReader.name() == INTERFACE_ELEMENT)
                        {
                            project.interfaces.append(parseProjectInterface(projectReader));
                        }
                        else if (projectReader.name() == TEST_SUITE_ELEMENT)
                        {
                            project.testSuites.append(parseTestSuite(projectReader));
                        }
                        else
                        {
                            skipUnknownSection(projectReader);
                        }
                    }
                    else
                    {
                        skipUnknownSection(projectReader);
                    }
                } while (!projectReader.atEnd() && !(projectReader.isEndElement()
                                                      && projectReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                      && projectReader.name() == PROJECT_ELEMENT));
            }
            else
            {
                skipUnknownSection(projectReader);
            }
        }
        projectFile.close();
        result = project;
    }
    return result;
}

QList<QPair<QString, QString>> parseSettingsKeyValueList(const QAnyStringView &xml)
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
            result.append(QPair<QString, QString>(QString(entryAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("key"))),
                                                  QString(entryAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("value")))));
        }
        else
        {
            skipUnknownSection(xmlReader);
        }
    }

    return result;
}

QList<QPair<QString, QString>> parseSettingsPropertyList(const QAnyStringView &xml)
{
    QList<QPair<QString, QString>> result;

    const auto NAME_ELEMENT = QLatin1StringView("name");
    const auto PROPERTY_ELEMENT = QLatin1StringView("property");
    const auto VALUE_ELEMENT = QLatin1StringView("value");

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
                    else
                    {
                        skipUnknownSection(xmlReader);
                    }
                }
                else
                {
                    skipUnknownSection(xmlReader);
                }
            } while (!xmlReader.atEnd() && !(xmlReader.isEndElement()
                                             && xmlReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                             && xmlReader.name() == PROPERTY_ELEMENT));
            result.append(QPair<QString, QString>(name, value));
        }
        else
        {
            skipUnknownSection(xmlReader);
        }
    }

    return result;
}

QStringList parseSettingsValueList(const QAnyStringView &xml)
{
    QStringList result;

    const auto ENTRY_ELEMENT = QLatin1StringView("entry");

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
        else
        {
            skipUnknownSection(xmlReader);
        }
    }

    return result;
}

std::optional<data::Preferences> parseSettingsFile(const QString &settingsFilePath)
{
    std::optional<data::Preferences> result = std::nullopt;
    QFile settinsgFile(settingsFilePath);

    const auto SETTING_ELEMENT = QLatin1StringView("setting");
    const auto SETTINGS_ELEMENT = QLatin1StringView("soapui-settings");
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
                        QString id = QString(settingsEntryAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("id")));
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
                    else
                    {
                        skipUnknownSection(settingsReader);
                    }
                } while (!settingsReader.atEnd() && !(settingsReader.isEndElement()
                                                      && settingsReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                      && settingsReader.name() == SETTINGS_ELEMENT));
            }
            else
            {
                skipUnknownSection(settingsReader);
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

    const auto PROJECT_ELEMENT = QLatin1StringView("project");
    const auto WORKSPACE_ELEMENT = QLatin1StringView("soapui-workspace");
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
                workspace.name = QString(workspaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
                workspace.appVersion = QString(workspaceAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("soapui-version")));

                do
                {
                    workspaceReader.readNext();

                    if (workspaceReader.isStartElement()
                            && workspaceReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                            && workspaceReader.name() == PROJECT_ELEMENT)
                    {
                        data::ProjectEntry projectEntry;
                        auto projectAttributes = workspaceReader.attributes();
                        projectEntry.name = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("name")));
                        projectEntry.closed = projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("status")) == QLatin1StringView("CLOSED");
                        projectEntry.remote = projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("type")) == QLatin1StringView("REMOTE");

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
                    else
                    {
                        skipUnknownSection(workspaceReader);
                    }
                } while (!workspaceReader.atEnd() && !(workspaceReader.isEndElement()
                                                       && workspaceReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                       && workspaceReader.name() == WORKSPACE_ELEMENT));
            }
            else
            {
                skipUnknownSection(workspaceReader);
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
