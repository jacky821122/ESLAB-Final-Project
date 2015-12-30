

#include <QtWidgets>
#include <iostream> 
#include "detectcolor.h"


using namespace cv;
using namespace std; 

QImage Mat2QImage(const Mat3b &src);


SubQLabel::SubQLabel(QWidget *parent): cap(0)
{

  scaleFactor = 1.0;

  capsize = QSize(480, 360);
  this -> resize(480, 360);
  this -> setWindowTitle("detect color");


  cap >> ccapimg; //CV_8UC3
  qcapimg = Mat2QImage(ccapimg);
  this -> setPixmap(QPixmap::fromImage(qcapimg).scaled(capsize));
  this -> resize(capsize);
  this -> image_test = qcapimg;

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
cout<<"setFactor :"<<  scaleFactor << endl;
scaleFactor = factor;
}




void SubQLabel::mousePressEvent(QMouseEvent *event)
{
    cout<<"QMouseEvent"<<endl;
    int x = event->x();
    int y = event->y();

    int x_image = x/scaleFactor;
    int y_image = y/scaleFactor;

    if (event->button() == Qt::LeftButton) {
/*        cout<<"x: "<< x <<endl;
        cout<<"y: "<< y <<endl;

        cout<<"Pixels  :  ("<< x_image <<","<< y_image << ")" <<endl;*/
          QColor clrCurrent( image_test.pixel( x_image, y_image ) );

  /*cout << "Pixel at [" << x_image << "," << y_image<< "] contains color ("
                  << clrCurrent.red() << ", "
                  << clrCurrent.green() << ", "
                  << clrCurrent.blue() << ", "
                  << ")"  << endl;*/

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

