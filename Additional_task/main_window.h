#pragma once

#include <QCheckBox>
#include <QColorDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>

#include "paint_widget.h"

class MainWindow : public QMainWindow {
 Q_OBJECT
 public:
  MainWindow();

 private:
  PaintWidget* widget_;
  QLabel* ellipse_radius_label_;
  QSpinBox* ellipse_radius_count_;
  QPushButton* change_color_;
  QColorDialog* color_dialog_;
};
