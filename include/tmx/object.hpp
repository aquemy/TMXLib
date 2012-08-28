///////////////////////////////////////////////////////////////////////////
//
// TMX Library - Simple C++11 library to parse TMX files
// Copyright (C) 2012 Alexandre Quemy (alexandre.quemy@gmail.com)
//
// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  ue,
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or
// data to be ensured and,  more generally, to use and operate it in the
// same conditions as regards security.
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
//
///////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_HPP
#define OBJECT_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <tmx/image.hpp>
#include <tmx/polygon.hpp>
#include <tmx/polyline.hpp>
#include <tmx/properties.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief Objects container
///
///////////////////////////////////////////////////////////////////////////
class Object
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Create an empty Object object
    ///
    ///////////////////////////////////////////////////////////////////////////
    Object() = default;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create a Object object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Object(const boost::property_tree::ptree &pt);
    
    std::string getName();     
    std::string getType();     
    int getX();                
    int getY();                
    int getWidth();             
    int getHeight();            
    int getId();                
    Image getImage();           
    Polygon getPolygon();       
    Polyline getPolyline();     
    Properties getProperties();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Print on the standard output the object
    ///
    ///////////////////////////////////////////////////////////////////////////
    void dump();

private:

    ///////////////////////////////////////////////////////////////////////////
    // Member data
    ///////////////////////////////////////////////////////////////////////////
    std::string name;      ///< Name of the object
    std::string type;      ///< Type of the object
    int x;                 ///< Abscissa of the object
    int y;                 ///< Ordinata of the object
    int width;             ///< Width of the object
    int height;            ///< Height of the object
    int id;                ///< ID of the object
    Image image;           ///< Image of the object
    Polygon polygon;       ///< Polygon
    Polyline polyline;     ///< Polyline
    Properties properties; ///< Properties of the object
    
};
    
using Objects = std::vector<Object>;

} // namespace tmx

#endif
