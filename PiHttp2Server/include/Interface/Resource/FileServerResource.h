#ifndef _FILESERVERRESOURCE_H_
#define _FILESERVERRESOURCE_H_

#include "Interface/Resource/AbstractResource.h"

namespace Interface {
namespace Resource {


   class FileServerResource : public AbstractResource
   {
   public:
      FileServerResource(std::string & docRoot);
      ~FileServerResource();
   protected:
      
      virtual void handle_get(const nghttp2::asio_http2::server::request & req,
                              const nghttp2::asio_http2::server::response & res);
      
      virtual void handle_put(const nghttp2::asio_http2::server::request &req,
                              const nghttp2::asio_http2::server::response &res);
      
      virtual void handle_post(const nghttp2::asio_http2::server::request &req,
                              const nghttp2::asio_http2::server::response &res);
      
      virtual void handle_delete(const nghttp2::asio_http2::server::request &req,
                                 const nghttp2::asio_http2::server::response &res);
      
      bool isDirectory(const std::string& filePath);

      bool pathExist(const std::string& filePath);

      std::string convertSize(uintmax_t size);
    };

} }

#endif