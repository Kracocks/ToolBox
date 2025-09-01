#ifndef SHOWTOKENWIDGET_H
#define SHOWTOKENWIDGET_H

#include <QWidget>
#include "../../model/Token.h"

namespace Ui {
	class ShowTokenWidget;
}

class ShowTokenWidget : public QWidget {
	Q_OBJECT

public:
	explicit ShowTokenWidget(model::Token &token, QWidget *parent = nullptr);
	~ShowTokenWidget();

	void show_view();
	void show_edit();

signals:
	void update_confirm_clicked(model::Token &token);
	void delete_clicked();

private slots:
	void on_copy_value_btn_clicked();

	void on_edit_btn_clicked();

	void on_delete_btn_clicked();

private:
	Ui::ShowTokenWidget *ui;
	model::Token m_token;
};

#endif // SHOWTOKENWIDGET_H
