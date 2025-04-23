#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "addservice.h"

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
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
