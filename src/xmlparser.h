#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "preferences.h"
#include "project.h"
#include "workspace.h"

#include <optional>
#include <QObject>
#include <QString>

namespace xml {

std::optional<data::Project> parseProjectFile(const QString &projectFilePath);

std::optional<data::Preferences> parseSettingsFile(const QString &settingsFilePath);

std::optional<data::Workspace> parseWorkspaceFile(const QString &workspaceFilePath);

} // namespace xml

#endif // XMLPARSER_H
