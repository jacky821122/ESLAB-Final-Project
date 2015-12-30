#ifndef DETECTCOLOR_H_
#define DETECTCOLOR_H_
#include <QPixmap>
#include <QLabel>
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
	QImage image_test,qcapimg;
	void cameracap();
	int red, green, blue;
public slots:
	void setFactor(const double &factor);

private:
	double scaleFactor;
};
#endif
