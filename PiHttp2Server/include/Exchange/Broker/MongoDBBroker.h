#ifndef _MONGODBBROKER_H_
#define _MONGODBBROKER_H_

#include <memory>
#include <mongocxx/pool.hpp>
#include <mongocxx/client.hpp>
#include "Exchange/Broker/BrokerIf.h"

namespace Exchange {
namespace Broker {

class MongoDBBroker : public BrokerIf
{
   public:
      MongoDBBroker();
      ~MongoDBBroker();
      virtual bool create(std::string & type, bsoncxx::document::value & doc);

   private:
      std::unique_ptr<mongocxx::pool> poolM;
      mongocxx::database dbM;
};

} }

#endif