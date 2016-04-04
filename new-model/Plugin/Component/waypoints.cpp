/****************************************************************************
 * Copyright 2014 Samuel Zapolsky
 * This library is distributed under the terms of the Apache V2.0
 * License (obtainable from http://www.apache.org/licenses/LICENSE-2.0).
 *
 * This code shows how to control Pacer to get a robot to walk in a Figure-8
 * pattern.
 ****************************************************************************/
#include <Pacer/controller.h>
#include <Pacer/utilities.h>
#include <iostream>
#include <fstream>
#include "plugin.h"
#include <math.h>

typedef std::pair<double,double> Point;

void loop(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);
  std::ofstream myfile;
  myfile.open("/home/brad/Desktop/Testing.txt",std::ios::app);
  std::fstream time;
  time.open("/home/brad/Desktop/Testing3.txt",std::ios::in | std::ios::out);
  std::fstream line;
  line.open("/home/brad/Desktop/Testing2.txt",std::ios::in | std::ios::out);
 int t;

   
	
  const unsigned X=0,Y=1,Z=2,THETA=5;
    // World frame
    boost::shared_ptr<Ravelin::Pose3d>
        environment_frame(new Ravelin::Pose3d());
    VISUALIZE(POSE(*environment_frame.get(),0.1));

      boost::shared_ptr<Ravelin::Pose3d>
        base_horizontal_frame(new Ravelin::Pose3d(ctrl->get_data<Ravelin::Pose3d>("base_horizontal_frame")));

    Ravelin::Vector3d com(base_horizontal_frame->x.data());
  
  Ravelin::VectorNd base_xd;
  ctrl->get_base_value(Pacer::Robot::velocity,base_xd);

    /////////////////////
    /// SET VARIABLES ///

    // Command robot to walk in a direction
    Ravelin::VectorNd command;
    command.set_zero(6);

    double max_forward_speed = ctrl->get_data<double>(plugin_namespace+".max-forward-speed");
    double max_strafe_speed  = ctrl->get_data<double>(plugin_namespace+".max-strafe-speed");
    double max_turn_speed    = ctrl->get_data<double>(plugin_namespace+".max-turn-speed");

    // if FALSE, drive like a car (x and theta)
    // Q: if TRUE, turn toward waypoint while stepping in direction of waypoint
    bool HOLONOMIC = false;

    /////////////////////////////////////
    /// Assign WAYPOINTS in the plane ///
    static std::vector<Point> waypoints;
  
    std::vector<double> waypoints_vec = ctrl->get_data<std::vector<double> >(plugin_namespace+".waypoints");
  
    // if (waypoints not inititalized) OR (waypoints changed) OR (only one waypoint)
    // update waypoints
    if(waypoints.empty() || waypoints_vec.size()/2 != waypoints.size() || waypoints_vec.size() == 2){
      waypoints.clear();
      for(int i=0;i<waypoints_vec.size();i+=2)
        waypoints.push_back(Point(waypoints_vec[i],waypoints_vec[i+1]));
    }
        
    /////////////////////////////
    /// CHOOSE NEXT WAYPOINT  ///

    int num_waypoints = waypoints.size();
  
    // if waypoints are empty
    // do not do anything (do not update SE2 command)
    if(num_waypoints != 0){
      Ravelin::Vector3d goto_point;

      static int waypoint_index = 0;
      static Ravelin::Vector3d
      next_waypoint(waypoints[waypoint_index].first,waypoints[waypoint_index].second,0,environment_frame);
	
      if(waypoints.size() == 1){
        waypoint_index = 0;
        next_waypoint = Ravelin::Vector3d(waypoints[waypoint_index].first,waypoints[waypoint_index].second,0,environment_frame);
      }
      double distance_to_wp = (Ravelin::Origin3d(next_waypoint.data()) - Ravelin::Origin3d(com[X],com[Y],0)).norm();

      double max_dist = ctrl->get_data<double>(plugin_namespace+".tolerance");
      if( distance_to_wp < max_dist){
	line << next_waypoint.x() << " ";
	line << next_waypoint.y() << " ";
	line << com.x() << " ";
        line << com.y() << '\n';
	

      waypoint_index = (waypoint_index+1)% num_waypoints;
      if(waypoint_index == 0)
        exit(0);
      next_waypoint = Ravelin::Vector3d(waypoints[waypoint_index].first,waypoints[waypoint_index].second,0,environment_frame);
      }
	time >> t;
	time.flush();
	if(t==0)
	{
		
		line << next_waypoint.x() << " ";
		line << next_waypoint.y() << " ";
		line << com.x() << " ";
        	line << com.y();
	}
	
	double lineX1; 
	double lineY1;
	double lineX2;
	double lineY2;
	line >> lineX1 >> lineY1 >> lineX2 >> lineY2; 
	double pointX=com.x(); 
	double pointY=com.y();
	double distance;
	line.close();
	time.seekg(0,std::ios::beg);
	time << t+1;
	time.close();

	double diffX = lineX2 - lineX1;
    	float diffY = lineY2 - lineY1;
    if ((diffX == 0) && (diffY == 0))
    {
        diffX = pointX - lineX1;
        diffY = pointY - lineY1;
        distance = sqrt(diffX * diffX + diffY * diffY);
    }

    float t = ((pointX - lineX1) * diffX + (pointY - lineY1) * diffY) / (diffX * diffX + diffY * diffY);

    if (t < 0)
    {
        //point is nearest to the first point i.e x1 and y1
        diffX = pointX - lineX1;
        diffY = pointY - lineY1;
    }
    else if (t > 1)
    {
        //point is nearest to the end point i.e x2 and y2
        diffX = pointX - lineX2;
        diffY = pointY - lineY2;
    }
    else
    {
        //if perpendicular line intersect the line segment.
        diffX = pointX - (lineX1 + t * diffX);
        diffY = pointY - (lineY1 + t * diffY);
    }

    //returning shortest distance
    distance = sqrt(diffX * diffX + diffY * diffY);
   	std::fstream dist;
 	 dist.open("/home/brad/Desktop/Testing4.txt",std::ios::in | std::ios::out);
	double oldDist;
	dist >> oldDist;
	dist.seekg(0,std::ios::beg);
	dist << distance+oldDist;
	dist.close();
	
      VISUALIZE(RAY(next_waypoint,com,Ravelin::Vector3d(1,0.5,0),0.05));
      
      

      for(int i=0;i<num_waypoints;i++){
          Ravelin::Vector3d wp(waypoints[i].first,waypoints[i].second,0,environment_frame);
          
      VISUALIZE(POINT(wp,Ravelin::Vector3d(1,0.5,0),0.1));
      }

      goto_point = next_waypoint;

      ///////////////////////
      /// GO TO WAYPOINT  ///

      // Find direction to waypoint from robot position
      Ravelin::Vector3d goto_direction =
        Ravelin::Vector3d(goto_point[X],goto_point[Y],0,environment_frame)
        - Ravelin::Vector3d(com[X],com[Y],0,environment_frame);
      goto_direction = Ravelin::Pose3d::transform_vector(base_horizontal_frame,goto_direction);
      goto_direction.normalize();

      double angle_to_goal = atan2(goto_direction[Y],goto_direction[X]);
      myfile.close();

      // If robot is facing toward goal already, walk in that direction
      if(fabs(angle_to_goal) < M_PI_4){
        if(HOLONOMIC){
          command[Y] = goto_direction[Y]*max_strafe_speed;
        }
        command[X] = goto_direction[X]*max_forward_speed;
        command[THETA] = angle_to_goal;
      } else {
        command[THETA] = Utility::sign(angle_to_goal)*max_turn_speed;
        if(HOLONOMIC){
          command[X] = goto_direction[X]*max_forward_speed;
          command[Y] = goto_direction[Y]*max_strafe_speed;
        } else {
          command[X] = 0;
          command[Y] = 0;
        }
      }
    
//      double slow_down_tol = 0.1;
//      if(distance_to_wp < slow_down_tol)
//        command *= distance_to_wp*slow_down_tol+0.05;
    
      Ravelin::Origin3d command_SE2(command[X],command[Y],command[THETA]);
      ctrl->set_data<Ravelin::Origin3d>("SE2_command",command_SE2);
    }

}
void setup(){
 
}
