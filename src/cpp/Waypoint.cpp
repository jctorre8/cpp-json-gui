#include "Waypoint.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>

/**
 * Copyright 2018 Tim Lindquist,
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
 * Purpose: demonstrate classes, alloc, init, in the context of
 * distance and direction calculations from one earth position (waypoint)
 * to another.
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version January 2018
 */
Waypoint::Waypoint(){
   lat = lon = ele = 0;
   name = "";
   address = "";
}

Waypoint::Waypoint(const Waypoint & wp){
   lat = wp.lat;
   lon = wp.lon;
   ele = wp.ele; 
   name = wp.name;
   address = wp.address;
}

Waypoint::Waypoint(Json::Value object){
   lat = object.get("lat",0).asDouble();
   lon = object.get("lon",0).asDouble();
   ele = object.get("ele",0).asDouble(); 
   name = object.get("name","").asString();
   address = object.get("adress","").asString();
}

Waypoint::Waypoint(double aLat, double aLon, double anElevation, string aName, string aAddress) {
   lat = aLat;
   lon = aLon;
   ele = anElevation;
   name = aName;
   address = aAddress;
}

Waypoint::~Waypoint() {
   //cout << "Waypoint destructor.\n";
   lat=lon=ele=0; name=""; address="";
}

void Waypoint::setValues(double aLat, double aLon, double anElevation,
                         string aName) {
   lat = aLat;
   lon = aLon;
   ele = anElevation;
   name = aName;
}

double Waypoint::distanceGCTo(Waypoint wp, int scale){
   double ret = 0.0;
   // ret is in kilometers. switch to either Statute or Nautical?
   double lat1 = this->toRadians(this->lat);
   double lat2 = this->toRadians(wp.lat);
   double deltaLat = this->toRadians(wp.lat-this->lat);
   double deltaLon = this->toRadians(wp.lon-this->lon);
   double a = std::sin(deltaLat/2)*std::sin(deltaLat/2) +
                 std::cos(lat1)*std::cos(lat2)*
                 std::sin(deltaLon/2)*std::sin(deltaLon/2);
   double c = 2 * atan2(std::sqrt(a), std::sqrt(1-a));
   ret = radiusE * c;
   switch(scale) {
   case STATUTE:
      ret = ret * 0.62137119;
      break;
   case NAUTICAL:
      ret = ret * 0.5399568;
      break;
   }
   return ret;
}

double Waypoint::bearingGCInitTo(Waypoint wp, int scale){
   double ret = 0.0;
   double lat1 = this->toRadians(this->lat);
   double lat2 = this->toRadians(wp.lat);
   double deltaLat = this->toRadians(wp.lat-this->lat);
   double deltaLon = this->toRadians(wp.lon-this->lon);
   double y = std::sin(deltaLon) * std::cos(lat2);
   double x = std::cos(lat1) * std::sin(lat2) - 
                 std::sin(lat1) * std::cos(lat2) * std::cos(deltaLat);
   double brng = atan2(y,x);
   ret = this->toDegrees(brng);
   return ret;
}

Json::Value Waypoint::toJSONObject(){
   Json::Value  ret;
   ret["lat"] = this->lat;
   ret["lon"] = this->lon;
   ret["ele"] = this->ele;
   ret["name"] = this->name;
   ret["address"] = this->address;

   return ret;
}

void Waypoint::print(){
   cout << "Waypoint " << name << " lat "
        << lat << " lon " << lon << "\n";
}
