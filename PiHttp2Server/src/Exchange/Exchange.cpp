#include "Exchange/Exchange.h"
#include "Exchange/Broker/Factory/BrokerFactory.h"
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <iostream>

using namespace Exchange::Broker::Factory;
using namespace std;
using namespace bsoncxx;
using bsoncxx::builder::basic::make_document;

namespace Exchange {

Exchange::Exchange()
{
   //We only have one broker.
   //If we add more, this should be read from configuration file
   auto factory = "MongoDB";
   brokerM = BrokerFactory::createBrokerFactory(factory)->createBroker();
}

bool Exchange::create(const string & type, shared_ptr<string> data)
{
   try
   {
      auto bData = from_json(*(data.get()));
      return brokerM->create(type, bData);
   }
   catch (exception e)
   {
      cout << "Error " << e.what() << " creating " << data->c_str() << endl;
      return false;
   }
}

bool Exchange::retrieve(const std::string & type, shared_ptr<string> query, string & resData)
{
   try
   {
      bsoncxx::document::value filter = make_document();
      if (query->size() > 0)
         filter = from_json(*(query.get()));
      return brokerM->retrieve(type, filter, resData);
   }
   catch (exception e)
   {
      cout << "Error " << e.what() << " retrieving " << query->c_str() << endl;
      return false;
   }
}

}