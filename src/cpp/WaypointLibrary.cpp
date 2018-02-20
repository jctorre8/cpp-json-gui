#include "WaypointLibrary.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


/**
 * Copyright 201 Jean Torres,
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
 * @version January 2018
 */

/**
* No parameter constructor. Just creates an empty Vector.
*/
WaypointLibrary::WaypointLibrary(){}

/**
* Waypoint Library constructor that takes a list as an argument.
*
* @param An old list of waypoints to initialize the library.
*/
WaypointLibrary::WaypointLibrary(vector<Waypoint> oldLibrary){
    for (int i=0; i<oldLibrary.size(); i++)
        this->library.push_back(oldLibrary[i]);
}

/**
* Waypoint Library constructor that gets populated by a json file.
* 
* @param The name of the json file.
*/
WaypointLibrary::WaypointLibrary(string jsonFileName){
    
    std::ifstream infile;
    Json::Value root;
    Json::Reader reader;
    infile.open("waypoints.json");      
    string data((std::istreambuf_iterator<char>(infile)),
                 std::istreambuf_iterator<char>());  
    // close the opened file.
    infile.close();
    bool parsingSuccessful = reader.parse( data, root );
    if (!parsingSuccessful){
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return;
    }
    
    for(Json::Value::iterator i= root.begin(); i != root.end(); i++){
        std::cout << (*i)["name"].asString() << endl;
    }

    for (Json::Value::iterator i= root.begin(); i != root.end(); i++){
        Waypoint aWaypoint((*i));
        this->library.push_back(aWaypoint);
    }


}

/**
* Outputs the content of the library into a string representation of json.
* 
* @return The string json content of the library.
*/
string WaypointLibrary::toJSONstring(){
    string ret = "";
    Json::Value obj;
    for (int i = 0; i < this->library.size(); i++){
        cout << "Converting to JSON STR:" << this->library[i].name << endl;
        obj[this->library[i].name] = this->library[i].toJSONObject();
    }
    ret = obj.toStyledString();
    return ret;
}

/**
* Adds a waypoint to the library.
* 
* @param A Waypoint object to be added to the library
* @return True if successful and false if don't.
*/
void WaypointLibrary::add(Waypoint aWaypoint){
    
    this->library.push_back(aWaypoint);
}

/**
* Adds a new waypoint to the library.
* 
* @param A Waypoint object to be added to the library
* @return True if successful and false if don't.
*/
void WaypointLibrary::addNew(string lat, string lon, string ele, string name, string address){
    std::string::size_type sz;
    double latitude = std::stod (lat,&sz);
    double longitude = std::stod (lon,&sz);
    double elevation = std::stod (ele,&sz);
    Waypoint temp(latitude, longitude, elevation, name, address);
    
    this->library.push_back(temp);
}

void WaypointLibrary::updateWaypoint(string lat, string lon, string ele, string name, string address){
    std::string::size_type sz;
    double latitude = std::stod (lat,&sz);
    double longitude = std::stod (lon,&sz);
    double elevation = std::stod (ele,&sz);
    Waypoint *temp = this->get(name);
    temp->name = name;
    temp->address = address;
    temp->lat = latitude;
    temp->lon = longitude;
    temp->ele = elevation;  
    
}

/**
* Removes the waypoint with the matching name.
* 
* @param  The name of the waypoint that needs to be removed.
* @return True if the waypoint was removed successfully, false if don't.
*/
void WaypointLibrary::remove(string name){
    for(int i = 0; i < library.size(); i++){
        Waypoint temp = library[i];
        if(name.compare(temp.name) == 0){
            library.erase(library.begin()+i);
        }
    }
}

/**
* Get the waypoint that matches the given name.
* 
* @param  The the name of the waypoint that needs to be returned.
* @return The waypoint that has the name.
*/
Waypoint * WaypointLibrary::get(string name){
    Waypoint * toReturn = NULL;
    for(int i = 0; i < library.size(); i++){
        if(name.compare(library[i].name) == 0){
            toReturn = &library[i];
            return toReturn;
        }
    }
    return toReturn;
}

/**
* Imports the waypoints from JSON file.
* 
* @return True if the waypoints were successfully imported to a JSON file, 
*          False if not.
*/
void WaypointLibrary::restoreFromFile(){
    this->library.clear();
    std::ifstream infile;
    Json::Value root;
    Json::Reader reader;
    infile.open("waypoints.json");      
    string data((std::istreambuf_iterator<char>(infile)),
                 std::istreambuf_iterator<char>());  
    // close the opened file.
    infile.close();
    bool parsingSuccessful = reader.parse( data, root );
    if (!parsingSuccessful){
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return;
    }
    
    for(Json::Value::iterator i= root.begin(); i != root.end(); i++){
        std::cout << (*i)["name"].asString() << endl;
    }

    for (Json::Value::iterator i= root.begin(); i != root.end(); i++){
        Waypoint aWaypoint((*i));
        this->library.push_back(aWaypoint);
    }
    
    std::cout << "Done importing waypoints in from waypoints.json" << endl;
    
}

/**
* Export the current waypoints to a JSON file.
* 
* @return True if the waypoints were successfully exported to a JSON file, 
*          False if not.
*/
bool WaypointLibrary::saveToFile(){
        
        ofstream outfile;
        outfile.open("waypoints.json");
        string data = this->toJSONstring();
        // write inputted data into the file.
        outfile << data << endl;
        outfile.close();
        cout << "Done exporting library to waypoints.json" << endl;
        return true;
}

/**
* This method collects all the the waypoint names in the library and returns them.
* 
* @return An array of strings with all the waypoint names in the library.
*/
std::vector<string> WaypointLibrary::getNames(){
    
    for(int i = 0; i < library.size(); i++){
        this->names.push_back(this->library[i].name);
    }
    return this->names;
}


