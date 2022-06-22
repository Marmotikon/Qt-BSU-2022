#include <iostream>
#include "main_window.h"

MainWindow::MainWindow() :
    QMainWindow(nullptr),
    widget_(new PaintWidget(this)),
    light_mode_(new QRadioButton("Light mode",this)),
    polygons_mode_(new QRadioButton("Polygons mode", this)),
    smart_mode_(new QRadioButton("Smart mode", this)),
    lights_count_(new QSpinBox(this)),
    lights_count_label_(new QLabel("Lights count:", this)),
    lights_radius_(new QSpinBox(this)),
    lights_radius_label_(new QLabel("Lights radius:", this)),
    check_box_(new QCheckBox("Enable light in polygons", this))
    {
  setWindowTitle("Ray Caster 3000");

  setMinimumSize(1000, 700);
  resize(1000, 700);

  widget_->setGeometry(10, 65, 980, 625);

  light_mode_->setGeometry(10, 0, 200, 20);
  polygons_mode_->setGeometry(10, 20, 200, 20);
  smart_mode_->setGeometry(10, 40, 200, 20);
  smart_mode_->setChecked(true);

  lights_count_label_->setGeometry(250, 10, 100, 20);
  lights_count_->setGeometry(250, 40, 100, 20);
  lights_count_->setRange(1, 20);
  lights_count_->setValue(5);

  lights_radius_label_->setGeometry(450, 10, 100, 20);
  lights_radius_->setGeometry(450, 40, 100, 20);
  lights_radius_->setRange(1, 20);
  lights_radius_->setValue(10);

  check_box_->setGeometry(650, 20, 200, 40);
  check_box_->setChecked(true);

  connect(light_mode_, &QRadioButton::clicked, widget_,
          &PaintWidget::SetLightMode);
  connect(polygons_mode_, &QRadioButton::clicked, widget_,
          &PaintWidget::SetPolygonMode);
  connect(smart_mode_, &QRadioButton::clicked, widget_,
          &PaintWidget::SetSmartMode);
  connect(lights_count_, &QSpinBox::valueChanged, widget_,
          &PaintWidget::SetLightsCount);
  connect(lights_radius_, &QSpinBox::valueChanged, widget_,
          &PaintWidget::SetLightsRadius);
  connect(check_box_, &QCheckBox::stateChanged, widget_,
          &PaintWidget::SetLightInPolygons);
}
