#ifndef SHOWPASSWORDWIDGET_H
#define SHOWPASSWORDWIDGET_H

#include <QWidget>
#include "../../model/Login.h"

namespace Ui {
	class ShowPasswordWidget;
}

class ShowPasswordWidget : public QWidget {
	Q_OBJECT

public:
	explicit ShowPasswordWidget(model::Login &login, QWidget *parent = nullptr);
	~ShowPasswordWidget();

	void show_view();
	void show_edit();

signals:
	void update_confirm_clicked(model::Login &login);
	void details_clicked(model::Login &login);
	void delete_clicked();

private slots:
	void on_copy_pwd_btn_clicked();

	void on_update_btn_clicked();

	void on_details_btn_clicked();

	void on_delete_btn_clicked();

	void on_edit_accepted();

	void on_edit_rejected();

private:
	Ui::ShowPasswordWidget *ui;
	model::Login m_login;
};

#endif // SHOWPASSWORDWIDGET_H
