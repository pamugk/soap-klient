#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include "preferences.h"
#include <QDialog>

namespace Ui { class PreferencesDialog; }

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();

    void setPreferences(const data::Preferences &preferences);

private:
    data::Preferences preferences;
    Ui::PreferencesDialog *ui;
};

#endif // PREFERENCESDIALOG_H
