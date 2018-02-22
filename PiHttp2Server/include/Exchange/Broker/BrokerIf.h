#ifndef _BROKERIF_H_
#define _BROKERIF_H_

#include <bsoncxx/json.hpp>

namespace Exchange {
namespace Broker {

class BrokerIf
{
   public:
      virtual bool create(std::string & type, bsoncxx::document::value & doc) = 0;
};

} }

#endif