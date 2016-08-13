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
SliderInput *slide12 = NULL;
SliderInput *slide13 = NULL;
SliderInput *slide14 = NULL;

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
    
    win = new Fl_Window(1300, 650, "Bot Builder");
    int height=80;
    slide1 = new SliderInput(0,height,200,25,"Front leg link 1 length");
    slide1->bounds(-100,100);       // set min/max for slider
    slide1->value(0);           // set initial value
    height+=40; 

    slide2 = new SliderInput(0,height,200,25,"Front leg link 2 length");
    slide2->bounds(-100,100);       // set min/max for slider
    slide2->value(0);           // set initial value
    height+=40; 

    slide3 = new SliderInput(0,height,200,25,"Front foot link length");
    slide3->bounds(-100,100);       // set min/max for slider
    slide3->value(0);           // set initial value
    height+=40; 

    slide4 = new SliderInput(0,height,200,25,"Back leg link 1 length");
    slide4->bounds(-100,100);       // set min/max for slider
    slide4->value(0);           // set initial value
    height+=40; 

    slide5 = new SliderInput(0,height,200,25,"Back leg link 2 length");
    slide5->bounds(-100,100);       // set min/max for slider
    slide5->value(0);           // set initial value
    height+=40; 

    slide6 = new SliderInput(0,height,200,25,"Back foot link length");
    slide6->bounds(-100,100);       // set min/max for slider
    slide6->value(0);           // set initial value
    height+=40; 

    slide7 = new SliderInput(0,height,200,25,"length of robot base");
    slide7->bounds(-100,100);       // set min/max for slider
    slide7->value(0);           // set initial value
    height+=40; 

    slide8 = new SliderInput(0,height,200,25,"width of robot base");
    slide8->bounds(-100,100);       // set min/max for slider
    slide8->value(0);           // set initial value
    height+=40; 

    slide9 = new SliderInput(0,height,200,25,"height of robot base");
    slide9->bounds(-100,100);       // set min/max for slider
    slide9->value(0);           // set initial value
    height+=40; 

    slide10 = new SliderInput(0,height,200,25,"radius of front links");
    slide10->bounds(-100,100);       // set min/max for slider
    slide10->value(0);           // set initial value
    height+=40; 

    slide11 = new SliderInput(0,height,200,25,"radius of back links");
    slide11->bounds(-100,100);       // set min/max for slider
    slide11->value(0);           // set initial value
    height+=40; 

    slide12 = new SliderInput(0,height,200,25,"density");
    slide12->bounds(-100,100);       // set min/max for slider
    slide12->value(0);           // set initial value
    height+=40; 

    slide13 = new SliderInput(0,height,200,25,"radius of front feet");
    slide13->bounds(-100,100);       // set min/max for slider
    slide13->value(0);           // set initial value
    height+=40; 
    slide14 = new SliderInput(0,height,200,25,"radius of back feet");
    slide14->bounds(-100,100);       // set min/max for slider
    slide14->value(0);           // set initial value
    
 

	  Fl_Text_Buffer *main_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *main_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *one_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *one_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *two_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *two_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *three_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *three_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *four_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *four_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *five_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *five_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *six_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *six_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *seven_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *seven_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *eight_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *eight_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *nine_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *nine_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *ten_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *ten_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *eleven_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *eleven_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *twelve_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *twelve_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *thirteen_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *thirteen_tor_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *fourteen_vel_buff = new Fl_Text_Buffer();
          Fl_Text_Buffer *fourteen_tor_buff = new Fl_Text_Buffer();
       
          Fl_Text_Display *main_vel_disp = new Fl_Text_Display(200, 20, 500, 40,"Velocity Limit Jacobian:" );
          Fl_Text_Display *main_tor_disp = new Fl_Text_Display(700, 20, 500, 40,"Torque Limit Jacobian:" );
          Fl_Text_Display *one_vel_disp = new Fl_Text_Display(200, 80, 500, 40);
          Fl_Text_Display *one_tor_disp = new Fl_Text_Display(700, 80, 500, 40);
          Fl_Text_Display *two_vel_disp = new Fl_Text_Display(200, 120, 500, 40);
          Fl_Text_Display *two_tor_disp = new Fl_Text_Display(700, 120, 500, 40);
          Fl_Text_Display *three_vel_disp = new Fl_Text_Display(200, 160, 500, 40);
          Fl_Text_Display *three_tor_disp = new Fl_Text_Display(700, 160, 500, 40);
          Fl_Text_Display *four_vel_disp = new Fl_Text_Display(200, 200, 500, 40);
          Fl_Text_Display *four_tor_disp = new Fl_Text_Display(700, 200, 500, 40);
          Fl_Text_Display *five_vel_disp = new Fl_Text_Display(200, 240, 500, 40);
          Fl_Text_Display *five_tor_disp = new Fl_Text_Display(700, 240, 500, 40);
          Fl_Text_Display *six_vel_disp = new Fl_Text_Display(200, 280, 500, 40);
          Fl_Text_Display *six_tor_disp = new Fl_Text_Display(700, 280, 500, 40);
          Fl_Text_Display *seven_vel_disp = new Fl_Text_Display(200, 320, 500, 40);
          Fl_Text_Display *seven_tor_disp = new Fl_Text_Display(700, 320, 500, 40);
          Fl_Text_Display *eight_vel_disp = new Fl_Text_Display(200, 360, 500, 40);
          Fl_Text_Display *eight_tor_disp = new Fl_Text_Display(700, 360, 500, 40);
          Fl_Text_Display *nine_vel_disp = new Fl_Text_Display(200, 400, 500, 40);
          Fl_Text_Display *nine_tor_disp = new Fl_Text_Display(700, 400, 500, 40);
          Fl_Text_Display *ten_vel_disp = new Fl_Text_Display(200, 440, 500, 40);
          Fl_Text_Display *ten_tor_disp = new Fl_Text_Display(700, 440, 500, 40);
          Fl_Text_Display *eleven_vel_disp = new Fl_Text_Display(200, 480, 500, 40);
          Fl_Text_Display *eleven_tor_disp = new Fl_Text_Display(700, 480, 500, 40);
          Fl_Text_Display *twelve_vel_disp = new Fl_Text_Display(200, 520, 500, 40);
          Fl_Text_Display *twelve_tor_disp = new Fl_Text_Display(700, 520, 500, 40);
          Fl_Text_Display *thirteen_vel_disp = new Fl_Text_Display(200, 560, 500, 40);
          Fl_Text_Display *thirteen_tor_disp = new Fl_Text_Display(700, 560, 500, 40);
          Fl_Text_Display *fourteen_vel_disp = new Fl_Text_Display(200, 600, 500, 40);
          Fl_Text_Display *fourteen_tor_disp = new Fl_Text_Display(700, 600, 500, 40);
    
    std::stringstream main_vel;
    main_vel << /*getenv("LF_X_1_vel") << " " <<*/ getenv("LF_Y_2_vel") << " " << getenv("LF_Y_3_vel") 
      << " " << /*getenv("RF_X_1_vel") << " " <<*/ getenv("RF_Y_2_vel") << " " << getenv("RF_Y_3_vel")
      << " " << /*getenv("LH_X_1_vel") << " " <<*/ getenv("LH_Y_2_vel") << " " << getenv("LH_Y_3_vel") 
      << " " << /*getenv("RH_X_1_vel") << " " <<*/ getenv("RH_Y_2_vel") << " " << getenv("RH_Y_3_vel");
     main_vel_buff->text(main_vel.str().c_str());
     main_vel_disp->buffer(main_vel_buff);
     
    

    std::stringstream main_tor;
    main_tor << /*getenv("LF_X_1_tor") << " " <<*/ getenv("LF_Y_2_tor") << " " << getenv("LF_Y_3_tor") 
       << " " << /*getenv("RF_X_1_tor") << " " <<*/ getenv("RF_Y_2_tor") << " " << getenv("RF_Y_3_tor")
       << " " << /*getenv("LH_X_1_tor")<< " " <<*/ getenv("LH_Y_2_tor") << " " << getenv("LH_Y_3_tor") 
       << " " << /*getenv("RH_X_1_tor") << " " <<*/ getenv("RH_Y_2_tor") << " " << getenv("RH_Y_3_tor");
    main_tor_buff->text(main_tor.str().c_str());
    main_tor_disp->buffer(main_tor_buff);


     std::stringstream one_vel;
    one_vel << /*getenv("1_LF_X_1_vel") << " " <<*/ getenv("1_LF_Y_2_vel") << " " << getenv("1_LF_Y_3_vel") 
      << " " << /*getenv("1_RF_X_1_vel") << " " <<*/ getenv("1_RF_Y_2_vel") << " " << getenv("1_RF_Y_3_vel")
      << " " << /*getenv("1_LH_X_1_vel") << " " <<*/ getenv("1_LH_Y_2_vel") << " " << getenv("1_LH_Y_3_vel") 
      << " " << /*getenv("1_RH_X_1_vel") << " " <<*/ getenv("1_RH_Y_2_vel") << " " << getenv("1_RH_Y_3_vel");
     one_vel_buff->text(one_vel.str().c_str());
     one_vel_disp->buffer(one_vel_buff);
     
    std::stringstream one_tor;
    one_tor << /*getenv("1_LF_X_1_tor") << " " <<*/ getenv("1_LF_Y_2_tor") << " " << getenv("1_LF_Y_3_tor") 
       << " " << /*getenv("1_RF_X_1_tor") << " " <<*/ getenv("1_RF_Y_2_tor") << " " << getenv("1_RF_Y_3_tor")
       << " " << /*getenv("1_LH_X_1_tor")<< " " <<*/ getenv("1_LH_Y_2_tor") << " " << getenv("1_LH_Y_3_tor") 
       << " " << /*getenv("1_RH_X_1_tor") << " " <<*/ getenv("1_RH_Y_2_tor") << " " << getenv("1_RH_Y_3_tor");
    one_tor_buff->text(one_tor.str().c_str());
    one_tor_disp->buffer(one_tor_buff);


    std::stringstream two_vel;
    two_vel << /*getenv("2_LF_X_1_vel") << " " <<*/ getenv("2_LF_Y_2_vel") << " " << getenv("2_LF_Y_3_vel") 
      << " " << /*getenv("2_RF_X_1_vel") << " " <<*/ getenv("2_RF_Y_2_vel") << " " << getenv("2_RF_Y_3_vel")
      << " " << /*getenv("2_LH_X_1_vel") << " " <<*/ getenv("2_LH_Y_2_vel") << " " << getenv("2_LH_Y_3_vel") 
      << " " << /*getenv("2_RH_X_1_vel") << " " <<*/ getenv("2_RH_Y_2_vel") << " " << getenv("2_RH_Y_3_vel");
     two_vel_buff->text(two_vel.str().c_str());
     two_vel_disp->buffer(two_vel_buff);
     
    std::stringstream two_tor;
    two_tor << /*getenv("2_LF_X_1_tor") << " " <<*/ getenv("2_LF_Y_2_tor") << " " << getenv("2_LF_Y_3_tor") 
       << " " << /*getenv("2_RF_X_1_tor") << " " <<*/ getenv("2_RF_Y_2_tor") << " " << getenv("2_RF_Y_3_tor")
       << " " << /*getenv("2_LH_X_1_tor")<< " " <<*/ getenv("2_LH_Y_2_tor") << " " << getenv("2_LH_Y_3_tor") 
       << " " << /*getenv("2_RH_X_1_tor") << " " <<*/ getenv("2_RH_Y_2_tor") << " " << getenv("2_RH_Y_3_tor");
    two_tor_buff->text(two_tor.str().c_str());
    two_tor_disp->buffer(two_tor_buff);

    std::stringstream three_vel;
    three_vel << /*getenv("3_LF_X_1_vel") << " " <<*/ getenv("3_LF_Y_2_vel") << " " << getenv("3_LF_Y_3_vel") 
      << " " << /*getenv("3_RF_X_1_vel") << " " <<*/ getenv("3_RF_Y_2_vel") << " " << getenv("3_RF_Y_3_vel")
      << " " << /*getenv("3_LH_X_1_vel") << " " <<*/ getenv("3_LH_Y_2_vel") << " " << getenv("3_LH_Y_3_vel") 
      << " " << /*getenv("3_RH_X_1_vel") << " " <<*/ getenv("3_RH_Y_2_vel") << " " << getenv("3_RH_Y_3_vel");
     three_vel_buff->text(three_vel.str().c_str());
     three_vel_disp->buffer(three_vel_buff);
     
    std::stringstream three_tor;
    three_tor << /*getenv("3_LF_X_1_tor") << " " <<*/ getenv("3_LF_Y_2_tor") << " " << getenv("3_LF_Y_3_tor") 
       << " " << /*getenv("3_RF_X_1_tor") << " " <<*/ getenv("3_RF_Y_2_tor") << " " << getenv("3_RF_Y_3_tor")
       << " " << /*getenv("3_LH_X_1_tor")<< " " <<*/ getenv("3_LH_Y_2_tor") << " " << getenv("3_LH_Y_3_tor") 
       << " " << /*getenv("3_RH_X_1_tor") << " " <<*/ getenv("3_RH_Y_2_tor") << " " << getenv("3_RH_Y_3_tor");
    three_tor_buff->text(three_tor.str().c_str());
    three_tor_disp->buffer(three_tor_buff);


    std::stringstream four_vel;
    four_vel << /*getenv("4_LF_X_1_vel") << " " <<*/ getenv("4_LF_Y_2_vel") << " " << getenv("4_LF_Y_3_vel") 
      << " " << /*getenv("4_RF_X_1_vel") << " " <<*/ getenv("4_RF_Y_2_vel") << " " << getenv("4_RF_Y_3_vel")
      << " " << /*getenv("4_LH_X_1_vel") << " " <<*/ getenv("4_LH_Y_2_vel") << " " << getenv("4_LH_Y_3_vel") 
      << " " << /*getenv("4_RH_X_1_vel") << " " <<*/ getenv("4_RH_Y_2_vel") << " " << getenv("4_RH_Y_3_vel");
     four_vel_buff->text(four_vel.str().c_str());
     four_vel_disp->buffer(four_vel_buff);
     
    std::stringstream four_tor;
    four_tor << /*getenv("4_LF_X_1_tor") << " " <<*/ getenv("4_LF_Y_2_tor") << " " << getenv("4_LF_Y_3_tor") 
       << " " << /*getenv("4_RF_X_1_tor") << " " <<*/ getenv("4_RF_Y_2_tor") << " " << getenv("4_RF_Y_3_tor")
       << " " << /*getenv("4_LH_X_1_tor")<< " " <<*/ getenv("4_LH_Y_2_tor") << " " << getenv("4_LH_Y_3_tor") 
       << " " << /*getenv("4_RH_X_1_tor") << " " <<*/ getenv("4_RH_Y_2_tor") << " " << getenv("4_RH_Y_3_tor");
    four_tor_buff->text(four_tor.str().c_str());
    two_tor_disp->buffer(four_tor_buff);

    std::stringstream five_vel;
    five_vel << /*getenv("5_LF_X_1_vel") << " " <<*/ getenv("5_LF_Y_2_vel") << " " << getenv("5_LF_Y_3_vel") 
      << " " << /*getenv("5_RF_X_1_vel") << " " <<*/ getenv("5_RF_Y_2_vel") << " " << getenv("5_RF_Y_3_vel")
      << " " << /*getenv("5_LH_X_1_vel") << " " <<*/ getenv("5_LH_Y_2_vel") << " " << getenv("5_LH_Y_3_vel") 
      << " " << /*getenv("5_RH_X_1_vel") << " " <<*/ getenv("5_RH_Y_2_vel") << " " << getenv("5_RH_Y_3_vel");
     five_vel_buff->text(five_vel.str().c_str());
     five_vel_disp->buffer(five_vel_buff);
     
    std::stringstream five_tor;
    five_tor << /*getenv("5_LF_X_1_tor") << " " <<*/ getenv("5_LF_Y_2_tor") << " " << getenv("5_LF_Y_3_tor") 
       << " " << /*getenv("5_RF_X_1_tor") << " " <<*/ getenv("5_RF_Y_2_tor") << " " << getenv("5_RF_Y_3_tor")
       << " " << /*getenv("5_LH_X_1_tor")<< " " <<*/ getenv("5_LH_Y_2_tor") << " " << getenv("5_LH_Y_3_tor") 
       << " " << /*getenv("5_RH_X_1_tor") << " " <<*/ getenv("5_RH_Y_2_tor") << " " << getenv("5_RH_Y_3_tor");
    five_tor_buff->text(five_tor.str().c_str());
    five_tor_disp->buffer(five_tor_buff);


    std::stringstream six_vel;
    six_vel << /*getenv("6_LF_X_1_vel") << " " <<*/ getenv("6_LF_Y_2_vel") << " " << getenv("6_LF_Y_3_vel") 
      << " " << /*getenv("6_RF_X_1_vel") << " " <<*/ getenv("6_RF_Y_2_vel") << " " << getenv("6_RF_Y_3_vel")
      << " " << /*getenv("6_LH_X_1_vel") << " " <<*/ getenv("6_LH_Y_2_vel") << " " << getenv("6_LH_Y_3_vel") 
      << " " << /*getenv("6_RH_X_1_vel") << " " <<*/ getenv("6_RH_Y_2_vel") << " " << getenv("6_RH_Y_3_vel");
     six_vel_buff->text(six_vel.str().c_str());
     six_vel_disp->buffer(six_vel_buff);
     
    std::stringstream six_tor;
    six_tor << /*getenv("6_LF_X_1_tor") << " " <<*/ getenv("6_LF_Y_2_tor") << " " << getenv("6_LF_Y_3_tor") 
       << " " << /*getenv("6_RF_X_1_tor") << " " <<*/ getenv("6_RF_Y_2_tor") << " " << getenv("6_RF_Y_3_tor")
       << " " << /*getenv("6_LH_X_1_tor")<< " " <<*/ getenv("6_LH_Y_2_tor") << " " << getenv("6_LH_Y_3_tor") 
       << " " << /*getenv("6_RH_X_1_tor") << " " <<*/ getenv("6_RH_Y_2_tor") << " " << getenv("6_RH_Y_3_tor");
    six_tor_buff->text(six_tor.str().c_str());
    six_tor_disp->buffer(six_tor_buff);

    std::stringstream seven_vel;
    seven_vel << /*getenv("7_LF_X_1_vel") << " " <<*/ getenv("7_LF_Y_2_vel") << " " << getenv("7_LF_Y_3_vel") 
      << " " << /*getenv("7_RF_X_1_vel") << " " <<*/ getenv("7_RF_Y_2_vel") << " " << getenv("7_RF_Y_3_vel")
      << " " << /*getenv("7_LH_X_1_vel") << " " <<*/ getenv("7_LH_Y_2_vel") << " " << getenv("7_LH_Y_3_vel") 
      << " " << /*getenv("7_RH_X_1_vel") << " " <<*/ getenv("7_RH_Y_2_vel") << " " << getenv("7_RH_Y_3_vel");
     seven_vel_buff->text(seven_vel.str().c_str());
     seven_vel_disp->buffer(seven_vel_buff);
     
    std::stringstream seven_tor;
    seven_tor << /*getenv("7_LF_X_1_tor") << " " <<*/ getenv("7_LF_Y_2_tor") << " " << getenv("7_LF_Y_3_tor") 
       << " " << /*getenv("7_RF_X_1_tor") << " " <<*/ getenv("7_RF_Y_2_tor") << " " << getenv("7_RF_Y_3_tor")
       << " " << /*getenv("7_LH_X_1_tor")<< " " <<*/ getenv("7_LH_Y_2_tor") << " " << getenv("7_LH_Y_3_tor") 
       << " " << /*getenv("7_RH_X_1_tor") << " " <<*/ getenv("7_RH_Y_2_tor") << " " << getenv("7_RH_Y_3_tor");
    seven_tor_buff->text(seven_tor.str().c_str());
    seven_tor_disp->buffer(seven_tor_buff);

    
    std::stringstream eight_vel;
    eight_vel << /*getenv("8_LF_X_1_vel") << " " <<*/ getenv("8_LF_Y_2_vel") << " " << getenv("8_LF_Y_3_vel") 
      << " " << /*getenv("8_RF_X_1_vel") << " " <<*/ getenv("8_RF_Y_2_vel") << " " << getenv("8_RF_Y_3_vel")
      << " " << /*getenv("8_LH_X_1_vel") << " " <<*/ getenv("8_LH_Y_2_vel") << " " << getenv("8_LH_Y_3_vel") 
      << " " << /*getenv("8_RH_X_1_vel") << " " <<*/ getenv("8_RH_Y_2_vel") << " " << getenv("8_RH_Y_3_vel");
     eight_vel_buff->text(eight_vel.str().c_str());
     eight_vel_disp->buffer(eight_vel_buff);
     
    std::stringstream eight_tor;
    eight_tor << /*getenv("8_LF_X_1_tor") << " " <<*/ getenv("8_LF_Y_2_tor") << " " << getenv("8_LF_Y_3_tor") 
       << " " << /*getenv("8_RF_X_1_tor") << " " <<*/ getenv("8_RF_Y_2_tor") << " " << getenv("8_RF_Y_3_tor")
       << " " << /*getenv("8_LH_X_1_tor")<< " " <<*/ getenv("8_LH_Y_2_tor") << " " << getenv("8_LH_Y_3_tor") 
       << " " << /*getenv("8_RH_X_1_tor") << " " <<*/ getenv("8_RH_Y_2_tor") << " " << getenv("8_RH_Y_3_tor");
    eight_tor_buff->text(eight_tor.str().c_str());
    eight_tor_disp->buffer(eight_tor_buff);

   
    std::stringstream nine_vel;
    nine_vel << /*getenv("9_LF_X_1_vel") << " " <<*/ getenv("9_LF_Y_2_vel") << " " << getenv("9_LF_Y_3_vel") 
      << " " << /*getenv("9_RF_X_1_vel") << " " <<*/ getenv("9_RF_Y_2_vel") << " " << getenv("9_RF_Y_3_vel")
      << " " << /*getenv("9_LH_X_1_vel") << " " <<*/ getenv("9_LH_Y_2_vel") << " " << getenv("9_LH_Y_3_vel") 
      << " " << /*getenv("9_RH_X_1_vel") << " " <<*/ getenv("9_RH_Y_2_vel") << " " << getenv("9_RH_Y_3_vel");
     nine_vel_buff->text(nine_vel.str().c_str());
     nine_vel_disp->buffer(nine_vel_buff);
     
    std::stringstream nine_tor;
    nine_tor << /*getenv("2_LF_X_1_tor") << " " <<*/ getenv("2_LF_Y_2_tor") << " " << getenv("2_LF_Y_3_tor") 
       << " " << /*getenv("2_RF_X_1_tor") << " " <<*/ getenv("2_RF_Y_2_tor") << " " << getenv("2_RF_Y_3_tor")
       << " " << /*getenv("2_LH_X_1_tor")<< " " <<*/ getenv("2_LH_Y_2_tor") << " " << getenv("2_LH_Y_3_tor") 
       << " " << /*getenv("2_RH_X_1_tor") << " " <<*/ getenv("2_RH_Y_2_tor") << " " << getenv("2_RH_Y_3_tor");
    nine_tor_buff->text(nine_tor.str().c_str());
    nine_tor_disp->buffer(nine_tor_buff);

   
    std::stringstream ten_vel;
    ten_vel << /*getenv("10_LF_X_1_vel") << " " <<*/ getenv("10_LF_Y_2_vel") << " " << getenv("10_LF_Y_3_vel") 
      << " " << /*getenv("10_RF_X_1_vel") << " " <<*/ getenv("10_RF_Y_2_vel") << " " << getenv("10_RF_Y_3_vel")
      << " " << /*getenv("10_LH_X_1_vel") << " " <<*/ getenv("10_LH_Y_2_vel") << " " << getenv("10_LH_Y_3_vel") 
      << " " << /*getenv("10_RH_X_1_vel") << " " <<*/ getenv("10_RH_Y_2_vel") << " " << getenv("10_RH_Y_3_vel");
     ten_vel_buff->text(ten_vel.str().c_str());
     ten_vel_disp->buffer(ten_vel_buff);
     
    std::stringstream ten_tor;
    ten_tor << /*getenv("10_LF_X_1_tor") << " " <<*/ getenv("10_LF_Y_2_tor") << " " << getenv("10_LF_Y_3_tor") 
       << " " << /*getenv("10_RF_X_1_tor") << " " <<*/ getenv("10_RF_Y_2_tor") << " " << getenv("10_RF_Y_3_tor")
       << " " << /*getenv("10_LH_X_1_tor")<< " " <<*/ getenv("10_LH_Y_2_tor") << " " << getenv("10_LH_Y_3_tor") 
       << " " << /*getenv("10_RH_X_1_tor") << " " <<*/ getenv("10_RH_Y_2_tor") << " " << getenv("10_RH_Y_3_tor");
    ten_tor_buff->text(ten_tor.str().c_str());
    ten_tor_disp->buffer(ten_tor_buff);


    std::stringstream eleven_vel;
    eleven_vel << /*getenv("11_LF_X_1_vel") << " " <<*/ getenv("11_LF_Y_2_vel") << " " << getenv("11_LF_Y_3_vel") 
      << " " << /*getenv("11_RF_X_1_vel") << " " <<*/ getenv("11_RF_Y_2_vel") << " " << getenv("11_RF_Y_3_vel")
      << " " << /*getenv("11_LH_X_1_vel") << " " <<*/ getenv("11_LH_Y_2_vel") << " " << getenv("11_LH_Y_3_vel") 
      << " " << /*getenv("11_RH_X_1_vel") << " " <<*/ getenv("11_RH_Y_2_vel") << " " << getenv("11_RH_Y_3_vel");
     eleven_vel_buff->text(eleven_vel.str().c_str());
     eleven_vel_disp->buffer(eleven_vel_buff);
     
    std::stringstream eleven_tor;
    eleven_tor << /*getenv("11_LF_X_1_tor") << " " <<*/ getenv("11_LF_Y_2_tor") << " " << getenv("11_LF_Y_3_tor") 
       << " " << /*getenv("11_RF_X_1_tor") << " " <<*/ getenv("11_RF_Y_2_tor") << " " << getenv("11_RF_Y_3_tor")
       << " " << /*getenv("11_LH_X_1_tor")<< " " <<*/ getenv("11_LH_Y_2_tor") << " " << getenv("11_LH_Y_3_tor") 
       << " " << /*getenv("11_RH_X_1_tor") << " " <<*/ getenv("11_RH_Y_2_tor") << " " << getenv("11_RH_Y_3_tor");
    eleven_tor_buff->text(eleven_tor.str().c_str());
    eleven_tor_disp->buffer(eleven_tor_buff);


    std::stringstream twelve_vel;
    twelve_vel << /*getenv("12_LF_X_1_vel") << " " <<*/ getenv("12_LF_Y_2_vel") << " " << getenv("12_LF_Y_3_vel") 
      << " " << /*getenv("12_RF_X_1_vel") << " " <<*/ getenv("12_RF_Y_2_vel") << " " << getenv("12_RF_Y_3_vel")
      << " " << /*getenv("12_LH_X_1_vel") << " " <<*/ getenv("12_LH_Y_2_vel") << " " << getenv("12_LH_Y_3_vel") 
      << " " << /*getenv("12_RH_X_1_vel") << " " <<*/ getenv("12_RH_Y_2_vel") << " " << getenv("12_RH_Y_3_vel");
     twelve_vel_buff->text(twelve_vel.str().c_str());
     twelve_vel_disp->buffer(twelve_vel_buff);
     
    std::stringstream twelve_tor;
    twelve_tor << /*getenv("12_LF_X_1_tor") << " " <<*/ getenv("12_LF_Y_2_tor") << " " << getenv("12_LF_Y_3_tor") 
       << " " << /*getenv("12_RF_X_1_tor") << " " <<*/ getenv("12_RF_Y_2_tor") << " " << getenv("12_RF_Y_3_tor")
       << " " << /*getenv("12_LH_X_1_tor")<< " " <<*/ getenv("12_LH_Y_2_tor") << " " << getenv("12_LH_Y_3_tor") 
       << " " << /*getenv("12_RH_X_1_tor") << " " <<*/ getenv("12_RH_Y_2_tor") << " " << getenv("12_RH_Y_3_tor");
    twelve_tor_buff->text(twelve_tor.str().c_str());
    twelve_tor_disp->buffer(twelve_tor_buff);


    std::stringstream thirteen_vel;
    thirteen_vel << /*getenv("13_LF_X_1_vel") << " " <<*/ getenv("13_LF_Y_2_vel") << " " << getenv("13_LF_Y_3_vel") 
      << " " << /*getenv("13_RF_X_1_vel") << " " <<*/ getenv("13_RF_Y_2_vel") << " " << getenv("13_RF_Y_3_vel")
      << " " << /*getenv("13_LH_X_1_vel") << " " <<*/ getenv("13_LH_Y_2_vel") << " " << getenv("13_LH_Y_3_vel") 
      << " " << /*getenv("13_RH_X_1_vel") << " " <<*/ getenv("13_RH_Y_2_vel") << " " << getenv("13_RH_Y_3_vel");
     thirteen_vel_buff->text(thirteen_vel.str().c_str());
     thirteen_vel_disp->buffer(thirteen_vel_buff);
     
    std::stringstream thirteen_tor;
    thirteen_tor << /*getenv("13_LF_X_1_tor") << " " <<*/ getenv("13_LF_Y_2_tor") << " " << getenv("13_LF_Y_3_tor") 
       << " " << /*getenv("13_RF_X_1_tor") << " " <<*/ getenv("13_RF_Y_2_tor") << " " << getenv("13_RF_Y_3_tor")
       << " " << /*getenv("13_LH_X_1_tor")<< " " <<*/ getenv("13_LH_Y_2_tor") << " " << getenv("13_LH_Y_3_tor") 
       << " " << /*getenv("13_RH_X_1_tor") << " " <<*/ getenv("13_RH_Y_2_tor") << " " << getenv("13_RH_Y_3_tor");
    thirteen_tor_buff->text(thirteen_tor.str().c_str());
    thirteen_tor_disp->buffer(thirteen_tor_buff);



     std::stringstream fourteen_vel;
    fourteen_vel << /*getenv("14_LF_X_1_vel") << " " <<*/ getenv("14_LF_Y_2_vel") << " " << getenv("14_LF_Y_3_vel") 
      << " " << /*getenv("14_RF_X_1_vel") << " " <<*/ getenv("14_RF_Y_2_vel") << " " << getenv("14_RF_Y_3_vel")
      << " " << /*getenv("14_LH_X_1_vel") << " " <<*/ getenv("14_LH_Y_2_vel") << " " << getenv("14_LH_Y_3_vel") 
      << " " << /*getenv("14_RH_X_1_vel") << " " <<*/ getenv("14_RH_Y_2_vel") << " " << getenv("14_RH_Y_3_vel");
     fourteen_vel_buff->text(fourteen_vel.str().c_str());
     fourteen_vel_disp->buffer(fourteen_vel_buff);
     
    std::stringstream fourteen_tor;
    fourteen_tor << /*getenv("14_LF_X_1_tor") << " " <<*/ getenv("14_LF_Y_2_tor") << " " << getenv("14_LF_Y_3_tor") 
       << " " << /*getenv("14_RF_X_1_tor") << " " <<*/ getenv("14_RF_Y_2_tor") << " " << getenv("14_RF_Y_3_tor")
       << " " << /*getenv("14_LH_X_1_tor")<< " " <<*/ getenv("14_LH_Y_2_tor") << " " << getenv("14_LH_Y_3_tor") 
       << " " << /*getenv("14_RH_X_1_tor") << " " <<*/ getenv("14_RH_Y_2_tor") << " " << getenv("14_RH_Y_3_tor");
    fourteen_tor_buff->text(fourteen_tor.str().c_str());
    fourteen_tor_disp->buffer(fourteen_tor_buff);

     Fl_Button *ebut = new Fl_Button(win->w()-125,win->h()-25,50,25,"Exit");
     ebut->callback(Exit_CB);

     Fl_Button *cbut = new Fl_Button(win->w()-75,win->h()-25,75,25,"Run Test");
     cbut->callback(Butt_CB);

    win->show();
    return(Fl::run());
}
    
