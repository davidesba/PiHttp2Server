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
   shared_ptr<string> queryData(new string());
   req.on_data([&res, this, queryData](const uint8_t *data, size_t len)
   {
      if (len > 0)
      {
         *(queryData.get()) += string((const char*)data, len);
      }
      else
      {
         string resData;
         if (!exchangeM.retrieve(typeM, queryData, resData))
         { 
            res.write_head(500);
            res.end();
         }
         else
         {
            res.write_head(200);
            res.end(resData);
         }
      }
   });
}
      
void MeasureResource::handle_post(const request &req, const response &res)
{
   shared_ptr<string> measureData(new string());
   req.on_data([&res, this, measureData](const uint8_t *data, size_t len)
   {
      if (len > 0)
      {
         *(measureData.get()) += string((const char*)data, len);
      }
      else
      {
         if (!exchangeM.create(typeM, measureData))
            res.write_head(500);
         else
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