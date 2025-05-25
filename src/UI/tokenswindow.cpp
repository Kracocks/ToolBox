#include "tokenswindow.h"
#include "ui_tokenswindow.h"

TokensWindow::TokensWindow(QWidget *parent) : QWidget(parent), ui(new Ui::TokensWindow) { ui->setupUi(this); }

TokensWindow::~TokensWindow() { delete ui; }
