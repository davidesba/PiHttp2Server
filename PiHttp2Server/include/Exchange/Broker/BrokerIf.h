#ifndef _BROKERIF_H_
#define _BROKERIF_H_

namespace Exchange {
namespace Broker {

class BrokerIf
{
   public:
      virtual void storeMeasure() = 0;
};

} }

#endif