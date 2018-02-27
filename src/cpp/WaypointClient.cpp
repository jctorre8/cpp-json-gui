#include "WaypointGUI.cpp"
#include "WaypointLibrary.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Multiline_Input.H>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

/**
 * Copyright (c) 2018 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ FLTK client UI for Waypoint management.
 * This class extends the Gui component class WaypointGUI and demonstrates
 * sample control functions that respond to button clicks drop-down selects.
 * This software is meant to run on Linux and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @file    samplemain.cpp
 * @date    January, 2018
 **/
class WaypointClient : public WaypointGUI {

   WaypointLibrary * library;

   /** ClickedX is one of the callbacks for GUI controls.
    * Callbacks need to be static functions. But, static functions
    * cannot directly access instance data. This program uses "userdata"
    * to get around that by passing the instance to the callback
    * function. The callback then accesses whatever GUI control object
    * that it needs for implementing its functionality.
    */
   static void ClickedX(Fl_Widget * w, void * userdata) {
      std::cout << "You clicked Exit" << std::endl;
      exit(1);
   }

   static void ClickedRemoveWP(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;
      Fl_Input_Choice * theWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      std::string selected(theWPChoice->value());
      std::cout << "You clicked the remove waypoint button with "
                << selected
                << std::endl;
      for (int i=0; i < theWPChoice->menubutton()->size(); i++ ) {
         const Fl_Menu_Item &item = theWPChoice->menubutton()->menu()[i];
         if(!selected.compare(item.label())){  // if they are equal
            theWPChoice->menubutton()->remove(i);
            toWPChoice->menubutton()->remove(i);
            cout << "removed " << selected << endl;
            break;
         }
      }
      anInstance->library->remove(selected);
      if(theWPChoice->menubutton()->size()>0){
         theWPChoice->value(theWPChoice->menubutton()->menu()[0].label());
         toWPChoice->value(theWPChoice->menubutton()->menu()[0].label());
      }else{
         theWPChoice->value("");
         toWPChoice->value("");
      }

  }

   static void ClickedAddWP(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      Fl_Input * theAddress = anInstance->addrIn;
      std::string lat(theLat->value());
      // what follows is not expedient, but shows how to convert to/from
      // double and formatted C and C++ strings.
      double latNum = atof(lat.c_str());  //convert from string to double
      char latFormat[10];
      sprintf(latFormat,"%4.4f",latNum);  //format the double into a C string
      std::string latCppStr(latFormat);   //convert formatted C str to C++ str

      std::string lon(theLon->value());
      std::string ele(theEle->value());
      std::string name(theName->value());
      std::string address(theAddress->value());
      std::cout << "You clicked the add waypoint button lat: "<< latCppStr
                << " lon: " << lon << " ele: " << ele << " name: "
                << name << std::endl;
      anInstance->library->addNew(lat, lon, ele, name, address);
      fromWPChoice->add(name.c_str());
      toWPChoice->add(name.c_str());
      fromWPChoice->value(name.c_str());
   }

   static void ClickedModWP(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      Fl_Input * theAddress = anInstance->addrIn;
      std::string lat(theLat->value());
      // what follows is not expedient, but shows how to convert to/from
      // double and formatted C and C++ strings.
      double latNum = atof(lat.c_str());  //convert from string to double
      char latFormat[10];
      sprintf(latFormat,"%4.4f",latNum);  //format the double into a C string
      std::string latCppStr(latFormat);   //convert formatted C str to C++ str

      std::string lon(theLon->value());
      std::string ele(theEle->value());
      std::string name(theName->value());
      std::string address(theAddress->value());
      std::cout << "You clicked the modify waypoint button lat: "<< latCppStr
                << " lon: " << lon << " ele: " << ele << " name: "
                << name << std::endl;
      anInstance->library->updateWaypoint(lat, lon, ele, name, address);
      fromWPChoice->value(name.c_str());
   }

   static void ClickedSave(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;
      
      anInstance->library->saveToFile();
      
  }

  static void ClickedRefresh(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;     

      Fl_Input_Choice * theWPChoice = anInstance->frWps;
      std::cout << "You clicked the restore button"
                << std::endl;
      
      anInstance->library->restoreFromFile();
      
      vector<string> names = anInstance->library->getNames();
      for(vector<string>::iterator i= names.begin(); i != names.end(); i++){
        int size = theWPChoice->menubutton()->size();
        bool alreadyIn = false;
        for (int j=0; j < size-1; j++ ) {
          const Fl_Menu_Item &item = theWPChoice->menubutton()->menu()[j];
          if(!(*i).compare(item.label())){
            alreadyIn = true;
            break;
          }

        }
        if(!alreadyIn){
          anInstance->frWps->add((*i).c_str());
          anInstance->toWps->add((*i).c_str()); 
        }
              
      }
      if(theWPChoice->menubutton()->size()>0){
         theWPChoice->value(theWPChoice->menubutton()->menu()[0].label());
      }else{
         theWPChoice->value("");
      }
  }

   static void SelectedFromWP(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;
      Fl_Input_Choice * frWps = anInstance->frWps;
      std::string selected(frWps->value());
      std::cout << "You changed the selection in the Fl_Input_Choice from to the value "
                << selected
                << std::endl;
   }

   static void ClickedDistBear(Fl_Widget * w, void * userdata) {
      WaypointClient* anInstance = (WaypointClient*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      Fl_Input * distBearIn = anInstance->distBearIn;

      std::string wpnt1(fromWPChoice->value());
      std::string wpnt2(toWPChoice->value());
      std::string distBear(anInstance->library->distanceAndBearing(wpnt1, wpnt2));

      distBearIn->value(distBear.c_str());

      std::cout << "You changed the selection in the Fl_Input_Choice from to the value "
                << distBear
                << std::endl;
   }

public:
   WaypointClient(const char * name = 0) : WaypointGUI(name) {
      library = new WaypointLibrary("waypoints.json");
      vector<string> names = library->getNames();
      for(vector<string>::iterator i= names.begin(); i != names.end(); i++){
        this->frWps->add((*i).c_str());
        this->toWps->add((*i).c_str());        
      }
      removeWPButt->callback(ClickedRemoveWP, (void*)this);
      modWPButt->callback(ClickedModWP, (void*)this);
      addWPButt->callback(ClickedAddWP, (void*)this);
      frWps->callback(SelectedFromWP, (void*)this);
      saveButt->callback(ClickedSave, (void*)this);
      refreshButt->callback(ClickedRefresh, (void*)this);
      distBearButt->callback(ClickedDistBear, (void*)this);
      callback(ClickedX);
   }

   ~WaypointClient() {
      delete(library);
   }
};

int main() {
   WaypointClient cm("Jean Torres's Waypoint Browser");
   return (Fl::run());
}
