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
Object::Object(const boost::property_tree::ptree &pt)
{
    const ptree& node = pt;

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
                    if(attr->first == "name")
                        name = attr->second.data();
                    else if(attr->first == "gid")
                        std::istringstream(attr->second.data()) >> id;
                    else if(attr->first == "x")
                        std::istringstream(attr->second.data()) >> x;
                    else if(attr->first == "y")
                        std::istringstream(attr->second.data()) >> y;
                    else if(attr->first == "width")
                        std::istringstream(attr->second.data()) >> width;
                    else if(attr->first == "height")
                        std::istringstream(attr->second.data()) >> height;
                    else if(attr->first == "type")
                        std::istringstream(attr->second.data()) >> type;
                    else
                        throw "Unknow attribut in Object";
                }
            }
        }
        else if(cat->first == "polygon")
        {
            const ptree& node = cat->second;
            polygon = Polygon(node);
        }
        else if(cat->first == "polyline")
        {
            const ptree& node = cat->second;
            polyline = Polyline(node);
        }
        else if(cat->first == "properties")
        {
            const ptree& node = cat->second;
            properties = Properties(node);
        }
        else
            throw "Unknow subsection in Object";
    }
}

///////////////////////////////////////////////////////////////////////////
void Object::dump()
{
    std::cout << "Name : " << name << std::endl;
    std::cout << "Id : " << id << std::endl;
    std::cout << "Type : " << type << std::endl;
    std::cout << "Object placement : " << x << " - " << y << std::endl;
    std::cout << "Object Dimension (w*h) : " << width << "*" << height << std::endl;
    polygon.dump();
    polyline.dump();
    properties.dump();
}

} // namespace tmx
