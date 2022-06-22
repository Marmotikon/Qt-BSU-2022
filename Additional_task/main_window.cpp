#include "main_window.h"

#include <iostream>

MainWindow::MainWindow() :
    QMainWindow(nullptr),
    widget_(new PaintWidget(this)),
    ellipse_radius_count_(new QSpinBox(this)),
    ellipse_radius_label_(new QLabel("Radius:", this)),
    change_color_(new QPushButton("Change color", this)),
    color_dialog_(new QColorDialog(this)) {

  setMinimumSize(1000, 700);
  resize(1000, 700);

  widget_->setGeometry(10, 65, 980, 625);
  ellipse_radius_label_->setGeometry(50, 10, 100, 20);
  ellipse_radius_count_->setGeometry(50, 30, 100, 20);
  ellipse_radius_count_->setRange(20, 150);
  ellipse_radius_count_->setValue(50);
  change_color_->setGeometry(170, 10, 100, 40);

  connect(ellipse_radius_count_, &QSpinBox::valueChanged, widget_,
          &PaintWidget::SetEllipseRadius);
  connect(change_color_, &QPushButton::pressed, this, [&]{
    color_dialog_->open();
  });
  connect(color_dialog_, &QColorDialog::colorSelected, this, [&]{
    widget_->SetColor(color_dialog_->currentColor());
  });
}
