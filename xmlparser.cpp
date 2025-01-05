#include "xmlparser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QXmlStreamReader>

namespace xml {

const QLatin1StringView DEFAULT_NAMESPACE = QLatin1StringView("");
const QLatin1StringView SOAPUI_CONFIG_NAMESPACE = QLatin1StringView("http://eviware.com/soapui/config");

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
            result.append(QPair<QString, QString>(QString(xmlReader.attributes().value(DEFAULT_NAMESPACE, "key")),
                                                  QString(xmlReader.attributes().value(DEFAULT_NAMESPACE, "value"))));
        }
    }

    return result;
}

QList<QPair<QString, QString>> parseSettingsPropertyList(const QStringView &xml)
{
    QList<QPair<QString, QString>> result;

    const QLatin1StringView NAME_ELEMENT = QLatin1StringView("name");
    const QLatin1StringView PROPERTY_ELEMENT = QLatin1StringView("property");
    const QLatin1StringView VALUE_ELEMENT = QLatin1StringView("value");

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
                    if (xmlReader.name() == NAME_ELEMENT)
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
                    else if (xmlReader.name() == VALUE_ELEMENT)
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

    const QLatin1StringView ENTRY_ELEMENT = QLatin1StringView("entry");

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

data::Preferences parseSettingsFile(const QString &settingsFilePath)
{
    data::Preferences preferences;
    QFile settinsgFile(settingsFilePath);

    const QLatin1StringView SETTING_ELEMENT = QLatin1StringView("setting");
    const QLatin1StringView SETTINGS_ELEMENT = QLatin1StringView("soapui-settings");
    if (settinsgFile.open(QIODeviceBase::ReadOnly | QIODevice::Text))
    {
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
                } while (!settingsReader.atEnd() && !(settingsReader.isEndElement()
                                                      && settingsReader.namespaceUri() == SOAPUI_CONFIG_NAMESPACE
                                                      && settingsReader.name() == SETTINGS_ELEMENT));
            }
        }
    }

    return preferences;
}

data::Workspace parseWorkspaceFile(const QString &workspaceFilePath)
{
    data::Workspace workspace;
    QFile workspaceFile(workspaceFilePath);

    const QLatin1StringView PROJECT_ELEMENT = QLatin1StringView("project");
    const QLatin1StringView WORKSPACE_ELEMENT = QLatin1StringView("soapui-workspace");
    if (workspaceFile.open(QIODeviceBase::ReadOnly | QIODevice::Text))
    {
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
                        projectEntry.status = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("status")));
                        projectEntry.type = QString(projectAttributes.value(DEFAULT_NAMESPACE, QLatin1StringView("type")));

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
    }

    return workspace;
}

} // namespace xml
