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
        {
            const ptree& node = cat->second;
            tiles.push_back(Tile(node));
        }
    }
    
    // If encoding is not XML, we have to parse data differently
    if(encoding == Encoding::CSV)
    {
        tiles = parseTilesFromCSV(node.data());
    }
    else if(encoding == Encoding::BASE64)
    {
        if(compression == Compression::GZIP)
        {
            throw std::runtime_error("The GZIP compression is not available at the moment");
        }
        else if(compression == Compression::ZLIB)
        {
            throw std::runtime_error("The ZLIB compression is not available at the moment");
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void Data::dump()
{
    std::cout << "#######################################################" << std::endl;
    std::cout << "### Encoding : " << encoding << std::endl;
    for(auto tile : tiles)
        tile.dump();
    std::cout << std::endl;
}

} // namespace tmx
