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
#include <vector>


template <typename T>
static std::string SSTR(T x)
{
  std::ostringstream oss;
  oss << std::dec << x;
  return oss.str();
}



struct Param {
  std::string name;
  std::string tooltip;
  std::vector<double> error_disp;
  std::vector<double> vel_error;
  std::vector<double> tor_error;
  int number;
  bool kinematic;
  double value;
  double unit;
};

std::vector<Param> params;

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
      sprintf(s, "%d", (int)(slider->value()));
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


std::vector<SliderInput*> slide;

void Butt_CB(Fl_Widget*w, void*data) {
  
  double modelNo= std::stod(getenv("modelNo"));
  modelNo++;
  
  setenv("curr_vel", "0", 1);
  
  for (int i=0;i<params.size();i++) {
    params[i].value += (params[i].unit*slide[i]->value());;
  }
  
  bool kinematic = false;
  for (int i=0;i<params.size();i++) {
    if(slide[i]->value()!=0 && params[i].kinematic){
      kinematic = true;
      break;
    }
  }
  
  std::string kin_val = (kinematic)? "true" : "false";
  setenv("KINEMATIC",kin_val.c_str(),1);
  
  for (int i=0;i<params.size();i++) {
    setenv(params[i].name.c_str(),SSTR(params[i].value).c_str(),1);
  }
  
  std::string line2=getenv("BUILDER_SCRIPT_PATH");
  line2+="/generate.sh";
  
  execl(line2.c_str(), line2.c_str(), NULL);
  
  win->hide();
}

#include <Ravelin/VectorNd.h>
#include <Ravelin/MatrixNd.h>
#include <Ravelin/LinAlgd.h>

int main() {
  double unitLen = std::stod(getenv("unit_len"));
  double unitDen = std::stod(getenv("unit_den"));
  double unitRad = std::stod(getenv("unit_rad"));
  {
    Param param;
    param.number = 1;
    param.name = "lenF1";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 2;
    param.name = "lenF2";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 3;
    param.name = "FfootLen";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 4;
    param.name = "lenH1";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 5;
    param.name = "lenH2";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 6;
    param.name = "HfootLen";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 7;
    param.name = "base_size_length";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 8;
    param.name = "base_size_width";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 9;
    param.name = "base_size_height";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 10;
    param.name = "FlinkRad";
    param.unit = unitRad;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 11;
    param.name = "HlinkRad";
    param.unit = unitRad;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 12;
    param.name = "density";
    param.unit = unitDen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 13;
    param.name = "FfootRad";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
    param.number = 14;
    param.name = "HfootRad";
    param.unit = unitLen;
    param.kinematic = true;
    params.push_back(param);
    
  }
  
  for (int i=0;i<params.size();i++) {
    params[i].value = std::stod(getenv(params[i].name.c_str()));
  }
  
#ifndef NDEBUG
  for (int i=0;i<params.size();i++) {
    std::cout << SSTR(params[i].number) << ": "<< params[i].name << " = " << params[i].value << std::endl;
  }
#endif
  
  std::vector<std::string> limit_names;
  limit_names.push_back("vel");
  limit_names.push_back("tor");
  
  std::vector<std::string> limb_names;
  limb_names.push_back("LF");
  limb_names.push_back("RF");
  limb_names.push_back("LH");
  limb_names.push_back("RH");
  
  std::vector<std::string> joint_names;
  //  joint_names.push_back("X_1");
  joint_names.push_back("Y_2");
  joint_names.push_back("Y_3");

  int N_LIMITS = limit_names.size();
  int N_LIMBS = limb_names.size();
  int N_JOINTS = joint_names.size();
  
  win = new Fl_Window(1300, 650, "Bot Builder");
  
  std::vector<Fl_Text_Buffer*> main_buff(N_LIMITS);
  std::vector<Fl_Text_Display*> main_disp(N_LIMITS);
  for(int index=0;index<N_LIMITS;index++)
  {
	main_buff[index]=new Fl_Text_Buffer();
  }

  main_disp[0]=new Fl_Text_Display(200, 20, 500, 40,std::string(limit_names[0] + " Limit Jacobian:").c_str());
  main_disp[1]=new Fl_Text_Display(700, 20, 500, 40,std::string(limit_names[1] + " Limit Jacobian:").c_str());
  
  Ravelin::VectorNd x(N_LIMBS*N_JOINTS*N_LIMITS);
  Ravelin::MatrixNd J(N_LIMBS*N_JOINTS*N_LIMITS,params.size());
  std::cout << "made matrices" << std::endl;

  {
    int j = 0;
    for (int limit=0;limit<limit_names.size();limit++) {
      std::stringstream row_val;
      std::cout << "limit: " <<limit << std::endl;
      for (int limb=0;limb<limb_names.size();limb++) {
        for (int joint=0;joint<joint_names.size();joint++,j++) {
          std::string env_name(limb_names[limb]+"_"+joint_names[joint]+"_"+limit_names[limit]);
          std::cout << "put variable in x" << j << std::endl;
          x[j] = std::stod(getenv(env_name.c_str()));
          std::cout << "added variable from getenv" << std::endl;
          row_val << x[j] << " ";
          std::cout << "added to row val:" <<x[j] << " " << env_name.c_str() << std::endl;
        }
      }
      std::cout << "putting values in front end" << std::endl;
      main_disp[limit]->buffer(main_buff[limit]);
      std::cout << "put values in disp" << std::endl;
      main_buff[limit]->text(row_val.str().c_str());
      std::cout << "put values in buff" << std::endl;
      
    }
  }
  std::cout << "put values in matrices" << std::endl;
 
  std::vector<std::vector<Fl_Text_Buffer*> > buff(N_LIMITS);
  std::vector<std::vector<Fl_Text_Display*> > disp(N_LIMITS);
  
  for (int limit=0;limit<limit_names.size();limit++) {
    buff[limit].resize(params.size());
    disp[limit].resize(params.size());
       for(int paramIndx=0;paramIndx<params.size();paramIndx++)
          {buff[limit][paramIndx]=new Fl_Text_Buffer();}
    int height=80;
    for (int i=0;i<params.size();i++) {
      disp[limit][i]=new Fl_Text_Display(200+(500*limit), height, 500, 40,"");
      if(limit==0)
     { slide.push_back(new SliderInput(0,height,200,25,params[i].tooltip.c_str()));
      slide[i]->bounds(-100,100);       // set min/max for slider
      slide[i]->value(0);  }         // set initial value
      
      height+=40;
    }
  }
  std::cout << "made sliders" << std::endl;
  for (int i=0;i<params.size();i++) {
    std::string num_str = SSTR(params[i].number);
    
    int j = 0;
    for (int limit=0;limit<limit_names.size();limit++) {
      std::cout << "limit: " <<limit << std::endl;
      std::stringstream row_val;
      for (int limb=0;limb<limb_names.size();limb++) {
        for (int joint=0;joint<joint_names.size();joint++,j++) {
           std::cout << "put variable in J" << std::endl;
          std::string env_name(num_str + "_"+limb_names[limb]+"_"+joint_names[joint]+"_"+limit_names[limit]);
          J(j,i) = std::stod(getenv(env_name.c_str()));
          row_val << J(j,i) << " ";
        }
      }
      std::cout << "putting values in front end" << std::endl;
      std::cout << "limit: " << limit << std::endl;
      std::cout << "number: " << params[i].number << std::endl;
      disp[limit][i]->buffer(buff[limit][i]);
      std::cout << "put values in disp" << std::endl;
      buff[limit][i]->text(row_val.str().c_str());
      std::cout << "put values in buff" << std::endl;
      
    }
    std::cout << "filled more matrix variables" << std::endl;
  }
  
  
  //negate?
//  x.negate();
  
  Ravelin::MatrixNd J_inv = J;

  Ravelin::LinAlgd LA;
  LA.pseudo_invert(J_inv, 1e-6);
  
  Ravelin::VectorNd step;
  J_inv.mult(x,step);
  std::cout << "got the inverse" << std::endl;
  std::cout << "step: " << step.rows()<< std::endl;
  std::cout << "slide: " << slide.size()<< std::endl;
  assert(step.rows() == slide.size());
  std::cout << "passed assertion" << std::endl;
  for (int i=0; i<step.rows(); i++) {
    double update = step[i] / (double) params[i].unit;
    slide[i]->value(update);
   /* std::cout << "\n" << "\n" << update << "\n" << "\n";*/
  }
  std::cout << "valued slides" << std::endl;
  
  Fl_Button ebut(win->w()-125,win->h()-25,50,25,"Exit");
  ebut.callback(Exit_CB);
  
  Fl_Button cbut(win->w()-75,win->h()-25,75,25,"Run Test");
  cbut.callback(Butt_CB);
  
  win->show();
  
  int RETURN_FLAG = Fl::run();
  
  return RETURN_FLAG;
}

