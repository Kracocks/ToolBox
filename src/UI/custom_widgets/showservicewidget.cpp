#include "showservicewidget.h"
#include "ui_showservicewidget.h"
#include "../../impl/ServiceDaoImpl.h"
#include <QClipboard>
#include <QThread>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

ShowServiceWidget::ShowServiceWidget(model::Service &service, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ShowServiceWidget),
	m_service(service)
{
	ui->setupUi(this);

	ui->stackedWidget->setCurrentWidget(ui->View); // Set to View widget by default

	ui->service_name->setText(QString::fromStdString(m_service.name));
	ui->service_url->setText(QString::fromStdString(m_service.url));

	if (m_service.url.empty()) {
		ui->copy_url_btn->setDisabled(true);
		ui->copy_url_btn->setHidden(true);
	}
}

ShowServiceWidget::~ShowServiceWidget() { delete ui; }

void ShowServiceWidget::show_view()
{
	ui->service_name->setText(QString::fromStdString(m_service.name));
	ui->service_url->setText(QString::fromStdString(m_service.url));
	ui->stackedWidget->setCurrentWidget(ui->View);
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

void ShowServiceWidget::on_update_btn_clicked()
{
	ui->new_name_tf->setText(QString::fromStdString(m_service.name));
	ui->new_url_tf->setText(QString::fromStdString(m_service.url));
	ui->stackedWidget->setCurrentWidget(ui->Edit); // Change to edit widget
}

void ShowServiceWidget::on_details_btn_clicked()
{
	emit details_clicked(m_service);
}

void ShowServiceWidget::on_delete_btn_clicked()
{
	impl::ServiceDaoImpl services {};
	services.remove(m_service);
	emit delete_clicked();
}

void ShowServiceWidget::on_edit_accepted()
{
	qDebug() << "clicked accept edit of " << QString::fromStdString(m_service.name);
	if (ui->new_name_tf->text().isEmpty()){
		QMessageBox::warning(this, "Error editing service", "The service could not have been edited because no name were provided");
		return;
	}
	impl::ServiceDaoImpl services {};
	model::Service new_service {0, ui->new_name_tf->text().toStdString(), ui->new_url_tf->text().toStdString()};
	services.update(m_service.id, new_service);
	if (new_service.id == -1) {
		QMessageBox::warning(this, "Error editing service", QString::fromStdString(new_service.name));
		return;
	}

	qDebug() << "edit confirmed";
	m_service = new_service;
	ui->stackedWidget->setCurrentWidget(ui->View);
	emit update_confirm_clicked(m_service);
}


void ShowServiceWidget::on_edit_rejected()
{
	ui->stackedWidget->setCurrentWidget(ui->View);
}
