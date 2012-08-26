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

#ifndef IMAGE_HPP
#define IMAGE_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <boost/property_tree/ptree.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief Image description for tilesets
///
///////////////////////////////////////////////////////////////////////////
class Image
{
public :

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Create an empty Image object
    ///
    ///////////////////////////////////////////////////////////////////////////
    Image() = default;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create an Image object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Image(const boost::property_tree::ptree &pt);
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Print on the standard output the object
    ///
    ///////////////////////////////////////////////////////////////////////////
    void dump();
    
private :

    ///////////////////////////////////////////////////////////////////////////
    // Member data
    /////////////////////////////////////////////////////////////////////////// 
    std::string source; ///< Path to the image
    int trans;          ///< Opacity of the image
    int width;          ///< Width of the image
    int height;         ///< Height of the image
    
};

} // namespace tmx

#endif
