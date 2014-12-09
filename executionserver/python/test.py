#!/usr/bin/env python

import httplib
import urllib
import json

jsonStr = """
{
"userID": 0,
"levelID": 1,
"classID": 2,
"level": {
     "backgroundcolor":"#000000",
     "height":10,
     "layers":[
            {
             "data":[1, 2, 2, 2, 2, 2, 2, 3, 1, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    21, 22, 22, 22, 22, 22, 22, 24, 25, 6, 7, 8, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 11, 12, 13, 22, 22, 22, 46, 47, 48, 22, 22, 22, 44, 22, 22,
                    22, 22, 22, 31, 32, 33, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 51, 52, 53, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
                    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22],
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
             "data":[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 215, 0, 0, 0,
                     0, 0, 0, 0, 210, 230, 0, 0, 0, 0, 0, 201, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 221, 0, 0, 0, 0, 0, 0,
                     132, 133, 0, 0, 0, 0, 0, 0, 0, 204, 0, 0, 0, 0, 0, 0, 0, 0,
                     152, 153, 0, 0, 0, 0, 0, 183, 203, 224, 0, 0, 0, 0, 0, 0, 0, 0,
                     172, 173, 0, 209, 209, 209, 0, 0, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     154, 156, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     174, 176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 157, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
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
                            "dialogue": "Hi",
                            "actor": "1",
                            "repeatable": "1"
                        },
                     "rotation":0,
                     "type":"dialogue",
                     "visible":true,
                     "width":64,
                     "x":896,
                     "y":0
                    },{
                     "height": 64,
                     "name": "obj",
                     "properties":
                       {
                           "dialog": "Get back here you meddling kids!",
                           "prompt": "Help Scooby and the gang escape",
                           "objectiveId": "4"
                       },
                     "rotation": 0,
                     "type": "objective",
                     "visible": true,
                     "width": 64,
                     "x": 832,
                     "y": 64
                    }],
             "opacity":1,
             "type":"objectgroup",
             "visible":true,
             "width":18,
             "x":0,
             "y":0
            },
            {
                "name": "ActorLayer",
                "type": "objectgroup",
                "width": 18,
                "height": 10,
                "objects":[
                    {
                        "height": 64,
                        "width": 64,
                        "rotation": 0,
                        "properties": {
                            "id": "0",
                            "rotation": "0"
                        },
                        "x": 896,
                        "y": 64,
                        "name": "My Hero",
                        "type": "hero"
                    }, {
                        "height": 64,
                        "width": 64,
                        "rotation": 0,
                        "properties": {
                            "id": "1",
                            "rotation": "0"
                        },
                        "x": 880,
                        "y": 128,
                        "name": "Villian A",
                        "type": "enemy"
                    }, {
                        "height": 64,
                        "width": 64,
                        "rotation": 180,
                        "properties": {
                            "id": "2",
                            "rotation": "0"
                        },
                        "x": 864,
                        "y": 256,
                        "name": "Villian B",
                        "type": "enemy"
                    }
                ],
                "visible": true,
                "x": 0,
                "y": 0
            }],
    "orientation":"orthogonal",
    "properties":{},
    "renderorder":"right-down",
    "tileheight":64,
    "tilesets":[ {
        "firstgid":1,
        "image":"assets\/spritesheets\/RPGpack_sheet.png",
        "imageheight":832,
        "imagewidth":1280,
        "margin":0,
        "name":"RPGpack_sheet",
        "properties": {},
        "spacing":0,
        "tileheight":64,
        "tilewidth":64
        }],
    "tilewidth":64,
    "version":1,
    "width":18
    }
}
"""

BASE_URL = "localhost:5000"
INITIALIZE_SESSION = "/initialize"
LEVEL_SUBMIT = "/level/submit"
CHALLENGE_SUBMIT = "/objective/submit"
PING_SERVER = "/ping"

def run_test(connection):

    default_params = {"Host": BASE_URL}

   
#----------------------------------------------------------
# Communication test
#----------------------------------------------------------

    # Much ping
    print "Sending ping to server...."
    connection.request(
            method  = "GET",
            url     = PING_SERVER,
            body    = "",
            headers = default_params)
    response = connection.getresponse()
    data = response.read()

    print response.status
    if response.status != 200:
        print "FAILED: Couldn't ping server"
        return
    print "PASSED: Pinged server"
    
    create_params = {"Content-Type": "application/json", "user_token": "test"}
    create_params.update(default_params)

#----------------------------------------------------------
# Session initialization test
#----------------------------------------------------------

    # Such session
    print "Initializing session..."
    connection.request(
            method  = "POST",
            url     = INITIALIZE_SESSION,
            body    = jsonStr,
            headers = create_params
        )
    response = connection.getresponse()
    print response.status
    if response.status != 200:
        print "FAILED: Couldn't initialize session"
        return
    print "PASSED: Initialized session"


#----------------------------------------------------------
# Level submission tests
#----------------------------------------------------------

    code = """
if hero.moveUp():
    hero.moveDown()
    """
    
    submission = { "codelines": code }

    submit_params = { "Content-Type": "application/json" }
    submit_params.update(default_params)

    # So level
    print "Submitting level move..."
    connection.request(
            method  = "POST",
            url     = LEVEL_SUBMIT,
            body    = json.dumps(submission),
            headers = submit_params
        )
    response = connection.getresponse()
    print response.status
    if response.status != 200:
        print "FAILED: Couldn't submit code"
        return

    data = response.read()
    data = json.loads(data)
    print "PASSED: Successfully submitted level" 
    print json.dumps(data)

    code = """
hero.moveDown(2)
for i in range(0, 2):
    hero.moveUp()
hero.moveLeft()
    """
    submission = { "codelines": code }

    submit_params = { "Content-Type": "application/json" }
    submit_params.update(default_params)

    # Much level
    print "Submitting another level submission..."
    connection.request(
            method  = "POST",
            url     = LEVEL_SUBMIT,
            body    = json.dumps(submission),
            headers = submit_params
        )
    response = connection.getresponse()
    print response.status
    if response.status != 200:
        print "FAILED: Couldn't submit code"
        return

    data = response.read()
    data = json.loads(data)
    print "PASSED: Successfully submitted another level" 
    print json.dumps(data)
     
#----------------------------------------------------------
# Challenge submission test
#----------------------------------------------------------

    code = """
x = 3
    """
    vcode = """
out = x == 3
    """

    submission = { "codelines": code, "validationcode": vcode, "outname": "out", "objectiveid": 4}

    submit_params = { "Content-Type": "application/json" }
    submit_params.update(default_params);

    # Such challenge
    print "Submitting challenge submission..."
    connection.request(
            method  = "POST",
            url     = CHALLENGE_SUBMIT,
            body    = json.dumps(submission),
            headers = submit_params
        )
    response = connection.getresponse()
    print response.status
    if response.status != 200:
        print "FAILED: Couldn't submit challenge"
        return

    data = response.read()
    data = json.loads(data)
    print "PASSED: Succesfully submitted challenge"
    print json.dumps(data)

#----------------------------------------------------------
# Deletion test
#----------------------------------------------------------

    delete_params = dict()
    delete_params.update(default_params)

    # Very delete
    print "Deleting session..."
    connection.request(
            method  = "POST",
            url     = "/shutdown/1000",
            body    = "",
            headers  = delete_params
        )
    response = connection.getresponse()

    print response.status
    if response.status != 200:
        print "FAILED: Couldn't delete session"
        return
    print "PASSED: Deleted session successfully"

if __name__ == "__main__":
   
    # Many connection
    connection = httplib.HTTPConnection(BASE_URL)
    run_test(connection)
    connection.close()
