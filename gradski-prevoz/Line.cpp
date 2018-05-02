#include "Line.h"

Line::Line(string code, string firstStop, string lastStop)
{
	this->code = code;
	this->firstStop = firstStop;
	this->lastStop = lastStop;
}

Line::~Line()
{
}

void Line::addStation(const Station s, char aOrB)
{
	if (aOrB == 'a' || aOrB == 'A')
		AfirstToLastStation.push_back(s);
	if (aOrB == 'b' || aOrB == 'B')
		BlastToFirstStation.push_back(s);
}



void Line::readStations(char aOrB)
{
	ifstream dir;
	string fileName = "data\\" + code + "_dir"+aOrB+".txt";
	dir.open(fileName);
	string lineInFile;
	if (dir.is_open())
	{
		while (getline(dir, lineInFile))
		{
			Station station = parseStation(lineInFile);
			
			addStation(station, aOrB);
		}
		dir.close();
	}
	else cout << "Unable to open file";
}

ostream & operator<<(ostream & it, const Line & l)
{
	it << "Linija: " << l.code;
	it << "\nSmer A\n";
	for(Station s : l.AfirstToLastStation)
	{
		it << s << "\n";
	}
	it << "Smer B\n";
	for (Station s : l.BlastToFirstStation)
	{
		it << s << "\n";
	}
	return it;
}

Station Line::parseStation(string line)
{

	regex reg("([0-9]+)!(.+)!([0-9]+.[0-9]+)!([0-9]+.[0-9]+)!([0-9]+)");
	smatch result;
	if (regex_match(line, result, reg)) {

		int code = atoi(result.str(1).c_str());
		string name = result.str(2);
		double latitude = atof(result.str(3).c_str());
		double longitude = atof(result.str(4).c_str());
		int zone = atoi(result.str(5).c_str());
		Station s(code, name, latitude, longitude, zone);
		return s;
	}
	else {
		cout << "No match" << endl;
	}
}

Line Line::parseLine(string textLine)
{
	regex reg("(.+)!(.+)!(.+)!");
	smatch result;

	if (regex_match(textLine, result, reg))
	{
		string code = result.str(1);
		string firstStop = result.str(2);
		string lastStop = result.str(3);
		Line line(code, firstStop, lastStop);
		return line;
	}
	else {
		cout << "No match" << endl;
	}
}