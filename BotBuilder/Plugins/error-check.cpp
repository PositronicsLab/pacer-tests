

#include <Pacer/controller.h>
#include "plugin.h"

void printQandQd()
{
  boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);
  std::map<std::string, Ravelin::VectorNd > q, qd,u;

  std::vector<double> torque_limit;
  std::vector<double> velocity_limit;

  std::ofstream errOut;
  errOut.open("/home/brad/Desktop/Tests/pacer-tests/trotting/matlabData.txt", std::ios::app);

  std::vector<std::string> joint_names = ctrl->get_data<std::vector<std::string> >("init.joint.id");
  std::vector<double> joint_dofs = ctrl->get_data<std::vector<double> >("init.joint.dofs");
  ctrl->get_data<std::vector<double> >("init.joint.limits.u",torque_limit);
  ctrl->get_data<std::vector<double> >("init.joint.limits.qd",velocity_limit);
  ctrl->get_joint_value(Pacer::Robot::position_goal, q);
  ctrl->get_joint_value(Pacer::Robot::velocity_goal, qd);
  ctrl->get_joint_value(Pacer::Robot::load_goal, u);

  for (int i=0, ii=0; i<joint_names.size(); i++) 
  {
    for (int j=0; j<joint_dofs[i]; j++,ii++) 
    {
        std::ostringstream s;
        s << joint_names[i] << "_vel";
        std::string line=s.str();
        s.clear();//clear any bits set
        s.str(std::string());
        s << qd[joint_names[i]][j]-velocity_limit[ii];
        
        setenv(line.c_str(),s.str().c_str(),1);
    }
  }

  for (int i=0, ii=0; i<joint_names.size(); i++) 
  {
    for (int j=0; j<joint_dofs[i]; j++,ii++) 
    {
        std::ostringstream s;
        s << joint_names[i] << "_tor";
        std::string line=s.str();
        s.clear();//clear any bits set
        s.str(std::string());
        s << qd[joint_names[i]][j]-velocity_limit[ii];
        setenv(line.c_str(),s.str().c_str(),1);
    }
 }
  
errOut << getenv("lenF1") << getenv("lenF2") << getenv("lenH1") << getenv("lenH2") << getenv("base_size_length") << getenv("base_size_width")
       << getenv("base_size_height") << getenv("density") << getenv("linkRad") << getenv("footRad") << getenv("footLen")
       << getenv("LF_X_1_vel") << getenv("LF_Y_2_vel") << getenv("LF_Y_3_vel") << getenv("RF_X_1_vel") << getenv("RF_Y_2_vel")
       << getenv("RF_Y_3_vel") << getenv("LH_X_1_vel") << getenv("LF_Y_2_vel") << getenv("LH_Y_3_vel") << getenv("RH_X_1_vel")
       << getenv("RH_Y_2_vel") << getenv("RH_Y_3_vel") << getenv("LF_X_1_tor") << getenv("LF_Y_2_tor")<< getenv("LF_Y_3_tor") 
       << getenv("RF_X_1_tor") << getenv("RF_Y_2_tor") << getenv("RF_Y_3_tor") << getenv("LH_X_1_tor") << getenv("LF_Y_2_tor") 
       << getenv("LH_Y_3_tor") << getenv("RH_X_1_tor") << getenv("RH_Y_2_tor") << getenv("RH_Y_3_tor") << "\n";
}

void loop(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);
  
  Ravelin::VectorNd generalized_fext = ctrl->get_generalized_value(Pacer::Robot::load);
/*
  // Unstable simulation.
  if(generalized_fext.norm() > 1e8)
    throw std::runtime_error("Robot exploded!");

  // Fell off edge
  Ravelin::Vector3d x;
  ctrl->get_data<Ravelin::Vector3d>("base.state.x",x);
  if(x[2] < -1)
    throw std::runtime_error("Robot fell!");

  boost::shared_ptr<Ravelin::Pose3d> base_link_frame(new Ravelin::Pose3d(ctrl->get_data<Ravelin::Pose3d>("base_link_frame")));

  Ravelin::Vector3d up(0,0,1,base_link_frame);
  up = Ravelin::Pose3d::transform_vector(Pacer::GLOBAL,up);
  if(up[2] < 0)
  {
    throw std::runtime_error("Robot flipped over!");
  }

    
  std::vector< boost::shared_ptr< Pacer::Robot::contact_t> > c;
  ctrl->get_link_contacts("BODY0",c);
  if(c.size() != 0)
    throw std::runtime_error("Robot body contacted ground!");
    
 // bounced too high!
  Ravelin::Vector3d z;
  ctrl->get_data<Ravelin::Vector3d>("base.state.com",z);
  if(z.z() >.1)
    throw std::runtime_error("Robot Bounced!");*/

  std::map<std::string, Ravelin::VectorNd > q, qd, u;
  ctrl->get_joint_value(Pacer::Robot::position_goal, q);
  ctrl->get_joint_value(Pacer::Robot::velocity_goal, qd);
  ctrl->get_joint_value(Pacer::Robot::load_goal, u);
  


  std::vector<std::string> joint_names = ctrl->get_data<std::vector<std::string> >("init.joint.id");
  std::vector<double> joint_dofs = ctrl->get_data<std::vector<double> >("init.joint.dofs");
  std::vector<double> torque_limit;
  bool apply_torque_limit = ctrl->get_data<std::vector<double> >("init.joint.limits.u",torque_limit);

  std::vector<double> velocity_limit;
  bool apply_velocity_limit = ctrl->get_data<std::vector<double> >("init.joint.limits.qd",velocity_limit);

  for (int i=0, ii=0; i<joint_names.size(); i++) {
    for (int j=0; j<joint_dofs[i]; j++,ii++) {
      // If motor speed limit met, cancel torque
      // (if applied in direction of limit)
        if (qd[joint_names[i]][j] > velocity_limit[ii]) {
          std::cout << joint_names[i] << ": qd["<<j<<"]= " << qd[joint_names[i]][j] << " exceeds velocity limit: " << velocity_limit[ii] << "\n";
          printQandQd();
          exit(6);
        } else if  (qd[joint_names[i]][j] < -velocity_limit[ii]) {
          std::cout << joint_names[i] << ": qd["<<j<<"]= " << qd[joint_names[i]][j] << " exceeds negative velocity limit: " << -velocity_limit[ii] << "\n";
          printQandQd();
          exit(6);
        }



        // Limit torque
        if (u[joint_names[i]][j] > torque_limit[ii]) {
          std::cout << joint_names[i] << ": u["<<j<<"]= " << u[joint_names[i]][j] << " exceeds torque limit: " << torque_limit[ii] << ", setting to " << torque_limit[ii] << "\n";
          printQandQd();
          exit(6);
        } else if  (u[joint_names[i]][j] < -torque_limit[ii]) {
          std::cout << joint_names[i] << ": u["<<j<<"]= " << u[joint_names[i]][j] << " exceeds torque limit: " << -torque_limit[ii] << ", setting to " << -torque_limit[ii] << "\n";
          printQandQd();
          exit(6);
        }

    }
  }
  
}


void setup(){
}
