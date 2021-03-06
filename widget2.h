#ifndef WIDGET2_H
#define WIDGET2_H
#include <string>
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
class SubQLabel;

class widget2: public QWidget
{
	Q_OBJECT
protected:
	void closeEvent(QCloseEvent *event);
public:
	widget2(QWidget *parent = 0);
	~widget2();
	sliderwidget *swidget;
	SubQLabel *subqlabel;
	QSize capsize;
	QLabel *showcap,*showqbackimg, *showqresult, *showcapture, *showSelectColor, *showRGB;
	QLabel *showRec;
	QImage qcapimg, qbackimg, qresult;
	QTimer *timer, *recTime;
	QPushButton *bt_pannel, *bt_capture, *bt_record, *bt_record_stop;
	QPushButton *bt0, *bt1;
	QPixmap *tmpix;
	std::string recname, capname;
	cv::VideoCapture cap;
	cv::Mat ccapimg, cbackimg, cresult, cshowRGB;
	cv::VideoWriter writer;

	QPushButton *bt_background, *bt_saveimage;
	bool loadFile(const QString &);

	public slots:
	void camera_caping();
	void color_select();
	void control_pannel_pop();
	void open_file();
	void record();
	void recording();
	void stop_record();
	void capture();
	void showRec_start();
	void showRec_stop();
};

#endif

