#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "detail.h"
#include "stock_detail.h"
#include "stock_log.h"

class DetailsArrayConverter {
 public:
  std::string to_json(const details_t& details);
};

class DetailConverter {
 public:
  std::string to_json(const Detail& detail);
};

class ProducersArrayConverter {
 public:
  std::string to_json(const producers_t& producers);
};

class ProducerConverter {
 public:
  std::string to_json(const DetailsProducer& producer);
};

class IdConverter {
 public:
  std::string to_json(const size_t& id);
};

class DetailQuantityConverter {
 public:
  std::string to_json(const detail_quantity_t& detail_quantity);
};

class PartNamesArrayConverter {
 public:
  std::string to_json(const details_names_t& detail_names);
};

class DetailsQuantitiesArrayConverter {
 public:
  std::string to_json(const details_quantities_t& details_quantities);
};

class StockLogsConverter {
 public:
  std::string to_json(const stock_logs_t& stock_logs);
};

class StockDetailsConverter {
 public:
  std::string to_json(const StockDetails& stock_details);
};

#endif  // CONVERTERS_H
