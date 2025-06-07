#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "add_popups/addservice.h"
#include "loginswindow.h"
#include "custom_widgets/flowlayout.h"

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

	void on_serviceNameSearch_textChanged(const QString &arg1);

private:
	AddService *addService;
	LoginsWindow *loginsWindow;
	FlowLayout *layout_services;
	void on_deleteServiceBtn_clicked();
	void on_AddService_accepted();
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
