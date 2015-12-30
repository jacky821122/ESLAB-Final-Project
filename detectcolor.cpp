#include <QtWidgets>
#include <iostream> 
#include "detectcolor.h"

using namespace cv;
using namespace std;

QImage Mat2QImage(const Mat3b &src);
double red_l, red_h;
double green_l, green_h;
double blue_l, blue_h;

SubQLabel::SubQLabel(QWidget *parent)
{
	scaleFactor = 1.0;
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

		red_l = red ;
		red_h = red + 50;
		green_l = green ;
		green_h = green + 50;
		blue_l = blue ;
		blue_h = blue + 50;

		cout << red_l << " " << green_l << " " << blue_l << "\n";

		emit redChanged( red_l);
	}

}

void SubQLabel::setScaleFactor(double factor){
	scaleFactor = factor;
}

SubQLabel::~SubQLabel()
{}

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
