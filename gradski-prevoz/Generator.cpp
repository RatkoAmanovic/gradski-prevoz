#include "Generator.h"



Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::generateGML_LTypeGraph(Network *n)
{
	ofstream gml;
	gml.open("l_type_graph.gml");
	gml << "graph\n[\n";

	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		gml << "\tnode\n\t[\n\t\tid " << it->first << "\n\t\tlabel " << it->first<<"\n\t]\n";
	}
	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		unordered_map<int, Station*> s = n->stations1DistnaceAway(it->first);
		for (auto it1 = s.begin(); it1 != s.end(); ++it1)
		{
			gml << "\tedge\n\t[\n\t\tsource " << it->first << "\n\t\ttarget " << it1->first << "\n\t]\n";
		}

	}


	gml << "]\n";
	gml.close();
}

void Generator::generateGML_CTypeGraph(Network *n)
{
	ofstream gml;
	gml.open("c_type_graph.gml");
	gml << "graph\n[\n";

	for (auto it = n->getLinesBegin(); it != n->getLinesEnd(); ++it)
	{
		gml << "\tnode\n\t[\n\t\tid " << (*it)->getCode() << "\n\t\tlabel " << (*it)->getCode() << "\n\t]\n";
	}
	for (auto it = n->getLinesBegin(); it != n->getLinesEnd(); ++it)
	{
		unordered_set<Line*> l = n->getLinesWithMutualStations((*it)->getCode());
		for (auto it1 = l.begin(); it1 != l.end(); ++it1)
		{
			gml << "\tedge\n\t[\n\t\tsource " << (*it)->getCode() << "\n\t\ttarget " << (*it1)->getCode() << "\n\t]\n";
		}

	}


	gml << "]\n";
	gml.close();
}

void Generator::generateCSV_CTypeGraph(Network *n)
{
	ofstream csv;
	csv.open("c_type_graph.csv");

	for (auto it = n->getLinesBegin(); it != n->getLinesEnd(); ++it)
	{
		csv << (*it)->getCode() << ";";
		unordered_set<Line*> l = n->getLinesWithMutualStations((*it)->getCode());
		for (auto it1 = l.begin(); it1 != l.end(); ++it1)
		{
			csv << (*it1)->getCode() << ";";
		}
		csv << "\n";
	}
	csv.close();
}

void Generator::generateCSV_LTypeGraph(Network *n)
{
	ofstream csv;
	csv.open("l_type_graph.csv");

	for (auto it = Station::getStationsBegin(); it != Station::getStationsEnd(); ++it)
	{
		csv << it->first << ";";
		unordered_map<int, Station*> s = n->stations1DistnaceAway(it->first);
		for (auto it1 = s.begin(); it1 != s.end(); ++it1)
		{
			csv << it1->first << ";";
		}
		csv << "\n";
	}
	csv.close();
}
