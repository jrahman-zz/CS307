# CS307 Fall 2014

**Team Members:**

 - Anant Goel
 - Don Phan
 - Jason Rahman
 - Jon Egeland
 - Josh Selbo
 - Levi Linville


### App Server Development (appserver/)

**To develop on the tilemaps in app/assets/images/tilemaps-src/**

1. Download [Tiled Map Editor](http://www.mapeditor.org/)
2. Copy the tilemap (e.g. sample.tmx) file to a local directory
3. Create this directory structure in the same directory: assets/spritesheets/
4. Copy all needed spritesheets from app/assets/images/spritesheets/ into that directory
5. Edit the .tmx file in Tiled Map Editor
6. File -> Export As... and save JSON file with same name (e.g. sample.json)
7. Copy both the edited .tmx file and the exported JSON file to the repository

This is the easiest way to ensure that the exported JSON file references the correct spritesheet path that Rails generates.