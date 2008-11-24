#include "parser.h"
#include "grammar.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include <boost/spirit/core.hpp>

// DEBUG!
//#include <boost/spirit/tree/tree_to_xml.hpp>

using namespace std;
using namespace boost::spirit;

namespace fm { namespace last { namespace query_parser {

parser::parser( )
{
   m_pGrammar.reset( new query_grammar() );
   m_pStringToParse = iterator_t();
}

// -----------------------------------------------------------------------------

bool parser::parse( const string& str )
{
   // make sure it's ready!
   errorMsg.clear();
   m_pStringToParse = str.c_str(); // will be used later

   try
   {
      m_pi = ast_parse<factory_t>(
         m_pStringToParse, m_pStringToParse + str.length(),
         *m_pGrammar, space_p);
   }
   catch (const parser_error<string, iterator_t> & e)
   {
      errorMsg = e.descriptor;
      m_pi.full = false;
      m_pi.stop = e.where;
   }

   return m_pi.full;
}

// -----------------------------------------------------------------------------

int parser::getErrorOffset()
{
   if ( m_pi.full || !m_pStringToParse )
      return 0;

   return static_cast<int>(m_pi.stop - m_pStringToParse);
}

// -----------------------------------------------------------------------------

int parser::getErrorLineNumber()
{
   if ( m_pi.full || !m_pStringToParse )
      return 0;

   char const* stringIt = m_pStringToParse;
   // count the line
   int line = 1;
   size_t i;
   for ( i = 0; stringIt != m_pi.stop && *stringIt != '\0'; ++stringIt, ++i)
   {
      if ( *stringIt == '\n' )
         ++line;
   }

   return line;
}

// -----------------------------------------------------------------------------

std::string parser::getErrorLine()
{
   if ( m_pi.full || !m_pStringToParse )
      return "";

   // find the beginning of the line
   char const* fullStrBegIt = m_pStringToParse;
   char const* errorBegIt = m_pi.stop;
   char const* errorEndIt = m_pi.stop;

   ostringstream oss;
   if ( !errorMsg.empty() )
      oss << "--> " << errorMsg << endl;

   for ( ; errorBegIt != fullStrBegIt && *errorBegIt != '\n'; --errorBegIt);
   if ( *errorBegIt == '\n' )
      ++errorBegIt;

   for ( ; *errorEndIt != '\n' && *errorEndIt != '\0'; ++errorEndIt );

   oss << string(errorBegIt, errorEndIt) << "\n" <<
          string(m_pi.stop - errorBegIt, ' ') << "^";

   return oss.str();
}

// -----------------------------------------------------------------------------

void parser::getToken(char* pBuf, const char* pLine, const int lineSize, int& lineIt)
{
   int bufPos = 0;

   for (; lineIt < lineSize; ++lineIt)
   {
      if ( pLine[lineIt] == '\t' || pLine[lineIt] == '\0' )
         break;
      pBuf[bufPos++] = pLine[lineIt];
   }
   ++lineIt;
   pBuf[bufPos] = '\0'; // terminate string
}

// -----------------------------------------------------------------------------

int parser::getID( boost::shared_ptr<const hashMap_t>& pItemMapper, 
                   const std::string& key, 
                   bool forceLowerCase )
{
   if ( !pItemMapper )
      return -1;

   string localKey = key;
   if ( forceLowerCase )
   {
      std::transform( localKey.begin(), localKey.end(),
                      localKey.begin(), (int(*)(int)) std::tolower);
   }


   hashMap_t::const_iterator mapIt;
   mapIt = pItemMapper->find(localKey);

   if ( mapIt != pItemMapper->end() )
      return mapIt->second;
   else
      return -1;
}

// -----------------------------------------------------------------------------

std::string parser::getOpName( int opType )
{
   switch ( opType )
   {
   case OT_AND:
      return "and";
   case OT_OR:
      return "or";
   case OT_AND_NOT:
      return "not";
   default:
      return "<unknown>";
   }
}

// -----------------------------------------------------------------------------

std::string parser::getServiceName( int serviceType )
{
   switch ( serviceType )
   {
      case RS_UNKNOWN:
         return "unknown";
         break;
      case RS_LIBRARY:
         return "library";
         break;
      case RS_LOVED:
         return "loved";
         break;
      case RS_NEIGHBORS:
         return "neighbors";
         break;
      case RS_PLAYLIST:
         return "playlist";
         break;
      case RS_RECOMMENDED:
         return "recommended";
         break;
      case RS_SIMILAR_ARTISTS:
         return "simArt";
         break;
      case RS_GLOBAL_TAG:
         return "globalTag";
         break;
      case RS_USER_TAG:
         return "userTag";
         break;
      case RS_GROUP:
         return "group";
         break;
      case RS_EVENT:
         return "event";
         break;
      case RS_ARTIST:
         return "art";
         break;
      default:
         return "<unknown>";
   }
}

}}} // end of namespaces
