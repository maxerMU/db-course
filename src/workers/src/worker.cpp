#include "worker.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <time.h>
#include "server_exceptions.h"

WorkerPost::WorkerPost(const std::string& name,
                       const std::string& surname,
                       const tm& birthdate,
                       const std::string& username,
                       const std::string& password,
                       const PrivilegeLevel& privilege)
    : WorkerAuth(username, password),
      WorkerBaseInf(name, surname, birthdate, privilege) {}

WorkerPost::WorkerPost(const std::string& json_str,
                       const PrivilegeLevel& privilege) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse WorkerPost object");
  }

  name_ = value["name"].asString();
  surname_ = value["surname"].asString();
  std::string birthdate_str = value["birthdate"].asString();
  if (!strptime(birthdate_str.c_str(), "%Y-%m-%d", &birthdate_))
    throw JsonParserException("Incorrect birtdate format");
  username_ = value["username"].asString();
  password_ = value["password"].asString();
  privilege_ = privilege;
}

WorkerAuth::WorkerAuth(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse WorkerAuth object");
  }

  username_ = value["username"].asString();
  password_ = value["password"].asString();
}

WorkerAuth::WorkerAuth(const std::string& username, const std::string& password)
    : username_(username), password_(password) {}

std::string WorkerAuth::username() const {
  return username_;
}

void WorkerAuth::setUsername(const std::string& username) {
  username_ = username;
}

std::string WorkerAuth::password() const {
  return password_;
}

void WorkerAuth::setPassword(const std::string& password) {
  password_ = password;
}

WorkerBaseInf::WorkerBaseInf(const std::string& name,
                             const std::string& surname,
                             const tm& birthdate,
                             const PrivilegeLevel& privilege)
    : name_(name),
      surname_(surname),
      birthdate_(birthdate),
      privilege_(privilege) {}

std::string WorkerBaseInf::name() const {
  return name_;
}

void WorkerBaseInf::setName(const std::string& name) {
  name_ = name;
}

std::string WorkerBaseInf::surname() const {
  return surname_;
}

void WorkerBaseInf::setSurname(const std::string& surname) {
  surname_ = surname;
}

tm WorkerBaseInf::birthdate() const {
  return birthdate_;
}

void WorkerBaseInf::setBirthdate(const tm& birthdate) {
  birthdate_ = birthdate;
}

PrivilegeLevel WorkerBaseInf::getPrivilege() const {
  return privilege_;
}

void WorkerBaseInf::setPrivilege(const PrivilegeLevel& value) {
  privilege_ = value;
}

WorkerUpdate::WorkerUpdate(size_t worker_id,
                           const std::string& name,
                           const std::string& surname,
                           const tm& birthdate,
                           const std::string& username,
                           const std::string& password,
                           const PrivilegeLevel& privilege)
    : worker_id_(worker_id),
      WorkerPost(name, surname, birthdate, username, password, privilege) {}

WorkerUpdate::WorkerUpdate(size_t worker_id, const WorkerPost& worker_post)
    : worker_id_(worker_id), WorkerPost(worker_post) {}

size_t WorkerUpdate::getWorker_id() const {
  return worker_id_;
}

void WorkerUpdate::setWorker_id(const size_t& value) {
  worker_id_ = value;
}

WorkerGet::WorkerGet(size_t worker_id, const WorkerBaseInf& base_inf)
    : worker_id_(worker_id), WorkerBaseInf(base_inf) {}

WorkerGet::WorkerGet(size_t worker_id,
                     const std::string& name,
                     const std::string& surname,
                     const tm& birthdate,
                     const PrivilegeLevel& privilege)
    : worker_id_(worker_id),
      WorkerBaseInf(name, surname, birthdate, privilege) {}

size_t WorkerGet::worker_id() const {
  return worker_id_;
}

void WorkerGet::setWorkerId(const size_t& worker_id) {
  worker_id_ = worker_id;
}
