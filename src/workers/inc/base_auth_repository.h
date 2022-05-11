#ifndef BASE_AUTH_REPOSITORY_H
#define BASE_AUTH_REPOSITORY_H

#include "worker.h"

class BaseAuthRepository {
public:
    virtual void create_session(size_t worker_id, const std::string &token) = 0;
    virtual bool is_valid_session(size_t worker_id, const std::string &token) = 0;
};

#endif // BASE_AUTH_REPOSITORY_H
