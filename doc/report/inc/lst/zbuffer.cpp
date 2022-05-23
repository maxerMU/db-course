void draw_manager::draw_surface(const surface &_surface) {
  surface surf_copy = _surface;
  bool shadow = is_in_shadow(surf_copy);

  sort_points(surf_copy);

  point p1 = cur_proected_points[surf_copy.get_p1()];
  point p2 = cur_proected_points[surf_copy.get_p2()];
  point p3 = cur_proected_points[surf_copy.get_p3()];

  if (p1.get_y() == p2.get_y() && p1.get_y() == p3.get_y())
    return;

  point left_move_1, right_move_1, left_move_2, right_move_2;
  color left_color_1, right_color_1, left_color_2, right_color_2;
  find_steps(left_move_1, right_move_1, left_move_2, right_move_2, surf_copy);

  if (!is_light_source && !shadow)
    find_color_steps(left_color_1, right_color_1, left_color_2, right_color_2,
                     surf_copy);

  point leftp = p1;
  point rightp = p1;

  color leftc, rightc;

  leftc = surf_copy.get_color();
  if (!is_light_source) {
    double intensity;
    if (!shadow)
      intensity =
          find_surface_intensity(surf_copy, cur_points[surf_copy.get_p1()]);
    else
      intensity = SHADOW_INTENSITY;
    leftc = leftc * (intensity / 255);
  }
  rightc = leftc;
  draw_surface_part(leftp, rightp, leftc, rightc, (int)p2.get_y(), left_move_1,
                    left_color_1, right_move_1, right_color_1);

  draw_surface_part(leftp, rightp, leftc, rightc, (int)p3.get_y(), left_move_2,
                    left_color_2, right_move_2, right_color_2);
}
