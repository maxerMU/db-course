#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H

#include <string>
#include <vector>

class BaseConfig {
public:
  virtual int get_int_field(const std::vector<std::string> &path) const = 0;
  virtual uint get_uint_field(const std::vector<std::string> &path) const = 0;
  virtual std::string
  get_string_field(const std::vector<std::string> &path) const = 0;

  virtual std::vector<int>
  get_int_array(const std::vector<std::string> &path) const = 0;
  virtual std::vector<uint>
  get_uint_array(const std::vector<std::string> &path) const = 0;
  virtual std::vector<std::string>
  get_string_array(const std::vector<std::string> &path) const = 0;
};

#endif // BASE_CONFIG_H
