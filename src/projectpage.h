#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include "project.h"

#include <QWidget>

namespace Ui { class ProjectPage; }

class ProjectPage : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectPage(QWidget *parent = nullptr);
    ~ProjectPage();

    void initialize(const std::optional<data::Project> *project);

private:
    Ui::ProjectPage *ui;

};

#endif // PROJECTPAGE_H
