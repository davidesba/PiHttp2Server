#include "Interface/Resource/FileServerResource.h"
#include "CTML/CTML.h"
#include "dirent.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace Interface::Resource;
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
namespace filesys = boost::filesystem;

FileServerResource::FileServerResource(std::string & docRoot)
   :AbstractResource(docRoot)
{}

FileServerResource::~FileServerResource() {}

void FileServerResource::handle_get(const request & req, const response & res)
{
   auto path = percent_decode(req.uri().path);
   auto fullPath = docRootM + path;

   if (!pathExist(fullPath))
   {
      res.write_head(404);
      res.end();
      return;
   }

   if (isDirectory(fullPath))
   {
      CTML::Document doc;
      doc.AddNodeToHead(CTML::Node("style","\
            table {\
               font-family: \"Trebuchet MS\", Arial, Helvetica, sans-serif;\
               border-collapse: collapse;\
            }\
            th, td {\
               text-align: left;\
               padding: 8px;\
               padding-top: 12px;\
               padding-bottom: 12px;\
            }\
            tr:nth-child(even){background-color: #f2f2f2}\
            th {\
               background-color: #4CAF50;\
               color: white;\
            }"));

      doc.AddNodeToBody(CTML::Node("h2", std::string("Index of ") + fullPath));
      CTML::Node table("table");
      CTML::Node tableIndex("tr");
      tableIndex.AppendChild(CTML::Node("th").SetContent("Name"));
      tableIndex.AppendChild(CTML::Node("th").SetContent("Size"));
      table.AppendChild(tableIndex);

      for (auto & iter : boost::filesystem::directory_iterator(fullPath))
      {
         std::string link;
         
         if (path != "/")
            link = path + std::string("/") + iter.path().filename().string();
         else
            link = path + iter.path().filename().string();

         CTML::Node tr("tr");
         CTML::Node fileName("td");

         fileName.AppendChild(
            CTML::Node("a.link").SetContent(iter.path().filename().string()).SetAttribute(
               "href", link));
         tr.AppendChild(fileName);
         
         std::string fSize = "-";
         if (filesys::is_regular_file(fullPath + iter.path().filename().string()))
         {
            fSize = convertSize(filesys::file_size(fullPath + iter.path().filename().string()));
         }

         tr.AppendChild(CTML::Node("td").SetContent(fSize));

         table.AppendChild(tr);
      }
      doc.AddNodeToBody(table);

      auto header = header_map();
      auto textDoc = doc.ToString(CTML::Readability::MULTILINE);
      header.emplace("content-length",
                           header_value{std::to_string(textDoc.size())});
      res.write_head(200, std::move(header));
      res.end(textDoc);
   }
   else
   {
      auto fd = open(fullPath.c_str(), O_RDONLY);
      if (fd == -1)
      {
         res.write_head(404);
         res.end();
         return;
      }

      auto header = header_map();

      struct stat stbuf;
      if (stat(fullPath.c_str(), &stbuf) == 0)
      {
         header.emplace("content-length",
                           header_value{std::to_string(stbuf.st_size)});
         header.emplace("last-modified",
                           header_value{http_date(stbuf.st_mtime)});
      }
      res.write_head(200, std::move(header));
      res.end(file_generator_from_fd(fd));
   }
}

void FileServerResource::handle_put(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}

void FileServerResource::handle_post(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}

void FileServerResource::handle_delete(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}

bool FileServerResource::isDirectory(const std::string& filePath)
{
   try
   {
      filesys::path pathObj(filePath);
      if (filesys::exists(pathObj) && filesys::is_directory(pathObj))
         return true;
   }
   catch (filesys::filesystem_error & e) {}
   return false;
}

bool FileServerResource::pathExist(const std::string& filePath)
{
   try
   {
      filesys::path pathObj(filePath);
      if (filesys::exists(pathObj))
         return true;
   }
   catch (filesys::filesystem_error & e) {}
   return false;
}

std::string FileServerResource::convertSize(uintmax_t size)
{              
   const char *SIZES[] = { "B", "KB", "MB", "GB" };
   int div = 0;
   uintmax_t rem = 0;

   while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES))
   {
      rem = (size % 1024);
      div++;
      size /= 1024;
   }

   double size_d = (float)size + (float)rem / 1024.0;
   std::string result = std::to_string(size_d);

   result = result.substr(0, div>0 ? result.size()-4 : result.size()-7) 
               + std::string(" ") + SIZES[div];
               
   return result;
}