#include <QApplication>

#include "connection.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QWidget widget;

	Connection ui;
	ui.show();

	return app.exec();
}
