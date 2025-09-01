#include "showtokenwidget.h"
#include "ui_showtokenwidget.h"
#include "../../impl/TokenDaoImpl.h"
#include <QClipboard>
#include <QThread>
#include <QTimer>
#include <QMessageBox>

ShowTokenWidget::ShowTokenWidget(model::Token &token, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ShowTokenWidget),
	m_token(token)
{
	ui->setupUi(this);

	show_view();
}

ShowTokenWidget::~ShowTokenWidget() { delete ui; }

void ShowTokenWidget::show_view()
{
	ui->token_value->setText(QString::fromStdString(m_token.value));
	ui->token_description->setText(QString::fromStdString(m_token.description));
	ui->stackedWidget->setCurrentWidget(ui->View);
}

void ShowTokenWidget::show_edit()
{
	// TODO : show edit
}

void ShowTokenWidget::on_copy_value_btn_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(ui->token_value->text(), QClipboard::Clipboard);
	if (clipboard->supportsSelection()) {
		clipboard->setText(ui->token_value->text(), QClipboard::Selection);
	}
#if defined(Q_OS_LINUX)
	QThread::msleep(1); //workaround for copied text not being available...
#endif

	QMessageBox* msgbox = new QMessageBox(this);
	msgbox->setWindowTitle("Note");
	msgbox->setText("Successfully copied value to clipboard");
	msgbox->open();

	QTimer* timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), msgbox, SLOT(close()));
	QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
	QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
	timer->start(1000);
}

void ShowTokenWidget::on_edit_btn_clicked()
{
	show_edit();
}

void ShowTokenWidget::on_delete_btn_clicked()
{
	impl::TokenDaoImpl logins {};
	logins.remove(m_token);
	emit delete_clicked();
}
