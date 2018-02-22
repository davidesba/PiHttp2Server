#ifndef _EXCHANGE_H_
#define _EXCHANGE_H_

#include "Exchange/Broker/BrokerIf.h"
#include <memory>

namespace Exchange {

class Exchange
{
   public:
      Exchange();
      bool create(std::string & type, const uint8_t *data, size_t len);

   private:
      std::unique_ptr<Broker::BrokerIf> brokerM;
};

}

#endif