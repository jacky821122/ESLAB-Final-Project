
#include "widget2.h"
#include "detectcolor.h"
#include <iostream>
#include <QPoint>
#include <QRect>

using namespace cv;
using namespace std;

extern QImage Mat2QImage(const Mat3b &src);
Mat QImage2Mat(const QImage &inImage);
void chromakey(const Mat, const Mat, Mat*);
void colortest(QImage img);

//void mousePressEvent(QMouseEvent *event);

double red_l, red_h;
double green_l, green_h;
double blue_l, blue_h;

int test = 0;
int xxx,yyy;

void on_trackbar(int,void*)
{
	/*red_l = getTrackbarPos("Red Low", "Image Result1");
	red_h = getTrackbarPos("Red High", "Image Result1");
	green_l = getTrackbarPos("Green Low", "Image Result1");
	green_h = getTrackbarPos("Green High", "Image Result1");
	blue_l = getTrackbarPos("Blue Low", "Image Result1");
	blue_h = getTrackbarPos("Blue High", "Image Result1");*/
}

widget2::widget2(QWidget *parent): cap(0)
{
	subqlabel = new SubQLabel();

	red_l = 255;
	red_h = 255;
	green_l = 255;
	green_h = 255;
	blue_l = 255;
	blue_h = 255;
	/*namedWindow("Image Result1", 1);

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
	cvSetTrackbarPos("Blue High", "Image Result1",0);*/


	delta = 0;
	showqbackimg = new QLabel(this);
	showcap = new QLabel(this);
	showqresult = new QLabel(this);

	/*----------Setup the Size of Images and Windows-----------*/
	capsize = QSize(480, 360);
	this -> resize(capsize.width()*2 + 60, 700);
	// this -> resize(capsize.width()*2 + 60, 1000);
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
	QPoint point = QPoint(capsize.width() + 60, 0);
	QRect rect = QRect(point, capsize);
	showqresult -> setGeometry(rect);
	showqbackimg -> setGeometry(rect);

	/*-----------------Setup The Switch Button-----------------*/
	bt0 = new QPushButton(this);
	bt0 -> setText("Switch");
	bt0 -> setGeometry(780, 400, 70, 50);
	connect(bt0, SIGNAL(clicked()), this, SLOT(change_bg()));

	/*-----------------Setup The Capture Button-----------------*/
	bt1 = new QPushButton(this);
	bt1 -> setText("Capture");
	bt1 -> setGeometry(700, 400, 70, 50);
	connect(bt1, SIGNAL(clicked()), this, SLOT(capture()));

	/*-----------------Show The Backing Image-----------------*/
	qbackimg = QImage("1new.jpg");
	// showqbackimg -> setPixmap(QPixmap::fromImage(qbackimg));


}

void widget2::camera_caping()
{
	/*---------------------Show Captured Image--------------------*/
	cap >> ccapimg; //CV_8UC3
	qcapimg = Mat2QImage(ccapimg);
	showcap -> setPixmap(QPixmap::fromImage(qcapimg).scaled(capsize));
	showcap -> resize(capsize);

	red_l = subqlabel -> red ;
	red_h = subqlabel -> red + 50;
	green_l = subqlabel -> green ;
	green_h = subqlabel -> green + 50;
	blue_l = subqlabel -> blue ;
	blue_h = subqlabel -> blue + 50;

	/*--------------Convert the BG to RGB888 then CV_8UC4---------------*/ 
	qbackimg = qbackimg.convertToFormat(QImage::Format_RGB888); //RGB888 <-> CV_8UC3
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
	cshowRGB = cresult;
	showcapture -> setPixmap(QPixmap::fromImage(qresult).scaled(QSize(320, 240)));
	showcapture -> resize(QSize(320, 240));

	subqlabel -> qcapimg = qresult;
	subqlabel-> setPixmap(QPixmap::fromImage(qcapimg).scaled(capsize));
  	subqlabel -> resize(capsize);
  	subqlabel -> image_test = qcapimg;
	subqlabel -> show();


// cout << red_l << " " << green_l << " " << blue_l << endl;
cout << subqlabel -> red << " " << subqlabel -> green << " " << subqlabel -> blue << endl;
	
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

/*QImage Mat2QImage(const Mat3b &src) {
	QImage dest(src.cols, src.rows, QImage::Format_RGB32);
	for (int y = 0; y < src.rows; ++y)
	{
		const Vec3b *srcrow = src[y];
		QRgb *destrow = (QRgb*)dest.scanLine(y);
		for (int x = 0; x < src.cols; ++x) destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
	}
	return dest;
}*/

Mat QImage2Mat(const QImage &inImage)
{
	QImage   swapped = inImage.rgbSwapped(); 
	return Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
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

void colortest(QImage img)
{

/*	if ( false == img.isNull() )
	{
    		QVector<QRgb> v = img.colorTable(); // returns a list of colors contained in the image's color table.
    		 QVector<QRgb>::const_iterator it, itE;
    		 it = v.begin();
    		 it = it + 2000;
    		 QColor clrCurrent(*it);
    		 cout << clrCurrent.red() << " " << clrCurrent.green() <<" " <<clrCurrent.blue() <<endl;
    		
	}*/

    		 for ( int row = 1; row < img.height() + 1; ++row )
    for ( int col = 1; col < img.width() + 1; ++col )
    {
        QColor clrCurrent( img.pixel( row, col ) );

        std::cout << "Pixel at [" << row << "," << col << "] contains color ("
                  << clrCurrent.red() << ", "
                  << clrCurrent.green() << ", "
                  << clrCurrent.blue() << ", "
                  << clrCurrent.alpha() << ")."
                  << std::endl;
    }
}


