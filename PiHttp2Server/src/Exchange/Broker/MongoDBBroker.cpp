#include "Exchange/Broker/MongoDBBroker.h"
#include <mongocxx/stdx.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>

using namespace Exchange::Broker;
using namespace mongocxx;

MongoDBBroker::MongoDBBroker()
{
   // This should be done only once
   instance instance{};
   uri uri("mongodb://localhost:27017");
   poolM = std::unique_ptr<pool>(new pool(uri));
   auto c = poolM->acquire();
   dbM = (*c)["MinerStats"];
}

MongoDBBroker::~MongoDBBroker()
{}

bool MongoDBBroker::createMeasure(bsoncxx::document::value & doc)
{
   collection measures = dbM["Measures"];
   
   try
   {
      auto result = measures.insert_one(std::move(doc));
      return (result->result().inserted_count() == 1);
   }
   catch (const bulk_write_exception& e)
   {
      return false;
   }
   
}