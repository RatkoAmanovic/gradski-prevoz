#include "Line.h"
#include <unordered_set>
#include <tuple>
#include "boost/functional/hash.hpp"

#ifndef __NETWORK_H_
#define __NETWORK_H_



class Network
{
public:

	struct pair_hash {
		template <class T1, class T2>
		std::size_t operator () (const std::pair<T1, T2> &p) const {
			boost::hash<pair<string, string>> hasher;
			return hasher(p);
		}
	};

	Network();
	~Network();
	void addLine(Line* l);
	void removeLine(Line* l);
	void readLines();
	void readLine(string code);
	Line* parseLine(string line);
	void setZone(int zone);
	friend ostream& operator<<(ostream& it, const Network n);
	inline void setNumberMin(int number) { numberMin = number; }
	inline void setNumberMax(int number) { numberMax = number; }
	inline void setMaxNumberOfStations(int number) { maxNumberOfStations = number; }
	inline void setMinNumberOfStations(int number) { minNumberOfStations = number; }
	unordered_set<Line*> getLinesWithMutualStations(string line);
	bool areStationsOnSameLineAndDirection(string line, int station1, int station2);
	Line* lineWithMostMutualStation(string line);
	Station* closestStation(double latitude, double longitude, string line = "");
	unordered_map<int, Station*> stations1DistnaceAway(int station);
	unordered_map<pair<string, string>, int, pair_hash> numberOfMutualStationsForAllLines();
private:
	vector<Line*> lines;
	int zone;
	int numberMin = 0;
	int numberMax = 200000;
	int maxNumberOfStations = 200000;
	int minNumberOfStations = 0;
};

#endif // !__NETWORK_H_