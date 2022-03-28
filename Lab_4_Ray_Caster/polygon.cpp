#include "polygon.h"

#include <QLineF>

Polygon::Polygon(const std::vector<QPointF>& vertices) : vertices_(vertices),
    vert_count_(vertices.size()) {}

const std::vector<QPointF>& Polygon::GetVertices() const {
  return vertices_;
}

void Polygon::AddVertex(const QPointF& vertex) {
  vertices_.push_back(vertex);
  vert_count_++;
}

void Polygon::UpdateLastVertex(const QPointF& new_vertex) {
  vertices_.at(vert_count_ - 1) = new_vertex;
}

std::optional<QPointF> Polygon::IntersectRay(const Ray& ray) const {
  if (vert_count_ == 0) {
    return std::nullopt;
  }

  bool has_intersection = false;
  double length = ray.GetLength();
  QPointF intersection;

  QPointF vert1(vertices_.at(vert_count_ - 1));

  for (int i = 0; i < vert_count_; i++) {
    QPointF vert2(vertices_.at(i));

    std::optional<QPointF> current_intersection =
        ray.IntersectSegment(vert1.x(), vert1.y(), vert2.x(), vert2.y());

    if (current_intersection.has_value()) {
      double distance(FindDist(ray.GetBegin(),
                               current_intersection.value()));
      if (distance < length) {
        length = distance;
        intersection = current_intersection.value();
        has_intersection = true;
      }
    }
    vert1 = vert2;
  }

  return  !has_intersection ? std::nullopt :
      std::optional<QPointF>{intersection};
}

double Polygon::FindDist(QPointF p1, QPointF p2) {
  return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
}
