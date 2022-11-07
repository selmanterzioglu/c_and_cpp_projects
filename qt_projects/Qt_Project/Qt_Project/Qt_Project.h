#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Project.h"
#include "Home_page.h"

class Qt_Project : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Project(QWidget *parent = nullptr);
    ~Qt_Project();

private slots:
    void login_button_clicked();

private:
    Ui::Qt_ProjectClass ui;
    Home_page *home_page = new Home_page();
    void connect_widgets();
    void user_control();

};
