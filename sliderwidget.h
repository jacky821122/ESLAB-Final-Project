#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QPixmap>
#include <QImage>
#include <QSize>
#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class SubQLabel : public QLabel
{
	Q_OBJECT
public:
	SubQLabel(QWidget *parent = 0);
	~SubQLabel();
	void mousePressEvent(QMouseEvent *event);
	void setScaleFactor(double factor);
	void cameracap();
	QImage image_test, qcapimg;
	int red, green, blue;

signals:
	void red_low_Changed( const int&);
	void red_high_Changed( const int&);
	void green_low_Changed( const int&);
	void green_high_Changed( const int&);
	void blue_low_Changed( const int&);
	void blue_high_Changed( const int&);

public slots:
	void setFactor(const double &factor);

private:
	double scaleFactor;
};

class sliderwidget : public QWidget
{
	Q_OBJECT
protected:
public:
	sliderwidget(QWidget *parent = 0);
	~sliderwidget();
	QLabel *red_low_label;
	QLabel *red_high_label;
	QLabel *green_low_label;
	QLabel *green_high_label;
	QLabel *blue_low_label;
	QLabel *blue_high_label;
	QSlider *red_low;
	QSlider *red_high;
	QSlider *green_low;
	QSlider *green_high;
	QSlider *blue_low;
	QSlider *blue_high;
	QSpinBox *red_low_spinbox;
	QSpinBox *red_high_spinbox;
	QSpinBox *green_low_spinbox;
	QSpinBox *green_high_spinbox;
	QSpinBox *blue_low_spinbox;
	QSpinBox *blue_high_spinbox;
public slots:
	// void setred_l( const int &)
	// void changeValue(int);

};

#endif
