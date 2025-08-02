#include "showpasswordwidget.h"
#include "ui_showpasswordwidget.h"
#include "../../impl/IdentifiantDaoImpl.h"
#include <QClipboard>
#include <QThread>
#include <QTimer>
#include <QMessageBox>

ShowPasswordWidget::ShowPasswordWidget(model::Login &login, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ShowPasswordWidget),
	m_login(login)
{
	ui->setupUi(this);

	ui->login_email->setText(QString::fromStdString(m_login.email));
	ui->login_pwd->setText(QString::fromStdString(m_login.password));
}

ShowPasswordWidget::~ShowPasswordWidget() { delete ui; }

void ShowPasswordWidget::on_delete_btn_clicked()
{
	impl::IdentifiantDaoImpl services {};
	services.remove(m_login);
	emit delete_clicked();
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

void ShowPasswordWidget::on_details_btn_clicked()
{
	emit details_clicked(m_login);
}
