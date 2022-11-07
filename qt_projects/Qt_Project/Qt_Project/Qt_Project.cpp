#include "Qt_Project.h"

Qt_Project::Qt_Project(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    Qt_Project::connect_widgets();
}

Qt_Project::~Qt_Project(){}

void Qt_Project::connect_widgets()
{
    connect(ui.button_login, &QPushButton::released, this, &Qt_Project::login_button_clicked);
}

void Qt_Project::user_control()
{
    QString user = ui.line_user->text();
    QString pass = ui.line_password->text();

    if (user == "user" && pass == "pass")
    {
        ui.label->setText("login succesfull");
    }
}
void Qt_Project::login_button_clicked()
{
    //Qt_Project::user_control(); // this func controls user via its password
    this->home_page->show();
    this->hide();

}


