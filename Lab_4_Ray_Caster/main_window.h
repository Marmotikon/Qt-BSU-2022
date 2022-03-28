#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QRadioButton>
#include <QSpinBox>

#include "paint_widget.h"

class MainWindow : public QMainWindow {
 Q_OBJECT
 public:
  MainWindow();

 private:
  PaintWidget* widget_;
  QRadioButton* light_mode_;
  QRadioButton* polygons_mode_;
  QRadioButton* smart_mode_;
  QLabel* lights_count_label_;
  QSpinBox* lights_count_;
  QLabel* lights_radius_label_;
  QSpinBox* lights_radius_;
  QCheckBox* check_box_;
};
