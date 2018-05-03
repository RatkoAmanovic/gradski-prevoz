#include "Network.h"



Network::Network()
{
}


Network::~Network()
{
}

void Network::addLine(Line* l)
{
	lines.push_back(l);
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
			addLine(line);
		}
		dir.close();
	}
	else cout << "Unable to open file";
}

Line* Network::parseLine(string textLine)
{
	regex reg("(.+)!(.+)!(.+)!");
	smatch result;

	if (regex_match(textLine, result, reg))
	{
		string code = result.str(1);
		string firstStop = result.str(2);
		string lastStop = result.str(3);
		Line* line = new Line(code, firstStop, lastStop);
		(*line).readStations('a');
		(*line).readStations('b');
		return line;
	}
	else {
		cout << "No match" << endl;
		return nullptr;
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
