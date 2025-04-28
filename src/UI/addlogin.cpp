#include "addlogin.h"
#include "ui_addlogin.h"
#include "../impl/IdentifiantDaoImpl.h"
#include "../model/Identifiant.h"
#include <QDebug>
#include <QMessageBox>

AddLogin::AddLogin(int serviceId, QWidget *parent) : QDialog(parent), ui(new Ui::AddLogin), m_serviceId(serviceId) { ui->setupUi(this); }

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
	model::Identifiant<> login {0, ui->emailTf->text().toStdString(), ui->pwdTf->text().toStdString(), m_serviceId};
	logins.insert(login);
	if (login.getId() == -1) {
		QMessageBox::warning(this, "Error adding login", QString::fromStdString(login.getEmail()));
		return;
	}
	QDialog::accept();
}
