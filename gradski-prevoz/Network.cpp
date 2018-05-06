#include "Network.h"

Network::Network()
{
}

Network::~Network()
{
	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		
		for (auto it1 = it->second->getLinesBegin(); it1 != it->second->getLinesEnd(); ++it1)
			delete it->second;
		delete it->second;
	}
	for (auto it = lines.begin(); it != lines.end(); ++it)
	{
		delete *it;
		for (auto it1 = (*it)->getA_firstBegin(); it1 != (*it)->getA_firstEnd(); ++it1)
			delete *it1;
		for (auto it1 = (*it)->getB_lastBegin(); it1 != (*it)->getB_lastEnd(); ++it1)
			delete *it1;
	}
	lines.clear();
}

void Network::addLine(Line* l)
{
	lines.push_back(l);
}

void Network::removeLine(string line)
{
	int i = 0;
	for (auto l : lines)
	{
		if (l->getCode() == line)
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
	return mutualLines;
}

bool Network::areStationsOnSameLineAndDirection(string line, int station1, int station2)
{
	int index;
	if (getLine(line) == nullptr)
	{
		cout << "Linija ne postoji";
		return false;
	}
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

bool Network::areStationsOnSameLine(string line, int station1, int station2)
{
	int index;
	auto it = find_if(lines.begin(), lines.end(), [line](Line* lin) {return (*lin).getCode() == line; });
	if (it != lines.end())
		index = distance(lines.begin(), it);
	Line lineObj = *lines[index];

	if (lineObj.isStationOnLine(station1, Direction::A))
		if (lineObj.isStationOnLine(station2, Direction::A)|| lineObj.isStationOnLine(station2, Direction::B))
			return true;
	if (lineObj.isStationOnLine(station1, Direction::B))
		if (lineObj.isStationOnLine(station2, Direction::B)|| lineObj.isStationOnLine(station2, Direction::A))
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

unordered_map<int,Station*> Network::stations1DistnaceAway(int station)
{
	unordered_map<int,Station*> stations;
	Station *s = Station::getStation(station);
	if (s == nullptr)
	{
		cout << "Stajaliste ne postoji\n";
		return stations;
	}
	for (auto it = s->getLinesBegin(); it != s->getLinesEnd(); ++it)
	{
		if (it->second->isStationOnLine(station, Direction::A))
		{
			for (auto it1 = it->second->getA_firstBegin(); it1 != it->second->getA_firstEnd(); ++it1)
			{
				if ((*it1)->getCode() == station)
				{
					++it1;
					if (it1 != it->second->getA_firstEnd())
						stations[(*it1)->getCode()] = (*it1);
					break;
				}
			}
		}
		else
		{
			for (auto it1 = it->second->getB_lastBegin(); it1 != it->second->getB_lastEnd(); ++it1)
			{
				if ((*it1)->getCode() == station)
				{
					++it1;
					if(it1!=it->second->getB_lastEnd())
						stations[(*it1)->getCode()] = (*it1);
					break;
				}
			}
		}
	}
	return stations;
}

unordered_map<pair<string, string>,int, Network::pair_hash> Network::numberOfMutualStationsForAllLines()
{
	unordered_map<pair<string, string>, int, pair_hash> linePairs;
	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		for (auto it1 = it->second->getLinesBegin(); it1 != it->second->getLinesEnd(); ++it1)
		{
			for (auto it2 = it->second->getLinesBegin(); it2 != it->second->getLinesEnd(); ++it2)
			{

				string line1 = it1->second->getCode();
				string line2 = it2->second->getCode();
				bool write = line1 < line2;
				if (line1 < line2)
					swap(line1, line2);
				pair<string, string> pairOfLines(line1, line2);
				if (write)
				{
					int &value = linePairs[pairOfLines];
					if (value)
						linePairs[pairOfLines] += 1;
					else
						linePairs[pairOfLines] = 1;
				}
			}
		}
	}

	for (auto m : linePairs)
		cout << m.first.first << " " << m.first.second << " " << m.second << "\n";
	return linePairs;
}

int Network::leastTransfersBetweenStations(int station1, int station2)
{
	Station* start = Station::getStation(station1);
	Station* finish = Station::getStation(station2);
	if (start == nullptr || finish == nullptr)
	{
		cout << "Stajaliste ne postoji\n";
		return -1;
	}
	unordered_set<string> visitedLines;
	vector<string> finishLines;
	vector<Line *> lines;
	for (auto l : lines)
		if (areStationsOnSameLine((*l).getCode(), station1, station2))
			return 0;
	queue<pair<Line *, int>> q;

	for (auto it = finish->getLinesBegin(); it != finish->getLinesEnd(); ++it)
		finishLines.push_back(it->second->getCode());
	for (auto it = start->getLinesBegin(); it != start->getLinesEnd(); ++it)
	{
		q.push(make_pair(it->second, 0));
		visitedLines.insert(it->second->getCode());
	}
	while (!q.empty())
	{
		pair<Line*, int> temp = q.front();
		q.pop();
		int depth = temp.second + 1;
		Line *l = temp.first;
		for (auto fL : finishLines)
			if (l->getCode() == fL)
				return temp.second;
		unordered_set<Line *> childLines = getLinesWithMutualStations(l->getCode());
		for (auto it = childLines.begin(); it != childLines.end(); ++it)
		{
			if (visitedLines.find((*it)->getCode()) == visitedLines.end())
			{
				q.push(make_pair(*it, depth));
				visitedLines.insert((*it)->getCode());
			}
		}
	}
	return -1;
}

int Network::leastNumberOfStationsBetweenStations(int station1, int station2)
{
	Station* start = Station::getStation(station1);
	Station* finish = Station::getStation(station2);
	if (start == nullptr || finish == nullptr)
	{
		cout << "Stajaliste ne postoji\n";
		return -1;
	}
	unordered_set<int> visitedStations;
	if (station1 == station2)
		return 0;
	queue<pair<Station*, int>> q;
	unordered_map<int, Station*> s = stations1DistnaceAway(station1);
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		q.push(make_pair(it->second, 0));
		visitedStations.insert(it->second->getCode());
	}
	while (!q.empty())
	{
		pair<Station*, int> temp = q.front();
		q.pop();
		int depth = temp.second + 1;
		Station *s = temp.first;
		if (s->getCode() == station2)
			return temp.second;
		unordered_map<int, Station*> childStations = stations1DistnaceAway(s->getCode());
		for (auto it = childStations.begin(); it != childStations.end(); ++it)
		{
			if (visitedStations.find(it->second->getCode()) == visitedStations.end())
			{
				q.push(make_pair(it->second, depth));
				visitedStations.insert(it->second->getCode());
			}
		}
	}
	return -1;
}

Line * Network::getLine(string line)
{
	for (auto it = lines.begin(); it != lines.end(); ++it)
		if ((*it)->getCode() == line)
			return *it;
	return nullptr;
}

ostream & operator<<(ostream & it, const Network n)
{
	for (Line* l : n.lines)
	{
		it << *l << "\n\n\n";
	}
	return it;
}

