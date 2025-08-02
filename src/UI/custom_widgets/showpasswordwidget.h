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

signals:
	void delete_clicked();
	void details_clicked(model::Login &login);

private slots:
	void on_delete_btn_clicked();

	void on_copy_pwd_btn_clicked();

	void on_details_btn_clicked();

private:
	Ui::ShowPasswordWidget *ui;
	model::Login m_login;
};

#endif // SHOWPASSWORDWIDGET_H
