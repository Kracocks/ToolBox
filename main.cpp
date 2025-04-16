#include <iostream>
#include <QApplication>

#include "mainwindow.h"
#include "src/bd/Connector.h"
#include "src/impl/ServiceDaoImpl.h"
#include "src/model/Encrypt.h"

// GLOBAL VARIABLE

// Pages

int main(int argc, char *argv[]) {
	if (!model::Encrypt::generateKeyPair()) {
		std::cerr << "Failed to generate key pair" << std::endl;
		return 2;
	}

	bd::Connector& db = bd::Connector::getInstance();
	if (db.getDB()) {
		std::cout << "ok" << std::endl;
	} else {
		std::cerr << "Failed to open db" << std::endl;
		return 1;
	}

	QApplication app(argc, argv);
	QWidget widget;

	MainWindow ui;
	ui.show();

	return app.exec();
}
