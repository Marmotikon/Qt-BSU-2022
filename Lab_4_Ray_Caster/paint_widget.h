#pragma once

#include <QColor>
#include <QPainter>
#include <QWidget>

#include "controller.h"

class PaintWidget : public QWidget {
 Q_OBJECT
 private:
  enum class Mode {
   kLight,
   kPolygon,
   kSmart
 };

 public:
  explicit PaintWidget(QWidget* parent);
  void paintEvent(QPaintEvent*) override;
  void Paint(QPainter* painter) const;

  void SetLightMode();
  void SetPolygonMode();
  void SetSmartMode();

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

  void SetLightsCount(int count);
  void SetLightsRadius(int count);
  void SetLightInPolygons(bool light_in_polygons);

 private:
  Controller* controller_;
  Mode mode_{Mode::kSmart};
  int lights_count_{5};
  int lights_radius_{10};
  bool light_in_polygons_{true};
  bool has_current_polygon_{false};
};
