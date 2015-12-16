#include "widget2.h"
#include <iostream>
#include <cstdio>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	widget2 *widget = new widget2();
	widget->show();
	return app.exec();
}

/*Mat detectFace(Mat image)
{
	CascadeClassifier cascade("haarcascade_frontalface_alt.xml");
	vector<Rect> faces;
	
	cascade.detectMultiScale(image, faces, 1.2, 2, 0|CV_HAAR_SCALE_IMAGE, Size(min_face_size, min_face_size), Size(max_face_size, max_face_size));

	for (int i = 0; i < faces.size(); i++)
	{
		min_face_size = faces[0].width*0.8;
		max_face_size = faces[0].width*1.2;
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}

	return image;
}
*/