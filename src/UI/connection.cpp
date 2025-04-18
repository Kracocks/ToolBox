#include "connection.h"
#include "ui_connection.h"
#include "../bd/Connector.h"

#include <QDebug>
#include <QTime>

Connection::Connection(QWidget *parent) : QWidget(parent), ui(new Ui::Connection)
{
	attempt	= 3;
	ui->setupUi(this);
	mainwindow = new MainWindow();
	connect(ui->loginBtn, &QPushButton::clicked, this, &Connection::login);
	connect(ui->viewPwd, &QCheckBox::stateChanged, this, &Connection::viewPwd);
}

Connection::~Connection() { delete ui; }

void Connection::login() {
	const std::string pwd = ui->passwordTf->text().toStdString();
	qDebug() << "Loging in...";
	bd::Connector& bd = bd::Connector::getInstance(pwd);
	// If the database is still a nullptr this means the password is wrong

	if (bd.getDB()) {
		qDebug() << "ok";
		ui->informationLabel->setText("");
		mainwindow->show();
		this->close();
	} else {
		qDebug() << "Failed to open db";
		attempt--;
		ui->passwordTf->setEnabled(false);
		ui->informationLabel->setText("Verifying...");

		QTime dieTime= QTime::currentTime().addSecs(3);
		while (QTime::currentTime() < dieTime)
			QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

		if (attempt == 0) {
			ui->informationLabel->setText("wrong password No attempt left.\nLeaving...");
			QTime dieTime= QTime::currentTime().addSecs(3);
			while (QTime::currentTime() < dieTime)
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			QApplication::quit();
		}

		ui->passwordTf->clear();
		ui->passwordTf->setEnabled(true);
		ui->informationLabel->setText("wrong password\nattempts left : " + QString::number(attempt));
	}
}

void Connection::viewPwd() {
	if (ui->viewPwd->isChecked()) {
		ui->passwordTf->setEchoMode(QLineEdit::Normal);
	} else {
		ui->passwordTf->setEchoMode(QLineEdit::Password);
	}
}
