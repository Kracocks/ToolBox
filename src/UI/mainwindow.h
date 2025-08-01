#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
#include "../model/Service.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void reload();

private:
	int current_index;
	std::stack<QWidget*> navigation_stack;
	Ui::MainWindow *ui;

	void showLogins(model::Service &service);
};

#endif // MAINWINDOW_H
