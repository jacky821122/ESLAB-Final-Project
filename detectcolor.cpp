#include <QtWidgets>
#include <iostream> 
#include "detectcolor.h"

using namespace cv;
using namespace std; 

QImage Mat2QImage(const Mat3b &src);

SubQLabel::SubQLabel(QWidget *parent)
{
	scaleFactor = 1.0;
}

QImage Mat2QImage(const Mat3b &src) {
	QImage dest(src.cols, src.rows, QImage::Format_RGB32);
	for (int y = 0; y < src.rows; ++y)
	{
		const Vec3b *srcrow = src[y];
		QRgb *destrow = (QRgb*)dest.scanLine(y);
		for (int x = 0; x < src.cols; ++x) destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
	}
	return dest;
}

void SubQLabel::setFactor(const double &factor){
	scaleFactor = factor;
}

void SubQLabel::mousePressEvent(QMouseEvent *event)
{
	int x = event -> x();
	int y = event -> y();

	int x_image = x/scaleFactor;
	int y_image = y/scaleFactor;

	if (event->button() == Qt::LeftButton) {
		QColor clrCurrent( image_test.pixel( x_image, y_image ) );
		red = clrCurrent.red();
		green = clrCurrent.green();
		blue = clrCurrent.blue();
	}
}

void SubQLabel::setScaleFactor(double factor){
	scaleFactor = factor;
}


SubQLabel::~SubQLabel()
{}
