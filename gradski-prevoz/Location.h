#include <iostream>

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

private:
	double latitude;
	double longitude;
};


#endif // !__LOCATION_H_

