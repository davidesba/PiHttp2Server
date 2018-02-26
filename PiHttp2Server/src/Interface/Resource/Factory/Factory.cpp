#include "Interface/Resource/Factory/Factory.h"
#include "Interface/Resource/Factory/NoRouteResourceFactory.h"
#include "Interface/Resource/Factory/FileServerResourceFactory.h"
#include "Interface/Resource/Factory/MeasureResourceFactory.h"
#include "Interface/Resource/Factory/IndexResourceFactory.h"
#include "Interface/Resource/Factory/StatisticsResourceFactory.h"

using namespace Interface::Resource::Factory;
using namespace std;

unique_ptr<AbstractFactory> Factory::createResourceFactory(const string& index)
{
   unique_ptr<AbstractFactory> factory;
   if ( index == "FileServerResource" )
   {
      factory = unique_ptr<AbstractFactory>(new FileServerResourceFactory());
   }
   else if ( index == "MeasureResource" )
   {
      factory = unique_ptr<AbstractFactory>(new MeasureResourceFactory());
   }
   else if ( index == "IndexResource" )
   {
      factory = unique_ptr<AbstractFactory>(new IndexResourceFactory());
   }
   else if ( index == "StatisticsResource" )
   {
      factory = unique_ptr<AbstractFactory>(new StatisticsResourceFactory());
   }
   else
   {
      factory = unique_ptr<AbstractFactory>(new NoRouteResourceFactory());
   }

   return factory;
}
