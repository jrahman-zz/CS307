#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "TileLayer.h"

using namespace std;

string testDataA = R"({ "backgroundcolor":"#000000",
 "height":10,
 "layers":[
        {
         "data":[1, 2, 2, 2, 2, 2, 2, 3, 1, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 22, 22, 22, 22, 22, 22, 24, 25, 6, 7, 8, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 12, 13, 22, 22, 22, 46, 47, 48, 22, 22, 22, 44, 22, 22, 22, 22, 22, 31, 32, 33, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 51, 52, 53, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22],
         "height":10,
         "name":"BackgroundLayer",
         "opacity":1,
         "type":"tilelayer",
         "visible":true,
         "width":18,
         "x":0,
         "y":0
        }, 
        {
         "data":[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 215, 0, 0, 0, 0, 0, 0, 0, 210, 230, 0, 0, 0, 0, 0, 201, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 221, 0, 0, 0, 0, 0, 0, 132, 133, 0, 0, 0, 0, 0, 0, 0, 204, 0, 0, 0, 0, 0, 0, 0, 0, 152, 153, 0, 0, 0, 0, 0, 183, 203, 224, 0, 0, 0, 0, 0, 0, 0, 0, 172, 173, 0, 209, 209, 209, 0, 0, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 156, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 174, 176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 157, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
         "height":10,
         "name":"BuildingsLayer",
         "opacity":1,
         "properties":
            {
             "trigger":"15"
            },
         "type":"tilelayer",
         "visible":true,
         "width":18,
         "x":0,
         "y":0
        }, 
        {
         "draworder":"topdown",
         "height":10,
         "name":"TriggerLayer",
         "objects":[
                {
                 "height":64,
                 "name":"scr1",
                 "properties":
                    {
                    },
                 "rotation":0,
                 "type":"trigger",
                 "visible":true,
                 "width":64,
                 "x":896,
                 "y":0
                }],
         "opacity":1,
         "type":"objectgroup",
         "visible":true,
         "width":18,
         "x":0,
         "y":0
        }],
 "orientation":"orthogonal",
 "properties":
    {
    },
 "renderorder":"right-down",
 "tileheight":64,
 "tilesets":[
        {
         "firstgid":1,
         "image":"assets\/spritesheets\/RPGpack_sheet.png",
         "imageheight":832,
         "imagewidth":1280,
         "margin":0,
         "name":"RPGpack_sheet",
         "properties":
            {
            },
         "spacing":0,
         "tileheight":64,
         "tilewidth":64
        }],
 "tilewidth":64,
 "version":1,
 "width":18
})";

START_TEST("tilemap");
	TilemapParser parser;
	parser.parse(testDataA);

	auto tilemaps = parser.getTileLayers();

    if (tilemaps.size() != 2) {
        cout << "Incorrect layer count: " << tilemaps.size() << endl;
        FAIL_TEST("tilemap");
    }

    auto layerIt = tilemaps.begin();
    auto firstLayer = *layerIt++;
    auto secondLayer = *layerIt++;

    auto mergedLayer = firstLayer->merge(secondLayer);
	auto id = (*mergedLayer)[1][0].getID();
	if (id != 21) {
		cout << "Incorrect tile ID: " << id << " should be 21" << endl;
        FAIL_TEST("tilemap");
	}
END_TEST("tilemap");
