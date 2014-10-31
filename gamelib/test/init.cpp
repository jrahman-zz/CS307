#include <iostream>
#include <string>

#include "TilemapParser.h"

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
         "name":"Object Layer 1",
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

int main(int argc, char **argv) {
	
	cout << "Starting test" << endl;

	TilemapParser parser;
	parser.parse(testDataA);

	cout << "Ending test" << endl;

	return 0;
}
