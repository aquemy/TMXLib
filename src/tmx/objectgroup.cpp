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
Objectgroup::Objectgroup(const boost::property_tree::ptree &pt)
{
    /*int name="Calque de Tile 1" width="20" height="15"*/
    const ptree& node = pt;

    // On parse pour trouver des attributs de la map, des tilesets, Objectgroups, etc
    for (ptree::const_iterator cat = node.begin(); cat != node.end(); ++cat)
    {
        if(cat->first == "<xmlattr>")
        {
            const ptree& node = cat->second;
            for (ptree::const_iterator attr = node.begin(); attr != node.end(); ++attr)
            {
                if(!attr->second.data().empty())
                {
                    if(attr->first == "name")
                        name = attr->second.data();
                    else if(attr->first == "color")
                        std::istringstream(attr->second.data()) >> color;
                    else if(attr->first == "width")
                        std::istringstream(attr->second.data()) >> width;
                    else if(attr->first == "height")
                        std::istringstream(attr->second.data()) >> height;
                    else if(attr->first == "opacity")
                        std::istringstream(attr->second.data()) >> opacity;
                    else if(attr->first == "color")
                        std::istringstream(attr->second.data()) >> color;
                    else
                        throw "Unknow attribut in Objectgroup";
                }
            }
        }
        else if(cat->first == "properties")
        {
            const ptree& node = cat->second;
            properties = Properties(node);
        }
        else if(cat->first == "object")
        {
            const ptree& node = cat->second;
            objects.push_back(Object(node));
        }
        else
            throw "Unknow subsection in Objectgroup";
    }
}

///////////////////////////////////////////////////////////////////////////
void Objectgroup::dump()
{
    std::cout << "Name : " << name << std::endl;
    std::cout << "Color : " << color << std::endl;
    std::cout << "Objectgroup Dimension (w*h) : " << width << "*" << height << std::endl;
    std::cout << "Opacity : " << opacity << std::endl;
    properties.dump();
for(auto object : objects)
        object.dump();
}

} // namespace tmx
