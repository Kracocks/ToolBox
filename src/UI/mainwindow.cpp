#include "mainwindow.h"
#include "UI_autogen/include/ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->checkNameBtn, &QPushButton::clicked, this, &MainWindow::changeName);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeName() {
	ui->nameLabel->setText(ui->nameText->text());
	qDebug() << "Changing name";
}
