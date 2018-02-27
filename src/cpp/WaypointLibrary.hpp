#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <jsoncpp/json/json.h>
#include "Waypoint.hpp"

using namespace std;

/**
 * Copyright 2018 Jean Torres,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Purpose: Class tp act as a library of waypoints compatible with JSON
 *
 * Ser321 Foundations of Distributed Applications
 * see http://pooh.poly.asu.edu/Ser321
 * @author Jean Torres jctorre8@asu.edu
 * @version February 2018
 */


class WaypointLibrary{

    public:

    vector<Waypoint> library;
    vector<string> names;

    /**
    * No parameter constructor. Just creates an empty Vector.
    */
    WaypointLibrary();

    /**
    * Waypoint Library constructor that takes a list as an argument.
    *
    * @param An old list of waypoints to initialize the library.
    */
    WaypointLibrary(vector<Waypoint> oldLibrary);

    /**
    * Waypoint Library constructor that gets populated by a json file.
    * 
    * @param The name of the json file.
    */
    WaypointLibrary(string jsonFileName);

    /**
    * Outputs the content of the library into a string representation of json.
    * 
    * @return The string json content of the library.
    */
    string toJSONstring();

    /**
    * Adds a waypoint to the library.
    * 
    * @param A Waypoint object to be added to the library
    * @return True if successful and false if don't.
    */
    void add(Waypoint aWaypoint);

    /**
    * Adds a new waypoint to the library.
    * 
    * @param A Waypoint object to be added to the library
    * @return True if successful and false if don't.
    */
    void addNew(string lat, string lon, string ele, string name, string address);
    void updateWaypoint(string lat, string lon, string ele, string name, string address);

    /**
    * Removes the waypoint with the matching name.
    * 
    * @param  The name of the waypoint that needs to be removed.
    * @return True if the waypoint was removed successfully, false if don't.
    */
    void remove(string name);
    /**
    * Get the waypoint that matches the given name.
    * 
    * @param  The the name of the waypoint that needs to be returned.
    * @return The waypoint that has the name.
    */
    Waypoint * get(string name);

    /**
    * Imports the waypoints from JSON file.
    * 
    * @return True if the waypoints were successfully imported to a JSON file, 
    *          False if not.
    */
    void restoreFromFile();

    /**
    * Export the current waypoints to a JSON file.
    * 
    * @return True if the waypoints were successfully exported to a JSON file, 
    *          False if not.
    */
    bool saveToFile();

    string distanceAndBearing(string waypoint1, string waypoint2);

    /**
    * This method collects all the the waypoint names in the library and returns them.
    * 
    * @return An array of strings with all the waypoint names in the library.
    */
    std::vector<string> getNames();


};