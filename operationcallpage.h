#ifndef OPERATIONCALLPAGE_H
#define OPERATIONCALLPAGE_H

#include "interface.h"
#include "operationcall.h"
#include "soapclient.h"
#include <QWidget>

namespace Ui { class OperationCallPage; }

class OperationCallPage : public QWidget
{
    Q_OBJECT
public:
    explicit OperationCallPage(QWidget *parent = nullptr);
    ~OperationCallPage();

    void initialize(const data::Interface *interface,
                    const data::Operation *operation,
                    const data::OperationCall *operationCall);
    Q_SLOT void sendRequest();

private:
    SoapVersion interfaceSoapVersion;
    QString operationSoapAction;
    SoapClient *soapClient;
    Ui::OperationCallPage *ui;

};

#endif // OPERATIONCALLPAGE_H
