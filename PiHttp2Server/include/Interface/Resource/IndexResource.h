#ifndef _INDEXRESOURCE_H_
#define _INDEXRESOURCE_H_

#include "Interface/Resource/AbstractResource.h"

namespace Interface {
namespace Resource {


   class IndexResource : public AbstractResource
   {
   public:
      IndexResource(std::string & docRoot, Exchange::Exchange & exchange);
      ~IndexResource();
      
   protected:
      
      virtual void handle_get(const nghttp2::asio_http2::server::request & req,
                              const nghttp2::asio_http2::server::response & res);
    };

} }

#endif