#include <iostream>
#include <QApplication>

#include "connection.h"
#include "src/impl/ServiceDaoImpl.h"
#include "src/model/Encrypt.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
	if (!model::Encrypt::generateKeyPair()) {
		std::cerr << "Failed to generate key pair" << std::endl;
		return 2;
	}

	QApplication app(argc, argv);
	QWidget widget;

	MainWindow mw;
	Connection ui;
	ui.show();

	return app.exec();
}
