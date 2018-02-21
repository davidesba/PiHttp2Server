#include "Exchange/Broker/Factory/MongoDBBrokerFactory.h"
#include "Exchange/Broker/MongoDBBroker.h"

using namespace Exchange::Broker;

std::unique_ptr<BrokerIf> Factory::MongoDBBrokerFactory::createBroker()
{
   return std::unique_ptr<BrokerIf>(new MongoDBBroker());
}