#define PI 3.14159265
#include <iostream>
#include <cmath>

#ifndef __LOCATION_H_
#define __LOCATION_H_

using namespace std;

class Location
{
public:
	Location() {}
	Location(double latitude, double longitude);
	~Location();
	inline void setLatitude(double l) { latitude = l; }
	inline void setLongitude(double l) { longitude = l; }
	inline double getLatitude() const { return latitude; }
	inline double getLongitude() const { return longitude; }
	friend ostream& operator<<(ostream &it, const Location &l);
	static double distance(double A_latitude, double A_longitude, double B_latitude, double B_longitude);
	inline static double degressToradian(double degrees) { return degrees * PI / 180; }

private:
	double latitude;
	double longitude;
};


#endif // !__LOCATION_H_

