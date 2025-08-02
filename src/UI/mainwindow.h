#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
#include "../model/Service.h"
#include "../model/Login.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void showServicesWindow();
	void showLoginsWindow(model::Service &service);
	void showTokensWindow(model::Login &login);

private:
	int current_index;
	std::stack<QWidget*> navigation_stack;
	Ui::MainWindow *ui;

	void back();
	void reload();
};

#endif // MAINWINDOW_H
