#ifndef TOKENSWINDOW_H
#define TOKENSWINDOW_H

#include <QWidget>
#include "../model/Login.h"
#include "add_popups/addtoken.h"

namespace Ui {
	class TokensWindow;
}

class TokensWindow : public QWidget {
	Q_OBJECT

public:
	explicit TokensWindow(model::Login &login, QWidget *parent = nullptr);
	~TokensWindow();

private slots:
	void on_addTokenBtn_clicked();

private:
	model::Login m_login;
	void reload();
	void on_deleteTokenBtn_clicked();
	AddToken *addToken;
	Ui::TokensWindow *ui;
};

#endif // TOKENSWINDOW_H
