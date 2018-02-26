#include "Interface/Resource/IndexResource.h"
#include "CTML/CTML.h"

using namespace Interface::Resource;
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
using namespace std;
using namespace CTML;

IndexResource::IndexResource(string & docRoot, Exchange::Exchange & exchange)
   :AbstractResource(docRoot, exchange)
{}

IndexResource::~IndexResource() {}

void IndexResource::handle_get(const request & req, const response & res)
{
   //Create main document including CSS style
   Document doc;
   doc.AddNodeToHead(Node("style","\
      body {\
         margin: 0;\
         font-family: Arial, Helvetica, sans-serif;\
      }\
      .topnav {\
         overflow: hidden;\
         background-color: #333;\
      }\
      .topnav a {\
         float: left;\
         color: #f2f2f2;\
         text-align: center;\
         padding: 14px 16px;\
         text-decoration: none;\
         font-size: 17px;\
      }\
      .topnav a:hover {\
         background-color: #ddd;\
         color: black;\
      }\
      .topnav a.active {\
         background-color: #4CAF50;\
         color: white;\
      }"));
   
   doc.AddNodeToHead(Node("meta")
      .SetAttribute("name", "viewport")
      .SetAttribute("content", "width=device-width, initial-scale=1")
   );

   doc.AddNodeToBody(
      Node("div").SetAttribute("class", "topnav")
         .AppendChild(Node("a", "Home")
            .SetAttribute("class", "active")
            .SetAttribute("href", "/"))
         .AppendChild(Node("a", "FileServer")
            .SetAttribute("href", "/FileServer"))
         .AppendChild(Node("a", "Statistics")
            .SetAttribute("href", "/Statistics"))
   );

   doc.AddNodeToBody(
      Node("div").SetAttribute("style", "padding-left:16px")
         .AppendChild(
            Node("h2", "Wecome to PiHttp2Server").SetAttribute("align", "left"))
   );

   auto header = header_map();
   auto textDoc = doc.ToString(Readability::MULTILINE);
   header.emplace("content-length",
                        header_value{to_string(textDoc.size())});
   res.write_head(200, move(header));
   res.end(textDoc);
}