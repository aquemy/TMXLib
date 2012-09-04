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

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>

#include <boost/regex.hpp>

#include <tmx/tmx>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
Points parsePoints(const std::string str)
{
    Points points;                                        
    Point p;
    boost::regex re("(-?\\d*)\\,(-?\\d*)");
    boost::match_results<std::string::iterator> matches;  
    std::string buf;           
    std::stringstream ss(str);
    
    while (ss >> buf) 
    {
        if(boost::regex_search(begin(buf), end(buf), matches, re))
        {
            std::istringstream(matches[1]) >> p.first;
            std::istringstream(matches[2]) >> p.second;
            points.insert(p);
        }
    }
    
    return points;
}

///////////////////////////////////////////////////////////////////////////
std::vector<Tile> parseTilesFromCSV(const std::string str)
{
    std::vector<Tile> tiles;                                        
    int id; 
    std::string buf;           
    std::stringstream ss(str);
    
    while (std::getline(ss, buf, ',')) 
    {
        std::istringstream(buf) >> id;
        tiles.push_back(Tile(id));
    }
    
    return tiles;
}

///////////////////////////////////////////////////////////////////////////
std::vector<Tile> parseTilesFromBase64(const std::string str, const Compression compression)
{
    static const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    static const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    static const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;
    
    std::vector<Tile> tiles;
    
    // Copying the raw data
    std::string copy = str;

    // Preparing data by removing useless characters
    for(std::string::iterator it = begin(copy); it != end(copy); ++it)
    {
        if(*it == ' ' || *it == '\n') {
            copy.erase(it,it+1);
            it--;
        } 
    }
    
    // Decoding the string
    std::string text = base64_decode(copy);
    
    // Preparing the data
    unsigned char data[text.size()];
    memcpy(data, text.c_str(), text.size());
    
    unsigned id = 0;
    bool flipped_horizontally = false;
    bool flipped_vertically = false;
    bool flipped_diagonally = false;
    
    // Parsing data to extract tiles
    for (int i = 0; i < text.size(); i+=4) 
    {  
        id = data[i] |
             data[i + 1] << 8 |
             data[i + 2] << 16 |
             data[i + 3] << 24;
                                  
        // Read out the flags
        flipped_horizontally = (id & FLIPPED_HORIZONTALLY_FLAG);
        flipped_vertically = (id & FLIPPED_VERTICALLY_FLAG);
        flipped_diagonally = (id & FLIPPED_DIAGONALLY_FLAG);

        // Clear the flags
        id &= ~(FLIPPED_HORIZONTALLY_FLAG |
                FLIPPED_VERTICALLY_FLAG |
                FLIPPED_DIAGONALLY_FLAG);

        tiles.push_back(Tile(id));
    }
    
    return tiles;
}    
    
} // namespace tmx
