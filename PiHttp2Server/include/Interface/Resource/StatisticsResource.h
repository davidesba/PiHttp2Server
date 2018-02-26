#ifndef _STATISTICSRESOURCE_H_
#define _STATISTICSRESOURCE_H_

#include "Interface/Resource/AbstractResource.h"

namespace Interface {
namespace Resource {


   class StatisticsResource : public AbstractResource
   {
   public:
      StatisticsResource(std::string & docRoot, Exchange::Exchange & exchange);
      ~StatisticsResource();
      
   protected:
      
      virtual void handle_get(const nghttp2::asio_http2::server::request & req,
                              const nghttp2::asio_http2::server::response & res);
    };

} }

#endif