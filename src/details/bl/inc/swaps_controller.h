#ifndef SWAPSCONTROLLER_H
#define SWAPSCONTROLLER_H

#include "base_config.h"
#include "base_details_repository.h"
#include "base_swaps_repository.h"
#include "detail.h"

class SwapsController {
 public:
  SwapsController(const std::shared_ptr<BaseSwapsRepository>& swaps_db,
                  const std::shared_ptr<BaseDetailsRepository>& details_db);

  void add_swap(const std::string& src, const std::string& dst);
  details_t get_swaps(const std::string& src);
  void remove_swap(const std::string& src, const std::string& dst);

 private:
  std::shared_ptr<BaseSwapsRepository> swaps_db_;
  std::shared_ptr<BaseDetailsRepository> details_db_;
};

#endif  // SWAPSCONTROLLER_H
