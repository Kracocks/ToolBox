#include "tokenswindow.h"
#include "ui_tokenswindow.h"
#include "../impl/TokenDaoImpl.h"
#include "custom_widgets/showtokenwidget.h"
#include <QDebug>

TokensWindow::TokensWindow(model::Login &login, QWidget *parent) : QWidget(parent), ui(new Ui::TokensWindow), m_login(login)
{
	ui->setupUi(this);
	ui->title->setText("Tokens from " + QString::fromStdString(login.email));

	addToken = new AddToken(m_login.id);
	// When token added, reload the table
	connect(addToken, &AddToken::accepted, this, &TokensWindow::reload);

	layout_tokens = new FlowLayout();
	ui->scrollAreaWidgetContents->setLayout(layout_tokens);
}

TokensWindow::~TokensWindow() { delete ui; }

void TokensWindow::on_returnBtn_clicked()
{
	emit return_clicked();
}

void TokensWindow::on_addTokenBtn_clicked()
{
	qDebug() << "open dialog to add token";
	addToken->open();
}

void TokensWindow::reload() {
	// get tokens
	impl::TokenDaoImpl tokens {};
	std::vector<model::Token> all = tokens.findByLogin(m_login.id);

	// clearing layout
	QLayoutItem *item;
	while ((item = layout_tokens->takeAt(0)) != nullptr) {
		if (QWidget *widget = item->widget()) {
			widget->deleteLater();
		}
		delete item;
	}

	// add elements
	for (int row = 0; row < all.size(); row++) {
		ShowTokenWidget *widget = new ShowTokenWidget(all[row]);
		layout_tokens->addWidget(widget);
		//receive delete button click
		connect(widget, &ShowTokenWidget::delete_clicked,
				this, &TokensWindow::reload);
		//received edit button confirm
		connect(widget, &ShowTokenWidget::update_confirm_clicked,
				this, &TokensWindow::reload);
	}
}
