#ifndef _BROKERFACTORY_H_
#define _BROKERFACTORY_H_


#include <memory>
#include "Exchange/Broker/BrokerIf.h"
#include "Exchange/Broker/Factory/BrokerAbstractFactory.h"

namespace Exchange {
namespace Broker {
namespace Factory {

    class BrokerFactory
    {
    public:
        static std::unique_ptr<BrokerAbstractFactory> createBrokerFactory(const std::string& db);

    };

} } }

#endif