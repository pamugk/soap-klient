#ifndef INTERFACEPAGE_H
#define INTERFACEPAGE_H

#include <QWidget>

namespace Ui { class InterfacePage; }

class InterfacePage : public QWidget
{
    Q_OBJECT
public:
    explicit InterfacePage(QWidget *parent = nullptr);
    ~InterfacePage();

private:
    Ui::InterfacePage *ui;
};

#endif // INTERFACEPAGE_H
