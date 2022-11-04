#include "detail_mother_object.h"

DetailMotherObject::DetailMotherObject()
    : detail_(Detail("name_rus", "name_eng", "123456-987654", 1)) {
  details_.push_back(Detail("name_rus", "name_eng", "123456-987654", 1));
  details_.push_back(Detail("name_rus2", "name_eng1", "123456-945654", 2));
  details_.push_back(Detail("name_rus3", "name_eng2", "465456-945654", 3));

  quantities_.push_back(std::pair<std::string, size_t>("123456-789978", 5));
  quantities_.push_back(std::pair<std::string, size_t>("123456-789123", 2));
  quantities_.push_back(std::pair<std::string, size_t>("987456-789123", 10));
}

Detail DetailMotherObject::create_detail() {
  return detail_;
}

details_t DetailMotherObject::create_details() {
  return details_;
}

details_quantities_t DetailMotherObject::create_detail_quanties() {
  return quantities_;
}
