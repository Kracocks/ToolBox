#ifndef LOGINSWINDOW_H
#define LOGINSWINDOW_H

#include <QWidget>
#include "../model/Service.h"

namespace Ui {
	class LoginsWindow;
}

class LoginsWindow : public QWidget {
	Q_OBJECT

public:
	explicit LoginsWindow(model::Service &service, QWidget *parent = nullptr);
	~LoginsWindow();

private:
	model::Service m_service;
	void reload();
	void on_deleteLoginBtn_clicked();
	Ui::LoginsWindow *ui;
};

#endif // LOGINSWINDOW_H
