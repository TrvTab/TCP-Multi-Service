from urllib.request import urlopen as uReq
from bs4 import BeautifulSoup as soup 
import sys


def nhl_points_leader():
	url = 'http://www.espn.com/nhl/statistics'
	client = uReq(url)
	page_html = client.read()
	client.close()
	page_soup = soup(page_html, "html.parser")
	tables = page_soup.findAll("table", {"class":"tablehead"})


	player_name = tables[0].findAll("tr")[1].findAll("a")[2].text
	player_team = tables[0].findAll("tr")[1].findAll("td")[1].text[-3:]
	player_points =  tables[0].findAll("tr")[1].findAll("td")[2].text

	f = open("statsDataFile.txt", "a")
	f.write("NHL Points\n") 
	f.write("Points Leader: " + player_name + "\n")
	f.write("Team: " + player_team + "\n")
	f.write("Points: " + player_points + "\n")
	f.close()

def nhl_goal_leader():

	url = 'http://www.espn.com/nhl/statistics'
	client = uReq(url)
	page_html = client.read()
	client.close()
	page_soup = soup(page_html, "html.parser")
	tables = page_soup.findAll("table", {"class":"tablehead"})


	player_name = tables[1].findAll("tr")[1].findAll("a")[2].text
	player_team = tables[1].findAll("tr")[1].findAll("td")[1].text[-3:]
	player_goals =  tables[1].findAll("tr")[1].findAll("td")[2].text

	f = open("datafile.txt", "a")
	f.write("NHL Goals\n") 
	f.write("Goals Leader: " + player_name + "\n")
	f.write("Team: " + player_team + "\n")
	f.write("Goals: " + player_goals + "\n")
	f.close()

def nhl_plus_minus():

	url = 'http://www.espn.com/nhl/statistics'
	client = uReq(url)
	page_html = client.read()
	client.close()
	page_soup = soup(page_html, "html.parser")
	tables = page_soup.findAll("table", {"class":"tablehead"})

	player_name = tables[2].findAll("tr")[1].findAll("a")[2].text
	player_team = tables[2].findAll("tr")[1].findAll("td")[1].text[-3:]
	player_plus_minus =  tables[2].findAll("tr")[1].findAll("td")[2].text

	f = open("datafile.txt", "a")
	f.write("NHL Plus/Minus\n") 
	f.write("Plus/Minus Leader: " + player_name + "\n")
	f.write("Team: " + player_team + "\n")
	f.write("Plus/Minus: " + player_plus_minus + "\n")
	f.close()


def nhl_GAA():
	url = 'http://www.espn.com/nhl/statistics'
	client = uReq(url)
	page_html = client.read()
	client.close()
	page_soup = soup(page_html, "html.parser")
	tables = page_soup.findAll("table", {"class":"tablehead"})

	player_name = tables[3].findAll("tr")[1].findAll("a")[2].text
	player_team = tables[3].findAll("tr")[1].findAll("td")[1].text[-3:]
	player_GAA =  tables[3].findAll("tr")[1].findAll("td")[2].text

	f = open("datafile.txt", "a")
	f.write("NHL GAA\n") 
	f.write("GAA Leader: " + player_name + "\n")
	f.write("Team: " + player_team + "\n")
	f.write("GAA: " + player_GAA + "\n")
	f.close()

def nhl_save_percentage():

	url = 'http://www.espn.com/nhl/statistics'
	client = uReq(url)
	page_html = client.read()
	client.close()
	page_soup = soup(page_html, "html.parser")
	tables = page_soup.findAll("table", {"class":"tablehead"})

	player_name = tables[4].findAll("tr")[1].findAll("a")[2].text
	player_team = tables[4].findAll("tr")[1].findAll("td")[1].text[-3:]
	player_save_percentage=  tables[4].findAll("tr")[1].findAll("td")[2].text

	f = open("datafile.txt", "a")
	f.write("NHL SavePercentage\n") 
	f.write("Save Percentage Leader: " + player_name + "\n")
	f.write("Team: " + player_team + "\n")
	f.write("Save Percentage: " + player_save_percentage + "\n")
	f.close()

def nhl_goalie_wins():

	url = 'http://www.espn.com/nhl/statistics'
	client = uReq(url)
	page_html = client.read()
	client.close()
	page_soup = soup(page_html, "html.parser")
	tables = page_soup.findAll("table", {"class":"tablehead"})

	player_name = tables[5].findAll("tr")[1].findAll("a")[2].text
	player_team = tables[5].findAll("tr")[1].findAll("td")[1].text[-3:]
	goalie_wins = tables[5].findAll("tr")[1].findAll("td")[2].text

	f = open("datafile.txt", "a")
	f.write("NHL Wins\n") 
	f.write("Goalie Wins Leader: " + player_name + "\n")
	f.write("Team: " + player_team + "\n")
	f.write("Goalie Wins: " + goalie_wins+ "\n")
	f.close()

if (sys.argv[2] == "Points"):
	nhl_points_leader()
elif (sys.argv[2] == "Goals"):
	nhl_goal_leader()
elif (sys.argv[2] == "Plus/Minus"):
	nhl_plus_minus()
elif (sys.argv[2] == "GAA"):
	nhl_GAA()
elif (sys.argv[2] == "SavePercentage"):
	nhl_save_percentage()
elif (sys.argv[2] == "Wins"):
	nhl_goalie_wins()

	

