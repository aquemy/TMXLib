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

#ifndef MAP_HPP
#define MAP_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <tmx/orientation.hpp>
#include <tmx/properties.hpp>
#include <tmx/tileset.hpp>
#include <tmx/layer.hpp>
#include <tmx/objectgroup.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief Main class to manipulate maps from TMX
///
///////////////////////////////////////////////////////////////////////////
class Map : public std::vector<Layer>
{
public :

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Create an empty Map object
    ///
    ///////////////////////////////////////////////////////////////////////////
    Map() = default;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor by loading
    ///
    /// Load a map from a file
    ///
    /// \param path Path to the tmx file your would like to load
    ///
    ///////////////////////////////////////////////////////////////////////////
    Map(const std::string path);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Load a map from a file
    ///
    /// \param path Path to the tmx file your would like to load
    ///
    ///////////////////////////////////////////////////////////////////////////
    void load(std::string path);
    
    std::string getVersion();       
    Orientation getOrientation();  
    int getWidth();                 
    int getHeight();               
    int getTilewidth();           
    int getTileheight();            
    Tilesets getTilesets();                   
    Objectgroups getObjectgroups(); 
    Properties getProperties();    
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Print on the standard output the object
    ///
    ///////////////////////////////////////////////////////////////////////////
    void dump();
    
private :

    ///////////////////////////////////////////////////////////////////////////
    // Member data
    ///////////////////////////////////////////////////////////////////////////
    std::string version;                               ///< Version of TMX format
    Orientation orientation = Orientation::ORTHOGONAL; ///< Orientation of the map
    int width = 0;                                     ///< Width of the map
    int height = 0;                                    ///< Height of the map
    int tilewidth = 0;                                 ///< Width of a tile
    int tileheight = 0;                                ///< Height of a tile
    Tilesets tilesets;                                 ///< Tilesets of the map
    Objectgroups objectgroups;                         ///< Objectgroups of the map
    Properties properties;                             ///< Properties of the map
    
};

} // namespace tmx

#endif
