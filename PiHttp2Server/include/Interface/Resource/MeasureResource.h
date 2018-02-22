#ifndef _MEASURERESOURCE_H_
#define _MEASURERESOURCE_H_

#include "Interface/Resource/AbstractResource.h"

namespace Interface {
namespace Resource {


   class MeasureResource : public AbstractResource
   {
   public:
      MeasureResource(std::string & docRoot, Exchange::Exchange & exchange);
      ~MeasureResource();
      
   protected:
      
      virtual void handle_get(const nghttp2::asio_http2::server::request & req,
                              const nghttp2::asio_http2::server::response & res);
      
      virtual void handle_post(const nghttp2::asio_http2::server::request &req,
                              const nghttp2::asio_http2::server::response &res);
      
      virtual void handle_delete(const nghttp2::asio_http2::server::request &req,
                                 const nghttp2::asio_http2::server::response &res);

      std::string typeM;
    };

} }

#endif