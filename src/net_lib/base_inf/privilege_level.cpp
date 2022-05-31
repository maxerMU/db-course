#include "privilege_level.h"
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

std::string make_privilege_json(const PrivilegeLevel& privilege) {
  Json::Value root;
  root["privilege_level"] = (int)privilege;

  Json::FastWriter writer;
  return writer.write(root);
}
