/**
 * @file feature_object_matches_sorted_objects.cc
 *
 * @brief
 *
 * Class used to describe feature_object_matches_sorted_objects 
 */
#include <assert.h>
#include <sstream>
#include <algorithm>

#include "h2sl/world.h"
#include "h2sl/spatial_relation.h"
#include "h2sl/feature_object_matches_sorted_objects.h"
#include "h2sl/object.h"

using namespace std;
using namespace h2sl;

/**
 * Feature_Object_Matches_Sorted_Objects class constructor
 */
Feature_Object_Matches_Sorted_Objects::
Feature_Object_Matches_Sorted_Objects( const bool& invert ) : Feature( invert ) {
  insert_prop< std::string >( _string_properties, "sorting_key", "na" );
}

/**
 * Feature_Object_Matches_Sorted_Objects class copy constructor
 */
Feature_Object_Matches_Sorted_Objects::
Feature_Object_Matches_Sorted_Objects( const Feature_Object_Matches_Sorted_Objects& other ) : Feature( other ) {

}

/**
 * Feature_Object_Matches_Sorted_Objects class destructor
 */
Feature_Object_Matches_Sorted_Objects::
~Feature_Object_Matches_Sorted_Objects() {

}

/** 
 * Feature_Object_Matches_Sorted_Objects class assignment operator
 */
Feature_Object_Matches_Sorted_Objects&
Feature_Object_Matches_Sorted_Objects::
operator=( const Feature_Object_Matches_Sorted_Objects& other ){
  _invert = other._invert;
  return (*this);
}

/**
 * returns the value of the feature
 */
bool
Feature_Object_Matches_Sorted_Objects::
value( const unsigned int& cv,
      const Grounding* grounding,
      const vector< pair< const Phrase*, vector< Grounding* > > >& children,
      const Phrase* phrase,
      const World* world ){
    return value( cv, grounding, children, phrase, world, NULL );
}


/**
 * returns the value of the feature
 */
bool
Feature_Object_Matches_Sorted_Objects::
value( const unsigned int& cv,
        const Grounding* grounding,
        const vector< pair< const Phrase*, vector< Grounding* > > >& children,
        const Phrase* phrase,
        const World* world,
        const Grounding* context ){
  const Object* object_grounding = dynamic_cast< const Object* >( grounding );
  if( object_grounding != NULL ){
    map< string, map< string, vector< Object* > > >::const_iterator it_sorted_objects_map = world->sorted_objects().find( sorting_key() );
    assert( it_sorted_objects_map != world->sorted_objects().end() ); 
    map< string, vector< Object* > >::const_iterator it_sorted_objects = it_sorted_objects_map->second.find( object_grounding->type() );
//    map< string, vector< Object* > >::const_iterator it = world->min_x_sorted_objects().find( object_grounding->type() );
    assert( it_sorted_objects != it_sorted_objects_map->second.end() );
    if ( *object_grounding == *( it_sorted_objects->second.front() ) ){
      return !_invert;
    } else {
      return _invert;
    }
  }
  return false;
}

/** 
 * imports the Feature_Object_Matches_Sorted_Objects class from an XML file
 */
void
Feature_Object_Matches_Sorted_Objects::
from_xml( const string& filename ){
  xmlDoc * doc = NULL;
  xmlNodePtr root = NULL;
  doc = xmlReadFile( filename.c_str(), NULL, 0 );
  if( doc != NULL ){
    root = xmlDocGetRootElement( doc );
    if( root->type == XML_ELEMENT_NODE ){
      xmlNodePtr l1 = NULL;
      for( l1 = root->children; l1; l1 = l1->next ){
        if( l1->type == XML_ELEMENT_NODE ){
          if( xmlStrcmp( l1->name, ( const xmlChar* )( "feature_object_matches_sorted_objects" ) ) == 0 ){
            from_xml( l1 );
          }
        }
      }
      xmlFreeDoc( doc );
    }
  }
  return;
}


/** 
 * imports the Feature_Object_Matches_Sorted_Objects class from an XML node pointer
 */
void
Feature_Object_Matches_Sorted_Objects::
from_xml( xmlNodePtr root ){
  _invert = false;
  sorting_key() = "na";
  if( root->type == XML_ELEMENT_NODE ){
    pair< bool, bool > invert_prop = has_prop< bool >( root, "invert" );
    if( invert_prop.first ){
      invert() = invert_prop.second;
    }
    pair< bool, string > sorting_key_prop = has_prop< std::string >( root, "sorting_key" );
    if( sorting_key_prop.first ){
      sorting_key() = sorting_key_prop.second;
    }
  }
}

/**
 * exports the Feature_Object_Matches_Sorted_Objects class to an XML file
 */
void
Feature_Object_Matches_Sorted_Objects::
to_xml( const string& filename )const{
  xmlDocPtr doc = xmlNewDoc( ( xmlChar* )( "1.0" ) );
  xmlNodePtr root = xmlNewDocNode( doc, NULL, ( xmlChar* )( "root" ), NULL );
  xmlDocSetRootElement( doc, root );
  to_xml( doc, root );
  xmlSaveFormatFileEnc( filename.c_str(), doc, "UTF-8", 1 );
  xmlFreeDoc( doc );
  return;
}

/**
 * exports the Feature_Object_Matches_Sorted_Objects class to an XML node pointer
 */
void
Feature_Object_Matches_Sorted_Objects::
to_xml( xmlDocPtr doc,
        xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( xmlChar* )( "feature_object_matches_sorted_objects" ), NULL );
  xmlNewProp( node, ( const xmlChar* )( "invert" ), ( const xmlChar* )( to_std_string( _invert ).c_str() ) );
  xmlNewProp( node, ( const xmlChar* )( "sorting_key" ), ( const xmlChar* )( get_prop< std::string >( _string_properties, "sorting_key" ).c_str() ) );
  xmlAddChild( root, node );
  return;
}

namespace h2sl {
  /** 
   * Feature_Object_Matches_Sorted_Objects class ostream operator
   */
  ostream&
  operator<<( ostream& out,
              const Feature_Object_Matches_Sorted_Objects& other ){
    out << "class:\"Feature_Object_Matches_Sorted_Objects\" ";
    return out;
  }
}


