#ifndef _EXCHANGE_H_
#define _EXCHANGE_H_

#include "Exchange/Broker/BrokerIf.h"
#include <memory>

namespace Exchange {

class Exchange
{
   public:
      Exchange();
      void storeMeasure();

   private:
      std::unique_ptr<Broker::BrokerIf> brokerM;
};

}

#endif