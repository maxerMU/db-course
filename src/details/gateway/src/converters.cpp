#include "converters.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

std::string DetailsArrayConverter::to_json(const details_t& details) {
  Json::Value arr = Json::arrayValue;

  for (auto detail : details) {
    Json::Value root;
    root["part_number"] = detail.part_number();
    root["name_rus"] = detail.name_rus();
    root["name_eng"] = detail.name_eng();
    root["producer_id"] = (int)detail.producer_id();
    arr.append(root);
  }

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;

  return writer.write(root);
}

std::string DetailConverter::to_json(const Detail& detail) {
  Json::Value root;

  root["part_number"] = detail.part_number();
  root["name_rus"] = detail.name_rus();
  root["name_eng"] = detail.name_eng();
  root["producer_id"] = (int)detail.producer_id();

  Json::FastWriter writer;

  return writer.write(root);
}

std::string ProducersArrayConverter::to_json(const producers_t& producers) {
  Json::Value arr = Json::arrayValue;

  for (auto producer : producers) {
    Json::Value root;
    root["id"] = (int)producer.id();
    root["name"] = producer.name();
    root["country"] = producer.country();
    arr.append(root);
  }

  Json::Value root;
  root["producers"] = arr;

  Json::FastWriter writer;

  return writer.write(root);
}

std::string ProducerConverter::to_json(const DetailsProducer& producer) {
  Json::Value root;
  root["id"] = (int)producer.id();
  root["name"] = producer.name();
  root["country"] = producer.country();

  Json::FastWriter writer;

  return writer.write(root);
}

std::string IdConverter::to_json(const size_t& id) {
  unsigned long long int tmp = id;
  Json::Value root;
  root["id"] = tmp;

  Json::FastWriter writer;
  return writer.write(root);
}

std::string DetailQuantityConverter::to_json(
    const detail_quantity_t& detail_quantity) {
  Json::Value root;
  root["part_number"] = detail_quantity.first;
  root["quantity"] = (int)detail_quantity.second;

  Json::FastWriter writer;

  return writer.write(root);
}

std::string PartNamesArrayConverter::to_json(
    const details_names_t& detail_names) {
  Json::Value arr = Json::arrayValue;
  for (auto name : detail_names) {
    Json::Value root;
    root["part_number"] = name;
    arr.append(root);
  }

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;

  return writer.write(root);
}

std::string DetailsQuantitiesArrayConverter::to_json(
    const details_quantities_t& details_quantities) {
  Json::Value arr = Json::arrayValue;
  for (auto detail_quantity : details_quantities) {
    Json::Value root;
    root["part_number"] = detail_quantity.first;
    root["quantity"] = (int)detail_quantity.second;
    arr.append(root);
  }

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;

  return writer.write(root);
}

std::string StockLogsConverter::to_json(const stock_logs_t& stock_logs) {
  Json::Value arr = Json::arrayValue;

  for (auto log : stock_logs) {
    Json::Value root;
    root["worker_id"] = (int)log.fk_worker();
    root["detail_id"] = log.fk_detail();
    root["change"] = (int)log.change();
    root["time_change"] = log.time_change();
    arr.append(root);
  }

  Json::Value root;
  root["logs"] = arr;

  Json::FastWriter writer;

  return writer.write(root);
}
