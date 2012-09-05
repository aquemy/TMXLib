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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <tmx/tmx>

using namespace boost::property_tree;

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
Data::Data(const boost::property_tree::ptree &pt)
{
    const ptree& node = pt;

    // Define the default encoding
    encoding = Encoding::XML;
    
    // Parse data
    for (ptree::const_iterator cat = node.begin(); cat != node.end(); ++cat)
    {
        if(cat->first == "<xmlattr>")
        {
            const ptree& node = cat->second;
            for (ptree::const_iterator attr = node.begin(); attr != node.end(); ++attr)
            {
                if(!attr->second.data().empty())
                {
                    if(attr->first == "encoding")
                    {
                        if(attr->second.data() == "csv")
                            encoding = Encoding::CSV;
                        else if(attr->second.data() == "base64")
                            encoding = Encoding::BASE64;
                        else
                            throw std::runtime_error("Invalid encoding in Data");
                    }
                    else if(attr->first == "compression")
                    {
                        if(attr->second.data() == "gzip")
                            compression = Compression::GZIP;
                        else if(attr->second.data() == "zlib")
                            compression = Compression::ZLIB;
                        else
                            throw std::runtime_error("Invalid compression in Data");
                    }
                }
            }
        }
        else if(encoding == Encoding::XML && cat->first == "tile")
            push_back(Tile(cat->second));
    }
    
    // If encoding is not XML, we have to parse data differently
    if(encoding == Encoding::CSV)
    {
        std::vector<Tile> tiles = parseTilesFromCSV(node.data());
        for(auto tile : tiles)
            push_back(tile);
    }
    else if(encoding == Encoding::BASE64)
    {
        std::vector<Tile> tiles = parseTilesFromBase64(node.data(),compression);
        for(auto tile : tiles)
            push_back(tile);
    }
}

///////////////////////////////////////////////////////////////////////////
Encoding Data::getEncoding() const
{
    return encoding;
}

///////////////////////////////////////////////////////////////////////////
Compression Data::getCompression() const
{
    return compression;
}

///////////////////////////////////////////////////////////////////////////
void Data::dump() const
{
    std::cout << "#######################################################" << std::endl;
    std::cout << "### Encoding : " << encoding << std::endl;
    for(auto tile : *this)
        tile.dump();
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////
std::vector<Tile> Data::parseTilesFromCSV(const std::string str)
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
std::vector<Tile> Data::parseTilesFromBase64(const std::string str, const Compression compression)
{
    static const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    static const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    static const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;
    
    std::vector<Tile> tiles;
    
    // Copying the raw data
    std::string copy = str;

    // Preparing data by removing useless characters
    for(std::string::iterator it = std::begin(copy); it != std::end(copy); ++it)
    {
        if(*it == ' ' || *it == '\n') {
            copy.erase(it,it+1);
            it--;
        } 
    }
    
    std::string text = DecodeBase64(copy);
    
    // Decoding the string
    if(compression == Compression::GZIP)
        text = DecompressGZIP(text);
    else if(compression == Compression::ZLIB)
        text = DecompressZLIB(text);
        
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
