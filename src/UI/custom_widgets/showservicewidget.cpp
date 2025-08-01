#include "showservicewidget.h"
#include "ui_showservicewidget.h"
#include "../../impl/ServiceDaoImpl.h"
#include <QClipboard>
#include <QThread>
#include <QTimer>
#include <QMessageBox>

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

void ShowServiceWidget::on_details_btn_clicked()
{
	emit details_clicked(m_service);
}

void ShowServiceWidget::on_copy_url_btn_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(ui->service_url->text(), QClipboard::Clipboard);
	if (clipboard->supportsSelection()) {
		clipboard->setText(ui->service_url->text(), QClipboard::Selection);
	}
	#if defined(Q_OS_LINUX)
		QThread::msleep(1); //workaround for copied text not being available...
	#endif

	QMessageBox* msgbox = new QMessageBox(this);
	msgbox->setWindowTitle("Note");
	msgbox->setText("Successfully copied link to clipboard");
	msgbox->open();

	QTimer* timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), msgbox, SLOT(close()));
	QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
	QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
	timer->start(1000);
}
