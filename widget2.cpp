#include "widget2.h"
#include <iostream>
#include <QPoint>
#include <QRect>

using namespace cv;

QImage Mat2QImage(const Mat3b &src);
Mat QImage2Mat(const QImage &inImage);
void chromakey(const Mat, const Mat, Mat*);

double red_l, red_h;
double green_l, green_h;
double blue_l, blue_h;

void on_trackbar(int,void*)
{
	red_l = getTrackbarPos("Red Low", "Image Result1");
	red_h = getTrackbarPos("Red High", "Image Result1");
	green_l = getTrackbarPos("Green Low", "Image Result1");
	green_h = getTrackbarPos("Green High", "Image Result1");
	blue_l = getTrackbarPos("Blue Low", "Image Result1");
	blue_h = getTrackbarPos("Blue High", "Image Result1");
}

widget2::widget2(QWidget *parent): cap(0)
{
	namedWindow("Image Result1", 1);

	createTrackbar("Red Low", "Image Result1", 0, 255, on_trackbar);
	createTrackbar("Red High", "Image Result1", 0, 255, on_trackbar);
	createTrackbar("Green Low", "Image Result1", 0, 255, on_trackbar);
	createTrackbar("Green High", "Image Result1", 0, 255, on_trackbar);
	createTrackbar("Blue Low", "Image Result1", 0, 255, on_trackbar);
	createTrackbar("Blue High", "Image Result1", 0, 255, on_trackbar);
	cvSetTrackbarPos("Red Low", "Image Result1",0);
	cvSetTrackbarPos("Red High", "Image Result1",0);
	cvSetTrackbarPos("Green Low", "Image Result1",0);
	cvSetTrackbarPos("Green High", "Image Result1",0);
	cvSetTrackbarPos("Blue Low", "Image Result1",0);
	cvSetTrackbarPos("Blue High", "Image Result1",0);

	delta = 0;
	showqbackimg = new QLabel(this);
	showcap = new QLabel(this);
	showqresult = new QLabel(this);
	capsize = QSize(480, 360);
	this -> resize(capsize.width()*2 + 60, 1000);
	this -> setWindowTitle("Ariel");

	timer = new QTimer(this);
	timer -> start(30);
	connect(timer, SIGNAL(timeout()), this, SLOT(capture()));

	QPoint point = QPoint(capsize.width() + 60, 0);
	QRect rect = QRect(point, capsize);
	showqresult -> setGeometry(rect);
	showqbackimg -> setGeometry(rect);

	bt0 = new QPushButton(this);
	bt0 -> setText("Switch");
	bt0 -> setGeometry(750, 400, 70, 50);
	connect(bt0, SIGNAL(clicked()), this, SLOT(change_bg()));

	qbackimg = QImage("1new.jpg");
	showqbackimg -> setPixmap(QPixmap::fromImage(qbackimg));
}

void widget2::capture()
{
	cap >> ccapimg;
	qcapimg = Mat2QImage(ccapimg);
	showcap -> setPixmap(QPixmap::fromImage(qcapimg).scaled(capsize));
	showcap -> resize(capsize);

	cbackimg = QImage2Mat(qbackimg);
	chromakey(cbackimg, ccapimg, &cresult);
	qresult = Mat2QImage(cresult);
	showqresult -> setPixmap(QPixmap::fromImage(qresult).scaled(capsize));

	if (delta == 0) showqresult->setHidden(false);
	else  showqresult->setHidden(true);
}


widget2::~widget2()
{}

void chromakey(const Mat under, const Mat over, Mat *dst){
	//create the destination matrix
	*dst = Mat(under.rows, under.cols, CV_8UC3);
	for(int y = 0 ; y < under.rows ; ++y)
	{
		for(int x = 0 ; x < under.cols ; ++x)
		{
			if(over.at<Vec3b>(y,x)[0] >= red_l && over.at<Vec3b>(y,x)[0] <= red_h && over.at<Vec3b>(y,x)[1] >= green_l && over.at<Vec3b>(y,x)[1] <= green_h && over.at<Vec3b>(y,x)[2] >= blue_l && over.at<Vec3b>(y,x)[2] <= blue_h)
			{
				dst->at<Vec3b>(y,x)[0] = under.at<Vec3b>(y,x)[0];
			            	dst->at<Vec3b>(y,x)[1] = under.at<Vec3b>(y,x)[1];
			            	dst->at<Vec3b>(y,x)[2] = under.at<Vec3b>(y,x)[2];
			}
			else
			{
				dst->at<Vec3b>(y,x)[0] = over.at<Vec3b>(y,x)[0];
				dst->at<Vec3b>(y,x)[1] = over.at<Vec3b>(y,x)[1];
			            	dst->at<Vec3b>(y,x)[2] = over.at<Vec3b>(y,x)[2];
			}
		}
	}
}

QImage Mat2QImage(const Mat3b &src) {
	QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
	for (int y = 0; y < src.rows; ++y)
	{
		const Vec3b *srcrow = src[y];
		QRgb *destrow = (QRgb*)dest.scanLine(y);
		for (int x = 0; x < src.cols; ++x) destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
	}
	return dest;
}

Mat QImage2Mat(const QImage &inImage)
{
	Mat  mat(inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine());
	return mat.clone();
}

void widget2::change_bg()
{
	switch (delta)
	{
		case 0:
		delta = 1;
		break;
		case 1:
		delta = 0;
		break;
	}
}
