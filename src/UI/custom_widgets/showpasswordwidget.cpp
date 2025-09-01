#include "showpasswordwidget.h"
#include "ui_showpasswordwidget.h"
#include "../../impl/IdentifiantDaoImpl.h"
#include <QClipboard>
#include <QThread>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

ShowPasswordWidget::ShowPasswordWidget(model::Login &login, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ShowPasswordWidget),
	m_login(login)
{
	ui->setupUi(this);

	ui->stackedWidget->setCurrentWidget(ui->View);

	ui->login_email->setText(QString::fromStdString(m_login.email));
	ui->login_pwd->setText(QString::fromStdString(m_login.password));
}

ShowPasswordWidget::~ShowPasswordWidget() { delete ui; }

void ShowPasswordWidget::show_view()
{
	ui->login_email->setText(QString::fromStdString(m_login.email));
	ui->login_pwd->setText(QString::fromStdString(m_login.password));
	ui->stackedWidget->setCurrentWidget(ui->View);
}

void ShowPasswordWidget::on_copy_pwd_btn_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(ui->login_pwd->text(), QClipboard::Clipboard);
	if (clipboard->supportsSelection()) {
		clipboard->setText(ui->login_pwd->text(), QClipboard::Selection);
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

void ShowPasswordWidget::on_update_btn_clicked()
{
	ui->new_email_tf->setText(QString::fromStdString(m_login.email));
	ui->new_pwd_tf->setText(QString::fromStdString(m_login.password));
	ui->stackedWidget->setCurrentWidget(ui->Edit);
}

void ShowPasswordWidget::on_details_btn_clicked()
{
	emit details_clicked(m_login);
}

void ShowPasswordWidget::on_delete_btn_clicked()
{
	impl::IdentifiantDaoImpl logins {};
	logins.remove(m_login);
	emit delete_clicked();
}

void ShowPasswordWidget::on_edit_accepted()
{
	qDebug() << "clicked accept edit of " << QString::fromStdString(m_login.email);
	if (ui->new_email_tf->text().isEmpty() || ui->new_pwd_tf->text().isEmpty()){
		QMessageBox::warning(this, "Error editing service", "The service could not have been edited because no email or password were provided");
		return;
	}
	impl::IdentifiantDaoImpl logins {};
	model::Login new_login {0, m_login.service_id, ui->new_email_tf->text().toStdString(), ui->new_pwd_tf->text().toStdString()};
	qDebug() << QString::fromStdString(new_login.email + " " + new_login.password);
	logins.update(m_login.id, new_login);
	if (new_login.id == -1) {
		QMessageBox::warning(this, "Error editing service", QString::fromStdString(new_login.email));
		return;
	}

	qDebug() << "edit confirmed";
	m_login = new_login;
	show_view();
	emit update_confirm_clicked(m_login);
}

void ShowPasswordWidget::on_edit_rejected()
{
	show_view();
}

