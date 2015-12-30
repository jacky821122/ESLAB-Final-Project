#ifndef WIDGET2_H
#define WIDGET2_H
#include <QWidget>
#include <QSize>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPushButton>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class sliderwidget;

class widget2 : public QWidget
{
	Q_OBJECT
protected:
public:
	widget2(QWidget *parent = 0);
	~widget2();
	sliderwidget *swidget;
	QSize capsize;
	QLabel *showcap, *showqbackimg, *showqresult, *showcapture;
	QImage qcapimg, qbackimg, qresult;
	QTimer *timer;
	QPushButton *bt0, *bt1;
	int delta;
	cv::VideoCapture cap;
	cv::Mat ccapimg, cbackimg, cresult;

	public slots:
	void camera_caping();
	void capture();
	void change_bg();
};

#endif