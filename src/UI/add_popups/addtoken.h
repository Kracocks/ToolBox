#ifndef ADDTOKEN_H
#define ADDTOKEN_H

#include <QDialog>

namespace Ui {
	class AddToken;
}

class AddToken : public QDialog {
	Q_OBJECT

public:
	explicit AddToken(int loginId, QWidget *parent = nullptr);
	~AddToken();

private slots:
	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

	void on_viewValue_stateChanged(int arg1);

	void on_rbNo_toggled(bool checked);

private:
	int m_loginId;
	void accept();
	Ui::AddToken *ui;
};

#endif // ADDTOKEN_H
