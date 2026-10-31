#ifndef INTERFACEPAGE_H
#define INTERFACEPAGE_H

#include "interface.h"

#include <QWidget>

namespace Ui { class InterfacePage; }

class InterfacePage : public QWidget
{
    Q_OBJECT
public:
    explicit InterfacePage(QWidget *parent = nullptr);
    ~InterfacePage();

    void initialize(const data::Interface *interface);

private:
    Ui::InterfacePage *ui;
};

#endif // INTERFACEPAGE_H
