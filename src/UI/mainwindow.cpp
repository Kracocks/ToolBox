#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->checkNameBtn, &QPushButton::clicked, this, &MainWindow::changeName);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeName() {
	qDebug() << "Changing name to " << ui->nameTf->text();
	ui->nameLabel->setText(ui->nameTf->text());
}
