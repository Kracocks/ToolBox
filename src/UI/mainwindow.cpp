#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servicewindow.h"
#include "loginswindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	showServicesWindow();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showServicesWindow()
{
	ServiceWindow *services_window = new ServiceWindow(this);
	connect(services_window, &ServiceWindow::details_cliked, this, &MainWindow::showLoginsWindow);
	ui->stackedWidget->addWidget(services_window);
	current_index = ui->stackedWidget->indexOf(services_window);
	navigation_stack.push(services_window);

	ui->stackedWidget->setCurrentWidget(services_window);
}

void MainWindow::showLoginsWindow(model::Service &service)
{
	LoginsWindow *logins_window = new LoginsWindow(service, this);
	ui->stackedWidget->addWidget(logins_window);
	current_index = ui->stackedWidget->indexOf(logins_window);
	navigation_stack.push(logins_window);

	ui->stackedWidget->setCurrentWidget(logins_window);
}

void MainWindow::reload()
{
	QWidget *current_window = ui->stackedWidget->currentWidget();
	Reloadable *r = dynamic_cast<Reloadable*>(current_window);
	if (r) {
		r->reload();
	}
}
