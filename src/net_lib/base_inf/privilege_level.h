#ifndef PRIVILEGE_LEVEL_H
#define PRIVILEGE_LEVEL_H

#include <string>

enum PrivilegeLevel { ADMIN = 1, SELLER, STOREKEEPER, CLIENT, GUEST };

std::string make_privilege_json(const PrivilegeLevel& privilege);

#endif  // PRIVILEGE_LEVEL_H
