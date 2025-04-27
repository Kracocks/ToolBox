#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../impl/ServiceDaoImpl.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Setup the table
	ui->servicesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->servicesTable->setSelectionMode(QAbstractItemView::SingleSelection);

	addService = new AddService();
	// When service added, reload the table
	connect(addService, &AddService::accepted, this, &MainWindow::reload);

	// Interaction when double clicking a row
	connect(ui->servicesTable, &QTableWidget::itemDoubleClicked, this, &MainWindow::on_row_doubleClicked);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_addServiceBtn_clicked()
{
	qDebug() << "open dialog to add service";
	addService->open();
}

void MainWindow::on_row_doubleClicked() {
	int row = ui->servicesTable->currentRow();
	impl::ServiceDaoImpl services {};

	int serviceId = ui->servicesTable->model()->index(row, 0).data().toInt();
	model::Service service = services.find(ui->servicesTable->item(row, 0)->data(Qt::DisplayRole).toInt());
	loginsWindow = new LoginsWindow(service);
	loginsWindow->show();
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
	ui->servicesTable->setColumnCount(4);
	ui->servicesTable->setHorizontalHeaderLabels({"", "Name", "URL", ""});
	ui->servicesTable->setColumnHidden(0, true);
	// add elements
	for (int row = 0; row < all.size(); ++row) {
		// set delete button
		QPushButton *deleteBtn = new QPushButton("Delete");
		deleteBtn->setProperty("idService", all[row].id);
		connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::on_deleteServiceBtn_clicked);

		// set elements
		ui->servicesTable->setItem(row, 0, new QTableWidgetItem(QString::number(all[row].id)));
		ui->servicesTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(all[row].name)));
		ui->servicesTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(all[row].url)));
		ui->servicesTable->setCellWidget(row, 3, deleteBtn);
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
	}
}
