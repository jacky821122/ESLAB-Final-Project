#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>

class sliderwidget : public QWidget
{
	Q_OBJECT
protected:
public:
	sliderwidget(QWidget *parent = 0);
	~sliderwidget();
	QSlider *red_low;
	QSlider *red_high;
	QSlider *green_low;
	QSlider *green_high;
	QSlider *blue_low;
	QSlider *blue_high;
	QLabel *red_low_label;
	QLabel *red_high_label;
	QLabel *green_low_label;
	QLabel *green_high_label;
	QLabel *blue_low_label;
	QLabel *blue_high_label;
	QSpinBox *red_low_spinbox;
	QSpinBox *red_high_spinbox;
	QSpinBox *green_low_spinbox;
	QSpinBox *green_high_spinbox;
	QSpinBox *blue_low_spinbox;
	QSpinBox *blue_high_spinbox;
	/* data */
	public slots:
	// setValue(int);
};

#endif