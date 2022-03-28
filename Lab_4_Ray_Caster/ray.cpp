#include "ray.h"

#include <cmath>

#include "constants.h"

Ray::Ray(const QPointF& begin, const QPointF& end, double angle) :
    begin_(begin), end_(end), angle_(angle) {}

const QPointF& Ray::GetBegin() const {
  return begin_;
}

const QPointF& Ray::GetEnd() const {
  return end_;
}

void Ray::SetBegin(const QPointF& begin) {
  begin_ = begin;
}

void Ray::SetEnd(const QPointF& end) {
  end_ = end;
}

Ray Ray::Rotate(double angle) const {
  double length = GetLength();
  double new_angle = angle_ + angle;

  double x = begin_.x() + length * cos(new_angle);
  double y = begin_.y() + length * sin(new_angle);
  return {begin_, QPointF(x,y), new_angle};
}

double Ray::GetLength() const {
  return sqrt(pow(begin_.x() - end_.x(), 2) + pow(begin_.y() - end_.y(), 2));
}

void Ray::SetLength(double length) {
  double x = begin_.x() + length * std::cos(angle_);
  double y = begin_.y() + length * std::sin(angle_);
  end_ = QPointF(x, y);
}

std::optional<QPointF> Ray::IntersectSegment(
    double x1,
    double y1,
    double x2,
    double y2) const{
  double A1 = y1 - y2;
  double B1 = x2 - x1;
  double C1 = -A1 * x1 - B1 * y1;

  double A2 = GetBegin().y() - GetEnd().y();
  double B2 = GetEnd().x() - GetBegin().x();
  double C2 = -A2 * GetBegin().x() - B2 * GetBegin().y();

  double denominator = Determinant(A1, B1, A2, B2);

  if (std::abs(denominator) >= kEps) {
    double x(-Determinant(C1, B1, C2, B2) / denominator);
    double y(-Determinant(A1, C1, A2, C2) / denominator);


    if (Is_between(x1, x2, x) &&
        Is_between(y1, y2, y) &&
        Is_between(GetEnd().x(), GetBegin().x(), x) &&
        Is_between(GetEnd().y(), GetBegin().y(), y)) {
      return QPointF(x, y);
    }
  }
  return std::nullopt;
}

bool Ray::Is_between(double border1, double border2, double value) {
  return (std::min(border1, border2) < value + kEps) &&
      (std::max(border1, border2) > value - kEps);
}

double Ray::Determinant(double a, double b, double c, double d) {
  return a * d - b * c;
}

double Ray::GetAngle() const {
  return angle_;
}

Ray::Ray() {}
