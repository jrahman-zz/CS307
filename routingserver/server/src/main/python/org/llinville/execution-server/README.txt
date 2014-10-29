Runs a RESTful server. Receives requests to run code, executes it, and sends changed values back

Code must be sent with a post request to /level/<levelid>/submit with the body:
key: jsondata
value:
{
    "codelines":[<line 1>, <line 2>, <line 3>, ... ]
    #Optional context
    "context":{<name>:<value>, <name>:<value>, ...}
}