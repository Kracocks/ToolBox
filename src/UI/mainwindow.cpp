#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../impl/ServiceDaoImpl.h"
#include "custom_widgets/showservicewidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	addService = new AddService();
	// When service added, reload the table
	connect(addService, &AddService::accepted, this, &MainWindow::on_AddService_accepted);

	layout_services = new FlowLayout();
	ui->scrollAreaWidgetContents->setLayout(layout_services);
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
	std::vector<model::Service> all {};
	std::string name = ui->serviceNameSearch->text().toStdString();
	if (name.empty()) {
		all = services.findAll();
	} else {
		all = services.findByName(name);
	}

	// clearing layout
	QLayoutItem *item;
	while ((item = layout_services->takeAt(0)) != nullptr) {
		if (QWidget *widget = item->widget()) {
			widget->deleteLater();
		}
		delete item;
	}

	// add elements
	for (int row = 0; row < all.size(); ++row) {
		// set delete button
		QPushButton *deleteBtn = new QPushButton("Delete");
		deleteBtn->setProperty("idService", all[row].id);
		connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::on_deleteServiceBtn_clicked);

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

