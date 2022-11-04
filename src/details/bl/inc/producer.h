#ifndef PRODUCER_H
#define PRODUCER_H

#include <string>
#include <vector>

class DetailsProducerData {
 public:
  DetailsProducerData() = default;
  DetailsProducerData(const std::string& name, const std::string& country);

  std::string name() const;
  void set_name(const std::string& name);

  std::string country() const;
  void set_country(const std::string& country);

  bool operator==(const DetailsProducerData& data) const;

 protected:
  std::string name_;
  std::string country_;
};

class DetailsProducer : public DetailsProducerData {
 public:
  DetailsProducer() = default;
  DetailsProducer(size_t id,
                  const std::string& name,
                  const std::string& country);
  DetailsProducer(size_t id, const DetailsProducerData& data);

  size_t id() const;
  void set_id(const size_t& id);

  bool operator==(const DetailsProducer& producer) const;

 private:
  size_t id_;
  std::string name_;
  std::string country_;
};

typedef std::vector<DetailsProducer> producers_t;

#endif  // PRODUCER_H
