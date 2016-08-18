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
//
//SliderInput *slide1 = NULL;
//SliderInput *slide2 = NULL;
//SliderInput *slide3 = NULL;
//SliderInput *slide4 = NULL;
//SliderInput *slide5 = NULL;
//SliderInput *slide6 = NULL;
//SliderInput *slide7 = NULL;
//SliderInput *slide8 = NULL;
//SliderInput *slide9 = NULL;
//SliderInput *slide10 = NULL;
//SliderInput *slide11 = NULL;
//SliderInput *slide12 = NULL;
//SliderInput *slide13 = NULL;
//SliderInput *slide14 = NULL;

void Butt_CB(Fl_Widget*w, void*data) {
  
//  double unitLen = std::stod(getenv("unit_len"));
//  double unitDen = std::stod(getenv("unit_den"));
//  double unitRad = std::stod(getenv("unit_rad"));
  
//  double lenF1= std::stod(getenv("lenF1"));
//  double lenF2= std::stod(getenv("lenF2"));
//  
//  double lenH1= std::stod(getenv("lenH1"));
//  double lenH2= std::stod(getenv("lenH2"));
//  
//  double base_size_length= std::stod(getenv("base_size_length"));
//  double base_size_width= std::stod(getenv("base_size_width"));
//  double base_size_height= std::stod(getenv("base_size_height"));
//  
//  double density= std::stod(getenv("density"));
//  
//  double FlinkRad= std::stod(getenv("FlinkRad"));
//  double FfootRad= std::stod(getenv("FfootRad"));
//  double FfootLen= std::stod(getenv("FfootLen"));
//  double HlinkRad= std::stod(getenv("HlinkRad"));
//  double HfootRad= std::stod(getenv("HfootRad"));
//  double HfootLen= std::stod(getenv("HfootLen"));
  
  double modelNo= std::stod(getenv("modelNo"));
  modelNo++;
  
  setenv("curr_vel", "0", 1);
  
  for (int i=0;i<params.size();i++) {
    params[i].value += (params[i].unit*slide[i]->value());;
  }

//  lenF1+=(unitLen*slide1->value());
//  lenF2+=(unitLen*slide2->value());
//  FfootLen+=(unitLen*slide3->value());
//  lenH1+=(unitLen*slide4->value());
//  lenH2+=(unitLen*slide5->value());
//  HfootLen+=(unitLen*slide6->value());
//  base_size_length+=(unitLen*slide7->value());
//  base_size_width+=(unitLen*slide8->value());
//  base_size_height+=(unitLen*slide9->value());
//  FlinkRad+=(unitRad*slide10->value());
//  HlinkRad+=(unitRad*slide11->value());
//  density+=(unitDen*slide12->value());
//  FfootRad+=(unitRad*slide13->value());
//  HfootRad+=(unitRad*slide14->value());
  
  bool kinematic = false;
  for (int i=0;i<params.size();i++) {
    if(slide[i]->value()!=0 && params[i].kinematic){
      kinematic = true;
      break;
    }
  }
  
  std::string kin_val = (kinematic)? "true" : "false";
  setenv("KINEMATIC",kin_val.c_str(),1);

//  if(slide1->value()!=0 || slide2->value()!=0 || slide3->value()!=0 || slide4->value()!=0 || slide5->value()!=0 || slide6->value()!=0 || slide7->value()!=0 || slide8->value()!=0 || slide9->value()!=0 || slide11->value()!=0)
//  {
//    setenv("KINEMATIC","true",1);
//  }
//  else
//  {
//    setenv("KINEMATIC","false",1);
//  }
  
  for (int i=0;i<params.size();i++) {
    setenv(params[i].name.c_str(),SSTR(params[i].value).c_str(),1);
  }
  /*s.clear();
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
  
  s << FfootRad;
  line=s.str();
  setenv("FfootRad",line.c_str(),1);
  s.clear();
  s.str(std::string());
  
  s << FlinkRad;
  line=s.str();
  setenv("FlinkRad",line.c_str(),1);
  s.clear();
  s.str(std::string());
  
  s << FfootLen;
  line=s.str();
  setenv("FfootLen",line.c_str(),1);
  s.clear();
  s.str(std::string());
  
  s << HfootRad;
  line=s.str();
  setenv("HfootRad",line.c_str(),1);
  s.clear();
  s.str(std::string());
  
  s << HlinkRad;
  line=s.str();
  setenv("HlinkRad",line.c_str(),1);
  s.clear();
  s.str(std::string());
  
  s << HfootLen;
  line=s.str();
  setenv("HfootLen",line.c_str(),1);
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
  s.str(std::string());*/
  
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
//  
//  std::stringstream main_vel;
//  main_vel << /*getenv("LF_X_1_vel") << " " <<*/ getenv("LF_Y_2_vel") << " " << getenv("LF_Y_3_vel")
//  << " " << /*getenv("RF_X_1_vel") << " " <<*/ getenv("RF_Y_2_vel") << " " << getenv("RF_Y_3_vel")
//  << " " << /*getenv("LH_X_1_vel") << " " <<*/ getenv("LH_Y_2_vel") << " " << getenv("LH_Y_3_vel")
//  << " " << /*getenv("RH_X_1_vel") << " " <<*/ getenv("RH_Y_2_vel") << " " << getenv("RH_Y_3_vel");
//  main_vel_buff.text(main_vel.str().c_str());
//  main_vel_disp.buffer(main_vel_buff);
//  
//  
//  std::stringstream main_tor;
//  main_tor << /*getenv("LF_X_1_tor") << " " <<*/ getenv("LF_Y_2_tor") << " " << getenv("LF_Y_3_tor")
//  << " " << /*getenv("RF_X_1_tor") << " " <<*/ getenv("RF_Y_2_tor") << " " << getenv("RF_Y_3_tor")
//  << " " << /*getenv("LH_X_1_tor")<< " " <<*/ getenv("LH_Y_2_tor") << " " << getenv("LH_Y_3_tor")
//  << " " << /*getenv("RH_X_1_tor") << " " <<*/ getenv("RH_Y_2_tor") << " " << getenv("RH_Y_3_tor");
//  main_tor_buff.text(main_tor.str().c_str());
//  main_tor_disp.buffer(main_tor_buff);
//  
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
//    std::stringstream one_vel;
//    one_vel << /*getenv(num_str + "_LF_X_1_vel") << " " <<*/ getenv(num_str + "_LF_Y_2_vel") << " " << getenv(num_str + "_LF_Y_3_vel")
//    << " " << /*getenv(num_str + "_RF_X_1_vel") << " " <<*/ getenv(num_str + "_RF_Y_2_vel") << " " << getenv(num_str + "_RF_Y_3_vel")
//    << " " << /*getenv(num_str + "_LH_X_1_vel") << " " <<*/ getenv(num_str + "_LH_Y_2_vel") << " " << getenv(num_str + "_LH_Y_3_vel")
//    << " " << /*getenv(num_str + "_RH_X_1_vel") << " " <<*/ getenv(num_str + "_RH_Y_2_vel") << " " << getenv(num_str + "_RH_Y_3_vel");
//    one_vel_buff.text(one_vel.str().c_str());
//    one_vel_disp.buffer(one_vel_buff);
//    
//    std::stringstream one_tor;
//    one_tor << /*getenv(num_str + "_LF_X_1_tor") << " " <<*/ getenv(num_str + "_LF_Y_2_tor") << " " << getenv(num_str + "_LF_Y_3_tor")
//    << " " << /*getenv(num_str + "_RF_X_1_tor") << " " <<*/ getenv(num_str + "_RF_Y_2_tor") << " " << getenv(num_str + "_RF_Y_3_tor")
//    << " " << /*getenv(num_str + "_LH_X_1_tor")<< " " <<*/ getenv(num_str + "_LH_Y_2_tor") << " " << getenv(num_str + "_LH_Y_3_tor")
//    << " " << /*getenv(num_str + "_RH_X_1_tor") << " " <<*/ getenv(num_str + "_RH_Y_2_tor") << " " << getenv(num_str + "_RH_Y_3_tor");
//    one_tor_buff.text(one_tor.str().c_str());
//    one_tor_disp.buffer(one_tor_buff);
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
  
  
  /*
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
   */
  /*
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
   */
  
  /*
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
   */
  
//  
//  std::stringstream main_vel;
//  main_vel << /*getenv("LF_X_1_vel") << " " <<*/ getenv("LF_Y_2_vel") << " " << getenv("LF_Y_3_vel")
//  << " " << /*getenv("RF_X_1_vel") << " " <<*/ getenv("RF_Y_2_vel") << " " << getenv("RF_Y_3_vel")
//  << " " << /*getenv("LH_X_1_vel") << " " <<*/ getenv("LH_Y_2_vel") << " " << getenv("LH_Y_3_vel")
//  << " " << /*getenv("RH_X_1_vel") << " " <<*/ getenv("RH_Y_2_vel") << " " << getenv("RH_Y_3_vel");
//  main_vel_buff->text(main_vel.str().c_str());
//  main_vel_disp->buffer(main_vel_buff);
//  
//  
//  
//  std::stringstream main_tor;
//  main_tor << /*getenv("LF_X_1_tor") << " " <<*/ getenv("LF_Y_2_tor") << " " << getenv("LF_Y_3_tor")
//  << " " << /*getenv("RF_X_1_tor") << " " <<*/ getenv("RF_Y_2_tor") << " " << getenv("RF_Y_3_tor")
//  << " " << /*getenv("LH_X_1_tor")<< " " <<*/ getenv("LH_Y_2_tor") << " " << getenv("LH_Y_3_tor")
//  << " " << /*getenv("RH_X_1_tor") << " " <<*/ getenv("RH_Y_2_tor") << " " << getenv("RH_Y_3_tor");
//  main_tor_buff->text(main_tor.str().c_str());
//  main_tor_disp->buffer(main_tor_buff);
//  
//  
//  std::stringstream one_vel;
//  one_vel << /*getenv("1_LF_X_1_vel") << " " <<*/ getenv("1_LF_Y_2_vel") << " " << getenv("1_LF_Y_3_vel")
//  << " " << /*getenv("1_RF_X_1_vel") << " " <<*/ getenv("1_RF_Y_2_vel") << " " << getenv("1_RF_Y_3_vel")
//  << " " << /*getenv("1_LH_X_1_vel") << " " <<*/ getenv("1_LH_Y_2_vel") << " " << getenv("1_LH_Y_3_vel")
//  << " " << /*getenv("1_RH_X_1_vel") << " " <<*/ getenv("1_RH_Y_2_vel") << " " << getenv("1_RH_Y_3_vel");
//  one_vel_buff->text(one_vel.str().c_str());
//  one_vel_disp->buffer(one_vel_buff);
//  
//  std::stringstream one_tor;
//  one_tor << /*getenv("1_LF_X_1_tor") << " " <<*/ getenv("1_LF_Y_2_tor") << " " << getenv("1_LF_Y_3_tor")
//  << " " << /*getenv("1_RF_X_1_tor") << " " <<*/ getenv("1_RF_Y_2_tor") << " " << getenv("1_RF_Y_3_tor")
//  << " " << /*getenv("1_LH_X_1_tor")<< " " <<*/ getenv("1_LH_Y_2_tor") << " " << getenv("1_LH_Y_3_tor")
//  << " " << /*getenv("1_RH_X_1_tor") << " " <<*/ getenv("1_RH_Y_2_tor") << " " << getenv("1_RH_Y_3_tor");
//  one_tor_buff->text(one_tor.str().c_str());
//  one_tor_disp->buffer(one_tor_buff);
//  
//  
//  std::stringstream two_vel;
//  two_vel << /*getenv("2_LF_X_1_vel") << " " <<*/ getenv("2_LF_Y_2_vel") << " " << getenv("2_LF_Y_3_vel")
//  << " " << /*getenv("2_RF_X_1_vel") << " " <<*/ getenv("2_RF_Y_2_vel") << " " << getenv("2_RF_Y_3_vel")
//  << " " << /*getenv("2_LH_X_1_vel") << " " <<*/ getenv("2_LH_Y_2_vel") << " " << getenv("2_LH_Y_3_vel")
//  << " " << /*getenv("2_RH_X_1_vel") << " " <<*/ getenv("2_RH_Y_2_vel") << " " << getenv("2_RH_Y_3_vel");
//  two_vel_buff->text(two_vel.str().c_str());
//  two_vel_disp->buffer(two_vel_buff);
//  
//  std::stringstream two_tor;
//  two_tor << /*getenv("2_LF_X_1_tor") << " " <<*/ getenv("2_LF_Y_2_tor") << " " << getenv("2_LF_Y_3_tor")
//  << " " << /*getenv("2_RF_X_1_tor") << " " <<*/ getenv("2_RF_Y_2_tor") << " " << getenv("2_RF_Y_3_tor")
//  << " " << /*getenv("2_LH_X_1_tor")<< " " <<*/ getenv("2_LH_Y_2_tor") << " " << getenv("2_LH_Y_3_tor")
//  << " " << /*getenv("2_RH_X_1_tor") << " " <<*/ getenv("2_RH_Y_2_tor") << " " << getenv("2_RH_Y_3_tor");
//  two_tor_buff->text(two_tor.str().c_str());
//  two_tor_disp->buffer(two_tor_buff);
//  
//  std::stringstream three_vel;
//  three_vel << /*getenv("3_LF_X_1_vel") << " " <<*/ getenv("3_LF_Y_2_vel") << " " << getenv("3_LF_Y_3_vel")
//  << " " << /*getenv("3_RF_X_1_vel") << " " <<*/ getenv("3_RF_Y_2_vel") << " " << getenv("3_RF_Y_3_vel")
//  << " " << /*getenv("3_LH_X_1_vel") << " " <<*/ getenv("3_LH_Y_2_vel") << " " << getenv("3_LH_Y_3_vel")
//  << " " << /*getenv("3_RH_X_1_vel") << " " <<*/ getenv("3_RH_Y_2_vel") << " " << getenv("3_RH_Y_3_vel");
//  three_vel_buff->text(three_vel.str().c_str());
//  three_vel_disp->buffer(three_vel_buff);
//  
//  std::stringstream three_tor;
//  three_tor << /*getenv("3_LF_X_1_tor") << " " <<*/ getenv("3_LF_Y_2_tor") << " " << getenv("3_LF_Y_3_tor")
//  << " " << /*getenv("3_RF_X_1_tor") << " " <<*/ getenv("3_RF_Y_2_tor") << " " << getenv("3_RF_Y_3_tor")
//  << " " << /*getenv("3_LH_X_1_tor")<< " " <<*/ getenv("3_LH_Y_2_tor") << " " << getenv("3_LH_Y_3_tor")
//  << " " << /*getenv("3_RH_X_1_tor") << " " <<*/ getenv("3_RH_Y_2_tor") << " " << getenv("3_RH_Y_3_tor");
//  three_tor_buff->text(three_tor.str().c_str());
//  three_tor_disp->buffer(three_tor_buff);
//  
//  
//  std::stringstream four_vel;
//  four_vel << /*getenv("4_LF_X_1_vel") << " " <<*/ getenv("4_LF_Y_2_vel") << " " << getenv("4_LF_Y_3_vel")
//  << " " << /*getenv("4_RF_X_1_vel") << " " <<*/ getenv("4_RF_Y_2_vel") << " " << getenv("4_RF_Y_3_vel")
//  << " " << /*getenv("4_LH_X_1_vel") << " " <<*/ getenv("4_LH_Y_2_vel") << " " << getenv("4_LH_Y_3_vel")
//  << " " << /*getenv("4_RH_X_1_vel") << " " <<*/ getenv("4_RH_Y_2_vel") << " " << getenv("4_RH_Y_3_vel");
//  four_vel_buff->text(four_vel.str().c_str());
//  four_vel_disp->buffer(four_vel_buff);
//  
//  std::stringstream four_tor;
//  four_tor << /*getenv("4_LF_X_1_tor") << " " <<*/ getenv("4_LF_Y_2_tor") << " " << getenv("4_LF_Y_3_tor")
//  << " " << /*getenv("4_RF_X_1_tor") << " " <<*/ getenv("4_RF_Y_2_tor") << " " << getenv("4_RF_Y_3_tor")
//  << " " << /*getenv("4_LH_X_1_tor")<< " " <<*/ getenv("4_LH_Y_2_tor") << " " << getenv("4_LH_Y_3_tor")
//  << " " << /*getenv("4_RH_X_1_tor") << " " <<*/ getenv("4_RH_Y_2_tor") << " " << getenv("4_RH_Y_3_tor");
//  four_tor_buff->text(four_tor.str().c_str());
//  four_tor_disp->buffer(four_tor_buff);
//  
//  std::stringstream five_vel;
//  five_vel << /*getenv("5_LF_X_1_vel") << " " <<*/ getenv("5_LF_Y_2_vel") << " " << getenv("5_LF_Y_3_vel")
//  << " " << /*getenv("5_RF_X_1_vel") << " " <<*/ getenv("5_RF_Y_2_vel") << " " << getenv("5_RF_Y_3_vel")
//  << " " << /*getenv("5_LH_X_1_vel") << " " <<*/ getenv("5_LH_Y_2_vel") << " " << getenv("5_LH_Y_3_vel")
//  << " " << /*getenv("5_RH_X_1_vel") << " " <<*/ getenv("5_RH_Y_2_vel") << " " << getenv("5_RH_Y_3_vel");
//  five_vel_buff->text(five_vel.str().c_str());
//  five_vel_disp->buffer(five_vel_buff);
//  
//  std::stringstream five_tor;
//  five_tor << /*getenv("5_LF_X_1_tor") << " " <<*/ getenv("5_LF_Y_2_tor") << " " << getenv("5_LF_Y_3_tor")
//  << " " << /*getenv("5_RF_X_1_tor") << " " <<*/ getenv("5_RF_Y_2_tor") << " " << getenv("5_RF_Y_3_tor")
//  << " " << /*getenv("5_LH_X_1_tor")<< " " <<*/ getenv("5_LH_Y_2_tor") << " " << getenv("5_LH_Y_3_tor")
//  << " " << /*getenv("5_RH_X_1_tor") << " " <<*/ getenv("5_RH_Y_2_tor") << " " << getenv("5_RH_Y_3_tor");
//  five_tor_buff->text(five_tor.str().c_str());
//  five_tor_disp->buffer(five_tor_buff);
//  
//  
//  std::stringstream six_vel;
//  six_vel << /*getenv("6_LF_X_1_vel") << " " <<*/ getenv("6_LF_Y_2_vel") << " " << getenv("6_LF_Y_3_vel")
//  << " " << /*getenv("6_RF_X_1_vel") << " " <<*/ getenv("6_RF_Y_2_vel") << " " << getenv("6_RF_Y_3_vel")
//  << " " << /*getenv("6_LH_X_1_vel") << " " <<*/ getenv("6_LH_Y_2_vel") << " " << getenv("6_LH_Y_3_vel")
//  << " " << /*getenv("6_RH_X_1_vel") << " " <<*/ getenv("6_RH_Y_2_vel") << " " << getenv("6_RH_Y_3_vel");
//  six_vel_buff->text(six_vel.str().c_str());
//  six_vel_disp->buffer(six_vel_buff);
//  
//  std::stringstream six_tor;
//  six_tor << /*getenv("6_LF_X_1_tor") << " " <<*/ getenv("6_LF_Y_2_tor") << " " << getenv("6_LF_Y_3_tor")
//  << " " << /*getenv("6_RF_X_1_tor") << " " <<*/ getenv("6_RF_Y_2_tor") << " " << getenv("6_RF_Y_3_tor")
//  << " " << /*getenv("6_LH_X_1_tor")<< " " <<*/ getenv("6_LH_Y_2_tor") << " " << getenv("6_LH_Y_3_tor")
//  << " " << /*getenv("6_RH_X_1_tor") << " " <<*/ getenv("6_RH_Y_2_tor") << " " << getenv("6_RH_Y_3_tor");
//  six_tor_buff->text(six_tor.str().c_str());
//  six_tor_disp->buffer(six_tor_buff);
//  
//  std::stringstream seven_vel;
//  seven_vel << /*getenv("7_LF_X_1_vel") << " " <<*/ getenv("7_LF_Y_2_vel") << " " << getenv("7_LF_Y_3_vel")
//  << " " << /*getenv("7_RF_X_1_vel") << " " <<*/ getenv("7_RF_Y_2_vel") << " " << getenv("7_RF_Y_3_vel")
//  << " " << /*getenv("7_LH_X_1_vel") << " " <<*/ getenv("7_LH_Y_2_vel") << " " << getenv("7_LH_Y_3_vel")
//  << " " << /*getenv("7_RH_X_1_vel") << " " <<*/ getenv("7_RH_Y_2_vel") << " " << getenv("7_RH_Y_3_vel");
//  seven_vel_buff->text(seven_vel.str().c_str());
//  seven_vel_disp->buffer(seven_vel_buff);
//  
//  std::stringstream seven_tor;
//  seven_tor << /*getenv("7_LF_X_1_tor") << " " <<*/ getenv("7_LF_Y_2_tor") << " " << getenv("7_LF_Y_3_tor")
//  << " " << /*getenv("7_RF_X_1_tor") << " " <<*/ getenv("7_RF_Y_2_tor") << " " << getenv("7_RF_Y_3_tor")
//  << " " << /*getenv("7_LH_X_1_tor")<< " " <<*/ getenv("7_LH_Y_2_tor") << " " << getenv("7_LH_Y_3_tor")
//  << " " << /*getenv("7_RH_X_1_tor") << " " <<*/ getenv("7_RH_Y_2_tor") << " " << getenv("7_RH_Y_3_tor");
//  seven_tor_buff->text(seven_tor.str().c_str());
//  seven_tor_disp->buffer(seven_tor_buff);
//  
//  
//  std::stringstream eight_vel;
//  eight_vel << /*getenv("8_LF_X_1_vel") << " " <<*/ getenv("8_LF_Y_2_vel") << " " << getenv("8_LF_Y_3_vel")
//  << " " << /*getenv("8_RF_X_1_vel") << " " <<*/ getenv("8_RF_Y_2_vel") << " " << getenv("8_RF_Y_3_vel")
//  << " " << /*getenv("8_LH_X_1_vel") << " " <<*/ getenv("8_LH_Y_2_vel") << " " << getenv("8_LH_Y_3_vel")
//  << " " << /*getenv("8_RH_X_1_vel") << " " <<*/ getenv("8_RH_Y_2_vel") << " " << getenv("8_RH_Y_3_vel");
//  eight_vel_buff->text(eight_vel.str().c_str());
//  eight_vel_disp->buffer(eight_vel_buff);
//  
//  std::stringstream eight_tor;
//  eight_tor << /*getenv("8_LF_X_1_tor") << " " <<*/ getenv("8_LF_Y_2_tor") << " " << getenv("8_LF_Y_3_tor")
//  << " " << /*getenv("8_RF_X_1_tor") << " " <<*/ getenv("8_RF_Y_2_tor") << " " << getenv("8_RF_Y_3_tor")
//  << " " << /*getenv("8_LH_X_1_tor")<< " " <<*/ getenv("8_LH_Y_2_tor") << " " << getenv("8_LH_Y_3_tor")
//  << " " << /*getenv("8_RH_X_1_tor") << " " <<*/ getenv("8_RH_Y_2_tor") << " " << getenv("8_RH_Y_3_tor");
//  eight_tor_buff->text(eight_tor.str().c_str());
//  eight_tor_disp->buffer(eight_tor_buff);
//  
//  
//  std::stringstream nine_vel;
//  nine_vel << /*getenv("9_LF_X_1_vel") << " " <<*/ getenv("9_LF_Y_2_vel") << " " << getenv("9_LF_Y_3_vel")
//  << " " << /*getenv("9_RF_X_1_vel") << " " <<*/ getenv("9_RF_Y_2_vel") << " " << getenv("9_RF_Y_3_vel")
//  << " " << /*getenv("9_LH_X_1_vel") << " " <<*/ getenv("9_LH_Y_2_vel") << " " << getenv("9_LH_Y_3_vel")
//  << " " << /*getenv("9_RH_X_1_vel") << " " <<*/ getenv("9_RH_Y_2_vel") << " " << getenv("9_RH_Y_3_vel");
//  nine_vel_buff->text(nine_vel.str().c_str());
//  nine_vel_disp->buffer(nine_vel_buff);
//  
//  std::stringstream nine_tor;
//  nine_tor << /*getenv("2_LF_X_1_tor") << " " <<*/ getenv("2_LF_Y_2_tor") << " " << getenv("2_LF_Y_3_tor")
//  << " " << /*getenv("2_RF_X_1_tor") << " " <<*/ getenv("2_RF_Y_2_tor") << " " << getenv("2_RF_Y_3_tor")
//  << " " << /*getenv("2_LH_X_1_tor")<< " " <<*/ getenv("2_LH_Y_2_tor") << " " << getenv("2_LH_Y_3_tor")
//  << " " << /*getenv("2_RH_X_1_tor") << " " <<*/ getenv("2_RH_Y_2_tor") << " " << getenv("2_RH_Y_3_tor");
//  nine_tor_buff->text(nine_tor.str().c_str());
//  nine_tor_disp->buffer(nine_tor_buff);
//  
//  
//  std::stringstream ten_vel;
//  ten_vel << /*getenv("10_LF_X_1_vel") << " " <<*/ getenv("10_LF_Y_2_vel") << " " << getenv("10_LF_Y_3_vel")
//  << " " << /*getenv("10_RF_X_1_vel") << " " <<*/ getenv("10_RF_Y_2_vel") << " " << getenv("10_RF_Y_3_vel")
//  << " " << /*getenv("10_LH_X_1_vel") << " " <<*/ getenv("10_LH_Y_2_vel") << " " << getenv("10_LH_Y_3_vel")
//  << " " << /*getenv("10_RH_X_1_vel") << " " <<*/ getenv("10_RH_Y_2_vel") << " " << getenv("10_RH_Y_3_vel");
//  ten_vel_buff->text(ten_vel.str().c_str());
//  ten_vel_disp->buffer(ten_vel_buff);
//  
//  std::stringstream ten_tor;
//  ten_tor << /*getenv("10_LF_X_1_tor") << " " <<*/ getenv("10_LF_Y_2_tor") << " " << getenv("10_LF_Y_3_tor")
//  << " " << /*getenv("10_RF_X_1_tor") << " " <<*/ getenv("10_RF_Y_2_tor") << " " << getenv("10_RF_Y_3_tor")
//  << " " << /*getenv("10_LH_X_1_tor")<< " " <<*/ getenv("10_LH_Y_2_tor") << " " << getenv("10_LH_Y_3_tor")
//  << " " << /*getenv("10_RH_X_1_tor") << " " <<*/ getenv("10_RH_Y_2_tor") << " " << getenv("10_RH_Y_3_tor");
//  ten_tor_buff->text(ten_tor.str().c_str());
//  ten_tor_disp->buffer(ten_tor_buff);
//  
//  
//  std::stringstream eleven_vel;
//  eleven_vel << /*getenv("11_LF_X_1_vel") << " " <<*/ getenv("11_LF_Y_2_vel") << " " << getenv("11_LF_Y_3_vel")
//  << " " << /*getenv("11_RF_X_1_vel") << " " <<*/ getenv("11_RF_Y_2_vel") << " " << getenv("11_RF_Y_3_vel")
//  << " " << /*getenv("11_LH_X_1_vel") << " " <<*/ getenv("11_LH_Y_2_vel") << " " << getenv("11_LH_Y_3_vel")
//  << " " << /*getenv("11_RH_X_1_vel") << " " <<*/ getenv("11_RH_Y_2_vel") << " " << getenv("11_RH_Y_3_vel");
//  eleven_vel_buff->text(eleven_vel.str().c_str());
//  eleven_vel_disp->buffer(eleven_vel_buff);
//  
//  std::stringstream eleven_tor;
//  eleven_tor << /*getenv("11_LF_X_1_tor") << " " <<*/ getenv("11_LF_Y_2_tor") << " " << getenv("11_LF_Y_3_tor")
//  << " " << /*getenv("11_RF_X_1_tor") << " " <<*/ getenv("11_RF_Y_2_tor") << " " << getenv("11_RF_Y_3_tor")
//  << " " << /*getenv("11_LH_X_1_tor")<< " " <<*/ getenv("11_LH_Y_2_tor") << " " << getenv("11_LH_Y_3_tor")
//  << " " << /*getenv("11_RH_X_1_tor") << " " <<*/ getenv("11_RH_Y_2_tor") << " " << getenv("11_RH_Y_3_tor");
//  eleven_tor_buff->text(eleven_tor.str().c_str());
//  eleven_tor_disp->buffer(eleven_tor_buff);
//  
//  
//  std::stringstream twelve_vel;
//  twelve_vel << /*getenv("12_LF_X_1_vel") << " " <<*/ getenv("12_LF_Y_2_vel") << " " << getenv("12_LF_Y_3_vel")
//  << " " << /*getenv("12_RF_X_1_vel") << " " <<*/ getenv("12_RF_Y_2_vel") << " " << getenv("12_RF_Y_3_vel")
//  << " " << /*getenv("12_LH_X_1_vel") << " " <<*/ getenv("12_LH_Y_2_vel") << " " << getenv("12_LH_Y_3_vel")
//  << " " << /*getenv("12_RH_X_1_vel") << " " <<*/ getenv("12_RH_Y_2_vel") << " " << getenv("12_RH_Y_3_vel");
//  twelve_vel_buff->text(twelve_vel.str().c_str());
//  twelve_vel_disp->buffer(twelve_vel_buff);
//  
//  std::stringstream twelve_tor;
//  twelve_tor << /*getenv("12_LF_X_1_tor") << " " <<*/ getenv("12_LF_Y_2_tor") << " " << getenv("12_LF_Y_3_tor")
//  << " " << /*getenv("12_RF_X_1_tor") << " " <<*/ getenv("12_RF_Y_2_tor") << " " << getenv("12_RF_Y_3_tor")
//  << " " << /*getenv("12_LH_X_1_tor")<< " " <<*/ getenv("12_LH_Y_2_tor") << " " << getenv("12_LH_Y_3_tor")
//  << " " << /*getenv("12_RH_X_1_tor") << " " <<*/ getenv("12_RH_Y_2_tor") << " " << getenv("12_RH_Y_3_tor");
//  twelve_tor_buff->text(twelve_tor.str().c_str());
//  twelve_tor_disp->buffer(twelve_tor_buff);
//  
//  
//  std::stringstream thirteen_vel;
//  thirteen_vel << /*getenv("13_LF_X_1_vel") << " " <<*/ getenv("13_LF_Y_2_vel") << " " << getenv("13_LF_Y_3_vel")
//  << " " << /*getenv("13_RF_X_1_vel") << " " <<*/ getenv("13_RF_Y_2_vel") << " " << getenv("13_RF_Y_3_vel")
//  << " " << /*getenv("13_LH_X_1_vel") << " " <<*/ getenv("13_LH_Y_2_vel") << " " << getenv("13_LH_Y_3_vel")
//  << " " << /*getenv("13_RH_X_1_vel") << " " <<*/ getenv("13_RH_Y_2_vel") << " " << getenv("13_RH_Y_3_vel");
//  thirteen_vel_buff->text(thirteen_vel.str().c_str());
//  thirteen_vel_disp->buffer(thirteen_vel_buff);
//  
//  std::stringstream thirteen_tor;
//  thirteen_tor << /*getenv("13_LF_X_1_tor") << " " <<*/ getenv("13_LF_Y_2_tor") << " " << getenv("13_LF_Y_3_tor")
//  << " " << /*getenv("13_RF_X_1_tor") << " " <<*/ getenv("13_RF_Y_2_tor") << " " << getenv("13_RF_Y_3_tor")
//  << " " << /*getenv("13_LH_X_1_tor")<< " " <<*/ getenv("13_LH_Y_2_tor") << " " << getenv("13_LH_Y_3_tor")
//  << " " << /*getenv("13_RH_X_1_tor") << " " <<*/ getenv("13_RH_Y_2_tor") << " " << getenv("13_RH_Y_3_tor");
//  thirteen_tor_buff->text(thirteen_tor.str().c_str());
//  thirteen_tor_disp->buffer(thirteen_tor_buff);
//  
//  
//  
//  std::stringstream fourteen_vel;
//  fourteen_vel << /*getenv("14_LF_X_1_vel") << " " <<*/ getenv("14_LF_Y_2_vel") << " " << getenv("14_LF_Y_3_vel")
//  << " " << /*getenv("14_RF_X_1_vel") << " " <<*/ getenv("14_RF_Y_2_vel") << " " << getenv("14_RF_Y_3_vel")
//  << " " << /*getenv("14_LH_X_1_vel") << " " <<*/ getenv("14_LH_Y_2_vel") << " " << getenv("14_LH_Y_3_vel")
//  << " " << /*getenv("14_RH_X_1_vel") << " " <<*/ getenv("14_RH_Y_2_vel") << " " << getenv("14_RH_Y_3_vel");
//  fourteen_vel_buff->text(fourteen_vel.str().c_str());
//  fourteen_vel_disp->buffer(fourteen_vel_buff);
//  
//  std::stringstream fourteen_tor;
//  fourteen_tor << /*getenv("14_LF_X_1_tor") << " " <<*/ getenv("14_LF_Y_2_tor") << " " << getenv("14_LF_Y_3_tor")
//  << " " << /*getenv("14_RF_X_1_tor") << " " <<*/ getenv("14_RF_Y_2_tor") << " " << getenv("14_RF_Y_3_tor")
//  << " " << /*getenv("14_LH_X_1_tor")<< " " <<*/ getenv("14_LH_Y_2_tor") << " " << getenv("14_LH_Y_3_tor")
//  << " " << /*getenv("14_RH_X_1_tor") << " " <<*/ getenv("14_RH_Y_2_tor") << " " << getenv("14_RH_Y_3_tor");
//  fourteen_tor_buff->text(fourteen_tor.str().c_str());
//  fourteen_tor_disp->buffer(fourteen_tor_buff);
  
  Fl_Button ebut(win->w()-125,win->h()-25,50,25,"Exit");
  ebut.callback(Exit_CB);
  
  Fl_Button cbut(win->w()-75,win->h()-25,75,25,"Run Test");
  cbut.callback(Butt_CB);
  
  win->show();
  
  int RETURN_FLAG = Fl::run();
  
  return RETURN_FLAG;
}

