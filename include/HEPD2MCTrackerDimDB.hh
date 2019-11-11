#ifndef TrackerDimDB_hh
#define TrackerDimDB_hh
#include "hashtable.h"

class TrackerDimDB{
private:

	hashtable<double> pmap;
	static	TrackerDimDB* Head;
	static	TrackerDimDB* GetHead(){if (!Head) {Head= new TrackerDimDB();} return Head; }
	TrackerDimDB(){}

public:

	static void     AddMeas(const char* name,double value){GetHead()->pmap.Add(name,value); return;	}
	static double   GetMeas(const char* name) ;
	static void     Clear(){GetHead()->pmap.clear();}
	static int      Size(){return GetHead()->pmap.size();}
};

#endif

#ifdef TrackerDimDB_cc
#include <string>
#include <stdexcept>

TrackerDimDB* TrackerDimDB::Head=0;

double  TrackerDimDB::GetMeas(const char* name) {
	GetHead();
	if(Head->pmap.contains(name)){
		return Head->pmap[name];
	}
	else {
		std::string aa=std::string("Measure: ")+std::string(name)+std::string("  not found!\n");
		printf("Error %s\n",aa.c_str());
		throw std::runtime_error(aa);
		return -123456789.;
	}
}


#endif