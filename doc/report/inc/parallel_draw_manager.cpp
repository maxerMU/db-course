#include "parallel_draw_manager.h"
#include "color_table_manager.h"
#include <vector>

void parallel_draw_manager::set_threads(size_t threads_count) {
  this->threads_count = threads_count;
}

std::shared_ptr<draw_manager> parallel_draw_manager_creator::get_manager() {
  if (_manager == nullptr)
    create_manager();

  return _manager;
}

void parallel_draw_manager_creator::create_manager() {
  static std::shared_ptr<draw_manager> _manager(new parallel_draw_manager());
  this->_manager = _manager;
}

void parallel_draw_manager::analyze_zbuffer(const point &p,
                                            const color &point_color) {

  bool set_point = false;
  int x = (int)p.get_x();
  int y = (int)p.get_y();
  int z = (int)p.get_z();
  mtx.lock();
  if (z_buffer[x][y] < z) {
    set_point = true;
    z_buffer[x][y] = z;
  }
  mtx.unlock();
  if (set_point)
    _drawer->set_point(p, point_color);
}

void parallel_draw_manager::draw_surfaces(
    const std::vector<point> &_points, const std::vector<surface> &_surfaces) {

  // std::vector<thread> threads(threads_count);
  thread *threads = new thread[threads_count];
  size_t surfaces_per_thread = _surfaces.size() / threads_count;
  size_t rest_surfaces = _surfaces.size() % threads_count;
  size_t start = 0, end = 0;

  for (size_t i = 0; i < threads_count; i++, start = end) {
    end += surfaces_per_thread;
    if (rest_surfaces) {
      end++;
      rest_surfaces--;
    }
    threads[i] = thread(&parallel_draw_manager::draw_range_surfaces, this,
                        start, end, _points, _surfaces);
  }

  for (size_t i = 0; i < threads_count; i++) {
    if (threads[i].joinable())
      threads[i].join();
  }
}

void parallel_draw_manager::draw_range_surfaces(
    size_t start, size_t end, const std::vector<point> &_points,
    const std::vector<surface> &_surfaces) {
  for (size_t i = start; i < end; i++) {
    draw_surface(
        _points[_surfaces[i].get_p1()], _points[_surfaces[i].get_p2()],
        _points[_surfaces[i].get_p3()],
        color_table_manager_creator().get_manager()->get_table()->get_color(
            _surfaces[i].get_color()));
  }
}
