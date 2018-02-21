#include "Exchange/Exchange.h"
#include "Exchange/Broker/Factory/BrokerFactory.h"

using namespace Exchange::Broker::Factory;

namespace Exchange {

Exchange::Exchange()
{
   //We only have one broker.
   //If we add more, this should be read from configuration file
   auto factory = "MongoDB";
   brokerM = BrokerFactory::createBrokerFactory(factory)->createBroker();
}

void Exchange::storeMeasure()
{}

}