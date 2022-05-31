#ifndef BASEDETAILSREPOSITORY_H
#define BASEDETAILSREPOSITORY_H

#include "detail.h"

class BaseDetailsRepository {
 public:
  virtual void create(const Detail& detail) = 0;
  virtual Detail read(const std::string &part_name) = 0;
  virtual details_t read_all() = 0;
  virtual void update(const Detail& detail) = 0;
  virtual void delete_(const std::string &part_name) = 0;
};

#endif  // BASEDETAILSREPOSITORY_H
