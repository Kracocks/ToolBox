#ifndef SHOWSERVICEWIDGET_H
#define SHOWSERVICEWIDGET_H

#include <QWidget>
#include "../../model/Service.h"
#include "../loginswindow.h"

namespace Ui {
	class ShowServiceWidget;
}

class ShowServiceWidget : public QWidget {
	Q_OBJECT

public:
	explicit ShowServiceWidget(model::Service &service, QWidget *parent = nullptr);
	~ShowServiceWidget();

	void show_view();
	void show_edit();

signals:
	void update_confirm_clicked(model::Service &service);
	void details_clicked(model::Service &service);
	void delete_clicked();

private slots:
	// View widget slots
	void on_copy_url_btn_clicked();

	void on_update_btn_clicked();

	void on_details_btn_clicked();

	void on_delete_btn_clicked();

	// Edit widget slots
	void on_edit_accepted();

	void on_edit_rejected();

private:
	model::Service m_service;
	Ui::ShowServiceWidget *ui;
	Ui::LoginsWindow *logins_window;
};

#endif // SHOWSERVICEWIDGET_H
