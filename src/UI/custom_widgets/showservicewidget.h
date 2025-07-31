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

signals:
	void delete_clicked();
	void details_clicked();

private slots:
	void on_delete_btn_clicked();

	void on_copy_url_btn_clicked();

	void on_details_btn_clicked();

private:
	model::Service m_service;
	Ui::ShowServiceWidget *ui;
	Ui::LoginsWindow *logins_window;
};

#endif // SHOWSERVICEWIDGET_H
