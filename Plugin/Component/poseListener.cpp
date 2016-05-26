#include <Pacer/controller.h>
#include "plugin.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>

bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

std::string IntToStr(int n) 
{
    std::stringstream result;
    result << n;
    return result.str();
}

void loop(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);
        std::fstream file;
	int i=0;
        std::string filename = "/home/brad/Desktop/Poses/PoseSet.txt";
       
        Ravelin::VectorNd command;
        ctrl->get_data<Ravelin::VectorNd>("base-command",command);
        std::vector<std::string> eef_names = ctrl->get_data<std::vector<std::string> >(plugin_namespace+".id");
      

      file.open(filename, std::fstream::app|std::fstream::out);
     for (int i=0; i<eef_names.size(); i++) 
     {
       
            
            Ravelin::Origin3d pos_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::position_goal);
            Ravelin::Origin3d vel_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::velocity_goal);
            Ravelin::Origin3d accel_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::acceleration_goal);
            file << pos_des[0] << " " << pos_des[1] << " " << pos_des[2] << " " << vel_des[0] << " " << vel_des[1] << " " << vel_des[2] << " " << accel_des[0] << " " << accel_des[1] << " " << accel_des[2] << " ";
       
     }

     file << command[0] << " " << command[1] << " " << command[2] << " " << command[3] << " " << command[4] << " " << command[5] << "\n";
     std::cout << "Command is this big: " << command.size() << "\n" << "\n";
file.close();
}

void setup(){
}
