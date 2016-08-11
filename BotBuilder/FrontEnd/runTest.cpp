#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Button.H>
#include <stdio.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>  
#include <stdlib.h>  
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>


Fl_Window *win = NULL;

void Exit_CB(Fl_Widget*w, void*data) {
    exit(0);
}

class SliderInput : public Fl_Group {
    Fl_Int_Input *input;
    Fl_Slider    *slider;

    // CALLBACK HANDLERS
    //    These 'attach' the input and slider's values together.
    //
    void Slider_CB2() {
        static int recurse = 0;
        if ( recurse ) { 
            return;
        } else {
            recurse = 1;
            char s[80];
            sprintf(s, "%d", (int)(slider->value() + .5));
            // fprintf(stderr, "SPRINTF(%d) -> '%s'\n", (int)(slider->value()+.5), s);
            input->value(s);          // pass slider's value to input
            recurse = 0;
        }
    }

    static void Slider_CB(Fl_Widget *w, void *data) {
        ((SliderInput*)data)->Slider_CB2();
    }

    void Input_CB2() {
        static int recurse = 0;
        if ( recurse ) {
            return;
        } else {
            recurse = 1;
            int val = 0;
            if ( sscanf(input->value(), "%d", &val) != 1 ) {
                val = 0;
            }
            // fprintf(stderr, "SCANF('%s') -> %d\n", input->value(), val);
            slider->value(val);         // pass input's value to slider
            recurse = 0;
        }
    }
    static void Input_CB(Fl_Widget *w, void *data) {
        ((SliderInput*)data)->Input_CB2();
    }

public:
    // CTOR
    SliderInput(int x, int y, int w, int h, const char *l=0) : Fl_Group(x,y,w,h,l) {
        int in_w = 40;
        input  = new Fl_Int_Input(x, y, in_w, h);
        input->callback(Input_CB, (void*)this);
        input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);

        slider = new Fl_Slider(x+in_w, y, w-in_w, h);
        slider->type(1);
        slider->callback(Slider_CB, (void*)this);

        bounds(1, 10);     // some usable default
        value(5);          // some usable default
        end();             // close the group
    }

    // MINIMAL ACCESSORS --  Add your own as needed
    int  value() const    { return((int)(slider->value() + 0.5)); }
    void value(int val)   { slider->value(val); Slider_CB2(); }
    void minumum(int val) { slider->minimum(val); }
    int  minumum() const  { return((int)slider->minimum()); }
    void maximum(int val) { slider->maximum(val); }
    int  maximum() const  { return((int)slider->maximum()); }
    void bounds(int low, int high) { slider->bounds(low, high); }
};


SliderInput *slide1 = NULL;
SliderInput *slide2 = NULL;
SliderInput *slide3 = NULL;
SliderInput *slide4 = NULL;
SliderInput *slide5 = NULL;
SliderInput *slide6 = NULL;
SliderInput *slide7 = NULL;
SliderInput *slide8 = NULL;
SliderInput *slide9 = NULL;
SliderInput *slide10 = NULL;
SliderInput *slide11 = NULL;

void Butt_CB(Fl_Widget*w, void*data) {

    double unitLen = std::stod(getenv("unit_len"));
    double unitDen = std::stod(getenv("unit_den"));
    double unitRad = std::stod(getenv("unit_rad"));
   
    double lenF1= std::stod(getenv("lenF1"));
    double lenF2= std::stod(getenv("lenF2"));

    double lenH1= std::stod(getenv("lenH1"));
    double lenH2= std::stod(getenv("lenH2"));

    double base_size_length= std::stod(getenv("base_size_length"));
    double base_size_width= std::stod(getenv("base_size_width"));
    double base_size_height= std::stod(getenv("base_size_height"));

    double density= std::stod(getenv("density"));

    double linkRad= std::stod(getenv("linkRad"));
    double footRad= std::stod(getenv("footRad"));
    double footLen= std::stod(getenv("footLen"));
    double modelNo= std::stod(getenv("modelNo"));
    modelNo++;

setenv("curr_vel", "0", 1);
   

   lenF1+=(unitLen*slide1->value());
   lenF2+=(unitLen*slide2->value());
   lenH1+=(unitLen*slide4->value());
   lenH2+=(unitLen*slide5->value());
   base_size_length+=(unitLen*slide6->value());
   base_size_width+=(unitLen*slide7->value());
   base_size_height+=(unitLen*slide8->value());
   density+=(unitDen*slide10->value());
   footRad+=(unitRad*slide11->value());
   linkRad+=(unitRad*slide9->value());
   footLen+=(unitLen*slide3->value());

   if(slide1->value()!=0 || slide2->value()!=0 || slide3->value()!=0 || slide4->value()!=0 || slide5->value()!=0 || slide6->value()!=0 || slide7->value()!=0 || slide8->value()!=0 || slide9->value()!=0 || slide11->value()!=0)
{
	setenv("KINEMATIC","true",1);
}
else
{
	setenv("KINEMATIC","false",1);
}

   std::ostringstream s;
   s << lenF1;
   std::string line=s.str();
   setenv("lenF1",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << lenF2;
   line=s.str();
   setenv("lenF2",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << lenH1;
   line=s.str();
   setenv("lenH1",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << lenH2;
   line=s.str();
   setenv("lenH2",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << base_size_length;
   line=s.str();
   setenv("base_size_length",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << base_size_width;
   line=s.str();
   setenv("base_size_width",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << base_size_height;
   line=s.str();
   setenv("base_size_height",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << footRad;
   line=s.str();
   setenv("footRad",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << linkRad;
   line=s.str();
   setenv("linkRad",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << footLen;
   line=s.str();
   setenv("footLen",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << density;
   line=s.str();
   setenv("density",line.c_str(),1);
   s.clear();
   s.str(std::string());

   s << modelNo;
   line=s.str();
   setenv("modelNo",line.c_str(),1);
   s.clear();
   s.str(std::string());

   std::string line2=getenv("BUILDER_SCRIPT_PATH");
	line2+="/generate.sh";
        char* args[] = { NULL };
   

	
        execl(line2.c_str(), line2.c_str(), (char *) 0);

	win->hide();



	
}

int main() {
    
    win = new Fl_Window(700, 500, "Bot Builder");
    
    slide1 = new SliderInput(20,200,200,25,"Front leg link 1 length");
    slide1->bounds(-100,100);       // set min/max for slider
    slide1->value(0);           // set initial value

    slide2 = new SliderInput(220,200,200,25,"Front leg link 2 length");
    slide2->bounds(-100,100);       // set min/max for slider
    slide2->value(0);           // set initial value

    slide3 = new SliderInput(420,200,200,25,"foot link length");
    slide3->bounds(-100,100);       // set min/max for slider
    slide3->value(0);           // set initial value

    slide4 = new SliderInput(20,260,200,25,"Back leg link 1 length");
    slide4->bounds(-100,100);       // set min/max for slider
    slide4->value(0);           // set initial value

    slide5 = new SliderInput(220,260,200,25,"Back leg link 2 length");
    slide5->bounds(-100,100);       // set min/max for slider
    slide5->value(0);           // set initial value

    slide6 = new SliderInput(20,320,200,25,"length of robot base");
    slide6->bounds(-100,100);       // set min/max for slider
    slide6->value(0);           // set initial value

    slide7 = new SliderInput(220,320,200,25,"width of robot base");
    slide7->bounds(-100,100);       // set min/max for slider
    slide7->value(0);           // set initial value

    slide8 = new SliderInput(420,320,200,25,"height of robot base");
    slide8->bounds(-100,100);       // set min/max for slider
    slide8->value(0);           // set initial value

    slide9 = new SliderInput(20,380,200,25,"radius of links");
    slide9->bounds(-100,100);       // set min/max for slider
    slide9->value(0);           // set initial value

    slide10 = new SliderInput(220,380,200,25,"density");
    slide10->bounds(-100,100);       // set min/max for slider
    slide10->value(0);           // set initial value

    slide11 = new SliderInput(420,380,200,25,"radius of feet");
    slide11->bounds(-100,100);       // set min/max for slider
    slide11->value(0);           // set initial value
 

	  Fl_Text_Buffer *txt_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *txt_buff2 = new Fl_Text_Buffer();
    std::string LF_1_vel=getenv("LF_X_1_vel");
    std::stringstream s;
    s << "LF leg: " << LF_1_vel << " " << getenv("LF_Y_2_vel") << " " << getenv("LF_Y_3_vel") 
      << "\n" << "RF leg: " << getenv("RF_X_1_vel") << " " << getenv("RF_Y_2_vel") << " " << getenv("RF_Y_3_vel")
      << "\n" << "LH leg: " << getenv("LH_X_1_vel") << " " << getenv("LH_Y_2_vel") << " " << getenv("LH_Y_3_vel") 
      << "\n" << "RH leg: " << getenv("RH_X_1_vel") << " " << getenv("RH_Y_2_vel") << " " << getenv("RH_Y_3_vel");

   std::cout << s.str();  
    std::cout << "\n";
     
                            
    Fl_Text_Display *disp = new Fl_Text_Display(20, 20, 100, 100,"Velocity Limit Jacobian:" );
    std::stringstream s2;
    s2 << "LF leg: " << getenv("LF_X_1_tor") << " " << getenv("LF_Y_2_tor") << " " << getenv("LF_Y_3_tor") 
      << "\n" << "RF leg: " << getenv("RF_X_1_tor") << " " << getenv("RF_Y_2_tor") << " " << getenv("RF_Y_3_tor")
      << "\n" << "LH leg: " << getenv("LH_X_1_tor")<< " " << getenv("LH_Y_2_tor") << " " << getenv("LH_Y_3_tor") 
      << "\n" << "RH leg: " << getenv("RH_X_1_tor") << " " << getenv("RH_Y_2_tor") << " " << getenv("RH_Y_3_tor");
      
std::cout << "getting environment" << getenv("LF_X_1_tor") << "\n" << "\n" << "\n";  
    txt_buff->text(s.str().c_str());
     disp->buffer(txt_buff);

    Fl_Text_Display *otherDisp = new Fl_Text_Display(200, 20, 100, 100,"Torque Limit Jacobian:" );

    txt_buff2->text(s2.str().c_str());
    otherDisp->buffer(txt_buff2);

     Fl_Button *ebut = new Fl_Button(win->w()-125,win->h()-25,50,25,"Exit");
     ebut->callback(Exit_CB);

     Fl_Button *cbut = new Fl_Button(win->w()-75,win->h()-25,75,25,"Run Test");
     cbut->callback(Butt_CB);

    win->show();
    return(Fl::run());
}
    
