#ifndef DETAILMOTHEROBJECT_H
#define DETAILMOTHEROBJECT_H

#include "detail.h"

class DetailMotherObject {
 public:
  DetailMotherObject();

  Detail create_detail();
  details_t create_details();
  details_quantities_t create_detail_quanties();

 private:
  Detail detail_;
  details_t details_;
  details_quantities_t quantities_;
};

#endif  // DETAILMOTHEROBJECT_H
