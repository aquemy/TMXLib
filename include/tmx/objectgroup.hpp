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

#ifndef OBJECTGROUP_HPP
#define OBJECTGROUP_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <tmx/object.hpp>
#include <tmx/abstractLayer.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief Objectgroups contain objects that share properties
///
///////////////////////////////////////////////////////////////////////////
class Objectgroup : public AbstractLayer, public std::vector<Object>
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Create an empty Objectgroup object
    ///
    ///////////////////////////////////////////////////////////////////////////
    Objectgroup() = default;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create a Objectgroup object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Objectgroup(const boost::property_tree::ptree &pt);
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the name
    ///
    /// \return Name
    ///
    /////////////////////////////////////////////////////////////////////////// 
    std::string getName() const;      
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the color
    ///
    /// \return Color
    ///
    /////////////////////////////////////////////////////////////////////////// 
    std::string getColor() const;     
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the width
    ///
    /// \return Width
    ///
    /////////////////////////////////////////////////////////////////////////// 
    int getWidth() const;             
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the height
    ///
    /// \return Height
    ///
    /////////////////////////////////////////////////////////////////////////// 
    int getHeight() const;            
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the opacity
    ///
    /// \return Opacity
    ///
    /////////////////////////////////////////////////////////////////////////// 
    float getOpacity() const;  
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the properties
    ///
    /// \return Properties
    ///
    ///////////////////////////////////////////////////////////////////////////            
    Properties getProperties() const;
        
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Print on the standard output the object
    ///
    ///////////////////////////////////////////////////////////////////////////
    void dump() const;
    
private:

    ///////////////////////////////////////////////////////////////////////////
    // Member data
    ///////////////////////////////////////////////////////////////////////////
    std::string name;      ///< Name of the objectgroup
    std::string color;     ///< Color of the objectgroup
    int width = 0;         ///< Witdh of the objectgroup
    int height = 0;        ///< Height of the objectgroup
    float opacity = 0;     ///< Opacity of the objectgroup
    Properties properties; ///< Properties of the objectgroup
    
};

using Objectgroups = std::vector<const Objectgroup*>;

} // namespace tmx

#endif
