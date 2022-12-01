#ifndef WORKERDTO_H
#define WORKERDTO_H

#include <string>

class WorkerDto {
 public:
  WorkerDto(const std::string &json_str);

  std::string get_name() const;
  void set_name(const std::string &value);

  std::string get_surname() const;
  void set_surname(const std::string &value);

 private:
  std::string name;
  std::string surname;
};

#endif  // WORKERDTO_H
