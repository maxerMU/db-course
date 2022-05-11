#ifndef BASE_SWAPS_REPOSITORY_H
#define BASE_SWAPS_REPOSITORY_H

#include "detail.h"

class BaseSwapsRepository {
 public:
  virtual void create(const std::string& src, const std::string& dst) = 0;
  virtual std::vector<std::string> read(const std::string& src) = 0;
  virtual void delete_(const std::string& src, const std::string& dst) = 0;
};

#endif  // BASE_SWAPS_REPOSITORY_H
