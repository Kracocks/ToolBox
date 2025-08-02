#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servicewindow.h"
#include "loginswindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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
	reload();
}

void MainWindow::showLoginsWindow(model::Service &service)
{
	LoginsWindow *logins_window = new LoginsWindow(service, this);
	connect(logins_window, &LoginsWindow::return_clicked, this, &MainWindow::back);
	connect(logins_window, &LoginsWindow::details_clicked, this, &MainWindow::showTokensWindow);
	ui->stackedWidget->addWidget(logins_window);
	current_index = ui->stackedWidget->indexOf(logins_window);
	navigation_stack.push(logins_window);

	ui->stackedWidget->setCurrentWidget(logins_window);
	reload();
}

void MainWindow::showTokensWindow(model::Login &login)
{
	TokensWindow *tokens_window = new TokensWindow(login, this);
	ui->stackedWidget->addWidget(tokens_window);
	current_index = ui->stackedWidget->indexOf(tokens_window);
	navigation_stack.push(tokens_window);

	ui->stackedWidget->setCurrentWidget(tokens_window);
	reload();
}

void MainWindow::back()
{
	navigation_stack.pop();
	QWidget *previous_window = navigation_stack.top();
	current_index = ui->stackedWidget->indexOf(previous_window);

	ui->stackedWidget->setCurrentWidget(previous_window);
	reload();
}

void MainWindow::reload()
{
	QWidget *current_window = ui->stackedWidget->currentWidget();
	Reloadable *r = dynamic_cast<Reloadable*>(current_window);
	if (r) {
		r->reload();
	}
}
