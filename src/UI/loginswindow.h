#ifndef LOGINSWINDOW_H
#define LOGINSWINDOW_H

#include <QWidget>
#include "../model/Service.h"
#include "add_popups/addlogin.h"
#include "tokenswindow.h"
#include "custom_widgets/flowlayout.h"
#include "reloadable.h"

namespace Ui {
	class LoginsWindow;
}

class LoginsWindow : public QWidget, public Reloadable {
	Q_OBJECT

public:
	explicit LoginsWindow(model::Service &service, QWidget *parent = nullptr);
	~LoginsWindow();

private slots:
	void on_addLoginBtn_clicked();

private:
	model::Service m_service;
	void reload();
	AddLogin *addLogin;
	TokensWindow *tokensWindow;
	FlowLayout *layout_logins;
	Ui::LoginsWindow *ui;
};

#endif // LOGINSWINDOW_H
