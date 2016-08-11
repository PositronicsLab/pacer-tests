#include <Pacer/controller.h>
#include "plugin.h"
#include <boost/tokenizer.hpp>
#include <sys/stat.h>
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>

void loop(){


std::fstream myfile;
   myfile.open ("/tmp/debug.txt", std::ios::in | std::ios::out | std::ios::ate);
   myfile << "----------------------------trajectory-table.cpp---------------------------------";
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
   myfile << "lenF1: " << getenv("lenF1") << "\n";
   myfile << "lenF2: " << getenv("lenF2") << "\n";
   myfile << "lenH1: " << getenv("lenH1") << "\n";
   myfile << "lenH2: " << getenv("lenH2") << "\n";
   myfile << "base_size_length: " << getenv("base_size_length") << "\n";
   myfile << "base_size_width: " << getenv("base_size_width") << "\n";
   myfile << "base_size_height: " << getenv("base_size_height") << "\n";
   myfile << "density: " << getenv("density") << "\n";
   myfile << "linkRad: " << getenv("linkRad") << "\n";
   myfile << "footRad: " << getenv("footRad") << "\n";
   myfile << "footLen: " << getenv("footLen") << "\n";
   myfile << "KINEMATIC: " << getenv("KINEMATIC") << "\n";
   myfile.close();





pid_t pid;





boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);

  double numIter= std::stod(getenv("curr_iter"));
  double testDur= std::stod(getenv("test_dur"));
  double currVel= std::stod(getenv("curr_vel")); 
  double currLine=std::stod(getenv("curr_line"));
  std::ostringstream s;
  if(numIter>=testDur)
   {
        setenv("curr_iter","0",1);
        std::string line2=getenv("BUILDER_SCRIPT_PATH");
	
	line2+="/setup-plugins-play.sh";
        
	pid=fork();
	if(pid==0)
        {execl(line2.c_str(), line2.c_str(), (char *) 0);}
pause();
	}
	
   else
   {
      numIter+=1;
      s << numIter;
      setenv("curr_iter",s.str().c_str(),1);
   }
  
  std::vector<std::vector<Ravelin::Origin3d> > allRowVals;
  std::vector<std::vector<Ravelin::VectorNd> > allBodyVals;
  double num_rows;
  const  std::vector<std::string> eef_names = ctrl->get_data<std::vector<std::string> >("init.end-effector.id");

  ctrl->get_data("eef_vals", allRowVals);
  ctrl->get_data("body_vals", allBodyVals);
  
  ctrl->get_data("num_pose_rows",num_rows);
  
for(int foot=0, vec=0;foot<eef_names.size(); foot++,vec+3)
{
	        ctrl->set_data<Ravelin::Origin3d>(eef_names[foot]+".goal.x",allRowVals[currLine][vec]);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[foot]+".goal.xd",allRowVals[currLine][vec+1]);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[foot]+".goal.xdd",allRowVals[currLine][vec+2]);

                ctrl->set_end_effector_value(eef_names[foot],Pacer::Controller::position_goal,allRowVals[currLine][vec]);
                ctrl->set_end_effector_value(eef_names[foot],Pacer::Controller::velocity_goal,allRowVals[currLine][vec+1]);
                ctrl->set_end_effector_value(eef_names[foot],Pacer::Controller::acceleration_goal,allRowVals[currLine][vec+2]);
}
            ctrl->set_base_value(Pacer::Controller::position_goal,allBodyVals[currLine][0]);
            ctrl->set_base_value(Pacer::Controller::velocity_goal,allBodyVals[currLine][1]);
        s.clear();
        s.str(std::string());
        currLine+=1;
        s << currLine;
    setenv("curr_line",s.str().c_str(),1);
    
    if(currLine>=num_rows && std::stod(getenv("curr_vel"))<std::stod(getenv("max_vel")))
    {
        setenv("curr_line","0",1);
        setenv("curr_iter","0",1);


	double curr_vel=std::stod(getenv("curr_vel"));
        curr_vel+=std::stod(getenv("delta_v"));
        std::ostringstream s;
        s << curr_vel;
        std::string line=s.str();

	setenv("curr_vel",line.c_str(),1);

        std::string line3=getenv("BUILDER_SCRIPT_PATH");
	
	line3+="/setup-plugins-play.sh";
        
	pid=fork();
	if(pid==0)
        {execl(line3.c_str(), line3.c_str(), (char *) 0);}
	pause();
	

    	
    }
}

void setup(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);

std::vector<std::vector<Ravelin::Origin3d> > allRowVals;
std::vector<std::vector<Ravelin::VectorNd> > allBodyVals;
std::vector<Ravelin::Origin3d> rowVals;
std::vector<Ravelin::VectorNd> bodyVals;
 //string to hold extracted values, and size_type to keep track of location in the line
  std::string line;

  //get the end effector names
  const  std::vector<std::string>
  eef_names = ctrl->get_data<std::vector<std::string> >("init.end-effector.id");

  double modelNo=std::stod(getenv("modelNo"));
  double currVel=std::stod(getenv("curr_vel"));
  double init=std::stod(getenv("curr_line"));
  
   std::ostringstream s;
    s << modelNo << "-" << currVel << "-" << "PoseSet.txt";
    std::string filename = s.str();
  std::ifstream myfile(filename);

int line_count=0;

//put everything into a vector of vector of vectors and store it
while(std::getline(myfile,line))
{
       typedef boost::tokenizer<boost::char_separator<char> > 
            tokenizer;
            boost::char_separator<char> sep(" ");
            tokenizer tokens(line, sep);
            tokenizer::iterator tok_iter = tokens.begin();

        rowVals.clear();
        bodyVals.clear();

for(int i=0;i<eef_names.size();i++)
{
     
	rowVals.push_back(Ravelin::Origin3d(std::stod(*tok_iter),std::stod(*(std::next(tok_iter,1))),std::stod(*(std::next(tok_iter,2)))));
        rowVals.push_back(Ravelin::Origin3d(std::stod(*(std::next(tok_iter,3))),std::stod(*(std::next(tok_iter,4))),std::stod(*(std::next(tok_iter,5)))));
        rowVals.push_back(Ravelin::Origin3d(std::stod(*(std::next(tok_iter,6))),std::stod(*(std::next(tok_iter,7))),std::stod(*(std::next(tok_iter,8)))));
       
          std::advance(tok_iter,9);
}

bodyVals.push_back(Ravelin::VectorNd::construct_variable(7,std::stod(*tok_iter),std::stod(*(std::next(tok_iter,1))),std::stod(*(std::next(tok_iter,2))),std::stod(*(std::next(tok_iter,3))),std::stod(*(std::next(tok_iter,4))),std::stod(*(std::next(tok_iter,5))),std::stod(*(std::next(tok_iter,6)))));

            bodyVals.push_back(Ravelin::VectorNd::construct_variable(6,std::stod(*(std::next(tok_iter,7))),std::stod(*(std::next(tok_iter,8))),std::stod(*(std::next(tok_iter,9))),std::stod(*(std::next(tok_iter,10))),std::stod(*(std::next(tok_iter,11))),std::stod(*(std::next(tok_iter,12)))));

allRowVals.push_back(rowVals);
allBodyVals.push_back(bodyVals);

	line_count++;
}
ctrl->set_data<double>("num_pose_rows",line_count);

ctrl->set_data<std::vector<std::vector<Ravelin::Origin3d> > >("eef_vals", allRowVals);
ctrl->set_data<std::vector<std::vector<Ravelin::VectorNd> > >("body_vals", allBodyVals);


for(int foot=0, vec=0;foot<eef_names.size(); foot++,vec+3)
{
	        ctrl->set_data<Ravelin::Origin3d>(eef_names[foot]+".init.x",allRowVals[init][vec]);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[foot]+".init.xd",allRowVals[init][vec+1]);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[foot]+".init.xdd",allRowVals[init][vec+2]);

                ctrl->set_end_effector_value(eef_names[foot],Pacer::Controller::position,allRowVals[init][vec]);
                ctrl->set_end_effector_value(eef_names[foot],Pacer::Controller::velocity,allRowVals[init][vec+1]);
                ctrl->set_end_effector_value(eef_names[foot],Pacer::Controller::acceleration,allRowVals[init][vec+2]);
}
            ctrl->set_base_value(Pacer::Controller::position,allBodyVals[init][0]);
            ctrl->set_base_value(Pacer::Controller::velocity,allBodyVals[init][1]);
std::cout << "\n" << "\n" << init << "\n" << "\n";

myfile.close();
}
