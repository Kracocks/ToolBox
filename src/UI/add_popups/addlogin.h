#ifndef ADDLOGIN_H
#define ADDLOGIN_H

#include <QDialog>

namespace Ui {
	class AddLogin;
}

class AddLogin : public QDialog {
	Q_OBJECT

public:
	explicit AddLogin(int serviceId, QWidget *parent = nullptr);
	~AddLogin();

private slots:
	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
	int m_serviceId;
	void accept();
	void viewPwd();
	Ui::AddLogin *ui;
};

#endif // ADDLOGIN_H
