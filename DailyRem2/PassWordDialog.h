#pragma once
#include <QMainWindow>

class PassWordDialog : public QMainWindow
{
public:
	PassWordDialog(QWidget* par);
	~PassWordDialog(void);

signals:
	void signalPassword(const QString& passWord);
	

protected:
	virtual void keyPressEvent(QKeyEvent *ev) override;
	virtual void eventFilter(QObject *obj, QEvent *ev) override;

private:
	void initialize();
	void connection();

	QLineEdit* m_edit;
};

