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
	// get services
	impl::ServiceDaoImpl services {};
	std::vector<model::Service> all = services.findAll();
	// setting table
	ui->servicesTable->setRowCount(all.size());
	ui->servicesTable->clearContents();
	ui->servicesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// set header
	ui->servicesTable->setColumnCount(3);
	ui->servicesTable->setHorizontalHeaderLabels({"Name", "URL", ""});
	// add elements
	for (int row = 0; row < all.size(); ++row) {
		QPushButton *deleteBtn = new QPushButton("Delete");
		deleteBtn->setProperty("idService", all[row].id);
		connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::on_deleteServiceBtn_clicked);

		ui->servicesTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(all[row].name)));
		ui->servicesTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(all[row].url)));
		ui->servicesTable->setCellWidget(row, 2, deleteBtn);
	}
}

void MainWindow::on_deleteServiceBtn_clicked() {
	QWidget *w = qobject_cast<QWidget *>(sender());
	if (w) {
		impl::ServiceDaoImpl services {};
		int id = w->property("idService").toInt();
		model::Service service = services.find(id);
		qDebug() << service.id << QString::fromStdString(service.name) << QString::fromStdString(service.url);
		services.remove(services.find(id));
		reload();
		qDebug() << id;
	}
}
