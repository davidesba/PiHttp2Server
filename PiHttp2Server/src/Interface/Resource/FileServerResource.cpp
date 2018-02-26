#include "Interface/Resource/FileServerResource.h"
#include "CTML/CTML.h"
#include "dirent.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <memory>

using namespace Interface::Resource;
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
namespace filesys = boost::filesystem;
using namespace std;
using namespace CTML;

FileServerResource::FileServerResource(string & docRoot, Exchange::Exchange & exchange)
   :AbstractResource(docRoot, exchange)
{}

FileServerResource::~FileServerResource() {}

void FileServerResource::handle_get(const request & req, const response & res)
{
   auto path = percent_decode(req.uri().path);
   path = path.substr(path.find("FileServer")+11);
   auto fullPath = docRootM + "/" + path;

   if (!pathExist(fullPath))
   {
      res.write_head(404);
      res.end();
      return;
   }

   //List directory content
   if (isDirectory(fullPath))
   {
      //Create main document including CSS style
      Document doc;
      doc.AddNodeToHead(Node("style","\
            body {\
               margin: 0;\
               font-family: Arial, Helvetica, sans-serif;\
            }\
            table {\
               font-family: \"Trebuchet MS\", Arial, Helvetica, sans-serif;\
               border-collapse: collapse;\
               width: 60%;\
            }\
            form {\
               text-align: center;\
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

      Node mainDiv("div");
      mainDiv.AppendChild(
            Node("h2", string("Index of ") + fullPath).SetAttribute("align", "center"));

      //POST form to upload files
      Node uploadForm("form");
      uploadForm.SetAttribute("id", "uploadbanner");
      uploadForm.SetAttribute("enctype", "multipart/form-data");
      uploadForm.SetAttribute("method", "post");
      uploadForm.SetAttribute("action", "#");
      Node inputForm("input");
      inputForm.SetAttribute("id", "uploadbanner");
      inputForm.SetAttribute("name", "myfile");
      inputForm.SetAttribute("type", "file");
      Node submitForm("input");
      submitForm.SetAttribute("type", "submit");
      submitForm.SetAttribute("value", "Upload");
      submitForm.SetAttribute("id", "submit");

      uploadForm.AppendChild(inputForm);
      uploadForm.AppendChild(submitForm);
      mainDiv.AppendChild(uploadForm);

      //Table with name and size for the contents of the directory
      Node table("table");
      table.SetAttribute("align", "center");
      Node tableIndex("tr");
      tableIndex.AppendChild(Node("th").SetContent("Name"));
      tableIndex.AppendChild(Node("th").SetContent("Size"));
      table.AppendChild(tableIndex);

      for (auto & iter : boost::filesystem::directory_iterator(fullPath))
      {
         string link;

         if (path != "")
            link = string("/FileServer/") + path + string("/") + iter.path().filename().string();
         else
            link = string("/FileServer/") + iter.path().filename().string();

         Node tr("tr");
         Node fileName("td");

         fileName.AppendChild(
            Node("a.link").SetContent(iter.path().filename().string()).SetAttribute(
               "href", link));
         tr.AppendChild(fileName);
         
         string fSize = "-";
         if (filesys::is_regular_file(fullPath + iter.path().filename().string()))
         {
            fSize = convertSize(filesys::file_size(fullPath + iter.path().filename().string()));
         }

         tr.AppendChild(Node("td").SetContent(fSize));

         table.AppendChild(tr);
      }
      mainDiv.AppendChild(table);
      doc.AddNodeToBody(mainDiv);

      auto header = header_map();
      auto textDoc = doc.ToString(Readability::MULTILINE);
      header.emplace("content-length",
                           header_value{to_string(textDoc.size())});
      res.write_head(200, move(header));
      res.end(textDoc);
   }
   //Read file and return data
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
                           header_value{to_string(stbuf.st_size)});
         header.emplace("last-modified",
                           header_value{http_date(stbuf.st_mtime)});
      }
      res.write_head(200, move(header));
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
   auto path = percent_decode(req.uri().path);
   auto fullPath = docRootM + path;
   shared_ptr<string> fileName(new string());
   shared_ptr<string> messageId(new string());
   shared_ptr<ofstream> outputFile(new ofstream());

   //This funtion is called every time we receive a chunk of data
   req.on_data([&res, fullPath, fileName, messageId, outputFile](const uint8_t *data, size_t len)
   {
      string receivedData = string((const char*)data, len);

      if (len > 0)
      {
         //Find filename and messageId in the first chunk of data
         if (fileName->size() == 0)
         {
            size_t headerPos = receivedData.find("\r\n\r\n");
            string header = receivedData.substr(0,headerPos);
            *(messageId.get()) = header.substr(0, header.find("\n")-2);
            size_t pos = header.find("filename=");
            if (pos != string::npos)
            {
               *(fileName.get()) = header.substr(pos+10,header.find("\"",pos+10) - pos - 10);
            }

            receivedData = receivedData.substr(headerPos+4);
            outputFile->open(fullPath + *(fileName.get()));
         }

         //Check if we have the last chunk
         size_t last = receivedData.find(string("\r\n") + *(messageId.get()));
         if (last != string::npos)
         {
            receivedData = receivedData.substr(0, last);
         }
         *(outputFile.get()) << receivedData;
      }
      else
      {
         outputFile->close();
         res.write_head(200);
         res.end();
      }
   });
}

void FileServerResource::handle_delete(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}

bool FileServerResource::isDirectory(const string& filePath)
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

bool FileServerResource::pathExist(const string& filePath)
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

string FileServerResource::convertSize(uintmax_t size)
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
   string result = to_string(size_d);

   result = result.substr(0, div>0 ? result.size()-4 : result.size()-7) 
               + string(" ") + SIZES[div];
               
   return result;
}