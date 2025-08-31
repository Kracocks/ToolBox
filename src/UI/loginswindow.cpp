#include "loginswindow.h"
#include "ui_loginswindow.h"
#include "../impl/IdentifiantDaoImpl.h"
#include "custom_widgets/showpasswordwidget.h"
#include <QDebug>

LoginsWindow::LoginsWindow(model::Service &service, QWidget *parent) : QWidget(parent), ui(new Ui::LoginsWindow), m_service(service)
{
	ui->setupUi(this);
	ui->title->setText("Logins from " + QString::fromStdString(service.name));

	addLogin = new AddLogin(m_service.id);
	// When service added, reload the table
	connect(addLogin, &AddLogin::accepted, this, &LoginsWindow::reload);

	layout_logins = new FlowLayout();
	ui->scrollAreaWidgetContents->setLayout(layout_logins);
}

LoginsWindow::~LoginsWindow() { delete ui; }

void LoginsWindow::on_returnBtn_clicked()
{
	emit return_clicked();
}

void LoginsWindow::on_addLoginBtn_clicked()
{
	qDebug() << "open dialog to add login";
	addLogin->open();
}

void LoginsWindow::on_details_clicked(model::Login &login)
{
	emit details_clicked(login);
}

void LoginsWindow::reload() {
	// get logins
	impl::IdentifiantDaoImpl logins {};
	std::vector<model::Login> all = logins.findByService(m_service.id);

	// clearing layout
	QLayoutItem *item;
	while ((item = layout_logins->takeAt(0)) != nullptr) {
		if (QWidget *widget = item->widget()) {
			widget->deleteLater();
		}
		delete item;
	}

	// add elements
	for (int row = 0; row < all.size(); ++row) {
		ShowPasswordWidget *widget = new ShowPasswordWidget(all[row]);
		layout_logins->addWidget(widget);
		//receive delete button click
		connect(widget, &ShowPasswordWidget::delete_clicked,
				this, &LoginsWindow::reload);
		//receive details button click
		connect(widget, &ShowPasswordWidget::details_clicked,
				this, &LoginsWindow::on_details_clicked);
		//received edit button confirm
		connect(widget, &ShowPasswordWidget::update_confirm_clicked,
				this, &LoginsWindow::reload);
	}
}
