#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../impl/ServiceDaoImpl.h"
#include "custom_widgets/showservicewidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Setup the table
	ui->servicesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->servicesTable->setSelectionMode(QAbstractItemView::SingleSelection);

	addService = new AddService();
	// When service added, reload the table
	connect(addService, &AddService::accepted, this, &MainWindow::on_AddService_accepted);

	// Interaction when double clicking a row
	connect(ui->servicesTable, &QTableWidget::itemDoubleClicked, this, &MainWindow::on_row_doubleClicked);

	layout_services = new FlowLayout();
	ui->scrollAreaWidgetContents->setLayout(layout_services);
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

	model::Service service = services.find(ui->servicesTable->item(row, 0)->data(Qt::DisplayRole).toInt());
	loginsWindow = new LoginsWindow(service);
	loginsWindow->show();
}

void MainWindow::reload() {
	// get services
	impl::ServiceDaoImpl services {};
	std::vector<model::Service> all {};
	std::string name = ui->serviceNameSearch->text().toStdString();

	QLayoutItem *item;
	while ((item = layout_services->takeAt(0)) != nullptr) {
		if (QWidget *widget = item->widget()) {
			widget->deleteLater();
		}
		delete item;
	}

	if (name.empty()) {
		all = services.findAll();
	} else {
		all = services.findByName(name);
	}
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

		ShowServiceWidget *widget = new ShowServiceWidget(all[row]);
		layout_services->addWidget(widget);
		connect(widget, &ShowServiceWidget::delete_clicked,
				this, &MainWindow::reload);
	}
}

void MainWindow::on_deleteServiceBtn_clicked() {
	QWidget *w = qobject_cast<QWidget *>(sender());
	if (w) {
		impl::ServiceDaoImpl services {};
		int id = w->property("idService").toInt();
		model::Service service = services.find(id);
		services.remove(services.find(id));
		reload();
	}
}

void MainWindow::on_AddService_accepted() {
	ui->serviceNameSearch->setText("");
	reload();
}

void MainWindow::on_serviceNameSearch_textChanged(const QString &arg1)
{
	reload();
}

