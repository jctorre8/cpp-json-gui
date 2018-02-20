#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include "WaypointLibrary.hpp"
using namespace std;
 
int main(int argc, char **argv)
{
// Creation
Json::Value minimizer;
Json::Value minParameters;
minParameters["MinimumRMS"] = 0.2;
minParameters["sgbUpdated"] = true;
minimizer["Minimizer"]["parameters"] = minParameters;
minimizer["algorithm"] = "TruncatedNewton";
 
string ret = minimizer.toStyledString();

// Output to see the result
cout<<"creating nested Json::Value Example pretty print: "
<<endl<<minimizer.toStyledString()
<<endl;

cout << "Testing the to string func:\n" << ret << endl;

WaypointLibrary lib("waypoints.json");
lib.saveToFile();
lib.restoreFromFile();
cout << lib.toJSONstring() << endl;
string name = "new waypoint";
string address = "no address";
string ele = "10201.0";
string lon = "123.123";
string lat = "10.10";

cout << "Adding new waypoint: " << name << address << ele << lon << lat << endl;

lib.addNew(lat, lon, ele, name, address);

cout << lib.toJSONstring() << endl;

cout << "Gettomg new waypoin and printing" << endl;

lib.get(name)->print();

cout << "Updating new waypoint: " << name << " with all values 111.11." << endl;

lib.updateWaypoint("111.11", "111.11", "111.11", name, address);

cout << lib.toJSONstring() << endl;

cout << "Removing new waypoin" << endl;

lib.remove(name);
cout << lib.toJSONstring() << endl;
 
return 0;
}