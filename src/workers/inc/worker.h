#ifndef WORKER_H
#define WORKER_H

#include <time.h>
#include <string>

enum PrivilegeLevel { ADMIN = 1, SELLER, STOREKEEPER, CLIENT, GUEST };

class WorkerAuth {
 public:
  WorkerAuth() = default;
  WorkerAuth(const std::string& json_str);
  WorkerAuth(const std::string& username, const std::string& password);

  std::string username() const;
  void setUsername(const std::string& username);

  std::string password() const;
  void setPassword(const std::string& password);

 protected:
  std::string username_;
  std::string password_;
};

class WorkerBaseInf {
 public:
  WorkerBaseInf() = default;
  WorkerBaseInf(const std::string& name,
                const std::string& surname,
                const struct tm& birthdate,
                const PrivilegeLevel& privilege = GUEST);

  std::string name() const;
  void setName(const std::string& name);

  std::string surname() const;
  void setSurname(const std::string& surname);

  tm birthdate() const;
  void setBirthdate(const tm& birthdate);

  PrivilegeLevel getPrivilege() const;
  void setPrivilege(const PrivilegeLevel& value);

 protected:
  std::string name_;
  std::string surname_;
  tm birthdate_;
  PrivilegeLevel privilege_;
};

class WorkerPost : public WorkerAuth, public WorkerBaseInf {
 public:
  WorkerPost(const std::string& name,
             const std::string& surname,
             const struct tm& birthdate,
             const std::string& username,
             const std::string& password,
             const PrivilegeLevel& privilege = GUEST);
  WorkerPost(const std::string& json_str,
             const PrivilegeLevel& privilege = GUEST);
};

class WorkerUpdate : public WorkerPost {
 public:
  WorkerUpdate(size_t worker_id,
               const std::string& name,
               const std::string& surname,
               const struct tm& birthdate,
               const std::string& username,
               const std::string& password,
               const PrivilegeLevel& privilege = GUEST);

  size_t getWorker_id() const;
  void setWorker_id(const size_t& value);

 protected:
  size_t worker_id_;
};

class WorkerGet : public WorkerBaseInf {
 public:
  WorkerGet(size_t worker_id,
            const std::string& name,
            const std::string& surname,
            const struct tm& birthdate,
            const PrivilegeLevel& privilege = GUEST);

  size_t worker_id() const;
  void setWorker_id(const size_t& worker_id);

  PrivilegeLevel privilege() const;
  void setPrivilege(const PrivilegeLevel& privilege);

 protected:
  size_t worker_id_;
};

#endif  // WORKER_H
