#include "Exchange/Broker/MongoDBBroker.h"
#include <mongocxx/stdx.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>

using namespace Exchange::Broker;
using namespace mongocxx;
using namespace std;

MongoDBBroker::MongoDBBroker()
{
   // This should be done only once
   instance instance{};
   uri uri("mongodb://localhost:27017");
   poolM = unique_ptr<pool>(new pool(uri));
   auto c = poolM->acquire();
   dbM = (*c)["MinerStats"];
}

MongoDBBroker::~MongoDBBroker()
{}

bool MongoDBBroker::create(const std::string & type, bsoncxx::document::value & doc)
{  
   try
   {
      collection col = dbM[type];
      auto result = col.insert_one(std::move(doc));
      return (result->result().inserted_count() == 1);
   }
   catch (const bulk_write_exception& e)
   {
      return false;
   }
}

bool MongoDBBroker::retrieve(const std::string & type, bsoncxx::document::value & doc, string & resData)
{
   collection col = dbM[type];
   cursor cursor = col.find(std::move(doc));

   resData.append("[");
   for(auto measure : cursor)
   {
      resData.append(bsoncxx::to_json(measure) + string(","));
   }
   resData = resData.substr(0, resData.size()-1);
   resData.append("]");

   return true;
}