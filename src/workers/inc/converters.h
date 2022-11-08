#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <string>

#include "worker.h"

#define MAX_TIME_STR_LENGTH 32

std::string to_json(const WorkerGet& worker);
std::string to_json(const std::vector<WorkerGet>& workers);

#endif  // CONVERTERS_H
