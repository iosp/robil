#ifndef C11_AGENT_NODE_H
#define C11_AGENT_NODE_H

#include "C10_Common/mission_selection.h"
#include "C10_Common/pause_mission.h"
#include "C10_Common/resume_mission.h"
#include "C10_Common/execution_status_change.h"
#include "C10_Common/path_update.h"
#include "Vec2d.hpp"
#include "C25_GlobalPosition/C25C0_ROP.h"
#include "C23_ObjectRecognition/C23C0_ODIM.h"
#include "C31_PathPlanner/C31_Waypoints.h"
#include "ros/ros.h"
#include "ros/package.h"
#include "std_msgs/String.h"
#include "atlas_msgs/VRCScore.h"
#include "C11_PushServer.hpp"
#include "C11_HMIResponseServer.hpp"
#include "C11_UntilOperatorIntervention.hpp"
#include "C11_TCPServer.h"
#include <QThread>
#include <QFile>
#include <QString>
#include <QStringList>

class IAgentInterface
{
public:
  virtual void PushImage(QImage img) = 0;
  virtual void PushGrid(StructGridData grid) = 0;
  virtual void PushPath(vector<StructPoint> path) = 0;
  virtual void HMIResponse() = 0;
  virtual void ExecutionStatusChanged(int status) = 0;
  virtual void SendExecuterStack(QString) = 0;
  virtual void SendVRCScoreData(double timeSec, int competionScore, int falls, QString message) = 0;
  virtual void SendDownlink(QString) = 0;
  virtual void SendUplink(QString) = 0;
  virtual void SendRobotData(StructPoint pos, StructOrientation orient) = 0;
};

class C11_Agent_Node : public QThread, public IPushHMIInterface, public IHMIResponseInterface
{
  Q_OBJECT

public:
  C11_Agent_Node(int argc, char** argv);
  ~C11_Agent_Node();

  void run();
  bool init();

//  void SetTcp(CTcpServer* ptcpServer);
  void SetAgentInterface(IAgentInterface* piAgentInterface);

  bool MissionSelection(C10_Common::mission_selection::Request& req,
                  C10_Common::mission_selection::Response& res);
  bool PauseMission(C10_Common::pause_mission::Request& req,
                  C10_Common::pause_mission::Response& res);
  bool ResumeMission(C10_Common::resume_mission::Request& req,
                  C10_Common::resume_mission::Response& res);
  bool PathUpdate(C10_Common::path_update::Request& req,
                  C10_Common::path_update::Response& res);
  void StopExecuteMessageCallback(const std_msgs::StringConstPtr& msg);

  void RobotPosUpdateCallback(const C25_GlobalPosition::C25C0_ROP& robot_pos);

  void ExecuterStackSubscriber(const std_msgs::StringConstPtr& stack);

  void VRCScoreSubscriber(const atlas_msgs::VRCScore& vrcScore);

  void DownlinkSubscriber(const std_msgs::StringConstPtr& down);

  void UplinkSubscriber(const std_msgs::StringConstPtr& up);

  void ObjectsSubscriber(const C23_ObjectRecognition::C23C0_ODIMConstPtr& obj);

  void SetReleased();

  void Pause();

  void Resume();

  void Stop();

  void HMIResponded();

  void LoadMission(int missionId);

  void PathUpdated(std::vector<StructPoint> points);

  void ImageRequest();

  void GridRequest();

  void PathRequest();

  void AllRequest();

  void NewGoalRequest(StructPoint goal);

  void ResetRequest();

  void GridAndPathRequest();

  void SendRobotData();

  virtual void PushImage(QImage img);
  virtual void PushGrid(StructGridData grid);
  virtual void PushPath(vector<StructPoint> path);
  virtual void HMIResponse();

private:

  size_t searchOnPathPosition(const Vec2d& pos, const vector<Vec2d>& path);
  void CheckPath();

  ros::NodeHandle *nh_;
  ros::Publisher path_update_pub;
  ros::Publisher goal_update_pub;
  ros::Publisher goal_reset_pub;
  ros::ServiceServer service_MissionSelection;
  ros::ServiceServer service_PauseMission;
  ros::ServiceServer service_ResumeSelection;
  ros::ServiceServer service_PathUpdate;
  ros::Subscriber status_subscriber;
  ros::Subscriber robot_pos_subscriber;
  ros::Subscriber executer_stack_subscriber;
  ros::Subscriber vrc_score_subscriber;
  ros::Subscriber uplink_subscriber;
  ros::Subscriber downlink_subscriber;
  ros::Subscriber objects_subscriber;
  ros::ServiceClient c34StopClient;
  ros::ServiceClient c11ExecutionStatusChangeClient;
  ros::ServiceClient c34RunClient;
  ros::ServiceClient c34ResumeClient;

  int init_argc;
  char** init_argv;
  std::string tree_id_str;
  std::vector<Vec2d> UpdatedPath;

  PushHMIServer *pushS;
  HMIResponseServer *HMIResS;
  IAgentInterface* pIAgentInterface;
  bool IsWaitForRelease;
  QStringList MissionsList;
  Vec2d position;
  StructOrientation orientation;
  size_t start_pos;

  ////////////VCScore Data/////////////////
  double SimTime;
  int Comletion_score;
  int Falls;
  QString Message;
  ////////////Up/Down Data/////////////////
  QString Uplink;
  QString Downlink;
};

#endif // C11_AGENT_NODE_H
