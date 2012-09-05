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

#include <iostream>
#include <iomanip>
#include <exception>
#include <vector>

#include <tmx/map.hpp>

using namespace std;
using namespace tmx;

typedef struct {
    unsigned width;
    unsigned height;
    vector<int> layer;
} MyMap;

void draw(MyMap);

int main(void)
{
    try
    {
        // We load a Map thanks to tmx
        Map map("example.tmx");
        
        // We create our own (basic map)
        MyMap myMap;
        
        // Define how using tmx information with our map
        myMap.width = map.getWidth();
        myMap.height = map.getHeight();
        
        // For the instance, we use only the first layer. 
        // Each tile is represented by its Id on the tileset.
        /*for(int i = 0; i < myMap.width*myMap.height; i++)
            myMap.layer.push_back(map[0].getData()[i].getId());*/

        // Let's draw our map on the screen with our powerful drawing function !
        draw(myMap);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

void draw(MyMap map)
{
    for(int i = 0; i < map.width; i++)
    {
        for(int j = 0; j < map.height; j++)
        {
            cout << setw(4) << map.layer[i+j*map.height] << " ";
        }
        cout << endl;
    }
}
