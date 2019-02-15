/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    //create a new MosaicCanvas which is appropriately
    //sized based on the rows and columns of tiles in the SourceImage
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    map<Point<3>, size_t> tiles_map; //points and index of image in theTiles
    vector<Point<3>> points;
    for(size_t i = 0; i < theTiles.size(); i++){
      LUVAPixel pixel = theTiles[i].getAverageColor();
      Point<3> point = convertToXYZ(pixel);
      points.push_back(point);
      tiles_map.insert(pair<Point<3>, size_t>(point,i));
    }
    //build a kdTree
    KDTree<3>* tree = new KDTree<3>(points);
    for(int i = 0; i < theSource.getRows(); i++){
      for(int j = 0; j < theSource.getColumns(); j++){
        LUVAPixel region_color = theSource.getRegionColor(i, j);
        Point<3> region_point = convertToXYZ(region_color);
        Point<3> nearest_point = tree->findNearestNeighbor(region_point);
        size_t index = tiles_map[nearest_point];
        canvas->setTile(i, j, &theTiles[index]);
      }
    }
    delete tree;  //for memory leak check
    return canvas;
}
