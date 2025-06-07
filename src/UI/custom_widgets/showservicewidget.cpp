#include "showservicewidget.h"
#include "ui_showservicewidget.h"
#include "../../impl/ServiceDaoImpl.h"

ShowServiceWidget::ShowServiceWidget(model::Service &service, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ShowServiceWidget),
	m_service(service)
{
	ui->setupUi(this);

	ui->service_name->setText(QString::fromStdString(m_service.name));
	ui->service_url->setText(QString::fromStdString(m_service.url));

	if (m_service.url.empty()) {
		ui->copy_url_btn->setDisabled(true);
		ui->copy_url_btn->setHidden(true);
	}
}

ShowServiceWidget::~ShowServiceWidget() { delete ui; }

void ShowServiceWidget::on_delete_btn_clicked()
{
	impl::ServiceDaoImpl services {};
	services.remove(m_service);
	emit delete_clicked();
}
