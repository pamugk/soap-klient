#ifndef OPERATIONCALL_H
#define OPERATIONCALL_H

#include <QString>

namespace data
{
struct WsaConfig
{
    QString mustUnderstand;
    QString version;
    QString action;
};

struct OperationCall
{
    QString id;
    QString name;
    QString encoding;
    QString endpoint;
    QString request;
    WsaConfig wsaConfig;
};
}

#endif // OPERATIONCALL_H
