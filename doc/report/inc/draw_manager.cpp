#include "draw_manager.h"
#include "camera.h"
#include "color_table_manager.h"
#include "composite.h"
#include "defs.h"
#include "model.h"
#include <unistd.h>

#include <algorithm>
#include <limits>
#include <math.h>

std::shared_ptr<draw_manager> draw_manager_creator::get_manager() {
  if (_manager == nullptr)
    create_manager();

  return _manager;
}

void draw_manager_creator::create_manager() {
  static std::shared_ptr<draw_manager> _manager(new draw_manager());
  this->_manager = _manager;
}

void draw_manager::set_cam(const std::shared_ptr<camera> &_camera) {
  cur_cam = _camera;
}

void draw_manager::set_drawer(const std::shared_ptr<base_drawer> &_drawer) {
  this->_drawer = _drawer;
}

void draw_manager::clear() {
  _height = _drawer->get_scene_height();
  _width = _drawer->get_scene_width();

  z_buffer = Matrix<double>(_width, _height);
  for (int i = 0; i < z_buffer.n(); i++)
    for (int j = 0; j < z_buffer.m(); j++)
      z_buffer[i][j] = std::numeric_limits<int>::min();
}

void draw_manager::set_width(const size_t &width) { _width = width; }

void draw_manager::set_height(const size_t &height) { _height = height; }

void draw_manager::set_depth(const size_t &depth) { _depth = depth; }

void draw_manager::set_kx(const size_t &kx) { _kx = kx; }

void draw_manager::set_ky(const size_t &ky) { _ky = ky; }

void draw_manager::set_kz(const size_t &kz) { _kz = kz; }

void draw_manager::visit(const camera &_camera) {}

void draw_manager::visit(const composite &_composite) {}

void draw_manager::visit(const scene &_scene) {}

void draw_manager::get_model_units_prepare(std::vector<point> &points_res,
                                           std::vector<surface> &surfaces_res,
                                           const model &_model) {
  model model_copy = _model;
  model_copy.transform(point(0, 0, 0), point(1, 1, 1),
                       point(cur_cam->get_xangle(), cur_cam->get_yangle(),
                             cur_cam->get_zangle()));

  points_res = model_copy.get_units()->get_points();
  for (auto &_point : points_res)
    proect_point(_point);

  surfaces_res = _model.get_units()->get_surfaces();

  model_copy.transform(point(0, 0, 0), point(1, 1, 1),
                       point(-cur_cam->get_xangle(), -cur_cam->get_yangle(),
                             -cur_cam->get_zangle()));
}

void draw_manager::visit(const model &_model) {
  std::vector<surface> _surfaces;
  std::vector<point> _points;

  get_model_units_prepare(_points, _surfaces, _model);

  draw_surfaces(_points, _surfaces);
}

void draw_manager::draw_surfaces(const std::vector<point> &_points,
                                 const std::vector<surface> &_surfaces) {
  for (auto _surface : _surfaces)
    draw_surface(
        _points[_surface.get_p1()], _points[_surface.get_p2()],
        _points[_surface.get_p3()],
        color_table_manager_creator().get_manager()->get_table()->get_color(
            _surface.get_color()));
}

void draw_manager::analyze_zbuffer(const point &p, const color &point_color) {
  if (z_buffer[(int)p.get_x()][(int)p.get_y()] < p.get_z()) {
    _drawer->set_point(p, point_color);
    z_buffer[(int)p.get_x()][(int)p.get_y()] = p.get_z();
  }
}

void draw_manager::draw_surface(point p1, point p2, point p3,
                                const color &_color) {
  if (p1.get_y() == p2.get_y() && p1.get_y() == p3.get_y())
    return;

  if (p1.get_y() > p3.get_y())
    p1.swap(p3);
  if (p2.get_y() > p3.get_y())
    p2.swap(p3);
  if (p1.get_y() > p2.get_y())
    p1.swap(p2);

  int total_height = (int)p3.get_y() - (int)p1.get_y();
  int first_segment_height = (int)p2.get_y() - (int)p1.get_y();
  int second_segment_height = (int)p3.get_y() - (int)p2.get_y();

  double dx1 = (p2.get_x() - p1.get_x());
  double dz1 = (p2.get_z() - p1.get_z());
  if (first_segment_height) {
    dx1 /= first_segment_height;
    dz1 /= first_segment_height;
  }

  double dx2 = (p3.get_x() - p1.get_x()) / total_height;
  double dz2 = (p3.get_z() - p1.get_z()) / total_height;

  double dx3 = (p3.get_x() - p2.get_x());
  double dz3 = (p3.get_z() - p2.get_z());
  if (second_segment_height) {
    dx3 /= second_segment_height;
    dz3 /= second_segment_height;
  }

  point left_move_1 = point(dx1, 1, dz1);
  point right_move_1 = point(dx2, 1, dz2);
  point left_move_2 = point(dx3, 1, dz3);
  point right_move_2 = point(dx2, 1, dz2);

  if (p3.get_x() < p2.get_x() ||
      (p2.get_x() == p3.get_x() && p1.get_x() < p2.get_x())) {
    left_move_1.swap(right_move_1);
    left_move_2.swap(right_move_2);
  }

  point left = p1;
  point right = p1;
  if (first_segment_height == 0) {
    right = p2;
    if (p1.get_x() > p2.get_x())
      right.swap(left);
  }
  bool is_first_segment = true;
  while (first_segment_height + second_segment_height) {
    double dz = (right.get_z() - left.get_z());
    if (fabs(right.get_x() - left.get_x()) > EPS)
      dz /= (right.get_x() - left.get_x());
    point move_x(1, 0, dz);
    for (point p = left; (int)p.get_x() <= (int)right.get_x(); p = p + move_x) {
      if ((int)p.get_x() >= 0 && (int)p.get_x() < z_buffer.m() &&
          (int)p.get_y() >= 0 && (int)p.get_y() < z_buffer.n()) {
        analyze_zbuffer(p, _color);
      }
    }

    if (!first_segment_height)
      is_first_segment = false;

    if (is_first_segment) {
      left = left + left_move_1;
      right = right + right_move_1;
      first_segment_height--;
    } else {
      left = left + left_move_2;
      right = right + right_move_2;
      second_segment_height--;
    }
  }
}

void draw_manager::proect_point(point &p) {
  p.set_x(_drawer->get_scene_width() / 2 +
          (p.get_x() * _kx - cur_cam->get_pos().get_x()));
  p.set_y(_drawer->get_scene_height() / 2 -
          (p.get_y() * _ky + cur_cam->get_pos().get_y()));
}
