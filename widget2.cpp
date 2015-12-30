#include "widget2.h"
#include "sliderwidget.h"
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
	// red_l = getTrackbarPos("Red Low", "Image Result1");
	// red_h = getTrackbarPos("Red High", "Image Result1");
	// green_l = getTrackbarPos("Green Low", "Image Result1");
	// green_h = getTrackbarPos("Green High", "Image Result1");
	// blue_l = getTrackbarPos("Blue Low", "Image Result1");
	// blue_h = getTrackbarPos("Blue High", "Image Result1");
}

widget2::widget2(QWidget *parent): cap(0)
{
	// namedWindow("Image Result1", 1);

	// createTrackbar("Red Low", "Image Result1", 0, 255, on_trackbar);
	// createTrackbar("Red High", "Image Result1", 0, 255, on_trackbar);
	// createTrackbar("Green Low", "Image Result1", 0, 255, on_trackbar);
	// createTrackbar("Green High", "Image Result1", 0, 255, on_trackbar);
	// createTrackbar("Blue Low", "Image Result1", 0, 255, on_trackbar);
	// createTrackbar("Blue High", "Image Result1", 0, 255, on_trackbar);
	// cvSetTrackbarPos("Red Low", "Image Result1",0);
	// cvSetTrackbarPos("Red High", "Image Result1",0);
	// cvSetTrackbarPos("Green Low", "Image Result1",0);
	// cvSetTrackbarPos("Green High", "Image Result1",0);
	// cvSetTrackbarPos("Blue Low", "Image Result1",0);
	// cvSetTrackbarPos("Blue High", "Image Result1",0);

	swidget = new sliderwidget();


	delta = 0;
	showqbackimg = new QLabel(this);
	showcap = new QLabel(this);
	showqresult = new QLabel(this);

	/*----------Setup the Size of Images and Windows-----------*/
	capsize = QSize(532, 399);
	this -> resize(800, 400); // In pandaboard
	// this -> resize(capsize.width()*2 + 60, 400); // Having two Windows
	this -> setWindowTitle("Ariel");

	/*-----------------Setup Capture Image Label-----------------*/
	showcapture = new QLabel(this);
	QPoint tmpoint = QPoint(0, capsize.height() + 20);
	QRect tmprect = QRect(tmpoint, capsize);
	showcapture -> setGeometry(tmprect);

	/*-----------------Setup Timer-----------------*/
	timer = new QTimer(this);
	timer -> start(30);
	connect(timer, SIGNAL(timeout()), this, SLOT(camera_caping()));

	/*-----------------Setup The Result Image Label-----------------*/
	QPoint point = QPoint(268, 0);
	QRect rect = QRect(point, capsize);
	showqresult -> setGeometry(rect);
	showqbackimg -> setGeometry(rect);

	/*-----------------Setup The Switch Button-----------------*/
	bt0 = new QPushButton(this);
	bt0 -> setText("Switch");
	bt0 -> setGeometry(99, 40, 70, 50);
	connect(bt0, SIGNAL(clicked()), this, SLOT(change_bg()));

	/*-----------------Setup The Capture Button-----------------*/
	bt1 = new QPushButton(this);
	bt1 -> setText("Capture");
	bt1 -> setGeometry(99, 130, 70, 50);
	connect(bt1, SIGNAL(clicked()), this, SLOT(capture()));

	/*-----------------Show The Backing Image-----------------*/
	qbackimg = QImage("1new.jpg");
	// showqbackimg -> setPixmap(QPixmap::fromImage(qbackimg));
}

void widget2::camera_caping()
{

	red_l = swidget -> red_low->sliderPosition();
	red_h = swidget -> red_high->sliderPosition();
	green_l = swidget -> green_low->sliderPosition();
	green_h = swidget -> green_high->sliderPosition();
	blue_l = swidget -> blue_low->sliderPosition();
	blue_h = swidget -> blue_high->sliderPosition();


	cap >> ccapimg; //CV_8UC3
	/*---------------------Show Captured Image--------------------*/
/*	qcapimg = Mat2QImage(ccapimg);
	showcap -> setPixmap(QPixmap::fromImage(qcapimg).scaled(capsize));
	showcap -> resize(capsize);
*/
	/*--------------Convert the BG to RGB888 then CV_8UC3---------------*/ 
	qbackimg = qbackimg.convertToFormat(QImage::Format_RGB888); //RGB888 (=) CV_8UC3
	cbackimg = QImage2Mat(qbackimg);
	chromakey(cbackimg, ccapimg, &cresult);
	
	/*-----------------Show the Result Image-----------------*/
	qresult = Mat2QImage(cresult);
	showqresult -> setPixmap(QPixmap::fromImage(qresult).scaled(capsize));

	if (delta == 0) showqresult->setHidden(false);
	else  showqresult->setHidden(true);
}

void widget2::capture()
{
	/*--------------------Small Screen-----------------------*/
	showcapture -> setPixmap(QPixmap::fromImage(qresult).scaled(QSize(320, 240)));
	showcapture -> resize(QSize(320, 240));

	/*----------------------Big Screen------------------------*/
	// showcapture -> setPixmap(QPixmap::fromImage(qresult).scaled(capsize));
	// showcapture -> resize(capsize);
}

widget2::~widget2()
{}

void chromakey(const Mat cbackimg, const Mat ccapimg, Mat *dst){
	*dst = Mat(cbackimg.rows, cbackimg.cols, CV_8UC3);
	for(int y = 0 ; y < cbackimg.rows ; ++y)
	{
		for(int x = 0 ; x < cbackimg.cols ; ++x)
		{
			if(ccapimg.at<Vec3b>(y,x)[0] >= red_l && ccapimg.at<Vec3b>(y,x)[0] <= red_h && ccapimg.at<Vec3b>(y,x)[1] >= green_l && ccapimg.at<Vec3b>(y,x)[1] <= green_h && ccapimg.at<Vec3b>(y,x)[2] >= blue_l && ccapimg.at<Vec3b>(y,x)[2] <= blue_h)
			{
				dst->at<Vec3b>(y,x)[0] = cbackimg.at<Vec3b>(y,x)[0];
				dst->at<Vec3b>(y,x)[1] = cbackimg.at<Vec3b>(y,x)[1];
				dst->at<Vec3b>(y,x)[2] = cbackimg.at<Vec3b>(y,x)[2];
			}
			else
			{
				dst->at<Vec3b>(y,x)[0] = ccapimg.at<Vec3b>(y,x)[0];
				dst->at<Vec3b>(y,x)[1] = ccapimg.at<Vec3b>(y,x)[1];
				dst->at<Vec3b>(y,x)[2] = ccapimg.at<Vec3b>(y,x)[2];
			}
		}
	}
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

Mat QImage2Mat(const QImage &inImage)
{
	QImage   swapped = inImage.rgbSwapped(); 
	return Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
}

void widget2::change_bg()
{
	/*switch (delta)
	{
		case 0:
		delta = 1;
		break;
		case 1:
		delta = 0;
		break;
	}*/
	swidget->show();
}
