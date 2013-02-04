/* Auto-generated by genmsg_cpp for file /home/darpa/Projects/Robil/C42_DynamicLocomotion/msg/C42_CpgWlkActionGoal.msg */
#ifndef C42_DYNAMICLOCOMOTION_MESSAGE_C42_CPGWLKACTIONGOAL_H
#define C42_DYNAMICLOCOMOTION_MESSAGE_C42_CPGWLKACTIONGOAL_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "C42_DynamicLocomotion/C42_CpgWlkGoal.h"

namespace C42_DynamicLocomotion
{
template <class ContainerAllocator>
struct C42_CpgWlkActionGoal_ {
  typedef C42_CpgWlkActionGoal_<ContainerAllocator> Type;

  C42_CpgWlkActionGoal_()
  : header()
  , goal_id()
  , goal()
  {
  }

  C42_CpgWlkActionGoal_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , goal_id(_alloc)
  , goal(_alloc)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
   ::actionlib_msgs::GoalID_<ContainerAllocator>  goal_id;

  typedef  ::C42_DynamicLocomotion::C42_CpgWlkGoal_<ContainerAllocator>  _goal_type;
   ::C42_DynamicLocomotion::C42_CpgWlkGoal_<ContainerAllocator>  goal;


  typedef boost::shared_ptr< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct C42_CpgWlkActionGoal
typedef  ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<std::allocator<void> > C42_CpgWlkActionGoal;

typedef boost::shared_ptr< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal> C42_CpgWlkActionGoalPtr;
typedef boost::shared_ptr< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal const> C42_CpgWlkActionGoalConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace C42_DynamicLocomotion

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > {
  static const char* value() 
  {
    return "f12cf02447d3f74acee1a486c2eccdb3";
  }

  static const char* value(const  ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xf12cf02447d3f74aULL;
  static const uint64_t static_value2 = 0xcee1a486c2eccdb3ULL;
};

template<class ContainerAllocator>
struct DataType< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C42_DynamicLocomotion/C42_CpgWlkActionGoal";
  }

  static const char* value(const  ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
C42_CpgWlkGoal goal\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: C42_DynamicLocomotion/C42_CpgWlkGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#goal position and orientation\n\
geometry_msgs/Pose2D goal_pos\n\
float64 tol\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
";
  }

  static const char* value(const  ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.goal_id);
    stream.next(m.goal);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct C42_CpgWlkActionGoal_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::C42_DynamicLocomotion::C42_CpgWlkActionGoal_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
s << std::endl;
    Printer< ::C42_DynamicLocomotion::C42_CpgWlkGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};


} // namespace message_operations
} // namespace ros

#endif // C42_DYNAMICLOCOMOTION_MESSAGE_C42_CPGWLKACTIONGOAL_H
