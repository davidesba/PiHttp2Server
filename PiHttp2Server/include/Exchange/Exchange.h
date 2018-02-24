#ifndef _EXCHANGE_H_
#define _EXCHANGE_H_

#include "Exchange/Broker/BrokerIf.h"
#include <memory>

namespace Exchange {

class Exchange
{
   public:
      Exchange();
      bool create(const std::string & type, std::shared_ptr<std::string> data);
      bool retrieve(const std::string & type, std::shared_ptr<std::string> query, std::string & resData);

   private:
      std::unique_ptr<Broker::BrokerIf> brokerM;
};

}

#endif