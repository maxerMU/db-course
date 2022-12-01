#ifndef SWAPSPARTNAMEDTO_H
#define SWAPSPARTNAMEDTO_H

#include <string>

class SwapsPartNameDto {
 public:
  SwapsPartNameDto(const std::string& json_str);

  std::string get_part_dst() const;
  void set_part_dst(const std::string& value);

 private:
  std::string part_dst;
};

#endif  // SWAPSPARTNAMEDTO_H
