#include "yamlcpp_config.h"

YamlCppConfig::YamlCppConfig(const std::string &filename) {
  start_node = YAML::LoadFile(filename);
}

void YamlCppConfig::get_node(YAML::Node &node,
                             const std::vector<std::string> &path) const {
  node = YAML::Clone(start_node);
  for (std::string section : path) {
    node = node[section.c_str()];
  }
}

int YamlCppConfig::get_int_field(const std::vector<std::string> &path) const {
  YAML::Node node;
  get_node(node, path);

  return node.as<int>();
}

uint YamlCppConfig::get_uint_field(const std::vector<std::string> &path) const {
  YAML::Node node;
  get_node(node, path);

  return node.as<uint>();
}

std::string
YamlCppConfig::get_string_field(const std::vector<std::string> &path) const {
  YAML::Node node;
  get_node(node, path);

  return node.as<std::string>();
}

std::vector<int>
YamlCppConfig::get_int_array(const std::vector<std::string> &path) const {
  return get_array<int>(path);
}

std::vector<uint>
YamlCppConfig::get_uint_array(const std::vector<std::string> &path) const {
  return get_array<uint>(path);
}

std::vector<std::string>
YamlCppConfig::get_string_array(const std::vector<std::string> &path) const {
  return get_array<std::string>(path);
}
