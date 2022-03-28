#pragma once

#include <QPointF>

class Ray {
 public:
  Ray();
  Ray(const QPointF& begin, const QPointF& end, double angle);

  const QPointF& GetBegin() const;
  const QPointF& GetEnd() const;
  double GetAngle() const;

  void SetBegin(const QPointF& begin);
  void SetEnd(const QPointF& end);

  Ray Rotate(double angle) const;

  double GetLength() const;
  void SetLength(double length);

  std::optional<QPointF> IntersectSegment(
      double x1, double y1, double x2, double y2) const;

 private:
  static bool Is_between(double border1, double border2, double value);
  static double Determinant(double a, double b, double c, double d);

  QPointF begin_;
  QPointF end_;
  double angle_;
};