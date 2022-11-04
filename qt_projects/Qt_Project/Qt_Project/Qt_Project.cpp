#include "Qt_Project.h"
#include <QDebug>

Qt_Project::Qt_Project(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

Qt_Project::~Qt_Project()
{}

void Qt_Project::on_button_login_clicked()
{
    QString user = ui.line_user->text();
    QString pass = ui.line_password->text();

    if (user == "a"  && pass == "b")
    {
        ui.label->setText("basarili");
    }
}


