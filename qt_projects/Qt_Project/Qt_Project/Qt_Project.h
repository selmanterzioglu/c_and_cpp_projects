#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Project.h"

class Qt_Project : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Project(QWidget *parent = nullptr);
    ~Qt_Project();

private slots:
    void on_button_login_clicked();

private:
    Ui::Qt_ProjectClass ui;

};
