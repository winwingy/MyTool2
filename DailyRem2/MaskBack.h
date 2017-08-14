#pragma once
class DailyMask;
class MaskBack : public QLabel
{
	Q_OBJECT
public:
	MaskBack(QWidget* par, DailyMask* child);
	~MaskBack(void);

protected:
	virtual void paintEvent(QPaintEvent * ev) override;

private:
	void initialize();
	void connection();

	DailyMask* m_daily;
	std::vector<QRect> m_selRect;

	int m_test;
};

