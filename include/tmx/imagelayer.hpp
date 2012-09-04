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

#ifndef IMAGELAYER_HPP
#define IMAGELAYER_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <tmx/properties.hpp>
#include <tmx/image.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief A class that stores Imagelayer description
///
///////////////////////////////////////////////////////////////////////////
class Imagelayer
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create a Imagelayer object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Imagelayer(const boost::property_tree::ptree &pt);
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the name
    ///
    /// \return Name
    ///
    ///////////////////////////////////////////////////////////////////////////
    std::string getName();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the width
    ///
    /// \return Width
    ///
    ///////////////////////////////////////////////////////////////////////////
    int getWidth();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the height
    ///
    /// \return Height
    ///
    ///////////////////////////////////////////////////////////////////////////
    int getHeight();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the image
    ///
    /// \return Image
    ///
    ///////////////////////////////////////////////////////////////////////////
    Image getImage();  
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the properties
    ///
    /// \return Properties
    ///
    ///////////////////////////////////////////////////////////////////////////         
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
    std::string name;      ///< Name of the Imagelayer
    int width = 0;     ///< Width of a tile
    int height = 0;    ///< Height of a tile
    Image image;           ///< Image of the Imagelayer
    Properties properties; ///< Properties of the Imagelayer
    
};
    
using Imagelayers =  std::vector<Imagelayer>;

} // namespace tmx

#endif
