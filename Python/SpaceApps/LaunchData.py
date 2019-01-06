import requests
import googlemaps
import pandas as pd
from bs4 import BeautifulSoup
from motionless import DecoratedMap, LatLonMarker

GMAPSKEY = 'AIzaSyDZR8co57TwueSwMQPx-5pO_fvImjMnVFc'
def getContents(url):
    """
    Gets html contents of url
    url: link to website to be parsed
    """
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    return soup

def parse(tag, label, soup):
    """
    tag: string containing html tag
    label: name of content to parse
    returns: list of parsed data
    """
    parsedData = soup.find_all(tag, class_=label)
    return [data.get_text() for data in parsedData]

def getData():
    url = "https://spaceflightnow.com/launch-schedule/"
    soup = getContents(url)
    launchDates = parse("span", "launchdate", soup)
    missions = parse("span", "mission", soup)
    timeSite = parse("div", "missiondata", soup)
    desc = parse("div", "missdescrip", soup)

    #format time and site data
    time = [ind[ind.index(':')+2:ind.index('\n')] for ind in timeSite]
    site = [ind[ind.index('\n'):] for ind in timeSite]
    site = [ind[ind.index(':')+2:] for ind in site]

    #format description
    desc = [ind[:ind.rfind('[')] for ind in desc]

    data = {"Launch Dates":launchDates, "Missions":missions, "Times":time,
            "Launch Sites":site, "Info":desc}
    return pd.DataFrame(data, columns = ["Launch Dates", "Missions", "Times", "Launch Sites", "Info"])


def parseLocation(dataFrame):
    #verify GMAPS API Key
    gmaps = googlemaps.Client(GMAPSKEY)

    coords = []
    #iterate for every launch site in the launch data frame
    for site in dataFrame["Launch Sites"]:
        #return JSON data from google API for the natural language location of the launch site
        geocode_result = gmaps.geocode(site)
        coords.append((geocode_result[0]['geometry']['location']['lat'], geocode_result[0]['geometry']['location']['lng']))

    dataFrame["Coordinates"] = (pd.Series(coords)).values

def createMap(coords):
    lat = coords[0]
    lng = coords[1]

    #create style for displayed map
    road_styles = [{
        'feature': 'road.highway',
        'element': 'geomoetry',
        'rules': {
            'visibility': 'simplified',
            'color': '#c280e9'
        }
    }, {
    'feature': 'transit.line',
    'rules': {
        'visibility': 'simplified',
        'color': '#bababa'
    }
    }]
    dmap = DecoratedMap(style=road_styles, key = GMAPSKEY)

    dmap.add_marker(LatLonMarker(lat, lng))
    url = dmap.generate_url()
    return url;
