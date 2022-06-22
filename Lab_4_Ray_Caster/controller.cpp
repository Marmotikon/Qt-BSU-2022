#include "controller.h"

#include <QLineF>
#include <algorithm>

const std::vector<Polygon>& Controller::GetPolygons() const {
  return polygons_;
}

void Controller::AddPolygon(const Polygon& polygon) {
  polygons_.push_back(polygon);
}

void Controller::AddVertexToLastPolygon(const QPointF& new_vertex) {
  polygons_.at(polygons_.size() - 1).AddVertex(new_vertex);
}

void Controller::UpdateLastPolygon(const QPointF& new_vertex) {
  polygons_.at(polygons_.size() - 1).UpdateLastVertex(new_vertex);
}

void Controller::SetLightSource(QPointF point) {
  light_source_ = point;
}

QPointF Controller::GetLightSource() const {
  return light_source_;
}

std::vector<Ray> Controller::CastRays() {
  std::vector<Ray> rays;
  for (auto& polygon : polygons_) {
    for (auto& vertex : polygon.GetVertices()) {
      Ray ray(light_source_, vertex,
              atan2((vertex.y() - light_source_.y()),
              (vertex.x() - light_source_.x())));
      rays.push_back(ray);
      rays.push_back(ray.Rotate(0.0001));
      rays.back().SetLength(2000);
      rays.push_back(ray.Rotate(-0.0001));
      rays.back().SetLength(2000);
    }
  }
  return rays;
}

void Controller::IntersectRays(std::vector<Ray>* rays) {
  for (auto& ray : *rays) {
    for (auto& polygon : polygons_) {
      auto intersection = polygon.IntersectRay(ray);
      if (intersection.has_value()) {
        double current_intersect_dist(Polygon::FindDist(ray.GetBegin(),
                                                        intersection.value()));

        if (current_intersect_dist < ray.GetLength()) {
          ray.SetLength(current_intersect_dist);
        }
      }
    }
  }
}

void Controller::RemoveAdjacentRays(std::vector<Ray>* rays) {
  std::sort(rays->begin(), rays->end(), [](const Ray& r1, const Ray& r2){
    if (r1.GetEnd().x() < r2.GetEnd().x()) {
      return true;
    } else if (r1.GetEnd().x() > r2.GetEnd().x()) {
      return false;
    } else {
      return r1.GetEnd().y() < r2.GetEnd().y();
    }
  });

  int new_index = 1;
  Ray prev_ray = (*rays)[0];
  for (int old_index = 1; old_index < rays->size(); old_index++) {
    if (Polygon::FindDist(rays->at(old_index).GetEnd(), prev_ray.GetEnd())
        > 1e-6) {
      prev_ray = rays->at(old_index);
      rays->at(new_index) = rays->at(old_index);
      new_index++;
    }
  }
  rays->resize(new_index);

  std::sort(rays->begin(), rays->end(), [](const Ray& r1, const Ray& r2){
    return r1.GetAngle() < r2.GetAngle();
  });
}

Polygon Controller::CreateLightArea() {
  std::vector<Ray> rays(CastRays());
  IntersectRays(&rays);
  RemoveAdjacentRays(&rays);
  std::vector<QPointF> vertices;
  for (const Ray& ray : rays) {
    vertices.push_back(ray.GetEnd());
  }

  Polygon light_area(vertices);
  return light_area;
}
void Controller::SetCursorPoint(QPointF point) {
  cursor_point_ = point;
}
QPointF Controller::GetCursorPoint() const {
  return cursor_point_;
}
