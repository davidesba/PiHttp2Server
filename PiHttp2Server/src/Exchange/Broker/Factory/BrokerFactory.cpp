#include "Exchange/Broker/Factory/BrokerFactory.h"
#include "Exchange/Broker/Factory/MongoDBBrokerFactory.h"

using namespace Exchange::Broker::Factory;
using namespace std;

unique_ptr<BrokerAbstractFactory> BrokerFactory::createBrokerFactory(const string& db)
{
   unique_ptr<BrokerAbstractFactory> factory;
   if ( db == "MongoDB" )
   {
      factory = unique_ptr<BrokerAbstractFactory>(new MongoDBBrokerFactory());
   }

   return factory;
}