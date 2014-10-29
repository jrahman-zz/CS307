import urllib
import urllib2
import json
import requests

url = 'http://localhost:5000/level/1/submit'
combined_data = {}

combined_data['valid_context'] = {'jsondata':json.dumps({"codelines":["z=x+2", "y=y*z"],"context":{"y":2, "x":3}})}
combined_data['valid_no_context'] = {'jsondata':json.dumps({"codelines":["z=x+2", "y=y*z"]})}

response = requests.post(url, data = combined_data['valid_context'])
print(response.text)

response = requests.post(url, data = combined_data['valid_no_context'])
print(response.text)