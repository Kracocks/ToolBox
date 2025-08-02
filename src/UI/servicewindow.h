#ifndef SERVICEWINDOW_H
#define SERVICEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "add_popups/addservice.h"
#include "loginswindow.h"
#include "custom_widgets/flowlayout.h"

namespace Ui {
	class ServiceWindow;
}

class ServiceWindow : public QWidget, public Reloadable {
	Q_OBJECT

public:
	explicit ServiceWindow(QWidget *parent = nullptr);
	~ServiceWindow();

	void on_AddService_accepted();
	void on_details_clicked(model::Service &service);
	void reload();

signals:
	void details_cliked(model::Service &service);

private slots:
	void on_addServiceBtn_clicked();

	void on_serviceNameSearch_textChanged(const QString &arg1);

private:
	AddService *addService;
	LoginsWindow *loginsWindow;
	FlowLayout *layout_services;
	Ui::ServiceWindow *ui;
};

#endif // SERVICEWINDOW_H
