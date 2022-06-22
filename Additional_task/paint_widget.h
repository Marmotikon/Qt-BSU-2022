#pragma once

#include <QColor>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>

class PaintWidget : public QWidget {
 Q_OBJECT
 private:
  enum class Direction {
    kCounterclockwise,
    kClockwise
  };

 public:
  explicit PaintWidget(QWidget* parent);
  void paintEvent(QPaintEvent*) override;
  void Paint(QPainter* painter);

  void timerEvent(QTimerEvent*) override;
  void mousePressEvent(QMouseEvent* event) override;

  void SetEllipseRadius(int count);
  void SetColor(QColor color);

 private:
  bool has_ellipse{false};
  QPointF ellipse_centre_;
  int ellipse_radius_{50};
  Direction direction;
  int angle_;
  int32_t timer_id_;
  QColor ellipse_color_{Qt::cyan};
  bool is_animation_ended_;
};
