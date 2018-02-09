#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif // HAVE_UNISTD_H
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif // HAVE_FCNTL_H
#include <iostream>
#include <string>

#include "Interface/Router.h"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

int main(int argc, char *argv[]) {
   try {
      // Check command line arguments.
      if (argc < 4)
      {
         std::cerr << "Usage: Http2Server <address> <port> <threads> <doc-root>"
                     << "[<private-key-file> <cert-file>]\n";
         return 1;
      }

      boost::system::error_code ec;

      std::string addr = argv[1];
      std::string port = argv[2];
      std::size_t num_threads = std::stoi(argv[3]);
      std::string docroot = argv[4];
      if (docroot[docroot.size()-1] == '/')
         docroot = docroot.substr(0,docroot.size()-1);

      http2 server;
      Interface::Router router(server, docroot);

      server.num_threads(num_threads);

      if (argc >= 7)
      {
         boost::asio::ssl::context tls(boost::asio::ssl::context::sslv23);
         tls.use_private_key_file(argv[5], boost::asio::ssl::context::pem);
         tls.use_certificate_chain_file(argv[6]);

         configure_tls_context_easy(ec, tls);

         if (server.listen_and_serve(ec, tls, addr, port))
            std::cerr << "error: " << ec.message() << std::endl;
      }
      else
      {
         if (server.listen_and_serve(ec, addr, port))
            std::cerr << "error: " << ec.message() << std::endl;
      }
   }
   catch (std::exception &e)
   {
      std::cerr << "exception: " << e.what() << "\n";
   }

   return 0;
}
