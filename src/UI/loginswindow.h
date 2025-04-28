#ifndef LOGINSWINDOW_H
#define LOGINSWINDOW_H

#include <QWidget>
#include "../model/Service.h"
#include "addlogin.h"

namespace Ui {
	class LoginsWindow;
}

class LoginsWindow : public QWidget {
	Q_OBJECT

public:
	explicit LoginsWindow(model::Service &service, QWidget *parent = nullptr);
	~LoginsWindow();

private slots:
	void on_addLoginBtn_clicked();

private:
	model::Service m_service;
	void reload();
	void on_deleteLoginBtn_clicked();
	AddLogin *addLogin;
	Ui::LoginsWindow *ui;
};

#endif // LOGINSWINDOW_H
