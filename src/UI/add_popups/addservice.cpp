#include "addservice.h"
#include "ui_addservice.h"
#include "../impl/ServiceDaoImpl.h"
#include "../model/Service.h"
#include <QDebug>
#include <QMessageBox>

AddService::AddService(QWidget *parent) : QDialog(parent), ui(new Ui::AddService) { ui->setupUi(this); }

AddService::~AddService() { delete ui; }

void AddService::on_buttonBox_accepted()
{

}

void AddService::on_buttonBox_rejected()
{
	qDebug() << "cancel adding service";
	this->close();
}

void AddService::accept() {
	if (ui->nameTf->text().isEmpty()){
		QMessageBox::warning(this, "Error adding service", "The service could not have been added because no name were provided");
		return;
	}
	impl::ServiceDaoImpl services {};
	model::Service service {0, ui->nameTf->text().toStdString(), ui->urlTf->text().toStdString()};
	services.insert(service);
	if (service.id == -1) {
		QMessageBox::warning(this, "Error adding service", QString::fromStdString(service.name));
		return;
	}
	QDialog::accept();
}

