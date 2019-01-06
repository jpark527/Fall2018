from darksky import forecast
from datetime import datetime as dt
import LaunchData
import WeatherProcessor

##RETURNS WEATHER DATA AS DICTONARY WHERE KEY = COORDINATES AND VALUES IS A TUPLE OF WEATHER VALEUS
#ex. {(lat,ln):(%precip, temp, visibility, windspeed)}


#using this to limit number of darksky pulls, will be integrated to use all coordinates in dataframe
df = LaunchData.getData()
LaunchData.parseLocation(df)
# coords = df.Coordinates[:5]
# print(coords)

#Unique DarkSky API key
DSKEY = '02382e7114e768e2588b030ae3803832'

#hardcoded date, can be made general
# DAY = 25
# MONTH = 12
# YEAR = 2018

# class weatherDataClass:
#     def init(jsonData):
#

def parseDates(df):
    dates = df["Launch Dates"]
    parsedDates = []
    convert = {"Oct.": 10, "Nov.":11, "Dec.":12, "Jan.":1, "Feb.":2, "Mar.":3, "April": 4, "May":5}
    for date in dates:
        list = date.split()
        if(len(list) > 1):
            if list[1].isdigit():
                if(list[0] in convert):
                    month = convert[list[0]]
                    year = 2019 if month < 6 else 2018
                    tup = convertLaunchDate(year, month, int(list[1]))
                    parsedDates.append(tup)
                else:
                    parsedDates.append("")
            else:
                parsedDates.append("")
        else:
            parsedDates.append("")
    return parsedDates

def convertLaunchDate(year, month, day):
    return dt(year, month, day).isoformat()

def getWeatherData(coords, DSKEY, date):
    lat = coords[0]
    lng = coords[1]
    weatherRaw = (forecast(DSKEY, lat, lng, time=date, units="si"))
    try:
        type = weatherRaw.icon
    except:
        type = 0
    try:
        precipProbability = weatherRaw.precipProbability * 100
    except:
        precipProbability = 0
    try:
        temp = weatherRaw.temperature
    except:
        temp = 35
    try:
        windSpeed = weatherRaw.windSpeed
    except:
        windSpeed = -999
    try:
        windGust = weatherRaw.windGust
    except:
        windGust = 0
    try:
        visibility = weatherRaw.visibility
    except:
        visibility = 999
    try:
        neareststormdistance = weatherRaw.nearestStormDistance
    except:
        neareststormdistance = -999
    try:
        summary = weatherRaw.summary
    except:
        summary = ""
    return {"Precip Probability": precipProbability, "Weather Type":type, "temperature":temp, "Wind Speed":windSpeed, "Wind Gust":windGust, "Summary":summary, "Nearest Storm Distance":neareststormdistance, "visibility":visibility}

def getStatus():
    dates = parseDates(df)
    data = []
    for i in range(len(df.Coordinates)):
        if dates[i] != "":
            data.append(WeatherProcessor.weatherProcessor( getWeatherData(df.Coordinates.iloc[i], DSKEY, dates[i])))
            # print(status[0] + ", " + status[1]) #"Launch Status":launch, "Status":""}
        else:
            data.append(('Unknown', ''))
    return data
# print(getStatus())
