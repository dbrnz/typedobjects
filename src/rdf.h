#ifndef _RDF_RDF_H
#define _RDF_RDF_H

//**************************************************************************//

#include <sord/sordmm.hpp>

#include <string>

//**************************************************************************//

namespace rdf {

  class Prefixes : protected Sord::Namespaces
  /*---------------------------------------*/
  {
   public:
    using Sord::Namespaces::add ;

    friend class Graph ;
    } ;

  class Node : protected Sord::Node
  /*-----------------------------*/
  {
   public:
    using Sord::Node::to_string ;
    using Sord::Node::to_u_string ;

    using Sord::Node::operator == ;
    inline bool operator !=(const Node &other) const {
      return !(*this == other) ;
      }
    friend class Statement ;

   protected:
    Node() ;
    Node(Type t, const std::string &s) ;
    Node(SordNode *node, bool copy) ;

    static SordNode *sord_node_from_serd_node(
      const SerdNode* node, const SerdNode *type, const SerdNode *lang) ;
    } ;


  class URI : public Node
  /*-------------------*/
  {
   public:
    URI() ;
    URI(const std::string& s) ;
    static const URI EMPTY ;

    friend class Literal ;
    } ;


  class BNode : public Node
  /*---------------------*/
  {
   public:
    BNode(void) ;
    BNode(const std::string& s) ;
    } ;


  class Literal : public Node
  /*-----------------------*/
  {
   public:
    Literal(const std::string& s) ;
    Literal(const std::string& s, const rdf::URI &datatype) ;
    Literal(const std::string& s, const std::string &language) ;
    Literal(double d, unsigned frac_digits) ;
    Literal(int64_t i) ;

   private:
    static SordNode *sord_datatype_node(const std::string& s, const rdf::URI &datatype) ;
    static SordNode *sord_language_node(const std::string& s, const std::string &language) ;
    static SordNode *sord_decimal_node(double d, unsigned frac_digits) ;
    static SordNode *sord_integer_node(int64_t i) ;
    } ;


  class Statement
  /*-----------*/
  {
   public:
    Statement(const URI   &s, const URI &p, const Node &o) ;
    Statement(const BNode &s, const URI &p, const Node &o) ;

    friend class Graph ;

   private:
    Statement(const Node &s, const Node &p, const Node &o) ;
    SordQuad quad ;
    } ;


  class Graph
  /*-------*/
  {
   public:
    Graph(const URI &p_uri) ;
    virtual ~Graph() ;

    enum class Format {
      UNKNOWN = 0,
      RDFXML,
      TURTLE,
      NTRIPLES
      } ;

    void parseResource(const std::string &resource,
                       const Format format=Format::RDFXML,
                       const std::string &base="") ;
    void parseString(const std::string &source,
                     const Format format=Format::RDFXML,
                     const std::string &base="") ;

    std::string serialise(const Format format=Format::RDFXML,
                          const std::string &base="",
                          const rdf::Prefixes &prefixes=Prefixes()) ;

    const URI &getUri(void) const ;

    const bool contains(const Statement &p_statement) const ;
    const bool contains(const URI   &s, const URI &p, const Node &o) const ;
    const bool contains(const BNode &s, const URI &p, const Node &o) const ;

   private:
    const URI &m_uri ;
    SordModel *m_model ;
    } ;


  } ;

//**************************************************************************//

#endif
