#pragma once

#include <vector>

#include "polygon.h"

class Controller {
 public:
  const std::vector<Polygon>& GetPolygons() const;
  void AddPolygon(const Polygon&);
  void AddVertexToLastPolygon(const QPointF& new_vertex);
  void UpdateLastPolygon(const QPointF& new_vertex);

  void SetLightSource(QPointF point);
  QPointF GetLightSource() const;
  void SetCursorPoint(QPointF point);
  QPointF GetCursorPoint() const;

  std::vector<Ray> CastRays();
  void IntersectRays(std::vector<Ray>* rays);
  void RemoveAdjacentRays(std::vector<Ray>* rays);
  Polygon CreateLightArea();

 private:
  std::vector<Polygon> polygons_;
  QPointF light_source_;
  QPointF cursor_point_;
};
