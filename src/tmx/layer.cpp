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
Layer::Layer(const boost::property_tree::ptree &pt)
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
                    else if(attr->first == "width")
                        width = std::stoi(attr->second.data());
                    else if(attr->first == "height")
                        height = std::stoi(attr->second.data());
                    else if(attr->first == "opacity")
                        opacity = std::stof(attr->second.data());
                    else
                        throw std::runtime_error("Unknow attribut in Layer");
                }
            }
        }
        else if(cat->first == "properties")
            properties = Properties(cat->second);
        else if(cat->first == "data")
            data = Data(cat->second);
        else
            throw std::runtime_error("Unknow subsection in Layer");
    }
}

///////////////////////////////////////////////////////////////////////////
std::string Layer::getName() const
{
    return name;
}

///////////////////////////////////////////////////////////////////////////
int Layer::getX() const
{
    return x;
}           

///////////////////////////////////////////////////////////////////////////
int Layer::getY() const
{
    return y;
}            
   
///////////////////////////////////////////////////////////////////////////
int Layer::getWidth() const
{
    return width;
}           

///////////////////////////////////////////////////////////////////////////
int Layer::getHeight() const
{
    return height;
}      

///////////////////////////////////////////////////////////////////////////
float Layer::getOpacity() const
{
    return opacity;
}       

///////////////////////////////////////////////////////////////////////////
bool Layer::getVisible() const
{
    return visible;
}         

///////////////////////////////////////////////////////////////////////////
Data Layer::getData() const
{
    return data;
}             

///////////////////////////////////////////////////////////////////////////
Properties Layer::getProperties() const
{
    return properties;
}

///////////////////////////////////////////////////////////////////////////
void Layer::dump() const
{
    std::cout << "#######################################################" << std::endl;
    std::cout << "## Name : " << name << std::endl;
    std::cout << "## Layer Dimension (w*h) : " << width << "*" << height << std::endl;
    std::cout << "## Opacity : " << opacity << std::endl;
    if(!properties.empty())
        properties.dump();
    data.dump();
}

} // namespace tmx
