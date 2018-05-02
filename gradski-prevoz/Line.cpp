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
