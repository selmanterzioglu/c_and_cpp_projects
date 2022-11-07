#pragma once

#include <QtWidgets/QMainWindow.h>
#include "ui_home_page.h"

class Home_page : public QMainWindow {
	
	Q_OBJECT

public:
	Home_page(QWidget *parent = nullptr);
	~Home_page();

private:
	Ui::Home_page ui;
};