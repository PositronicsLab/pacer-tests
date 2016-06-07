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
  //string to hold extracted values, and size_type to keep track of location in the line
  std::string line;
  exit(0);
  /*
  //storage for each x/y/z value of the position, velocity, and acceleration of the end effectors
  double eef_x_x_0, eef_x_y_0, eef_x_z_0, eef_xd_x_0, eef_xd_y_0, eef_xd_z_0, eef_xdd_x_0, eef_xdd_y_0, eef_xdd_z_0;
  double eef_x_x_1, eef_x_y_1, eef_x_z_1, eef_xd_x_1, eef_xd_y_1, eef_xd_z_1, eef_xdd_x_1, eef_xdd_y_1, eef_xdd_z_1;
  double eef_x_x_2, eef_x_y_2, eef_x_z_2, eef_xd_x_2, eef_xd_y_2, eef_xd_z_2, eef_xdd_x_2, eef_xdd_y_2, eef_xdd_z_2;
  double eef_x_x_3, eef_x_y_3, eef_x_z_3, eef_xd_x_3, eef_xd_y_3, eef_xd_z_3, eef_xdd_x_3, eef_xdd_y_3, eef_xdd_z_3;
  double base_x_0, base_x_1, base_x_2, base_x_3, base_x_4, base_x_5, base_x_6,
         base_xd_0, base_xd_1, base_xd_2, base_xd_3, base_xd_4, base_xd_5;
  //Origin3ds for position(x), velocity(xd), and acceleration(xdd)
  Ravelin::Origin3d newX, newXd, newXdd;

  //VectorNds for the base values
  Ravelin::VectorNd newBaseX, newBaseXd;

  //get the end effector names
  const  std::vector<std::string>
  eef_names = ctrl->get_data<std::vector<std::string> >("init.end-effector.id");

  //open the lookup table(PoseSet), and the file containing the current row of values to use
  std::ifstream myfile ("/home/brad/Desktop/Poses/PoseSet.txt");
  std::ifstream currLine ("/home/brad/Desktop/Poses/currLine.txt");

  //get the current row to be used, and convert it to a double
  getline(currLine,line);
  double current=std::stod(line);
   


  if (myfile.is_open())
  {
    //get to the line that is needed
    for( int i = 0; i < current; i++ )
    {
        getline (myfile,line);
        //once the desired line has been reached, put it in the line variable and feed those values into pacer
        if(i==current-1)
        {  
            
            typedef boost::tokenizer<boost::char_separator<char> > 
            tokenizer;
            boost::char_separator<char> sep(" ");
            tokenizer tokens(line, sep);
            tokenizer::iterator tok_iter = tokens.begin();
            //for each end effector, get the x,y,z values of x/xd/xdd, but those into their respective Origin3ds, and send those Origins to Pacer as goal states
            // the values are always in the order LF to RF to LH to RH to Body.

            	eef_x_x_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_y_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_z_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_x_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_y_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_z_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_x_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_y_0 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_z_0 = std::stod(*tok_iter);
                ++tok_iter;
                     
                eef_x_x_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_y_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_z_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_x_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_y_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_z_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_x_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_y_1 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_z_1 = std::stod(*tok_iter);
                ++tok_iter;
                  
                eef_x_x_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_y_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_z_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_x_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_y_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_z_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_x_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_y_2 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_z_2 = std::stod(*tok_iter);
                ++tok_iter;
                  
                eef_x_x_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_y_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_x_z_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_x_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_y_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xd_z_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_x_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_y_3 = std::stod(*tok_iter);
                ++tok_iter;
            	eef_xdd_z_3 = std::stod(*tok_iter);
                ++tok_iter;
                
                



 

                newX = Ravelin::Origin3d(eef_x_x_0,eef_x_y_0,eef_x_z_0);
                newXd = Ravelin::Origin3d(eef_xd_x_0,eef_xd_y_0,eef_xd_z_0);
                newXdd = Ravelin::Origin3d(eef_xdd_x_0,eef_xdd_y_0,eef_xdd_z_0);
                 
                ctrl->set_data<Ravelin::Origin3d>(eef_names[0]+".goal.x",newX);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[0]+".goal.xd",newXd);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[0]+".goal.xdd",newXdd);

                ctrl->set_end_effector_value(eef_names[0],Pacer::Controller::position_goal,newX);
                ctrl->set_end_effector_value(eef_names[0],Pacer::Controller::velocity_goal,newXd);
                ctrl->set_end_effector_value(eef_names[0],Pacer::Controller::acceleration_goal,newXdd);

                newX = Ravelin::Origin3d(eef_x_x_1,eef_x_y_1,eef_x_z_1);
                newXd = Ravelin::Origin3d(eef_xd_x_1,eef_xd_y_1,eef_xd_z_1);
                newXdd = Ravelin::Origin3d(eef_xdd_x_1,eef_xdd_y_1,eef_xdd_z_1);
                 
                ctrl->set_data<Ravelin::Origin3d>(eef_names[1]+".state.x",newX);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[1]+".state.xd",newXd);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[1]+".state.xdd",newXdd);

                ctrl->set_end_effector_value(eef_names[1],Pacer::Controller::position_goal,newX);
                ctrl->set_end_effector_value(eef_names[1],Pacer::Controller::velocity_goal,newXd);
                ctrl->set_end_effector_value(eef_names[1],Pacer::Controller::acceleration_goal,newXdd);

                newX = Ravelin::Origin3d(eef_x_x_2,eef_x_y_2,eef_x_z_2);
                newXd = Ravelin::Origin3d(eef_xd_x_2,eef_xd_y_2,eef_xd_z_2);
                newXdd = Ravelin::Origin3d(eef_xdd_x_2,eef_xdd_y_2,eef_xdd_z_2);
                 
                ctrl->set_data<Ravelin::Origin3d>(eef_names[2]+".state.x",newX);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[2]+".state.xd",newXd);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[2]+".state.xdd",newXdd);

                ctrl->set_end_effector_value(eef_names[2],Pacer::Controller::position_goal,newX);
                ctrl->set_end_effector_value(eef_names[2],Pacer::Controller::velocity_goal,newXd);
                ctrl->set_end_effector_value(eef_names[2],Pacer::Controller::acceleration_goal,newXdd);

                newX = Ravelin::Origin3d(eef_x_x_3,eef_x_y_3,eef_x_z_3);
                newXd = Ravelin::Origin3d(eef_xd_x_3,eef_xd_y_3,eef_xd_z_3);
                newXdd = Ravelin::Origin3d(eef_xdd_x_3,eef_xdd_y_3,eef_xdd_z_3);
                 
                ctrl->set_data<Ravelin::Origin3d>(eef_names[3]+".state.x",newX);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[3]+".state.xd",newXd);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[3]+".state.xdd",newXdd);

                ctrl->set_end_effector_value(eef_names[3],Pacer::Controller::position_goal,newX);
                ctrl->set_end_effector_value(eef_names[3],Pacer::Controller::velocity_goal,newXd);
                ctrl->set_end_effector_value(eef_names[3],Pacer::Controller::acceleration_goal,newXdd);
           
            

            //get the base x and base-command values and put those into 6 dimensional Ravelin Vectors, and then send those to Pacer 
            base_xd_0 = std::stod(*tok_iter);
            ++tok_iter;
            base_xd_1 = std::stod(*tok_iter);
            ++tok_iter;
            base_xd_2 = std::stod(*tok_iter);
            ++tok_iter;
            base_xd_3 = std::stod(*tok_iter);
            ++tok_iter;
            base_xd_4 = std::stod(*tok_iter);
            ++tok_iter;
            base_xd_5 = std::stod(*tok_iter);
            ++tok_iter;

            base_x_0 = std::stod(*tok_iter);
            ++tok_iter;
            base_x_1 = std::stod(*tok_iter);
            ++tok_iter;
            base_x_2 = std::stod(*tok_iter);
            ++tok_iter;
            base_x_3 = std::stod(*tok_iter);
            ++tok_iter;
            base_x_4 = std::stod(*tok_iter);
            ++tok_iter;
            base_x_5 = std::stod(*tok_iter);
            ++tok_iter;
            base_x_6 = std::stod(*tok_iter);

        
            newBaseX=Ravelin::VectorNd::construct_variable(7,base_x_0, base_x_1, base_x_2, base_x_3, base_x_4, base_x_5, base_x_6);
            newBaseXd=Ravelin::VectorNd::construct_variable(6,base_xd_0, base_xd_1, base_xd_2, base_xd_3, base_xd_4, base_xd_5);
            
            ctrl->set_base_value(Pacer::Controller::position_goal,newBaseX);
            ctrl->set_base_value(Pacer::Controller::velocity_goal,newBaseXd);
        }
    } 

    //close the files
    myfile.close();
    currLine.close();

  }
  else std::cout << "Unable to open file";
  
  
  
  //to-do, convert this to just an fstream so the file doesn't have to be re-opened
  //increase the counter for what row to use and send that to the holding file for that
  std::ofstream currLine2 ("/home/brad/Desktop/Poses/currLine.txt");  
  current++;
  currLine2 << current;
  currLine2.close();
*/
}

void setup(){
boost::shared_ptr<Pacer::Controller> ctrl(ctrl_weak_ptr);

std::vector<std::vector<Ravelin::VectorNd> > allVals;
std::vector<Ravelin::Origin3d> rowVals;
std::vector<Ravelin::VectorNd> bodyVals;
 //string to hold extracted values, and size_type to keep track of location in the line
  std::string line;

  //get the end effector names
  const  std::vector<std::string>
  eef_names = ctrl->get_data<std::vector<std::string> >("init.end-effector.id");

  //open the lookup table(PoseSet), and the file containing the current row of values to use
  std::ifstream myfile ("/home/brad/Desktop/Poses/PoseSet.txt");
  std::ifstream currLine ("/home/brad/Desktop/Poses/currLine.txt");

  //get the current row to be used, and convert it to a double
  getline(currLine,line);
  double current=std::stod(line);
   


  if (myfile.is_open())
  {
    //get to the line that is needed
    
        getline (myfile,line);
        //once the desired line has been reached, put it in the line variable and feed those values into pacer
       
            
            typedef boost::tokenizer<boost::char_separator<char> > 
            tokenizer;
            boost::char_separator<char> sep(" ");
            tokenizer tokens(line, sep);
            tokenizer::iterator tok_iter = tokens.begin();
            //for each end effector, get the x,y,z values of x/xd/xdd, but those into their respective Origin3ds, and send those Origins to Pacer as goal states
            // the values are always in the order LF to RF to LH to RH to Body.

for(int i=0;i<eef_names.size();i++)
{
     
	rowVals.push_back(Ravelin::Origin3d(std::stod(*tok_iter),std::stod(*(std::next(tok_iter,1))),std::stod(*(std::next(tok_iter,2)))));
        rowVals.push_back(Ravelin::Origin3d(std::stod(*(std::next(tok_iter,3))),std::stod(*(std::next(tok_iter,4))),std::stod(*(std::next(tok_iter,5)))));
        rowVals.push_back(Ravelin::Origin3d(std::stod(*(std::next(tok_iter,6))),std::stod(*(std::next(tok_iter,7))),std::stod(*(std::next(tok_iter,8)))));
        
        	std::advance(tok_iter,8);
}
for(int i=0;i<eef_names.size();i++)
{
                ctrl->set_data<Ravelin::Origin3d>(eef_names[i]+".init.x",rowVals[(3*i)]);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[i]+".init.xd",rowVals[(3*i)+1]);
                ctrl->set_data<Ravelin::Origin3d>(eef_names[i]+".init.xdd",rowVals[(3*i)+2]);

                ctrl->set_end_effector_value(eef_names[i],Pacer::Controller::position,rowVals[(3*i)]);
                ctrl->set_end_effector_value(eef_names[i],Pacer::Controller::velocity,rowVals[(3*i)+1]);
                ctrl->set_end_effector_value(eef_names[i],Pacer::Controller::acceleration,rowVals[(3*i)+2]);	
std::cout << "\n" << "\n" << rowVals[(3*i)] << "\n" << "\n";
std::cout << "\n" << "\n" << rowVals[(3*i)+1] << "\n" << "\n";
std::cout << "\n" << "\n" << rowVals[(3*i)+2] << "\n" << "\n";

}               

            //get the base x and base-command values and put those into 6 dimensional Ravelin Vectors, and then send those to Pacer 
            bodyVals.push_back(Ravelin::VectorNd::construct_variable(6,std::stod(*(std::next(tok_iter,1))),std::stod(*(std::next(tok_iter,2))),std::stod(*(std::next(tok_iter,3))),std::stod(*(std::next(tok_iter,4))),std::stod(*(std::next(tok_iter,5))),std::stod(*(std::next(tok_iter,6)))));
           
bodyVals.push_back(Ravelin::VectorNd::construct_variable(7,std::stod(*(std::next(tok_iter,7))),std::stod(*(std::next(tok_iter,8))),std::stod(*(std::next(tok_iter,9))),std::stod(*(std::next(tok_iter,10))),std::stod(*(std::next(tok_iter,11))),std::stod(*(std::next(tok_iter,12))),std::stod(*(std::next(tok_iter,13)))));

            
            std::cout << "\n" << bodyVals[0] << "\n";
          
            
            std::cout << "\n" << bodyVals[1] << "\n";
           

 std::cout << "\n" << eef_names[0] << "\n";
std::cout << "\n" << eef_names[1] << "\n";
std::cout << "\n" << eef_names[2] << "\n";
std::cout << "\n" << eef_names[3] << "\n";

        
            
            ctrl->set_base_value(Pacer::Controller::position,bodyVals[0]);
            ctrl->set_base_value(Pacer::Controller::velocity,bodyVals[1]);
        
    

    //close the files
    myfile.clear();
    myfile.seekg (0, std::ios::beg);
    myfile.close();
    currLine.close();

  }
  else std::cout << "Unable to open file";
  
  
  
  //to-do, convert this to just an fstream so the file doesn't have to be re-opened
  //increase the counter for what row to use and send that to the holding file for that
  std::ofstream currLine2 ("/home/brad/Desktop/Poses/currLine.txt");  
  current++;
  currLine2 << current;
  currLine2.close();

std::ostringstream strs;
Ravelin::Origin3d workv;
ctrl->get_data("LF_FOOT.init.x",workv);
strs << workv;
std::string str = strs.str();
str.erase(std::remove(str.begin(), str.end(), '['), str.end());
str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
std::cout << "\n" << str << "\n";
std::ifstream myfile2 ("/home/brad/Desktop/Poses/PoseSet.txt");
std::string line2;
int line_count=0;

//put everything into a vector of vector of vectors and store it
while(std::getline(myfile2,line2))
{
	line_count++;
}
ctrl->set_data<double>("num_pose_rows",line_count);
std::cout << "\n" << "\n" << line_count << "\n" << "\n"; 
myfile2.clear();
myfile2.seekg (0, std::ios::beg);

myfile2.close();
myfile2.open("/home/brad/Desktop/Poses/PoseSet.txt");

line_count=0;


while(std::getline(myfile2,line2));
{
	if(strstr(line2.c_str(),str.c_str()))
        {
          ctrl->set_data<double>("init_row",line_count);   
          std::cout << "\n" << "\n" << line_count << "\n" << "\n"; 
        }
   line_count++;
}
myfile2.clear();
myfile2.seekg (0, std::ios::beg);
myfile2.close();
}
