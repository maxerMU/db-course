#include "swaps_controller.h"
#include <iostream>
#include "base_details_repository.h"
#include "base_swaps_repository.h"

SwapsController::SwapsController(
    const std::shared_ptr<BaseSwapsRepository>& swaps_db,
    const std::shared_ptr<BaseDetailsRepository>& details_db)
    : swaps_db_(swaps_db), details_db_(details_db) {}

void SwapsController::add_swap(const std::string& src, const std::string& dst) {
  swaps_db_->create(src, dst);
}

details_t SwapsController::get_swaps(const std::string& src) {
  auto part_names = swaps_db_->read(src);

  details_t details;
  for (auto part_name : part_names) {
    details.push_back(details_db_->read(part_name));
  }

  return details;
}

void SwapsController::remove_swap(const std::string& src,
                                  const std::string& dst) {
  swaps_db_->delete_(src, dst);
}
