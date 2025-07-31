#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servicewindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ServiceWindow *services_window = new ServiceWindow(this);
	ui->stackedWidget->addWidget(services_window);
	current_index = ui->stackedWidget->indexOf(services_window);
	navigation_stack.push(services_window);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::reload()
{
	QWidget *current_window = ui->stackedWidget->currentWidget();
	Reloadable *r = dynamic_cast<Reloadable*>(current_window);
	if (r) {
		r->reload();
	}
}
