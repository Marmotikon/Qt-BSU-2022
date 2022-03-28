#pragma once

#include <vector>
#include <QPoint>

#include "ray.h"

class Polygon {
 public:
  Polygon(const std::vector<QPointF>& vertices);

  const std::vector<QPointF>& GetVertices() const;

  void AddVertex(const QPointF& vertex);

  void UpdateLastVertex(const QPointF& new_vertex);

  std::optional<QPointF> IntersectRay(const Ray& ray) const;

  static double FindDist(QPointF p1, QPointF p2);

 private:
  std::vector<QPointF> vertices_;
  int vert_count_;
};

