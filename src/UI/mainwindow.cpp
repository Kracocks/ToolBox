#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servicewindow.h"
#include "loginswindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ServiceWindow *services_window = new ServiceWindow(this);
	connect(services_window, &ServiceWindow::details_cliked, this, &MainWindow::showLogins);
	ui->stackedWidget->addWidget(services_window);
	current_index = ui->stackedWidget->indexOf(services_window);
	navigation_stack.push(services_window);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showLogins(model::Service &service)
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
