#include "Interface/Resource/Factory/Factory.h"
#include "Interface/Resource/Factory/NoRouteResourceFactory.h"
#include "Interface/Resource/Factory/FileServerResourceFactory.h"

using namespace Interface::Resource::Factory;
using namespace std;

unique_ptr<AbstractFactory> Factory::createResourceFactory(const string& index)
{
   unique_ptr<AbstractFactory> factory;
   if ( index == "FileServerResource" )
   {
      factory = unique_ptr<AbstractFactory>(new FileServerResourceFactory());
   }
   else
   {
      factory = unique_ptr<AbstractFactory>(new NoRouteResourceFactory());
   }

   return factory;
}
