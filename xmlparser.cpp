#include "xmlparser.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

namespace xml {

const QLatin1StringView DEFAULT_NAMESPACE = QLatin1StringView("");
const QLatin1StringView SOAPUI_CONFIG_NAMESPACE = QLatin1StringView("http://eviware.com/soapui/config");

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
                                value = QString(settingsReader.text());
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
