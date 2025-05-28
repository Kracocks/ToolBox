#include "loginswindow.h"
#include "ui_loginswindow.h"
#include "../impl/IdentifiantDaoImpl.h"
#include <QDebug>

LoginsWindow::LoginsWindow(model::Service &service, QWidget *parent) : QWidget(parent), ui(new Ui::LoginsWindow), m_service(service)
{
	ui->setupUi(this);
	reload();
	ui->title->setText("Logins from " + QString::fromStdString(service.name));

	// Setup the table
	ui->loginsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->loginsTable->setSelectionMode(QAbstractItemView::SingleSelection);

	addLogin = new AddLogin(m_service.id);
	// When service added, reload the table
	connect(addLogin, &AddLogin::accepted, this, &LoginsWindow::reload);

	// Interaction when double clicking a row
	connect(ui->loginsTable, &QTableWidget::itemDoubleClicked, this, &LoginsWindow::on_row_doubleClicked);
}

LoginsWindow::~LoginsWindow() { delete ui; }

void LoginsWindow::on_row_doubleClicked() {
	int row = ui->loginsTable->currentRow();
	impl::IdentifiantDaoImpl logins {};

	model::Login login = logins.find(ui->loginsTable->item(row, 0)->data(Qt::DisplayRole).toInt());
	tokensWindow = new TokensWindow(login);
	tokensWindow->show();
}

void LoginsWindow::on_deleteLoginBtn_clicked() {
	QWidget *w = qobject_cast<QWidget *>(sender());
	if (w) {
		impl::IdentifiantDaoImpl logins {};
		int id = w->property("idLogin").toInt();
		model::Login login = logins.find(id);
		qDebug() << login.id << QString::fromStdString(login.password) << QString::fromStdString(login.password);
		logins.remove(logins.find(id));
		reload();
	}
}

void LoginsWindow::reload() {
	// get logins
	impl::IdentifiantDaoImpl logins {};
	std::vector<model::Login> all = logins.findByService(m_service.id);
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
		deleteBtn->setProperty("idLogin", all[row].id);
		connect(deleteBtn, &QPushButton::clicked, this, &LoginsWindow::on_deleteLoginBtn_clicked);

		// set elements
		ui->loginsTable->setItem(row, 0, new QTableWidgetItem(QString::number(all[row].id)));
		ui->loginsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(all[row].email)));
		ui->loginsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(all[row].password)));
		ui->loginsTable->setCellWidget(row, 3, deleteBtn);
	}
}

void LoginsWindow::on_addLoginBtn_clicked()
{
	qDebug() << "open dialog to add login";
	addLogin->open();
}

