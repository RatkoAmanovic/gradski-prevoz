#include"Network.h"
#include<fstream>
#ifndef __GENERATOR_H_
#define __GENERATOR_H_



class Generator
{
public:
	Generator();
	~Generator();
	static void generateGML_CTypeGraph(Network *n);
	static void generateGML_LTypeGraph(Network *n);
	static void generateCSV_CTypeGraph(Network *n);
	static void generateCSV_LTypeGraph(Network *n);
};

#endif // !__GENERATOR_H_
