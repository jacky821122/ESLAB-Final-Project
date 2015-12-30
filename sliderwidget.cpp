#include "sliderwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QImage> //for test
#include <QLabel> //for test
#include <QPixmap> //for test

sliderwidget::sliderwidget(QWidget *parent)
{
	red_low_label = new QLabel(tr("Red Low"));
	red_high_label = new QLabel(tr("Red High"));
	green_low_label = new QLabel(tr("Green Low"));
	green_high_label = new QLabel(tr("Green High"));
	blue_low_label = new QLabel(tr("Blue Low"));
	blue_high_label = new QLabel(tr("Blue High"));

	red_low_spinbox = new QSpinBox();
	red_low_spinbox -> setRange(0, 255);
	red_low_spinbox -> setSingleStep(1);
	red_high_spinbox = new QSpinBox();
	red_high_spinbox -> setRange(0, 255);
	red_high_spinbox -> setSingleStep(1);
	green_low_spinbox = new QSpinBox();
	green_low_spinbox -> setRange(0, 255);
	green_low_spinbox -> setSingleStep(1);
	green_high_spinbox = new QSpinBox();
	green_high_spinbox -> setRange(0, 255);
	green_high_spinbox -> setSingleStep(1);
	blue_low_spinbox = new QSpinBox();
	blue_low_spinbox -> setRange(0, 255);
	blue_low_spinbox -> setSingleStep(1);
	blue_high_spinbox = new QSpinBox();
	blue_high_spinbox -> setRange(0, 255);
	blue_high_spinbox -> setSingleStep(1);

	red_low = new QSlider(Qt::Horizontal);
	red_low -> setMinimum(0);  
	red_low -> setMaximum(255);  
	red_low -> setSingleStep(1);
	red_high = new QSlider(Qt::Horizontal);
	red_high -> setMinimum(0);  
	red_high -> setMaximum(255);  
	red_high -> setSingleStep(1);
	green_low = new QSlider(Qt::Horizontal);
	green_low -> setMinimum(0);  
	green_low -> setMaximum(255);  
	green_low -> setSingleStep(1);
	green_high = new QSlider(Qt::Horizontal);
	green_high -> setMinimum(0);  
	green_high -> setMaximum(255);  
	green_high -> setSingleStep(1);
	blue_low = new QSlider(Qt::Horizontal);
	blue_low -> setMinimum(0);  
	blue_low -> setMaximum(255);  
	blue_low -> setSingleStep(1);
	blue_high = new QSlider(Qt::Horizontal);
	blue_high -> setMinimum(0);  
	blue_high -> setMaximum(255);  
	blue_high -> setSingleStep(1);

	connect(red_low_spinbox, SIGNAL(valueChanged(int)), red_low, SLOT(setValue(int)));
	connect(red_low, SIGNAL(valueChanged(int)), red_low_spinbox, SLOT(setValue(int)));
	connect(red_high_spinbox, SIGNAL(valueChanged(int)), red_high, SLOT(setValue(int)));
	connect(red_high, SIGNAL(valueChanged(int)), red_high_spinbox, SLOT(setValue(int)));
	connect(green_low_spinbox, SIGNAL(valueChanged(int)), green_low, SLOT(setValue(int)));
	connect(green_low, SIGNAL(valueChanged(int)), green_low_spinbox, SLOT(setValue(int)));
	connect(green_high_spinbox, SIGNAL(valueChanged(int)), green_high, SLOT(setValue(int)));
	connect(green_high, SIGNAL(valueChanged(int)), green_high_spinbox, SLOT(setValue(int)));
	connect(blue_low_spinbox, SIGNAL(valueChanged(int)), blue_low, SLOT(setValue(int)));
	connect(blue_low, SIGNAL(valueChanged(int)), blue_low_spinbox, SLOT(setValue(int)));
	connect(blue_high_spinbox, SIGNAL(valueChanged(int)), blue_high, SLOT(setValue(int)));
	connect(blue_low, SIGNAL(valueChanged(int)), blue_low_spinbox, SLOT(setValue(int)));

	// QLabel *showimg = new QLabel(this);
	// QImage img = QImage("1new.jpg");
	// showimg -> setPixmap(QPixmap::fromImage(img));
	QGridLayout *layout = new QGridLayout();
	layout -> addWidget(red_low_label, 0, 0);
	layout -> addWidget(red_low, 0, 1);
	layout -> addWidget(red_low_spinbox, 0, 2);
	layout -> addWidget(red_high_label, 1, 0);
	layout -> addWidget(red_high, 1, 1);
	layout -> addWidget(red_high_spinbox, 1, 2);
	layout -> addWidget(green_low_label, 2, 0);
	layout -> addWidget(green_low, 2, 1);
	layout -> addWidget(green_low_spinbox, 2, 2);
	layout -> addWidget(green_high_label, 3, 0);
	layout -> addWidget(green_high, 3, 1);
	layout -> addWidget(green_high_spinbox, 3, 2);
	layout -> addWidget(blue_low_label, 4, 0);
	layout -> addWidget(blue_low, 4, 1);
	layout -> addWidget(blue_low_spinbox, 4, 2);
	layout -> addWidget(blue_high_label, 5, 0);
	layout -> addWidget(blue_high, 5, 1);
	layout -> addWidget(blue_high_spinbox, 5, 2);

	this -> setLayout(layout);
	this -> resize(400, 400);
	this -> setWindowTitle("Control Pannel");

}

sliderwidget::~sliderwidget()
{}

// sliderwidget::setValue(int value)
// {

// }