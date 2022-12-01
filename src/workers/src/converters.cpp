#include "converters.h"
#include <ctime>

std::string to_json(const WorkerGet& worker) {
  Json::Value root;
  root["id"] = (unsigned long long)worker.worker_id();
  root["name"] = worker.name();
  root["surname"] = worker.surname();
  auto birthdate = worker.birthdate();
  std::vector<char> temp_time_str(MAX_TIME_STR_LENGTH);
  std::strftime(temp_time_str.data(), MAX_TIME_STR_LENGTH, "%D", &birthdate);
  root["birthdate"] = std::string(temp_time_str.data());
  root["privilege"] = (int)worker.getPrivilege();

  Json::FastWriter writer;
  return writer.write(root);
}

std::string to_json(const std::vector<WorkerGet>& workers) {
  Json::Value arr = Json::arrayValue;

  for (auto worker : workers) {
    Json::Value root;
    root["id"] = (unsigned long long)worker.worker_id();
    root["name"] = worker.name();
    root["surname"] = worker.surname();
    auto birthdate = worker.birthdate();
    std::vector<char> temp_time_str(MAX_TIME_STR_LENGTH);
    std::strftime(temp_time_str.data(), MAX_TIME_STR_LENGTH, "%D", &birthdate);
    root["birthdate"] = std::string(temp_time_str.data());
    root["privilege"] = (int)worker.getPrivilege();

    arr.append(root);
  }

  Json::Value root;
  root["workers"] = arr;

  Json::FastWriter writer;
  return writer.write(root);
}
