#ifndef BASE_WORKERS_REPOSITORY_H
#define BASE_WORKERS_REPOSITORY_H

#include "worker.h"

class BaseWorkersRepository {
 public:
  virtual size_t create(const WorkerPost& worker) = 0;

  virtual WorkerBaseInf read(size_t worker_id) = 0;
  virtual std::vector<WorkerGet> read() = 0;
  virtual size_t workers_count() = 0;
  virtual int update(const WorkerUpdate& worker) = 0;
  virtual void update_privilege(size_t worker_id,
                                const PrivilegeLevel& privilege) = 0;
  virtual bool get_password(std::string& password,
                            size_t& worker_id,
                            const std::string& username) = 0;
  // void delete_(Token) = 0;
};

#endif  // BASE_WORKERS_REPOSITORY_H
