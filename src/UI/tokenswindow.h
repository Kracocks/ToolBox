#ifndef TOKENSWINDOW_H
#define TOKENSWINDOW_H

#include <QWidget>

namespace Ui {
	class TokensWindow;
}

class TokensWindow : public QWidget {
	Q_OBJECT

public:
	explicit TokensWindow(QWidget *parent = nullptr);
	~TokensWindow();

private:
	Ui::TokensWindow *ui;
};

#endif // TOKENSWINDOW_H
