#include "paint_widget.h"

#include <iostream>
#include <QMouseEvent>
#include <QTimerEvent>

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent),
                                            timer_id_(startTimer(10)) {
  setMouseTracking(true);
}

void PaintWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  Paint(&painter);
}

void PaintWidget::Paint(QPainter* painter) {
  // painter->save();

  //background color
  painter->setBrush(Qt::black);
  painter->drawRect(0, 0, 980, 625);

  //draw ellipse
  if (!has_ellipse) {
    return;
  }
  painter->setPen(Qt::NoPen);
  painter->setBrush(ellipse_color_);
  painter->drawEllipse(ellipse_centre_.x() - ellipse_radius_,
                       ellipse_centre_.y() - ellipse_radius_,
                       2 * ellipse_radius_,
                       2 * ellipse_radius_);

  //draw rect
  if (!is_animation_ended_) {
    QLineF temp_line(
        ellipse_centre_.x(), ellipse_centre_.y(),
        ellipse_centre_.x() + ellipse_radius_, ellipse_centre_.y());
    temp_line.setAngle(angle_);
    switch (direction) {
      case Direction::kCounterclockwise : {
        angle_++;
        if (angle_ == 360) {
          direction = Direction::kClockwise;
        }
        break;
      }
      case Direction::kClockwise : {
        angle_--;
        if (angle_ == 0) {
          direction = Direction::kCounterclockwise;
          is_animation_ended_ = true;
        }
        break;
      }
    }
    QPointF rect_point = temp_line.p2();
    painter->setBrush(QColor(QColor(0xFFEA30)));
    painter->drawRect(rect_point.x() - 5, rect_point.y() - 5, 10, 10);
  }

  // painter->restore();
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() != Qt::LeftButton) {
    return;
  }
  has_ellipse = true;
  ellipse_centre_ = mapFromGlobal(cursor().pos());
  direction = Direction::kCounterclockwise;
  angle_ = 0;
  is_animation_ended_ = false;
}

void PaintWidget::SetEllipseRadius(int count) {
  ellipse_radius_ = count;
}

void PaintWidget::timerEvent(QTimerEvent* event) {
  if (event->timerId() != timer_id_) {
    return;
  }
  repaint();
}

void PaintWidget::SetColor(QColor color) {
  ellipse_color_ = color;
}
