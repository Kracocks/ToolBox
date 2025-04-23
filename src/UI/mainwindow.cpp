#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../impl/ServiceDaoImpl.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	addService = new AddService();
	connect(addService, &AddService::accepted, this, &MainWindow::reload);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_addServiceBtn_clicked()
{
	qDebug() << "open dialog to add service";
	addService->open();
}

void MainWindow::reload() {
	impl::ServiceDaoImpl services {};
	ui->servicesLV->clear();
	for (model::Service service : services.findAll()) {
		ui->servicesLV->addItem(QString::fromStdString(service.name));
	}
}
