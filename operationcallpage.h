#ifndef OPERATIONCALLPAGE_H
#define OPERATIONCALLPAGE_H

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

    void initialize(const data::OperationCall *data);
    Q_SLOT void sendRequest();

private:
    SoapClient *soapClient;
    Ui::OperationCallPage *ui;

};

#endif // OPERATIONCALLPAGE_H
