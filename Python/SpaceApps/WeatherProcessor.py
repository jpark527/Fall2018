def checkIfMultipleSame(checkWord, arrayOfWords):
    same = False
    for x in arrayOfWords:
        if checkWord == x:
            same = True
    return same

def checkIfVarsEmpty(arrayOfVars):
    for x in arrayOfVars:
        if str(x):
            return False
    return True

def printIfVarsEmpty(arrayOfVars):
    for x in arrayOfVars:
        print(x)

def weatherProcessor(weatherData):
    """   Returns as DICTONARY: {"launch_status" : (Potential values -> "Launch", "Fail", "Unknown"),
                                 "Reason" : (string of reason for Fail or Unknown. "Launch" returns > "" <) }
    """
    ## (precip%, temp, visibility, windspeed, windgust, nearstormdistance, summary)
    ## (weatherRaw.precipProbability, weatherRaw.temperature, weatherRaw.windSpeed, weatherRaw.windGust, weatherRaw.summary)
    launch = "Launch"
    failLaunch = "Fail"
    unknown = "Unknown"

    type = weatherData["Weather Type"]
    temperature = weatherData["temperature"]
    visibility = weatherData["visibility"]
    windspeed = weatherData["Wind Speed"]
    windgust = weatherData["Wind Gust"]
    nearstormdistance = weatherData["Nearest Storm Distance"]
    summary = weatherData["Summary"]

    #{"precipication":precip, "temperature":temp, "Wind Speed":windSpeed,
    #"Wind Gust":windGust, "Summary":summary, "Nearest Storm Distance":neareststormdistance, "visibility":visibility}


    #printIfVarsEmpty([type, temperature, visibility, windspeed, windgust, nearstormdistance, summary])
    if checkIfVarsEmpty((type, temperature, windspeed, windgust)):
        return (unknown, summary)

        #this if statement is comparing a float to string

        #Yeah, my bad. Should be icon

    if checkIfMultipleSame(type, ["rain", "snow", "sleet", "fog", "cloudy", "hail", "thunderstorm", "tornado"]):
        return (failLaunch, summary)
    if windspeed > 33:
        return (failLaunch, summary)
    if visibility < 6.4:
        return (failLaunch, summary)
    if temperature > 37 or temperature < 2:
        return (failLaunch, summary)
    if nearstormdistance > 63:
        return (failLaunch, summary)

    return (launch, "")

def getPercent(weatherData):
    precipLiklehood = weatherData['Precip Probability']
    # print(precipLiklehood)
    return ('Unknown', 'Based on historical data there is a {}% chance of precipitation'.format(precipLiklehood))

"""
Criterias to NOT LAUNCH
-------------------------------
- "weather" (from DS's icon) #
      Don't launch
          Rain
          Snow
          Thunderstorm
          Cumulus clouds
Other possible criterias: clear-day, clear-night, rain, snow, sleet, wind, fog, cloudy, partly-cloudy-day, or partly-cloudy-night

- "wind speed" (from DS's windSpeed)
      More than 33 km
- "visibility" (from DS's visibility)
      Less than 6.4 km
- "temperature" (from DS's temperature)
      More than 37 C
      Less than 2 C
- "nearest storm distance" (from DarkSky's nearStormDistance)
      Less than 19 km
- "wind gust" (from DS's windGust)
      More than 63 km/h
"""
