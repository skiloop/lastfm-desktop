#ifndef __QUERY_PARSER_PARSER_H
#define __QUERY_PARSER_PARSER_H

#include "node.h"
#include "enums.h"

#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/error_handling.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>
#include <map>

#include <map>
#include <boost/functional/hash.hpp>

/**
 * \namespace fm::last::query_parser
 * \brief Query parser for the \c radioql language
 */
namespace fm { namespace last { namespace query_parser {

struct query_grammar;

/// Parser that parses \c radioql queries
/**
 * The parser is implemented using the tools provided in boost::spirit. If
 * you feel like you don't understand a single word from the comments in
 * the parser classes, read the documentation of boost::spirit first.
 *
 * The parser uses Spirit to turn the string to be parsed into an abstract
 * syntax tree representation using parser::parse(). The abstract syntax tree
 * representation cannot be queried directly; the data structure used by the
 * radio services is a vector of operation (typically TAggregatorEntry)
 * instances which represent the prefix traversal of the syntax tree. Since one
 * can unambiguously decide whether a given TAggregatorEntry is a leaf node
 * (its \c type field is one of the values defined in the TRadioService enums)
 * or not, the vector representation is completely equivalent to the AST.
 *
 * Roughly speaking, the source code of the parser can be divided into the
 * following subunits:
 *
 * - symbols.h: the symbol tables we use for the operators and the source names
 * - enums.h:  the enums we use for representing the operators and the radio
 *   sources as integers
 * - node.h:  the data structures we have for a single tree node in the abstract
 *   syntax tree
 * - grammar.h:  rules of the parser grammar in Spirit's syntax
 * - parser.h:  the parser interface itself
 *
 * The grammar accepted by the \c radioql parser in an EBNF-like (but maybe
 * not fully accurate) syntax is as follows:
 * \verbatim
expression   ::= term , { expressionop , term } ;
expressionop ::= "OR" ;
term         ::= factor , { termop , factor } ;
termop       ::= "AND" | "AND_NOT" ;
factor       ::= "(" , expression, ")" | token ;
token        ::= [ servicetype, ":" ] , ( identifier | string | number ) , [ "^" , weight ] ;
servicetype  ::= ? see symbols.h for a list of accepted service types ?
identifier   ::= identchar , { identchar }
identchar    ::= ? all printable non-whitespace characters ? - operator
operator     ::= "(" | ")" | "[" | "]" | ":" | "^"
string       ::= '"' , nonquote , { nonquote } , '"'
number       ::= "[" , int_p , "]"
weight       ::= ureal_p
nonquote     ::= ? all characters ? - "'"
\endverbatim
 *
 * where \c int_p is Spirit's built-in integer parser and \c ureal_p is Spirit's
 * built-in unsigned real number parser. \c expressionop, \c termop and
 * \c servicetype are case insensitive and are implemented by symbol tables.
 *
 * \sa http://spirit.sourceforge.net/documentation.html for the Spirit docs
 * \note The query parser is \em NOT thread safe!
 */
class parser
{
public:

   /// Shorthand notation for a Google dense hash map mapping from string to int with Boost's string hash function
   /**
    * These hash maps are used extensively when mapping user/tag/artist names
    * to their IDs, hence the typedef.
    */
  typedef std::map< std::string, int> hashMap_t;

public:

   /// Constructs the parser
   parser();

   /// Parses the given \c radioql query
   /** \param  str  the query to be parsed
    * \return  whether the query was fully parsed (\c true) or we had to stop
    *          prematurely due to an error (\c false)
    */
   bool        parse(const std::string& str);

   /// Returns the line number of the last error (if any)
   /** \return 0 if there was no error, otherwise it returns the line number
    *          where the error occurred
    */
   int         getErrorLineNumber();

   /// Returns the line itself where the last error occurred (if any)
   /** \return an empty string if there was no error, otherwise it returns the
    *          line where the parsers stopped.
    */
   std::string getErrorLine();

   /// Returns the character offset of the last error from the start of the string
   /** \return 0 if there was no error, otherwise it returns the character offset
    *          of the last error
    */
   int         getErrorOffset();

   /// Returns a vector representation of the currently parsed query
   /**
    * This function practically just calls parser::eval_expression with the
    * root of the tree.
    *
    * \tparam      T            the operator type we use in the vector representation
    * \param[out]  ops          the vector representation is returned here. The
    *                           vector will \em not be cleared
    * \param[in]   rootToOpFun  Boost function that tells us how to turn a root
    *                           node to an operator for the vector representation
    * \param[in]   leafToOpFun  Boost function that tells us how to turn a leaf
    *                           node to an operator for the vector representation
    */
   template <typename T>
   void getOperations(
      std::vector<T>& ops,
      const boost::function< T( const querynode_data& node )>& rootToOpFun,
      const boost::function< T( const querynode_data& node )>& leafToOpFun );

   /// Returns the name of an operator, given the operator type
   /**
    * \param   opType  the type of the operator (an enum value from TAggregatorOpType)
    * \return  the operator name as a string
    */
   std::string getOpName(int opType);

   /// Returns the name of a service, given the service type
   /**
    * \param   serviceType  the type of the service (an enum value from TRadioService)
    * \return  the service name as a string
    */
   std::string getServiceName(int serviceType);

private:

   /// Shorthand notation for the resulting abstract syntax tree
   typedef boost::spirit::tree_match<iterator_t, factory_t>     parse_tree_match_t;
   /// Shorthand notation for an iterator over the resulting abstract syntax tree
   typedef parse_tree_match_t::tree_iterator                    tree_iter_t;

   /// Returns a vector representation of some part of the currently parsed query
   /**
    * \tparam      T            the operator type we use in the vector representation
    * \param[out]  ops          the vector representation is returned here
    * \param[in]   rootToOpFun  Boost function that tells us how to turn a root
    *                           node to an operator for the vector representation
    * \param[in]   leafToOpFun  Boost function that tells us how to turn a leaf
    *                           node to an operator for the vector representation
    * \param       it           iterator pointing to the node of the tree that is
    *                           the root of the expression we are processing
    */
   template <typename T>
   void eval_expression( std::vector<T>& ops,
                         const boost::function< T( const querynode_data& node )>& rootToOpFun,
                         const boost::function< T( const querynode_data& node )>& leafToOpFun,
                         tree_iter_t const& it );

   /// Copies the next token from a <tt>char*</tt> line into a <tt>char*</tt> buffer
   /**
    * \param[out]    pBuf      the next token is returned here
    * \param[in]     pLine     the line being parsed
    * \param[in]     lineSize  length of the line we have (used as a max value for \a lineIt)
    * \param[in,out] lineIt    the current position in the line (will be updated)
    */
   static void getToken(char* pBuf, const char* pLine, const int lineSize, int& lineIt);

   /// Returns the ID corresponding to the given key from the given map
   /**
    * \param  pItemMapper  the name-to-ID mapping
    * \param  key          the key we are looking for
    * \param  forceLowerCase will convert the key to lowercase before checking
    * \return  the ID or -1 if the key was not found
    */
   int  getID( boost::shared_ptr<const hashMap_t>& pItemMapper, const std::string& key, bool forceLowerCase = true );

private:

   /// Iterator of the string we are parsing (or that we parsed the last time)
   iterator_t  m_pStringToParse;
   /// Last error message coming from the parser itself
   std::string errorMsg;

   /// Shared pointer to the \c radioql grammar we are using
   boost::shared_ptr<query_grammar> m_pGrammar;
   /// A boost::spirit::tree_parse_info holding the information related to the last parse attempt
   boost::spirit::tree_parse_info<iterator_t, factory_t> m_pi;
};

// -----------------------------------------------------------------------------

template <typename T>
void parser::getOperations(
   std::vector<T>& ops,
   const boost::function< T( const querynode_data& node )>& rootToOpFun,
   const boost::function< T( const querynode_data& node )>& leafToOpFun )
{
   ops.clear();
   eval_expression(ops, rootToOpFun, leafToOpFun, m_pi.trees.begin());
}

// -----------------------------------------------------------------------------


template <typename T>
void parser::eval_expression(
   std::vector<T>& ops,
   const boost::function< T( const querynode_data& node )>& rootToOpFun,
   const boost::function< T( const querynode_data& node )>& leafToOpFun,
   tree_iter_t const& it )
{
   T op;
   querynode_data currNode = it->value.value(); // make a copy

   if ( it->value.id() == querynode_data::operationID )
   {
      op = rootToOpFun(currNode);
      //if ( currNode.name.empty() )
      //   currNode.name = getOpName(currNode.type);

      ops.push_back(op);
      if ( it->children.size() != 2 )
         throw std::runtime_error("radioql_parser: Invalid number of children for operator!");

      eval_expression(ops, rootToOpFun, leafToOpFun, it->children.begin());
      eval_expression(ops, rootToOpFun, leafToOpFun, it->children.begin()+1);
   }
   else if ( it->value.id() == querynode_data::tokenID )
   {
/*
      if ( currNode.ID < 0 )
      { // no ID specified: let's try to set it from the mappings
         switch ( currNode.type )
         {
         case RS_LIBRARY:
         case RS_LOVED:
         case RS_NEIGHBORS:
         case RS_RECOMMENDED:
            currNode.ID = getID(m_pUserMappings, currNode.name);
            break;

         case RS_GLOBAL_TAG:
            currNode.ID = getID(m_pTagMappings, currNode.name);
            break;

         case RS_SIMILAR_ARTISTS:
            currNode.ID = getID(m_pArtistMappings, currNode.name);
            break;
         }
      }
*/
      op = leafToOpFun(currNode);
      ops.push_back(op);
   }
   else
      throw std::runtime_error("radioql_parser: Invalid node ID!");
}


// -----------------------------------------------------------------------------

//void eval_expression( std::vector<TAggregatorEntry>& ops, tree_iter_t const& it );


}}} // namespaces

#endif // __QUERY_PARSER_PARSER_H

// -----------------------------------------------------------------------------
