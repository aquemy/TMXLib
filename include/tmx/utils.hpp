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

#ifndef UTILS_HPP
#define UTILS_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <tmx/point.hpp>
#include <tmx/tile.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief Some useful free functions
///
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// \brief Parse a string containing points
///
/// As poligons and polylines are represented by a string, we need to parse
/// it using regular expressions.
/// Note that, at the moment, the function uses Boost::regex instead of
/// C++11 regex. This is due to the fact that gcc does not implement regex.
///
/// \param path Path to the tmx file your would like to load
///
/// \return Points extracted from string
///
///////////////////////////////////////////////////////////////////////////
Points parsePoints(const std::string str);

///////////////////////////////////////////////////////////////////////////
/// \brief Parse tiles from the CSV format
///
/// As tiles using CSV are represented by a string, we need to parse
/// it using regular expressions.
///
/// \param path Path to the tmx file your would like to load
///
/// \return Tiles extracted from string
///
///////////////////////////////////////////////////////////////////////////
std::vector<Tile> parseTilesFromCSV(const std::string str);

}

#endif
