#include "Interface/Resource/MeasureResource.h"

using namespace Interface::Resource;
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
using namespace std;

MeasureResource::MeasureResource(string & docRoot, Exchange::Exchange & exchange)
   :AbstractResource(docRoot, exchange),
    typeM("Measure")
{}

MeasureResource::~MeasureResource()
{}

void MeasureResource::handle_get(const request & req, const response & res)
{
   res.write_head(404);
   res.end();
}
      
void MeasureResource::handle_post(const request &req, const response &res)
{
   req.on_data([&res, this](const uint8_t *data, size_t len)
   {
      if (len > 0)
      {
         if (!exchangeM.create(typeM, data, len))
         {
            res.write_head(500);
            res.end();
         }
      }
      else
      {
         res.write_head(200);
         res.end();
      }
   });
}
      
void MeasureResource::handle_delete(const request &req, const response &res)
{
   res.write_head(404);
   res.end();
}