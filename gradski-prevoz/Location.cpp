#include "Location.h"

Location::Location(double latitude, double longitude)
{
	this->latitude = latitude;
	this->longitude = longitude;
}

Location::~Location()
{
}

ostream& operator<<(ostream &it, const Location &l)
{
	it << "Geografska sirina: " << l.latitude;
	it << " Geografska duzina: " << l.longitude;
	return it;
}