#include "Waypoint.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

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
void split(vector<string> & aStringVector,  /* return value */
           const string & aString,
           const string & aDelimiter) {
   size_t  start = 0, end = 0;
   while ( end != string::npos) {
      end = aString.find(aDelimiter, start);
      // If at end, use length=maxLength.  Else use length=end-start.
      aStringVector.push_back(aString.substr(start,
                          (end == string::npos) ? string::npos : end - start));
      // If at end, use start=maxSize.  Else use start=end+delimiter.
      start = ((end > (string::npos - aDelimiter.size()) )
               ? string::npos : end + aDelimiter.size());
   }
}

int main () {
   std::vector<Waypoint> points;
   Waypoint wp;
   try {
      string inLine;
      while(true){
         std::cout << "Enter waypoint lat lon ele name or calc >";
         std::getline (std::cin, inLine);
         vector<string> tokens;
         split(tokens, inLine, " ");
         if(tokens.size()>=3){
            double lat, lon, ele;
            string name;
            istringstream latStream(tokens[0]);
            latStream >> lat;
            istringstream lonStream(tokens[1]);
            lonStream >> lon;
            istringstream eleStream(tokens[2]);
            eleStream >> ele;
            name = tokens[3];
            wp.setValues(lat, lon, ele, name);
            points.push_back(wp);
            wp.print();
         } else if(tokens[0]=="calc"){
            Waypoint next, last;
            cout << "points.size() is " << points.size() << endl;
            for (unsigned it=0; it != points.size(); it++){
               next = points[it];
               if(last.name.compare("") != 0){
//               if(last != NULL){
                  cout << "GC distance from " << last.name << " to "
                       << next.name <<  " is " << 
                          last.distanceGCTo(next, last.STATUTE)
                       << " bearing "
                       << last.bearingGCInitTo(next, last.STATUTE)
                       << endl;
               }
               last = next;
            }
            break;
         }
      }
   } catch (exception e) {
      cerr << e.what() << endl;
   }
   return 0;
}
