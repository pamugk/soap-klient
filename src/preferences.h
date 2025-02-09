#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QHash>
#include <QList>
#include <QString>
#include <QVariant>

namespace data
{
class Preferences
{
    QHash<QString, QVariant> configuration;
    QList<QString> configurationKeys;

public:
    void insert(const QString &key, const QVariant &value)
    {
        if (!configuration.contains(key))
        {
            configurationKeys << key;
        }
        configuration[key] = value;
    }

    const QVariant value(const QString &key)
    {
        return configuration.value(key);
    }
};
}

#endif // PREFERENCES_H
