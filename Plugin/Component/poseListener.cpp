#include <Pacer/controller.h>
#include "plugin.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>


//return true if the file exists, return false otherwise
bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

//turn an integer into a string
std::string IntToStr(int n) 
{
    std::stringstream result;
    result << n;
    return result.str();
}

void loop(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);
   std::ifstream durTest;
   std::string dur;
   durTest.open("/home/brad/Desktop/Poses/iterCount.txt");
   double duration=0;
   ctrl->get_data<double>("gait-planner.gait-duration",duration);
   std::getline(durTest,dur);
   durTest.close();
   if(std::stod(dur)>=(duration*10*10*10))
   {
     exit(0);
   }
   else
   {
     std::ofstream durTest2;
     durTest2.open("/home/brad/Desktop/Poses/iterCount.txt");
     double hold = std::stod(dur)+1;
     durTest2 << hold;
   }
   durTest.close();
 
        //initializing variables
        std::fstream file;
	int i=0;
        std::string filename = "/home/brad/Desktop/Poses/PoseSet.txt";
        Ravelin::VectorNd command_x,command_xd;

        //get the position, base command, and end effector names
        command_x=ctrl->get_base_value(Pacer::Controller::position);
        
        ctrl->get_data<Ravelin::VectorNd>("base-command",command_xd);
        std::vector<std::string> eef_names = ctrl->get_data<std::vector<std::string> >(plugin_namespace+".id");
      
      //open the file that is being written to
      file.open(filename, std::fstream::app|std::fstream::out);

      //get the desired position, velocity, and acceleration for each end effector and put that in the file
     for (int i=0; i<eef_names.size(); i++) 
     {
       
           
            Ravelin::Origin3d pos_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::position_goal);
            Ravelin::Origin3d vel_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::velocity_goal);
            Ravelin::Origin3d accel_des =  ctrl->get_end_effector_value(eef_names[i],Pacer::Robot::acceleration_goal);
            file << pos_des[0] << " " << pos_des[1] << " " << pos_des[2] << " " << vel_des[0] << " " << vel_des[1] << " " << vel_des[2] << " " << accel_des[0] << " " << accel_des[1] << " " << accel_des[2] << " ";
       
     }
     
     //grab base position and base command and put those in the file and return to start the next row for the next iteration
     file << command_xd[0] << " " << command_xd[1] << " " << command_xd[2] << " " << command_xd[3] << " " << command_xd[4] << " " << command_xd[5] << " ";
     file << command_x[0] << " " << command_x[1] << " " << command_x[2] << " " << command_x[3] << " " << command_x[4] << " " << command_x[5]  << " " << command_x[6] <<"\n";

     //close the file
     file.close();
}

void setup(){
}
