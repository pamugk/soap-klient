#include "projectpage.h"
#include "ui_projectpage.h"

ProjectPage::ProjectPage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::ProjectPage)
{
    ui->setupUi(this);
}

ProjectPage::~ProjectPage()
{
    delete ui;
}

void ProjectPage::initialize(const std::optional<data::Project> *project)
{
}
