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

		red_l =  (red > 30)? red - 30 : 0;
		red_h = (red > 205)? 255 : red + 50;
		green_l = (green > 30)? green - 30 : 0;
		green_h = (green > 205)? 255 : green + 50;
		blue_l = (blue > 30)? blue - 30 : 0;
		blue_h = (blue > 205)? 255 : blue + 50;

		emit red_low_Changed( red_l);
		emit red_high_Changed( red_h);
		emit green_low_Changed( green_l);
		emit green_high_Changed( green_h);
		emit blue_low_Changed( blue_l);
		emit blue_high_Changed( blue_h);

		this->setHidden(true);
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
