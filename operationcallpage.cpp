#include "operationcallpage.h"
#include "ui_operationcallpage.h"

OperationCallPage::OperationCallPage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::OperationCallPage)
{
    ui->setupUi(this);
}

OperationCallPage::~OperationCallPage()
{
    delete ui;
}
