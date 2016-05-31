#include "plugin.h"
#include <Pacer/controller.h>
#include <Pacer/utilities.h>

void loop(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);
  boost::shared_ptr<Ravelin::Pose3d>
        environment_frame(new Ravelin::Pose3d());
    VISUALIZE(POSE(*environment_frame.get(),0.1));

boost::shared_ptr<Ravelin::Pose3d>
        base_horizontal_frame(new Ravelin::Pose3d(ctrl->get_data<Ravelin::Pose3d>("base_horizontal_frame")));

Ravelin::Vector3d goto_point = Ravelin::Vector3d(100,0,0);
Ravelin::Vector3d com(base_horizontal_frame->x.data());

 Ravelin::Vector3d goto_direction =
        Ravelin::Vector3d(goto_point[0],goto_point[1],0,environment_frame)
        - Ravelin::Vector3d(com[0],com[1],0,environment_frame);

      goto_direction = Ravelin::Pose3d::transform_vector(base_horizontal_frame,goto_direction);
      goto_direction.normalize();

  Ravelin::Origin3d command_SE2(goto_direction[0]*ctrl->get_data<double>("waypoints.max-forward-speed"),goto_direction[1]*ctrl->get_data<double>("waypoints.max-strafe-speed"),0);
      ctrl->set_data<Ravelin::Origin3d>("SE2_command",command_SE2);
}

void setup(){
}
