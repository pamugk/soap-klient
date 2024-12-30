#include "xmlparser.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

namespace xml {

data::Workspace parseWorkspaceFile(const QString &workspaceFilePath)
{
    data::Workspace workspace;
    QFile workspaceFile(workspaceFilePath);

    const QLatin1StringView DEFAULT_NAMESPACE = QLatin1StringView("");
    const QLatin1StringView PROJECT_ELEMENT = QLatin1StringView("project");
    const QLatin1StringView SOAPUI_CONFIG_NAMESPACE = QLatin1StringView("http://eviware.com/soapui/config");
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

                    if (workspaceReader.isStartElement() && workspaceReader.name() == PROJECT_ELEMENT)
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
                        } while(!workspaceReader.atEnd() && !(workspaceReader.isEndElement() && workspaceReader.name() == PROJECT_ELEMENT));

                        workspace.projects << projectEntry;
                    }
                } while (!workspaceReader.atEnd() && !(workspaceReader.isEndElement() && workspaceReader.name() == WORKSPACE_ELEMENT));
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
