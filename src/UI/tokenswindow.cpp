#include "tokenswindow.h"
#include "ui_tokenswindow.h"
#include "../impl/TokenDaoImpl.h"
#include <QDebug>

TokensWindow::TokensWindow(model::Login &login, QWidget *parent) : QWidget(parent), ui(new Ui::TokensWindow), m_login(login)
{
	ui->setupUi(this);
	reload();
	ui->title->setText("Tokens from " + QString::fromStdString(login.email));

	// Setup the table
	ui->tokensTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tokensTable->setSelectionMode(QAbstractItemView::SingleSelection);

	addToken = new AddToken(m_login.id);
	// When token added, reload the table
	connect(addToken, &AddToken::accepted, this, &TokensWindow::reload);
}

TokensWindow::~TokensWindow() { delete ui; }

void TokensWindow::on_deleteTokenBtn_clicked() {
	QWidget *w = qobject_cast<QWidget *>(sender());
	if (w) {
		impl::TokenDaoImpl tokens {};
		int id = w->property("idToken").toInt();
		model::Token token = tokens.find(id);
		tokens.remove(tokens.find(id));
		reload();
	}
}

void TokensWindow::reload() {
	// get logins
	impl::TokenDaoImpl tokens {};
	std::vector<model::Token> all = tokens.findByLogin(m_login.id);
	// setting table
	ui->tokensTable->setRowCount(all.size());
	ui->tokensTable->clearContents();
	ui->tokensTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// set header
	ui->tokensTable->setColumnCount(5);
	ui->tokensTable->setHorizontalHeaderLabels({"", "Value", "Description", "Expired at", ""});
	ui->tokensTable->setColumnHidden(0, true);
	// add elements
	for (int row = 0; row < all.size(); ++row) {
		// set delete button
		QPushButton *deleteBtn = new QPushButton("Delete");
		deleteBtn->setProperty("idToken", all[row].id);
		connect(deleteBtn, &QPushButton::clicked, this, &TokensWindow::on_deleteTokenBtn_clicked);

		// set elements
		ui->tokensTable->setItem(row, 0, new QTableWidgetItem(QString::number(all[row].id)));
		std::string decrypted_value {};
		ui->tokensTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(all[row].value)));
		ui->tokensTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(all[row].description)));
		ui->tokensTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(all[row].expired_at)));
		ui->tokensTable->setCellWidget(row, 4, deleteBtn);
	}
}

void TokensWindow::on_addTokenBtn_clicked()
{
	qDebug() << "open dialog to add token";
	addToken->open();
}

