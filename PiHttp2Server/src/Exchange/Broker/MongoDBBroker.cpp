#include "Exchange/Broker/MongoDBBroker.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using namespace Exchange::Broker;
using namespace mongocxx;

MongoDBBroker::MongoDBBroker()
{
   // This should be done only once
   instance instance{};
   uri uri("mongodb://localhost:27017");
   poolM = std::unique_ptr<pool>(new pool(uri));
}

void MongoDBBroker::storeMeasure()
{}