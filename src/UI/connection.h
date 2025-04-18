#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
	class Connection;
}

class Connection : public QWidget {
	Q_OBJECT

public:
	explicit Connection(QWidget *parent = nullptr);
	~Connection();

private:
	void login();
	int attempt;
	MainWindow *mainwindow;
	Ui::Connection *ui;
};

#endif // CONNECTION_H
