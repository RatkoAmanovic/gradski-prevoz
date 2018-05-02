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

void Line::addStationToA(const Station s)
{
	AfirstToLastStation.push_back(s);
}

void Line::addStationToB(const Station s)
{
	BlastToFirstStation.push_back(s);
}

void Line::readStationsToA()
{
	ifstream dirA;
	string fileName = "data\\" + code + "_dirA.txt";
	dirA.open(fileName);
	string lineInFile;
	if (dirA.is_open())
	{
		while (getline(dirA, lineInFile))
		{
			cout << lineInFile << '\n';
		}
		dirA.close();
	}
	else cout << "Unable to open file";
}

void Line::readStationsToB()
{
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
