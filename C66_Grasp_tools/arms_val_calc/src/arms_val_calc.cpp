#include <ros/ros.h>
#include <math.h>
#include <Eigen/Dense>
#include <arms_val_calc/arms_val_calc.h>
#include <sensor_msgs/JointState.h>

class arms_val_calculator{
private:
	double q0_l,q1_l,q2_l,q3_l,q4_l,q5_l;
	double q0_r,q1_r,q2_r,q3_r,q4_r,q5_r;
	Eigen::MatrixXf l_jc,r_jc;
	ros::NodeHandle nh_;
	ros::Subscriber joint_states;
	ros::ServiceServer arms_val_calc_service_;
	std::map <std::string, int> joints;
	std::vector<double> positions;


public:
	arms_val_calculator(){

		l_jc.resize(6,6),r_jc.resize(6,6);
		joint_states = nh_.subscribe("/atlas/joint_states",100,&arms_val_calculator::joint_states_CB,this);
		arms_val_calc_service_= nh_.advertiseService("arms_val_calc_srv",&arms_val_calculator::val_calc_srv_CB,this);

	}

	~arms_val_calculator(){}

	void joint_states_CB(const sensor_msgs::JointStateConstPtr &state){
		for(unsigned int i=0; i < state->name.size(); i++){
			joints[state->name[i]] = i;
		}
		/*left subscribers*/
		/*q0_l=states_msg->position[15];
    q1_l=states_msg->position[13];
    q2_l=states_msg->position[12];
    q3_l=states_msg->position[10];
    q4_l=states_msg->position[14];
    q5_l=states_msg->position[11];*/

		/*right subscribers*/
		/*q0_r=states_msg->position[28];
    q1_r=states_msg->position[26];
    q2_r=states_msg->position[25];
    q3_r=states_msg->position[23];
    q4_r=states_msg->position[27];
    q5_r=states_msg->position[24];*/

		q0_l=state->position[joints["l_arm_usy"]];
		q1_l=state->position[joints["l_arm_shx"]];
		q2_l=state->position[joints["l_arm_ely"]];
		q3_l=state->position[joints["l_arm_elx"]];
		q4_l=state->position[joints["l_arm_uwy"]];
		q5_l=state->position[joints["l_arm_mwx"]];
		q0_r=state->position[joints["r_arm_usy"]];
		q1_r=state->position[joints["r_arm_shx"]];
		q2_r=state->position[joints["r_arm_ely"]];
		q3_r=state->position[joints["r_arm_elx"]];
		q4_r=state->position[joints["r_arm_uwy"]];
		q5_r=state->position[joints["r_arm_mwx"]];

	}

	bool val_calc_srv_CB(arms_val_calc::arms_val_calcRequest &req,arms_val_calc::arms_val_calcResponse &res){

		/*left leg jacobian*/
		double c_q0_l=cos(q0_l);
		double s_q0_l=sin(q0_l);
		double c_q1_l=cos(q1_l);
		double s_q1_l=sin(q1_l);
		double c_q2_l=cos(q2_l);
		double s_q2_l=sin(q2_l);
		double c_q3_l=cos(q3_l);
		double s_q3_l=sin(q3_l);
		double c_q4_l=cos(q4_l);
		double s_q4_l=sin(q4_l);
		double c_q5_l=cos(q5_l);
		double s_q5_l=sin(q5_l);

		double temp1 = s_q4_l*(c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) - s_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l);
		double temp2 = s_q5_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l) - c_q5_l*(c_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l));
		double temp3 = (c_q5_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l) + s_q5_l*(c_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)));

		l_jc(0,0)=(13*c_q0_l*c_q1_l)/1000 + (309*c_q0_l*s_q1_l)/1000 + (13*s_q0_l*s_q2_l)/1000 - (29*s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l))/500 - (13*c_q0_l*c_q1_l*c_q2_l)/1000 + (29*c_q0_l*c_q3_l*s_q1_l)/500;
		l_jc(0,1)=(309*c_q1_l*s_q0_l)/1000 - (13*s_q0_l*s_q1_l)/1000 + (29*c_q1_l*c_q3_l*s_q0_l)/500 + (13*c_q2_l*s_q0_l*s_q1_l)/1000 - (29*c_q2_l*s_q0_l*s_q1_l*s_q3_l)/500;
		l_jc(0,2)=(29*s_q3_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l))/500 - (13*c_q0_l*c_q2_l)/1000 + (13*c_q1_l*s_q0_l*s_q2_l)/1000;
		l_jc(0,3)=(29*c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l))/500 - (29*s_q0_l*s_q1_l*s_q3_l)/500;
		l_jc(0,4)=0;
		l_jc(0,5)=0;
		l_jc(1,0)=0;
		l_jc(1,1)=(13*c_q1_l*c_q2_l)/1000 - (309*s_q1_l)/1000 - (13*c_q1_l)/1000 - (29*c_q3_l*s_q1_l)/500 - (29*c_q1_l*c_q2_l*s_q3_l)/500;
		l_jc(1,2)=(29*s_q1_l*s_q2_l*s_q3_l)/500 - (13*s_q1_l*s_q2_l)/1000;
		l_jc(1,3)=- (29*c_q1_l*s_q3_l)/500 - (29*c_q2_l*c_q3_l*s_q1_l)/500;
		l_jc(1,4)=0;
		l_jc(1,5)=0;
		l_jc(2,0)=(13*c_q0_l*s_q2_l)/1000 - (13*c_q1_l*s_q0_l)/1000 - (309*s_q0_l*s_q1_l)/1000 - (29*s_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l))/500 + (13*c_q1_l*c_q2_l*s_q0_l)/1000 - (29*c_q3_l*s_q0_l*s_q1_l)/500;
		l_jc(2,1)=(309*c_q0_l*c_q1_l)/1000 - (13*c_q0_l*s_q1_l)/1000 + (29*c_q0_l*c_q1_l*c_q3_l)/500 + (13*c_q0_l*c_q2_l*s_q1_l)/1000 - (29*c_q0_l*c_q2_l*s_q1_l*s_q3_l)/500;
		l_jc(2,2)=(13*c_q2_l*s_q0_l)/1000 - (29*s_q3_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))/500 + (13*c_q0_l*c_q1_l*s_q2_l)/1000;
		l_jc(2,3)=- (29*c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l))/500 - (29*c_q0_l*s_q1_l*s_q3_l)/500;
		l_jc(2,4)=0;
		l_jc(2,5)=0;
		l_jc(3,0)=-((s_q4_l*(c_q1_l*s_q3_l + c_q2_l*c_q3_l*s_q1_l) + c_q4_l*s_q1_l*s_q2_l)*(s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)))/pow(temp1,2);
		l_jc(3,1)=(s_q4_l*(s_q1_l*s_q3_l - c_q1_l*c_q2_l*c_q3_l) - c_q1_l*c_q4_l*s_q2_l)/(temp1) - ((s_q4_l*(c_q1_l*s_q3_l + c_q2_l*c_q3_l*s_q1_l) + c_q4_l*s_q1_l*s_q2_l)*(s_q4_l*(c_q1_l*s_q0_l*s_q3_l + c_q2_l*c_q3_l*s_q0_l*s_q1_l) + c_q4_l*s_q0_l*s_q1_l*s_q2_l))/pow(temp1,2);
		l_jc(3,2)=((s_q4_l*(c_q1_l*s_q3_l + c_q2_l*c_q3_l*s_q1_l) + c_q4_l*s_q1_l*s_q2_l)*(c_q4_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) + c_q3_l*s_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l)))/pow(temp1,2) - (c_q2_l*c_q4_l*s_q1_l - c_q3_l*s_q1_l*s_q2_l*s_q4_l)/(temp1);
		l_jc(3,3)=- (s_q4_l*(c_q1_l*c_q3_l - c_q2_l*s_q1_l*s_q3_l))/(temp1) - (s_q4_l*(s_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) + c_q3_l*s_q0_l*s_q1_l)*(s_q4_l*(c_q1_l*s_q3_l + c_q2_l*c_q3_l*s_q1_l) + c_q4_l*s_q1_l*s_q2_l))/pow(temp1,2);
		l_jc(3,4)=((s_q4_l*(c_q1_l*s_q3_l + c_q2_l*c_q3_l*s_q1_l) + c_q4_l*s_q1_l*s_q2_l)*(c_q4_l*(c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) - s_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l)))/pow(temp1,2) - (c_q4_l*(c_q1_l*s_q3_l + c_q2_l*c_q3_l*s_q1_l) - s_q1_l*s_q2_l*s_q4_l)/(temp1);
		l_jc(3,5)=0;
		l_jc(4,0)=((s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*(2*(c_q5_l*(s_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) + c_q3_l*s_q0_l*s_q1_l) + s_q5_l*(c_q4_l*(c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) - s_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l)))*temp3 + 2*(s_q5_l*(s_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) + c_q3_l*s_q0_l*s_q1_l) - c_q5_l*(c_q4_l*(c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) - s_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l)))*(temp2)))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) - (temp1)/pow(pow(temp3,2) + pow(temp2,2),1/2);
		l_jc(4,1)=- (s_q4_l*(c_q0_l*c_q1_l*s_q3_l + c_q0_l*c_q2_l*c_q3_l*s_q1_l) + c_q0_l*c_q4_l*s_q1_l*s_q2_l)/pow(pow(temp3,2) + pow(temp2,2),(1/2)) - ((s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*(2*(s_q5_l*(c_q0_l*c_q1_l*c_q3_l - c_q0_l*c_q2_l*s_q1_l*s_q3_l) + c_q5_l*(c_q4_l*(c_q0_l*c_q1_l*s_q3_l + c_q0_l*c_q2_l*c_q3_l*s_q1_l) - c_q0_l*s_q1_l*s_q2_l*s_q4_l))*(temp2) + 2*(c_q5_l*(c_q0_l*c_q1_l*c_q3_l - c_q0_l*c_q2_l*s_q1_l*s_q3_l) - s_q5_l*(c_q4_l*(c_q0_l*c_q1_l*s_q3_l + c_q0_l*c_q2_l*c_q3_l*s_q1_l) - c_q0_l*s_q1_l*s_q2_l*s_q4_l))*temp3))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2)));
		l_jc(4,2)=((s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*(2*(c_q5_l*(s_q4_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q3_l*c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)) + s_q3_l*s_q5_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*(temp2) - 2*(s_q5_l*(s_q4_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q3_l*c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)) - c_q5_l*s_q3_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*temp3))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) - (c_q4_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q3_l*s_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))/pow(pow(temp3,2) + pow(temp2,2),(1/2));
		l_jc(4,3)=((s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*(2*(s_q5_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) + c_q4_l*c_q5_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l))*(temp2) + 2*(c_q5_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*s_q5_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l))*temp3))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) + (s_q4_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l))/pow(pow(temp3,2) + pow(temp2,2),(1/2));
		l_jc(4,4)=((2*c_q5_l*(s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*(temp2) - 2*s_q5_l*(s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*temp3)*(s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) - (c_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))/pow(pow(temp3,2) + pow(temp2,2),(1/2));
		l_jc(4,5)=0;
		l_jc(5,0)=((s_q5_l*(s_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) + c_q3_l*s_q0_l*s_q1_l) - c_q5_l*(c_q4_l*(c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) - s_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l)))*temp3)/pow(temp2,2) - (c_q5_l*(s_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) + c_q3_l*s_q0_l*s_q1_l) + s_q5_l*(c_q4_l*(c_q3_l*(c_q0_l*s_q2_l + c_q1_l*c_q2_l*s_q0_l) - s_q0_l*s_q1_l*s_q3_l) + s_q4_l*(c_q0_l*c_q2_l - c_q1_l*s_q0_l*s_q2_l)))/(temp2);
		l_jc(5,1)=(c_q5_l*(c_q0_l*c_q1_l*c_q3_l - c_q0_l*c_q2_l*s_q1_l*s_q3_l) - s_q5_l*(c_q4_l*(c_q0_l*c_q1_l*s_q3_l + c_q0_l*c_q2_l*c_q3_l*s_q1_l) - c_q0_l*s_q1_l*s_q2_l*s_q4_l))/(temp2) - ((s_q5_l*(c_q0_l*c_q1_l*c_q3_l - c_q0_l*c_q2_l*s_q1_l*s_q3_l) + c_q5_l*(c_q4_l*(c_q0_l*c_q1_l*s_q3_l + c_q0_l*c_q2_l*c_q3_l*s_q1_l) - c_q0_l*s_q1_l*s_q2_l*s_q4_l))*temp3)/pow(temp2,2);
		l_jc(5,2)=(s_q5_l*(s_q4_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q3_l*c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)) - c_q5_l*s_q3_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))/(temp2) + ((c_q5_l*(s_q4_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q3_l*c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)) + s_q3_l*s_q5_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*temp3)/pow(temp2,2);
		l_jc(5,3)=((s_q5_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) + c_q4_l*c_q5_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l))*temp3)/pow(temp2,2) - (c_q5_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*s_q5_l*(s_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) - c_q0_l*c_q3_l*s_q1_l))/(temp2);
		l_jc(5,4)=(s_q5_l*(s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l)))/(temp2) + (c_q5_l*(s_q4_l*(c_q3_l*(s_q0_l*s_q2_l - c_q0_l*c_q1_l*c_q2_l) + c_q0_l*s_q1_l*s_q3_l) - c_q4_l*(c_q2_l*s_q0_l + c_q0_l*c_q1_l*s_q2_l))*temp3)/pow(temp2,2);
		l_jc(5,5)=pow(temp3,2)/pow(temp2,2) + 1;

		double c_q0_r=cos(q0_r);
		double s_q0_r=sin(q0_r);
		double c_q1_r=cos(q1_r);
		double s_q1_r=sin(q1_r);
		double c_q2_r=cos(q2_r);
		double s_q2_r=sin(q2_r);
		double c_q3_r=cos(q3_r);
		double s_q3_r=sin(q3_r);
		double c_q4_r=cos(q4_r);
		double s_q4_r=sin(q4_r);
		double c_q5_r=cos(q5_r);
		double s_q5_r=sin(q5_r);

		temp1 = s_q4_r*(c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) - s_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r);
		temp2 = s_q5_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r) - c_q5_r*(c_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r));
		temp3 = (c_q5_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r) + s_q5_r*(c_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)));

		r_jc(0,0)=(13*c_q0_r*c_q1_r)/1000 + (309*c_q0_r*s_q1_r)/1000 + (13*s_q0_r*s_q2_r)/1000 - (29*s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r))/500 - (13*c_q0_r*c_q1_r*c_q2_r)/1000 + (29*c_q0_r*c_q3_r*s_q1_r)/500;
		r_jc(0,1)=(309*c_q1_r*s_q0_r)/1000 - (13*s_q0_r*s_q1_r)/1000 + (29*c_q1_r*c_q3_r*s_q0_r)/500 + (13*c_q2_r*s_q0_r*s_q1_r)/1000 - (29*c_q2_r*s_q0_r*s_q1_r*s_q3_r)/500;
		r_jc(0,2)=(29*s_q3_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r))/500 - (13*c_q0_r*c_q2_r)/1000 + (13*c_q1_r*s_q0_r*s_q2_r)/1000;
		r_jc(0,3)=(29*c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r))/500 - (29*s_q0_r*s_q1_r*s_q3_r)/500;
		r_jc(0,4)=0;
		r_jc(0,5)=0;
		r_jc(1,0)=0;
		r_jc(1,1)=(13*c_q1_r*c_q2_r)/1000 - (309*s_q1_r)/1000 - (13*c_q1_r)/1000 - (29*c_q3_r*s_q1_r)/500 - (29*c_q1_r*c_q2_r*s_q3_r)/500;
		r_jc(1,2)=(29*s_q1_r*s_q2_r*s_q3_r)/500 - (13*s_q1_r*s_q2_r)/1000;
		r_jc(1,3)=- (29*c_q1_r*s_q3_r)/500 - (29*c_q2_r*c_q3_r*s_q1_r)/500;
		r_jc(1,4)=0;
		r_jc(1,5)=0;
		r_jc(2,0)=(13*c_q0_r*s_q2_r)/1000 - (13*c_q1_r*s_q0_r)/1000 - (309*s_q0_r*s_q1_r)/1000 - (29*s_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r))/500 + (13*c_q1_r*c_q2_r*s_q0_r)/1000 - (29*c_q3_r*s_q0_r*s_q1_r)/500;
		r_jc(2,1)=(309*c_q0_r*c_q1_r)/1000 - (13*c_q0_r*s_q1_r)/1000 + (29*c_q0_r*c_q1_r*c_q3_r)/500 + (13*c_q0_r*c_q2_r*s_q1_r)/1000 - (29*c_q0_r*c_q2_r*s_q1_r*s_q3_r)/500;
		r_jc(2,2)=(13*c_q2_r*s_q0_r)/1000 - (29*s_q3_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))/500 + (13*c_q0_r*c_q1_r*s_q2_r)/1000;
		r_jc(2,3)=- (29*c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r))/500 - (29*c_q0_r*s_q1_r*s_q3_r)/500;
		r_jc(2,4)=0;
		r_jc(2,5)=0;
		r_jc(3,0)=-((s_q4_r*(c_q1_r*s_q3_r + c_q2_r*c_q3_r*s_q1_r) + c_q4_r*s_q1_r*s_q2_r)*(s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)))/pow(temp1,2);
		r_jc(3,1)=(s_q4_r*(s_q1_r*s_q3_r - c_q1_r*c_q2_r*c_q3_r) - c_q1_r*c_q4_r*s_q2_r)/(temp1) - ((s_q4_r*(c_q1_r*s_q3_r + c_q2_r*c_q3_r*s_q1_r) + c_q4_r*s_q1_r*s_q2_r)*(s_q4_r*(c_q1_r*s_q0_r*s_q3_r + c_q2_r*c_q3_r*s_q0_r*s_q1_r) + c_q4_r*s_q0_r*s_q1_r*s_q2_r))/pow(temp1,2);
		r_jc(3,2)=((s_q4_r*(c_q1_r*s_q3_r + c_q2_r*c_q3_r*s_q1_r) + c_q4_r*s_q1_r*s_q2_r)*(c_q4_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) + c_q3_r*s_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r)))/pow(temp1,2) - (c_q2_r*c_q4_r*s_q1_r - c_q3_r*s_q1_r*s_q2_r*s_q4_r)/(temp1);
		r_jc(3,3)=- (s_q4_r*(c_q1_r*c_q3_r - c_q2_r*s_q1_r*s_q3_r))/(temp1) - (s_q4_r*(s_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) + c_q3_r*s_q0_r*s_q1_r)*(s_q4_r*(c_q1_r*s_q3_r + c_q2_r*c_q3_r*s_q1_r) + c_q4_r*s_q1_r*s_q2_r))/pow(temp1,2);
		r_jc(3,4)=((s_q4_r*(c_q1_r*s_q3_r + c_q2_r*c_q3_r*s_q1_r) + c_q4_r*s_q1_r*s_q2_r)*(c_q4_r*(c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) - s_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r)))/pow(temp1,2) - (c_q4_r*(c_q1_r*s_q3_r + c_q2_r*c_q3_r*s_q1_r) - s_q1_r*s_q2_r*s_q4_r)/(temp1);
		r_jc(3,5)=0;
		r_jc(4,0)=((s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*(2*(c_q5_r*(s_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) + c_q3_r*s_q0_r*s_q1_r) + s_q5_r*(c_q4_r*(c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) - s_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r)))*temp3 + 2*(s_q5_r*(s_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) + c_q3_r*s_q0_r*s_q1_r) - c_q5_r*(c_q4_r*(c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) - s_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r)))*(temp2)))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) - (temp1)/pow(pow(temp3,2) + pow(temp2,2),1/2);
		r_jc(4,1)=- (s_q4_r*(c_q0_r*c_q1_r*s_q3_r + c_q0_r*c_q2_r*c_q3_r*s_q1_r) + c_q0_r*c_q4_r*s_q1_r*s_q2_r)/pow(pow(temp3,2) + pow(temp2,2),(1/2)) - ((s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*(2*(s_q5_r*(c_q0_r*c_q1_r*c_q3_r - c_q0_r*c_q2_r*s_q1_r*s_q3_r) + c_q5_r*(c_q4_r*(c_q0_r*c_q1_r*s_q3_r + c_q0_r*c_q2_r*c_q3_r*s_q1_r) - c_q0_r*s_q1_r*s_q2_r*s_q4_r))*(temp2) + 2*(c_q5_r*(c_q0_r*c_q1_r*c_q3_r - c_q0_r*c_q2_r*s_q1_r*s_q3_r) - s_q5_r*(c_q4_r*(c_q0_r*c_q1_r*s_q3_r + c_q0_r*c_q2_r*c_q3_r*s_q1_r) - c_q0_r*s_q1_r*s_q2_r*s_q4_r))*temp3))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2)));
		r_jc(4,2)=((s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*(2*(c_q5_r*(s_q4_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q3_r*c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)) + s_q3_r*s_q5_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*(temp2) - 2*(s_q5_r*(s_q4_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q3_r*c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)) - c_q5_r*s_q3_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*temp3))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) - (c_q4_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q3_r*s_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))/pow(pow(temp3,2) + pow(temp2,2),(1/2));
		r_jc(4,3)=((s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*(2*(s_q5_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) + c_q4_r*c_q5_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r))*(temp2) + 2*(c_q5_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*s_q5_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r))*temp3))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) + (s_q4_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r))/pow(pow(temp3,2) + pow(temp2,2),(1/2));
		r_jc(4,4)=((2*c_q5_r*(s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*(temp2) - 2*s_q5_r*(s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*temp3)*(s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)))/(2*pow(pow(temp3,2) + pow(temp2,2),(3/2))) - (c_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))/pow(pow(temp3,2) + pow(temp2,2),(1/2));
		r_jc(4,5)=0;
		r_jc(5,0)=((s_q5_r*(s_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) + c_q3_r*s_q0_r*s_q1_r) - c_q5_r*(c_q4_r*(c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) - s_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r)))*temp3)/pow(temp2,2) - (c_q5_r*(s_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) + c_q3_r*s_q0_r*s_q1_r) + s_q5_r*(c_q4_r*(c_q3_r*(c_q0_r*s_q2_r + c_q1_r*c_q2_r*s_q0_r) - s_q0_r*s_q1_r*s_q3_r) + s_q4_r*(c_q0_r*c_q2_r - c_q1_r*s_q0_r*s_q2_r)))/(temp2);
		r_jc(5,1)=(c_q5_r*(c_q0_r*c_q1_r*c_q3_r - c_q0_r*c_q2_r*s_q1_r*s_q3_r) - s_q5_r*(c_q4_r*(c_q0_r*c_q1_r*s_q3_r + c_q0_r*c_q2_r*c_q3_r*s_q1_r) - c_q0_r*s_q1_r*s_q2_r*s_q4_r))/(temp2) - ((s_q5_r*(c_q0_r*c_q1_r*c_q3_r - c_q0_r*c_q2_r*s_q1_r*s_q3_r) + c_q5_r*(c_q4_r*(c_q0_r*c_q1_r*s_q3_r + c_q0_r*c_q2_r*c_q3_r*s_q1_r) - c_q0_r*s_q1_r*s_q2_r*s_q4_r))*temp3)/pow(temp2,2);
		r_jc(5,2)=(s_q5_r*(s_q4_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q3_r*c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)) - c_q5_r*s_q3_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))/(temp2) + ((c_q5_r*(s_q4_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q3_r*c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)) + s_q3_r*s_q5_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*temp3)/pow(temp2,2);
		r_jc(5,3)=((s_q5_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) + c_q4_r*c_q5_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r))*temp3)/pow(temp2,2) - (c_q5_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*s_q5_r*(s_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) - c_q0_r*c_q3_r*s_q1_r))/(temp2);
		r_jc(5,4)=(s_q5_r*(s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r)))/(temp2) + (c_q5_r*(s_q4_r*(c_q3_r*(s_q0_r*s_q2_r - c_q0_r*c_q1_r*c_q2_r) + c_q0_r*s_q1_r*s_q3_r) - c_q4_r*(c_q2_r*s_q0_r + c_q0_r*c_q1_r*s_q2_r))*temp3)/pow(temp2,2);
		r_jc(5,5)=pow(temp3,2)/pow(temp2,2) + 1;

		/*input vector to Eigen vector*/
		Eigen::VectorXf desired_vel(6);
		desired_vel(0)=req.x_dot;
		desired_vel(1)=req.y_dot;
		desired_vel(2)=req.z_dot;
		desired_vel(3)=req.roll_dot;
		desired_vel(4)=req.pitch_dot;
		desired_vel(5)=req.yaw_dot;

		/*inverse calc*/
		Eigen::MatrixXf l_jc_inverse(6,6),r_jc_inverse(6,6);
		l_jc_inverse=l_jc.inverse();
		r_jc_inverse=r_jc.inverse();

		/*matrix dot vector*/
		Eigen::VectorXf output_left_vel(6);
		Eigen::VectorXf output_right_vel(6);
		output_left_vel=l_jc_inverse*desired_vel;
		output_right_vel=r_jc_inverse*desired_vel;

		/*Eigen vector to output vector*/
		res.q_left_dot[0]=output_left_vel(0);
		res.q_left_dot[1]=output_left_vel(1);
		res.q_left_dot[2]=output_left_vel(2);
		res.q_left_dot[3]=output_left_vel(3);
		res.q_left_dot[4]=output_left_vel(4);
		res.q_left_dot[5]=output_left_vel(5);

		res.q_right_dot[0]=output_right_vel(0);
		res.q_right_dot[1]=output_right_vel(1);
		res.q_right_dot[2]=output_right_vel(2);
		res.q_right_dot[3]=output_right_vel(3);
		res.q_right_dot[4]=output_right_vel(4);
		res.q_right_dot[5]=output_right_vel(5);

		return true;
	}
};



int main(int argc, char** argv){
	ros::init(argc, argv, "arms_val_calculator_service");
	arms_val_calculator arms_calc_objct =arms_val_calculator();
	ROS_INFO("ready");
	ros::spin();
	return 0;
}
