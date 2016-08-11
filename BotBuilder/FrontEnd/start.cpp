#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Display.H>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>

// GLOBALS
Fl_Window *win = NULL;
Fl_Input        *G_maxvelocity = NULL;
Fl_Input        *G_deltav = NULL;
Fl_Input        *G_unitlength = NULL;
Fl_Input        *G_unitdensity = NULL;
Fl_Input        *G_unitradius = NULL;
Fl_Input        *G_testduration = NULL;
Fl_File_Chooser *G_chooser    = NULL;

void Next_CB(Fl_Widget*w, void*data) {
    setenv("modelNo","1",1);
    setenv("max_vel",G_maxvelocity->value(),1);
    setenv("delta_v",G_deltav->value(),1);
    setenv("curr_vel","0",1);
    setenv("unit_len",G_unitlength->value(),1);
    setenv("unit_den",G_unitdensity->value(),1);
    setenv("unit_rad",G_unitradius->value(),1);
    setenv("test_dur",G_testduration->value(),1);
    setenv("curr_line","0",1);
    setenv("curr_iter","0",1);


   std::ofstream myfile;
   myfile.open ("/tmp/debug.txt");
   myfile << "----------------------------start.cpp---------------------------------";
   myfile << "\n";
   myfile << "modelNo: " << getenv("modelNo") << "\n";
   myfile << "max_vel: " << getenv("max_vel") << "\n";
   myfile << "delta_v: " << getenv("delta_v") << "\n";
   myfile << "curr_vel: " << getenv("curr_vel") << "\n";
   myfile << "unit_len: " << getenv("unit_len") << "\n";
   myfile << "unit_den: " << getenv("unit_den") << "\n";
   myfile << "unit_rad: " << getenv("unit_rad") << "\n";
   myfile << "test_dur: " << getenv("test_dur") << "\n";
   myfile << "curr_line: " << getenv("curr_line") << "\n";
   myfile << "curr_iter: " << getenv("curr_iter") << "\n";
   myfile.close();
    

	


   std::string line=getenv("BUILDER_SCRIPT_PATH");
   line+="/init.sh";
    
    std::cout << "execling" << "/n";
    execl(line.c_str(),line.c_str(),0);
	
    
}

void Exit_CB(Fl_Widget*w, void*data) {
    exit(0);
}

int main() {
     win = new Fl_Window(425, 325, "Bot Builder");

     int y = 10;

     G_maxvelocity = new Fl_Input(200,y,200,25,"Maximum Velocity:");
     G_maxvelocity->value("");
     y+=30;

     G_deltav = new Fl_Input(200,y,200,25,"Change in velocity per test:");
     G_deltav->value("");
     y+=30;
     
     G_unitlength = new Fl_Input(200,y,200,25,"Unit Length(SI):");
     G_unitlength->value("");
     y+=30;

     G_unitdensity = new Fl_Input(200,y,200,25,"Unit Density(SI):");
     G_unitdensity->value("");
     y+=30;

     G_unitradius = new Fl_Input(200,y,200,25,"Unit Radius(SI):");
     G_unitradius->value("");
     y+=30;

     G_testduration = new Fl_Input(200,y,200,25,"Test Duration:");
     G_testduration->value("");
     y+=30;

     Fl_Button *ebut = new Fl_Button(win->w()-100,win->h()-25,50,25,"Exit");
     ebut->callback(Exit_CB);


     Fl_Button *cbut = new Fl_Button(win->w()-50,win->h()-25,50,25,"Next");
     cbut->callback(Next_CB);

     win->show();

     return(Fl::run());
}
    
