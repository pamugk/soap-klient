#ifndef OPERATIONCALLPAGE_H
#define OPERATIONCALLPAGE_H

#include <QWidget>

namespace Ui { class OperationCallPage; }

class OperationCallPage : public QWidget
{
    Q_OBJECT
public:
    explicit OperationCallPage(QWidget *parent = nullptr);
    ~OperationCallPage();

private:
    Ui::OperationCallPage *ui;

};

#endif // OPERATIONCALLPAGE_H
