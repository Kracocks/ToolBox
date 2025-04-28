#include "addlogin.h"
#include "ui_addlogin.h"
#include "../impl/IdentifiantDaoImpl.h"
#include "../model/Login.h"
#include "../model/Encrypt.h"
#include <QDebug>
#include <QMessageBox>

AddLogin::AddLogin(int serviceId, QWidget *parent) : QDialog(parent), ui(new Ui::AddLogin), m_serviceId(serviceId)
{
	ui->setupUi(this);
	connect(ui->viewPwd, &QCheckBox::stateChanged, this, &AddLogin::viewPwd);
}

AddLogin::~AddLogin() { delete ui; }

void AddLogin::on_buttonBox_accepted()
{

}


void AddLogin::on_buttonBox_rejected()
{
	qDebug() << "cancel adding login";
	this->close();
}

void AddLogin::accept() {
	if (ui->emailTf->text().isEmpty()){
		QMessageBox::warning(this, "Error adding login", "The login could not have been added because no email were provided");
		return;
	}
	if (ui->pwdTf->text().isEmpty()) {
		QMessageBox::warning(this, "Error adding login", "The login could not have been added because no password were provided");
		return;
	}
	impl::IdentifiantDaoImpl logins {};
	qDebug() << "here1";
	const std::string password = ui->pwdTf->text().toStdString();
	std::string encryptedPassword {};
	if (model::Encrypt::encrypt(password, &encryptedPassword)) {
		qDebug() << "here3";
		model::Login login {0, m_serviceId, ui->emailTf->text().toStdString(), encryptedPassword};
		qDebug() << "here4";
		logins.insert(login);
		if (login.id == -1) {
			QMessageBox::warning(this, "Error adding login", QString::fromStdString(login.email));
			return;
		}
		QDialog::accept();
		return;
	} else {
		QMessageBox::warning(this, "Error adding login", "Error while encrypting the password");
		return;
	}
}

void AddLogin::viewPwd() {
	if (ui->viewPwd->isChecked()) {
		ui->pwdTf->setEchoMode(QLineEdit::Normal);
	} else {
		ui->pwdTf->setEchoMode(QLineEdit::Password);
	}
}
