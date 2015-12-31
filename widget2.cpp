#include "widget2.h"
#include "sliderwidget.h"
#include "detectcolor.h"
#include <iostream>
#include <QPoint>
#include <QRect>
#include <QApplication>

using namespace cv;
using namespace std;

extern QImage Mat2QImage(const Mat3b &src);
Mat QImage2Mat(const QImage &inImage);
void chromakey(const Mat, const Mat, Mat*);

extern double red_l, red_h;
extern double green_l, green_h;
extern double blue_l, blue_h;

widget2::widget2(QWidget *parent): cap(0)
{
	/*----------Initializing Everything-----------*/
	swidget = new sliderwidget();
	subqlabel = new SubQLabel();
	showqbackimg = new QLabel(this);
	showcap = new QLabel(this);
	showqresult = new QLabel(this);

	/*----------Setup the Size of Images and Windows-----------*/
	capsize = QSize(532, 399);
	this -> resize(800, 400); // In pandaboard
	this -> setWindowTitle("Ariel");

	/*-----------------Setup Capture Image Label-----------------*/
	showcapture = new QLabel(this);
	QPoint tmpoint = QPoint(0, capsize.height() + 20);
	QRect tmprect = QRect(tmpoint, capsize);
	showcapture -> setGeometry(tmprect);

	/*-----------------Setup Timer-----------------*/
	timer = new QTimer(this);
	timer -> start(100);
	connect(timer, SIGNAL(timeout()), this, SLOT(camera_caping()));

	/*-----------------Setup The Result Image Label-----------------*/
	QPoint point = QPoint(268, 0);
	QRect rect = QRect(point, capsize);
	showqresult -> setGeometry(rect);
	showqbackimg -> setGeometry(rect);

	/*-----------------Setup The Switch Button-----------------*/
	bt_pannel = new QPushButton("&Color Select", this);
	bt_pannel -> setGeometry(84, 40, 100, 50);
	connect(bt_pannel, SIGNAL(clicked()), this, SLOT(control_pannel_pop()));

	/*-----------------Setup The Capture Button-----------------*/
	bt_capture = new QPushButton("&Capture", this);
	bt_capture -> setGeometry(84, 130, 100, 50);
	connect(bt_capture, SIGNAL(clicked()), this, SLOT(capture()));

	/*-----------------Setup The Backing Image-----------------*/
	qbackimg = QImage("1new.jpg");

	/*-----------------Setup The Connection between Slider and Mouse Detecting-----------------*/
	connect(subqlabel, SIGNAL(red_low_Changed( const int&)), swidget->red_low, SLOT(setValue(int)));
	connect(subqlabel, SIGNAL(red_high_Changed( const int&)), swidget->red_high, SLOT(setValue(int)));
	connect(subqlabel, SIGNAL(green_low_Changed( const int&)), swidget->green_low, SLOT(setValue(int)));
	connect(subqlabel, SIGNAL(green_high_Changed( const int&)), swidget->green_high, SLOT(setValue(int)));
	connect(subqlabel, SIGNAL(blue_low_Changed( const int&)), swidget->blue_low, SLOT(setValue(int)));
	connect(subqlabel, SIGNAL(blue_high_Changed( const int&)), swidget->blue_high, SLOT(setValue(int)));
}

void widget2::camera_caping()
{
	cap >> ccapimg; //CV_8UC3

	/*--------------Get Color Information---------------*/ 
	red_l = swidget -> red_low->sliderPosition();
	red_h = swidget -> red_high->sliderPosition();
	green_l = swidget -> green_low->sliderPosition();
	green_h = swidget -> green_high->sliderPosition();
	blue_l = swidget -> blue_low->sliderPosition();
	blue_h = swidget -> blue_high->sliderPosition();

	/*--------------Convert the BG to RGB888 then CV_8UC3---------------*/ 
	qbackimg = qbackimg.convertToFormat(QImage::Format_RGB888); //RGB888 (=) CV_8UC3
	cbackimg = QImage2Mat(qbackimg);
	chromakey(cbackimg, ccapimg, &cresult);
	
	/*-----------------Show the Result Image-----------------*/
	qresult = Mat2QImage(cresult);
	showqresult -> setPixmap(QPixmap::fromImage(qresult).scaled(capsize));
}

void widget2::capture()
{
	subqlabel -> qcapimg = Mat2QImage(ccapimg);
	subqlabel -> setPixmap(QPixmap::fromImage(subqlabel->qcapimg).scaled(capsize));
  	subqlabel -> resize(capsize);
  	subqlabel -> image_test = subqlabel -> qcapimg;
	subqlabel -> show();
}


widget2::~widget2()
{}

void widget2::control_pannel_pop()
{
	swidget -> show();
}

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

Mat QImage2Mat(const QImage &inImage)
{
	QImage   swapped = inImage.rgbSwapped(); 
	return Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
}
