#include "Exchange/Exchange.h"
#include "Exchange/Broker/Factory/BrokerFactory.h"
#include <bsoncxx/json.hpp>

using namespace Exchange::Broker::Factory;
using namespace std;
using namespace bsoncxx;

namespace Exchange {

Exchange::Exchange()
{
   //We only have one broker.
   //If we add more, this should be read from configuration file
   auto factory = "MongoDB";
   brokerM = BrokerFactory::createBrokerFactory(factory)->createBroker();
}

bool Exchange::createMeasure(const uint8_t *data, size_t len)
{
   try
   {
      auto bData = from_json(string((const char*)data, len));
      return brokerM->createMeasure(bData);
   }
   catch (exception e)
   {
      return false;
   }
}

}