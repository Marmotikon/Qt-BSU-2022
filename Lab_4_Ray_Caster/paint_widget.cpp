#include "paint_widget.h"

#include <iostream>
#include <QMouseEvent>

#include "constants.h"

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent),
                                            controller_(new Controller) {
  controller_->AddPolygon({{{-20, -20}, {-20, 645}, {1000, 645}, {1000, -20}}});
  setMouseTracking(true);
}

void PaintWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  Paint(&painter);
}

void PaintWidget::Paint(QPainter* painter) const {
  //background color
  painter->setBrush(Qt::black);
  painter->drawRect(0, 0, 980, 625);

  //draw light areas
  painter->setPen(Qt::NoPen);
  painter->setBrush(QColor(QColor(0xFFEA30)));
  painter->setOpacity(1.5 / lights_count_);
  const QPointF cursor_point(controller_->GetCursorPoint());
  Ray light_point_ray(cursor_point,
      {cursor_point.x(), cursor_point.y() + lights_radius_},
      atan2(0, lights_radius_));
  for (int i = 0; i < lights_count_; i++) {
    light_point_ray = light_point_ray.Rotate(kPi * 2. / lights_count_);
    controller_->SetLightSource(light_point_ray.GetEnd());
    Polygon light_area = controller_->CreateLightArea();
    painter->drawPolygon(light_area.GetVertices().data(),
                         light_area.GetVertices().size());
  }

  //draw Polygons
  painter->setPen(Qt::SolidPattern);
  painter->setPen(QColor(0xFFA900));
  painter->setOpacity(1);
  const std::vector<Polygon>& polygons = controller_->GetPolygons();
  if (light_in_polygons_) {
    for (int i = 1; i < polygons.size(); i++) {
      const Polygon& polygon(polygons.at(i));
      const std::vector<QPointF>& vertices = polygon.GetVertices();
      QPointF current_vert = vertices.at(0);
      for (int i = 1; i < vertices.size(); i++) {
        painter->drawLine(current_vert, vertices.at(i));
        current_vert = vertices.at(i);
      }
      painter->drawLine(current_vert, vertices.at(0));
    }
  } else {
    for (int i = 1; i < polygons.size(); i++) {
      const Polygon& polygon(polygons.at(i));
      painter->setBrush(Qt::black);
      painter->drawPolygon(polygon.GetVertices().data(),
                           polygon.GetVertices().size());
    }
  }
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
  if (mode_ == Mode::kLight) {
    return;
  }
  if (event->button() == Qt::LeftButton) {
    if (has_current_polygon_) {
      controller_->AddVertexToLastPolygon(mapFromGlobal(cursor().pos()));
    } else {
      controller_->AddPolygon({{mapFromGlobal(cursor().pos())}});
      has_current_polygon_ = true;
    }
  }
  if (event->button() == Qt::RightButton) {
    has_current_polygon_ = false;
  }

  repaint();
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event) {
  if (mode_ == Mode::kPolygon) {
    return;
  }
  controller_->SetCursorPoint(mapFromGlobal(cursor().pos()));

  repaint();
}

void PaintWidget::SetLightMode() {
  mode_ = Mode::kLight;
}

void PaintWidget::SetPolygonMode() {
  mode_ = Mode::kPolygon;
}

void PaintWidget::SetSmartMode() {
  mode_ = Mode::kSmart;
}

void PaintWidget::SetLightsCount(int count) {
  lights_count_ = count;
}

void PaintWidget::SetLightsRadius(int count) {
  lights_radius_ = count;
}

void PaintWidget::SetLightInPolygons(bool light_in_polygons) {
  light_in_polygons_ = light_in_polygons;
}
