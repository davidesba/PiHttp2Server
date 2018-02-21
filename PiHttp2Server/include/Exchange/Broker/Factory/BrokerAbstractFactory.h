#ifndef _BROKERABSTRACTFACTORY_H_
#define _BROKERABSTRACTFACTORY_H_


#include <memory>
#include "Exchange/Broker/BrokerIf.h"

namespace Exchange {
namespace Broker {
namespace Factory {

    class BrokerAbstractFactory
    {
    public:
        virtual std::unique_ptr<BrokerIf> createBroker() = 0;

    };

} } }

#endif