# import requests # Allows for API gets (readings)

# def yelpProcessor(coords):
#     lat = coords[0]
#     longit = coords[1]
#     yelpJSON = requests.get("https://api.yelp.com/v3/autocomplete?text=del&latitude=" + str(lat) + "&longitude=" + str(longit)).json()
#     print(yelpJSON)

# yelpProcessor((34.1397, 118.0353))

# -*- coding: utf-8 -*-

import argparse
import json
import requests
import sys
import urllib


# This client code can run on Python 2.x or 3.x.  Your imports can be
# simpler if you only need one of those.
try:
    from urllib.error import HTTPError
    from urllib.parse import quote
    from urllib.parse import urlencode
except ImportError:
    from urllib2 import HTTPError
    from urllib import quote
    from urllib import urlencode


API_HOST = 'https://api.yelp.com'
SEARCH_PATH = '/v3/businesses/search'

def request(coords, category):
  lat = coords[0]
  longit = coords[1]

  host = 'https://api.yelp.com'
  path = '/v3/businesses/search'
  api_key= 'Ee2elaFp3RVr9JzlCGYIncuXH_WH_0INiVwt7cFc5WG6Hsdf1v1evj3Nj7tDNr6cpJbiJLtQml4u3TISdsDHFTCQ3TLV0-mFkSdicYc0l3O0x2KtuxzYBTZUSrrKW3Yx'

  url = '{0}{1}'.format(host, quote(path.encode('utf8')))

  headers = {
      'Authorization': 'Bearer %s' % api_key,
  }

  response = requests.request('GET', url, headers=headers, params={
    'latitude':lat,
    'longitude':longit,
    'radius':40000,
    'limit':21,
    'categories':category
  })

  return yelpJsonDict(response.json())

def yelpJsonDict(json):
  yelpBusArray = json["businesses"]
  yelpDict = []
  for x in yelpBusArray:

    addrStt = x["location"]
    addressCreate = str(addrStt["address1"] + ", " + str(addrStt["city"]) + ", " + str(addrStt["state"] + " " + str(addrStt["zip_code"])))

    try:
      price = x["price"]
    except:
      price = ""

    yelpDict.append({
      "name":x["name"],
      "stars":x["rating"],
      "address":addressCreate,
      "distance":(x["distance"])/1609.344,
      "picture link":x["image_url"],
      "price":price,
      "link":x["url"]
    })
  return yelpDict
  # print(yelpBusArray)
  # print(" ")
  # for x in yelpDict:
  #   print(x)
  #   print(" ")


# food = request(coord, "food")
# hotels = request(coord, "hotels")
# misc = request(coord, " ")
#
# #Call formula: request(coordinates)
# print(request((34.1397, -118.0353), " ")) # Test in Arcadia
