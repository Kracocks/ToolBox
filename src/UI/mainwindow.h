#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "addservice.h"
#include "loginswindow.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	void reload();
	~MainWindow();

private slots:
	void on_addServiceBtn_clicked();

private:
	AddService *addService;
	LoginsWindow *loginsWindow;
	void on_deleteServiceBtn_clicked();
	void on_row_doubleClicked();
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
