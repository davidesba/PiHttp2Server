#ifndef _MONGODBBROKERFACTORY_H_
#define _MONGODBBROKERFACTORY_H_

#include "Exchange/Broker/Factory/BrokerFactory.h"

namespace Exchange {
namespace Broker {
namespace Factory {

    class MongoDBBrokerFactory : public BrokerAbstractFactory
    {
    public:
        std::unique_ptr<Broker::BrokerIf> createBroker();
    };

} } }

#endif