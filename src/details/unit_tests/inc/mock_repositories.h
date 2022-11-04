#ifndef MOCKREPOSITORIES_H
#define MOCKREPOSITORIES_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "base_details_repository.h"
#include "base_producers_repository.h"
#include "base_stock_repository.h"
#include "base_swaps_repository.h"

class DetailsMockReposiroty : public BaseDetailsRepository {
 public:
  MOCK_METHOD(void, create, (const Detail& detail), (override));
  MOCK_METHOD(Detail, read, (const std::string& part_name), (override));
  MOCK_METHOD(details_t, read_all, (), (override));
  MOCK_METHOD(void, update, (const Detail& detail), (override));
  MOCK_METHOD(void, delete_, (const std::string& part_name), (override));
};

class ProducersMockRepository : public BaseProducersRepository {
 public:
  MOCK_METHOD(size_t,
              create,
              (const DetailsProducerData& producer),
              (override));
  MOCK_METHOD(DetailsProducer, read, (size_t producer_id), (override));
  MOCK_METHOD(producers_t, read_all, (), (override));
  MOCK_METHOD(void, update, (const DetailsProducer& producer), (override));
  MOCK_METHOD(void, delete_, (size_t producer_id), (override));
};

class SwapsMockRepository : public BaseSwapsRepository {
 public:
  MOCK_METHOD(void,
              create,
              (const std::string& src, const std::string& dst),
              (override));
  MOCK_METHOD(std::vector<std::string>,
              read,
              (const std::string& src),
              (override));
  MOCK_METHOD(void,
              delete_,
              (const std::string& src, const std::string& dst),
              (override));
};

class StockMockRepository : public BaseStockRepository {
 public:
  MOCK_METHOD(void,
              create,
              (const std::string& part_name, size_t worker_id, size_t quantity),
              (override));
  MOCK_METHOD(detail_quantity_t,
              read,
              (const std::string& part_name),
              (override));
  MOCK_METHOD(details_quantities_t, read_current, (), (override));
  MOCK_METHOD(details_names_t, read_prev, (), (override));
  MOCK_METHOD(stock_logs_t,
              read_log,
              (const std::string& time_start, const std::string& time_end),
              (override));
  MOCK_METHOD(void,
              delete_,
              (const std::string& part_name, size_t worker_id, size_t quantity),
              (override));
};

#endif  // MOCKREPOSITORIES_H
