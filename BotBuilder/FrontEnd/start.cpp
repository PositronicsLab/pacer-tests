#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Display.H>

// GLOBALS
Fl_Input        *G_inpdirname = NULL;
Fl_Input        *G_maxvelocity = NULL;
Fl_Input        *G_deltav = NULL;
Fl_Input        *G_unitlength = NULL;
Fl_Input        *G_unitdensity = NULL;
Fl_Input        *G_unitradius = NULL;
Fl_Input        *G_testduration = NULL;
Fl_File_Chooser *G_chooser    = NULL;

void Next_CB(Fl_Widget*w, void*data) {
    setenv("filename",G_inpdirname->value(),1);
    setenv("max_vel",G_maxvelocity->value(),1);
    setenv("delta_v",G_deltav->value(),1);
    setenv("curr_vel","0",1);
    setenv("unit_len",G_unitlength->value(),1);
    setenv("unit_den",G_unitdensity->value(),1);
    setenv("unit_rad",G_unitradius->value(),1);
    setenv("test_dur",G_testduration->value(),1);
    setenv("curr_line","0",1);
    setenv("curr_iter","0",1);

    system("./init.sh");
    exit(0);
}

void Exit_CB(Fl_Widget*w, void*data) {
    exit(0);
}

void Butt_CB(Fl_Widget*w, void*data) {
    const char *directory = G_inpdirname->value();

    if ( ! G_chooser ) {
        G_chooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "");
    }

    G_chooser->directory(directory[0]?directory:NULL);
    G_chooser->show();

    // Block until user picks something.
    //     (The other way to do this is to use a callback())
    //
    while(G_chooser->shown()) {
        Fl::wait();
    }

    // Print the results
    if ( G_chooser->value() == NULL ) {
        fprintf(stderr, "(User hit 'Cancel')\n");
        return;
    }

    fprintf(stderr, "DIRECTORY: '%s'\n", G_chooser->directory());
    fprintf(stderr, "    VALUE: '%s'\n", G_chooser->value());
    G_inpdirname->value(G_chooser->value());
}

int main() {
     Fl_Window *win = new Fl_Window(425, 325, "Bot Builder");

     int y = 10;
     G_inpdirname = new Fl_Input(80,y,200,25,"Filename");
     G_inpdirname->value("");
     y+=90;

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

     Fl_Text_Display *disp = new Fl_Text_Display(80, 80, 0, 0, "Test Conditions:");

     Fl_Button *ebut = new Fl_Button(win->w()-100,win->h()-25,50,25,"Exit");
     ebut->callback(Exit_CB);

     Fl_Button *bbut = new Fl_Button(300,10,80,25,"Browse");
     bbut->callback(Butt_CB);

     Fl_Button *cbut = new Fl_Button(win->w()-50,win->h()-25,50,25,"Next");
     cbut->callback(Next_CB);

     win->show();

     return(Fl::run());
}
    
