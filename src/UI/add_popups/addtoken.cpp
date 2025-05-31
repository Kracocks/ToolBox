#include "addtoken.h"
#include "ui_addtoken.h"
#include "../impl/TokenDaoImpl.h"
#include "../model/Token.h"
#include <QDebug>
#include <QMessageBox>

AddToken::AddToken(int loginId, QWidget *parent) : QDialog(parent), ui(new Ui::AddToken), m_loginId(loginId) {
	ui->setupUi(this);

	QDate date = QDate::currentDate();
	ui->expDateEdit->setDate(date);
	ui->expDateEdit->setMinimumDate(date);
}

AddToken::~AddToken() { delete ui; }

void AddToken::on_buttonBox_accepted()
{

}


void AddToken::on_buttonBox_rejected()
{
	qDebug() << "cancel adding token";
	this->close();
}

void AddToken::accept() {
	if (ui->valueTf->text().isEmpty()) {
		QMessageBox::warning(this, "Error adding token", "The token could not have been added because no value were provided");
		return;
	}
	impl::TokenDaoImpl tokens;
	model::Token token {0,
				 m_loginId,
				 ui->valueTf->text().toStdString(),
				 ui->descPtf->toPlainText().toStdString(),
				 ui->rbNo->isChecked() ? "" : ui->expDateEdit->date().toString().toStdString()
	};
	tokens.insert(token);
	if (token.id == -1) {
		QMessageBox::warning(this, "Error adding login", QString::fromStdString(token.description));
		return;
	}
	QDialog::accept();
	return;
}

void AddToken::on_viewValue_stateChanged(int arg1)
{
	if (arg1 == 0) { // unchecked
		ui->valueTf->setEchoMode(QLineEdit::Password);
	} else { // checked
		ui->valueTf->setEchoMode(QLineEdit::Normal);
	}
}


void AddToken::on_rbNo_toggled(bool checked)
{
	if (checked) {
		ui->expDateEdit->setEnabled(false);
	} else {
		ui->expDateEdit->setEnabled(true);
	}
}

