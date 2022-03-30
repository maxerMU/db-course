#ifndef YAMLCPPCONFIG_H
#define YAMLCPPCONFIG_H

#include "base_config.h"
#include "yaml-cpp/yaml.h"

class YamlCppConfig : public BaseConfig {
public:
  YamlCppConfig(const std::string &filename);

  virtual int
  get_int_field(const std::vector<std::string> &path) const override;
  virtual uint
  get_uint_field(const std::vector<std::string> &path) const override;
  virtual std::string
  get_string_field(const std::vector<std::string> &path) const override;

  virtual std::vector<int>
  get_int_array(const std::vector<std::string> &path) const override;
  virtual std::vector<uint>
  get_uint_array(const std::vector<std::string> &path) const override;
  virtual std::vector<std::string>
  get_string_array(const std::vector<std::string> &path) const override;

private:
  void get_node(YAML::Node &node, const std::vector<std::string> &path) const;
  YAML::Node start_node;

  template <typename T>
  std::vector<T> get_array(const std::vector<std::string> &path) const;
};

template <typename T>
std::vector<T>
YamlCppConfig::get_array(const std::vector<std::string> &path) const {
  YAML::Node node;
  get_node(node, path);

  std::vector<T> res;
  for (size_t i = 0; i < node.size(); i++)
    res.push_back(node[i].as<T>());

  return res;
}

#endif // YAMLCPPCONFIG_H
