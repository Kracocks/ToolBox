#include "servicewindow.h"
#include "ui_servicewindow.h"
#include "../impl/ServiceDaoImpl.h"
#include "custom_widgets/showservicewidget.h"
#include <QDebug>

ServiceWindow::ServiceWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ServiceWindow)
{
	ui->setupUi(this);

	addService = new AddService();
	// When service added, reload the table
	connect(addService, &AddService::accepted, this, &ServiceWindow::on_AddService_accepted);

	layout_services = new FlowLayout();
	ui->scrollAreaWidgetContents->setLayout(layout_services);
}

ServiceWindow::~ServiceWindow() { delete ui; }

void ServiceWindow::on_addServiceBtn_clicked()
{
	qDebug() << "open dialog to add service";
	addService->open();
}

void ServiceWindow::on_AddService_accepted()
{
	ui->serviceNameSearch->setText("");
	reload();
}

void ServiceWindow::on_serviceNameSearch_textChanged(const QString &arg1)
{
	reload();
}

void ServiceWindow::reload()
{
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
		ShowServiceWidget *widget = new ShowServiceWidget(all[row]);
		layout_services->addWidget(widget);
		connect(widget, &ShowServiceWidget::delete_clicked,
				this, &ServiceWindow::reload);
	}
}
