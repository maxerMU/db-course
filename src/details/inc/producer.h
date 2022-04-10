#ifndef PRODUCER_H
#define PRODUCER_H

#include <string>

class DetailsProducer {
public:
  DetailsProducer() = default;
  DetailsProducer(const std::string &name, const std::string &country);

  std::string name() const;
  void set_name(const std::string &name);

  std::string country() const;
  void set_country(const std::string &country);

private:
  std::string name_;
  std::string country_;
};

#endif // PRODUCER_H
