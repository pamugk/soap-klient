#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "preferences.h"
#include <KXmlGuiWindow>

namespace Ui { class MainWindow; }

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Q_SLOT void selectWorkspaceModelItem(const QModelIndex &index);
    Q_SLOT void showPreferencesDialog();

private:
    data::Preferences preferences;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
