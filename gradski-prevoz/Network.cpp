#include "Network.h"

Network::Network()
{
}

Network::~Network()
{
	lines.clear();
}

void Network::addLine(Line* l)
{
	lines.push_back(l);
}

void Network::removeLine(Line * l)
{
	int i = 0;
	for (Line* line : lines)
	{
		if (l == line)
			lines.erase(lines.begin() + i);
		i++;
	}
}

void Network::readLines()
{
	ifstream dir;
	string fileName = "data\\_lines.txt";
	dir.open(fileName);
	string lineInFile;
	if (dir.is_open())
	{
		while (getline(dir, lineInFile))
		{
			Line* line = parseLine(lineInFile);
			if ((*line).getZone() <= zone)
				if ((*line).getNumber() > numberMin && (*line).getNumber() < numberMax)
					if ((*line).getNumberOfStations() > minNumberOfStations && (*line).getNumberOfStations() < maxNumberOfStations)
						addLine(line);
		}
		dir.close();
	}
	else cout << "Unable to open file";
}

void Network::readLine(string code)
{
	ifstream dir;
	string fileName = "data\\_lines.txt";
	dir.open(fileName);
	string lineInFile;
	if (dir.is_open())
	{
		while (getline(dir, lineInFile))
		{
			Line* line = parseLine(lineInFile);
			if (line->getCode() == code)
			{
				addLine(line);
				break;
			}
		}
		dir.close();
	}
	else cout << "Nije moguce otvoriti fajl";
}

Line* Network::parseLine(string textLine)
{
	regex reg("(([0-9]*)[a-zA-Z]*([0-9]*))!(.+)!(.+)!");
	smatch result;

	if (regex_match(textLine, result, reg))
	{
		string code = result.str(1);
		int number;
		if (result.str(3) == "")
			number = atoi(result.str(2).c_str());
		else
			number = atoi(result.str(3).c_str());
		string firstStop = result.str(4);
		string lastStop = result.str(5);
		Line* line = new Line(code, firstStop, lastStop, number);
		(*line).readStations(Direction::A);
		(*line).readStations(Direction::B);
		return line;
	}
	else {
		cout << "No match" << endl;
		return nullptr;
	}
}

void Network::setZone(int zone)
{
	this->zone = zone;
}

unordered_set<Line*> Network::getLinesWithMutualStations(string line)
{
	unordered_set<Line*> mutualLines;
	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		if(it->second->isInLines(line))
			for (auto it1 = it->second->getLinesBegin(); it1 != it->second->getLinesEnd(); ++it1)
			{
				if (it1->first != line)
					mutualLines.insert(it1->second);
			}
	}
	for (auto it = mutualLines.begin(); it != mutualLines.end(); ++it)
	{
		cout << (*it)->getCode() << " ";
	}
	cout << "\n";
	return mutualLines;
}

bool Network::areStationsOnSameLineAndDirection(string line, int station1, int station2)
{
	int index;
	auto it = find_if(lines.begin(), lines.end(), [line](Line* lin) {return (*lin).getCode() == line; });
	if (it != lines.end())
		index = distance(lines.begin(), it);
	Line lineObj = *lines[index];
	
	if (lineObj.isStationOnLine(station1, Direction::A))
		if (lineObj.isStationOnLine(station2, Direction::A))
			return true;
	if (lineObj.isStationOnLine(station1, Direction::B))
		if (lineObj.isStationOnLine(station2, Direction::B))
			return true;

	return false;
}

Line * Network::lineWithMostMutualStation(string line)
{
	unordered_map<Line*,int> mutualLines;
	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		if (it->second->isInLines(line))
			for (auto it1 = it->second->getLinesBegin(); it1 != it->second->getLinesEnd(); ++it1)
			{
				if (it1->first != line)
					mutualLines[it1->second]++;
			}
	}
	Line* maxLine = nullptr;
	int max = 0;
	for (auto p : mutualLines)
	{
		if (p.second > max)
		{
			maxLine = p.first;
			max = p.second;
		}
	}
	return maxLine;
}

Station * Network::closestStation(double latitude, double longitude, string line)
{
	if (line == "")
	{
		double minDistance = 200000;
		Station* s = nullptr;
		for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
		{
			double distance = Location::distance(it->second->getStationLatitude(), it->second->getStationLongitude(), latitude, longitude);
			if (distance < minDistance)
			{
				minDistance = distance;
				s = it->second;
			}
		}
		return s;
	}
	else {//TODO moze brze
		double minDistance = 200000;
		Station* s = nullptr;
		for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
		{
			if (it->second->isInLines(line))
				for (auto it1 = it->second->getLinesBegin(); it1 != it->second->getLinesEnd(); ++it1)
				{
					double distance = Location::distance(it->second->getStationLatitude(), it->second->getStationLongitude(), latitude, longitude);
					if (distance < minDistance)
					{
						minDistance = distance;
						s = it->second;
					}
				}
		}
		return s;
	}
}

ostream & operator<<(ostream & it, const Network n)
{
	for (Line* l : n.lines)
	{
		it << *l << "\n\n\n";
	}
	return it;
}
