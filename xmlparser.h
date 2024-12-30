#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "datastructures.h"

#include <QObject>
#include <QString>

namespace xml {

data::Workspace parseWorkspaceFile(const QString &workspaceFilePath);

} // namespace xml

#endif // XMLPARSER_H
