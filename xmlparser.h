#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "preferences.h"
#include "workspace.h"

#include <QObject>
#include <QString>

namespace xml {

data::Preferences parseSettingsFile(const QString &settingsFilePath);

data::Workspace parseWorkspaceFile(const QString &workspaceFilePath);

} // namespace xml

#endif // XMLPARSER_H
