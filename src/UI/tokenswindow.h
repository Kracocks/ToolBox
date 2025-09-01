#ifndef TOKENSWINDOW_H
#define TOKENSWINDOW_H

#include <QWidget>
#include "../model/Login.h"
#include "add_popups/addtoken.h"
#include "custom_widgets/flowlayout.h"
#include "reloadable.h"

namespace Ui {
	class TokensWindow;
}

class TokensWindow : public QWidget, public Reloadable {
	Q_OBJECT

public:
	explicit TokensWindow(model::Login &login, QWidget *parent = nullptr);
	~TokensWindow();

	void reload();

signals:
	void return_clicked();

private slots:
	void on_returnBtn_clicked();

	void on_addTokenBtn_clicked();

private:
	model::Login m_login;
	AddToken *addToken;
	FlowLayout *layout_tokens;
	Ui::TokensWindow *ui;
};

#endif // TOKENSWINDOW_H
