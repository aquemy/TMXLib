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

#ifndef TILESET_HPP
#define TILESET_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <tmx/properties.hpp>
#include <tmx/image.hpp>
#include <tmx/tile.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief A class that stores tileset description
///
///////////////////////////////////////////////////////////////////////////
class Tileset : public std::vector<Tile>
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create a Tileset object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Tileset(const boost::property_tree::ptree &pt);
        
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Load a tileset from a tsx file
    ///
    /// Note that, at the moment, the tsx file does not support properties
    ///
    /// \param path Path to the tsx file your would like to load
    ///
    ///////////////////////////////////////////////////////////////////////////        
    void load(const std::string path);
    
    int getFirstGid();          
    std::string getSource();    
    std::string getName();      
    int getTilewidth();         
    int getTileheight();        
    int getSpacing();           
    int getMargin();            
    Image getImage();           
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
    int firstgid = 0;      ///< ID for the first tile of the tileset
    std::string source;    ///< Path to the tileset
    std::string name;      ///< Name of the tileset
    int tilewidth = 0;     ///< Width of a tile
    int tileheight = 0;    ///< Height of a tile
    int spacing = 0;       ///< Spacing of the tileset
    int margin = 0;        ///< Margin of the tileset
    Image image;           ///< Image of the tileset
    Properties properties; ///< Properties of the tileset
    
};
    
using Tilesets =  std::vector<Tileset>;

} // namespace tmx

#endif
