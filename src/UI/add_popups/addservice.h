#ifndef ADDSERVICE_H
#define ADDSERVICE_H

#include <QDialog>

namespace Ui {
	class AddService;
}

class AddService : public QDialog {
	Q_OBJECT

public:
	explicit AddService(QWidget *parent = nullptr);
	~AddService();

private slots:
	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
	Ui::AddService *ui;
	void accept();
};

#endif // ADDSERVICE_H
