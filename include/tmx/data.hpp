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

#ifndef DATA_HPP
#define DATA_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <boost/property_tree/ptree.hpp>

#include <tmx/encoding.hpp>
#include <tmx/compression.hpp>
#include <tmx/tile.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief A class that contains layer data
///
///////////////////////////////////////////////////////////////////////////
class Data : public std::vector<Tile>
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Create an empty Data object
    ///
    ///////////////////////////////////////////////////////////////////////////
    Data() = default;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create a Data object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Data(const boost::property_tree::ptree &pt);
     
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the encoding
    ///
    /// \return Encoding
    ///
    ///////////////////////////////////////////////////////////////////////////
    Encoding getEncoding() const;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the compression
    ///
    /// \return Compression
    ///
    ///////////////////////////////////////////////////////////////////////////
    Compression getCompression() const;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Print on the standard output the object
    ///
    ///////////////////////////////////////////////////////////////////////////
    void dump() const;    

    ///////////////////////////////////////////////////////////////////////////
    // Member data
    ///////////////////////////////////////////////////////////////////////////
    Encoding encoding = Encoding::XML;           ///< Encoding for data
    Compression compression = Compression::NONE; ///< Compression for data
    
protected :
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Parse tiles from the CSV format
    ///
    /// As tiles using CSV are represented by a string, we need to parse
    /// it using regular expressions.
    ///
    /// \param str String containing tiles information
    ///
    /// \return Tiles extracted from string
    ///
    ///////////////////////////////////////////////////////////////////////////
    std::vector<Tile> parseTilesFromCSV(const std::string str);
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Parse tiles from the Base64 format
    ///
    /// As tiles using Base64 are represented by a string, we need to parse
    /// it using regular expressions.
    ///
    /// \param str String containing tiles information
    /// \param compression Compression type
    ///
    /// \return Tiles extracted from string
    ///
    ///////////////////////////////////////////////////////////////////////////
    std::vector<Tile> parseTilesFromBase64(const std::string str, const Compression compression);
    
};

} // namespace tmx

#endif
