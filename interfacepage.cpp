#include "interfacepage.h"
#include "ui_interfacepage.h"

InterfacePage::InterfacePage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::InterfacePage)
{
    ui->setupUi(this);
}

InterfacePage::~InterfacePage()
{
    delete ui;
}
