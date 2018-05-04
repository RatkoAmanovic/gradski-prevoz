#include "Location.h"

Location::Location(double latitude, double longitude)
{
	this->latitude = latitude;
	this->longitude = longitude;
}

Location::~Location()
{
}

double Location::distance(double A_latitude, double A_longitude, double B_latitude, double B_longitude)
{
	int R = 6371; // Radius of the earth in km
	double distanceLatitude = degressToradian(B_latitude - A_latitude);
	double distanceLongitude = degressToradian(B_longitude - A_longitude);
	double a = sin(distanceLatitude / 2) * sin(distanceLatitude / 2) + cos(degressToradian(A_latitude)) * cos(degressToradian(B_latitude)) * sin(distanceLongitude / 2) * sin(distanceLongitude / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double distance = R * c; // Distance in km
	return distance;
}

ostream& operator<<(ostream &it, const Location &l)
{
	it << "Geografska sirina: " << l.latitude;
	it << " Geografska duzina: " << l.longitude;
	return it;
}

