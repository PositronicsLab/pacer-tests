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

void loop(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);

  double numIter;
  double testDur;
  double currVel, currLine;

  ctrl->get_data("test_duration",testDur);
  ctrl->get_data("test_iterations", numIter);
  ctrl->get_data("currLine", currLine);
  ctrl->get_data("currVel", currVel);
  
  if(numIter>=testDur)
   {
	exit(currLine);
   }
   else
   {
      ctrl->set_data("test_iterations",++numIter);
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

    ctrl->set_data("currLine", ++currLine);
    
    if(currLine>=num_rows)
    {
    	return currVel;
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

  //open the lookup table(PoseSet), and the file containing the current row of values to use
  
  std::ifstream initLine ("trackVars.txt");

  //get the current row to be used, and convert it to a double
  std::getline(initLine,line);
	typedef boost::tokenizer<boost::char_separator<char> > 
            tokenizer;
            boost::char_separator<char> sep(" ");
            tokenizer tokens(line, sep);
            tokenizer::iterator tok_iter = tokens.begin();

  double init=std::stod(*(std::next(tok_iter,4)));
  double duration=std::stod(*(std::next(tok_iter,5)));
  double modelNo=std::stod(*tok_iter);
  double currVel=std::stod(*(std::next(tok_iter,2)));
   initLine.close();

  ctrl->set_data<double>("test_duration", duration);
  ctrl->set_data<double>("test_iterations", 0);
  ctrl->set_data<double>("currVel", currVel);
  
  
  std::string filename = modelNo + "-" + currVel + "-" + "PoseSet.txt";
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

ctrl->set_data<double>("currLine",++init);

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

myfile.close();
}
