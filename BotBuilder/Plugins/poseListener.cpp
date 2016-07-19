#include <Pacer/controller.h>
#include "plugin.h"
#include <boost/tokenizer.hpp>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>

void loop(){
    boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);

     //initializing variables
     std::fstream file;
     std::string filename;
     Ravelin::VectorNd command_x,command_xd;

  double modelNo= std::stod(getenv("filename"));
  double currVel= std::stod(getenv("curr_vel"));
    
    std::ostringstream s;
    s << modelNo << "-" << currVel << "-" << "PoseSet.txt";
    filename = s.str();

   std::cout << "I'm here" << "\n" << "\n" << "\n";
     //get the position, base command, and end effector names
    
     std::vector<std::string> eef_names = ctrl->get_data<std::vector<std::string> >(plugin_namespace+".id");
      
     //open the file that is being written to
     file.open(filename, std::fstream::app|std::fstream::out);

     //get the desired position, velocity, and acceleration for each end effector and put that in the file
     for (int i=0; i<eef_names.size(); i++) 
     {
            Ravelin::Origin3d pos_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::position_goal);
            Ravelin::Origin3d vel_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::velocity_goal);
            Ravelin::Origin3d accel_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::acceleration_goal);

            file << pos_des[0] << " " << pos_des[1] << " " << pos_des[2] << " " 
                 << vel_des[0] << " " << vel_des[1] << " " << vel_des[2] << " " 
                 << accel_des[0] << " " << accel_des[1] << " " << accel_des[2] << " "; 
     }
     
     //grab base position and base command and put those in the file and return to start the next row for the next iteration
     command_x=ctrl->get_base_value(Pacer::Controller::position);
     ctrl->get_data<Ravelin::VectorNd>("base-command",command_xd);

     file << command_x[0] << " " << command_x[1] << " " << command_x[2] << " " << command_x[3] << " " << command_x[4] << " " << command_x[5]  << " " << command_x[6] <<" ";
     file << command_xd[0] << " " << command_xd[1] << " " << command_xd[2] << " " << command_xd[3] << " " << command_xd[4] << " " << command_xd[5] 
     << "\n";
     

     //close the file
     file.close();
 std::cout << "now I'm here" << "\n" << "\n" << "\n";
}

void setup(){
	boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);

        

}
