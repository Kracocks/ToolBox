#include "loginswindow.h"
#include "ui_loginswindow.h"
#include "../impl/IdentifiantDaoImpl.h"
#include <QDebug>

LoginsWindow::LoginsWindow(model::Service &service, QWidget *parent) : QWidget(parent), ui(new Ui::LoginsWindow)
{
	ui->setupUi(this);
	m_service = service;
	reload();
	ui->title->setText("Logins from " + QString::fromStdString(service.name));
}

LoginsWindow::~LoginsWindow() { delete ui; }

void LoginsWindow::on_deleteLoginBtn_clicked() {
	QWidget *w = qobject_cast<QWidget *>(sender());
	if (w) {
		impl::IdentifiantDaoImpl logins {};
		int id = w->property("idLogin").toInt();
		model::Identifiant<> login = logins.find(id);
		qDebug() << login.getId() << QString::fromStdString(login.getPassword()) << QString::fromStdString(login.getPassword());
		logins.remove(logins.find(id));
		reload();
	}
}

void LoginsWindow::reload() {
	// get logins
	impl::IdentifiantDaoImpl logins {};
	std::vector<model::Identifiant<>> all = logins.findByService(m_service.id);
	// setting table
	ui->loginsTable->setRowCount(all.size());
	ui->loginsTable->clearContents();
	ui->loginsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// set header
	ui->loginsTable->setColumnCount(4);
	ui->loginsTable->setHorizontalHeaderLabels({"", "Email", "Password", ""});
	ui->loginsTable->setColumnHidden(0, true);
	// add elements
	for (int row = 0; row < all.size(); ++row) {
		// set delete button
		QPushButton *deleteBtn = new QPushButton("Delete");
		deleteBtn->setProperty("idLogin", all[row].getId());
		connect(deleteBtn, &QPushButton::clicked, this, &LoginsWindow::on_deleteLoginBtn_clicked);

		// set elements
		ui->loginsTable->setItem(row, 0, new QTableWidgetItem(QString::number(all[row].getId())));
		ui->loginsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(all[row].getEmail())));
		ui->loginsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(all[row].getPassword())));
		ui->loginsTable->setCellWidget(row, 3, deleteBtn);
	}
}
