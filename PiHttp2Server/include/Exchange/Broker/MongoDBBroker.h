#ifndef _MONGODBBROKER_H_
#define _MONGODBBROKER_H_

#include <memory>
#include <mongocxx/pool.hpp>
#include "Exchange/Broker/BrokerIf.h"

namespace Exchange {
namespace Broker {

class MongoDBBroker : public BrokerIf
{
   public:
      MongoDBBroker();
      virtual void storeMeasure();

   private:
      std::unique_ptr<mongocxx::pool> poolM;
};

} }

#endif