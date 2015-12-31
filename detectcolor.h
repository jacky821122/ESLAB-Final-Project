#ifndef DETECTCOLOR_H
#define DETECTCOLOR_H
#include <QLabel>
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
#endif
