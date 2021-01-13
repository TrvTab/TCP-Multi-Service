import requests
import sys
import json

key = 'be75b2c55649b9904967600bcb738db8'



def isCanadian(inputString):
    return any(char.isalpha() for char in inputString)




def getTemp(postal_code):

	country_code = "us"


	if (isCanadian(postal_code)):
		postal_code = postal_code[:3]
		country_code = "ca"


	response = requests.get("https://api.openweathermap.org/data/2.5/weather?zip=" + postal_code + "," + country_code + "&appid=" + key)
	temp_in_celsius = response.json().get("main").get("temp") - 273.15
	temp_in_celsius = round(temp_in_celsius, 2)
	location = response.json().get("name")

	if (response.status_code == 200):
		f = open("weatherDataFile.txt", "a")
		f.write(postal_code + "\n")
		f.write("The temperature in " + location + " is " + str(temp_in_celsius) + " degrees celsius\n")
		f.close()
	else:
		f = open("weatherDataFile.txt", "a")
		f.write(postal_code + "\n")
		f.write("Invalid Postal Code \n")
		f.close()


	












getTemp(sys.argv[1])
