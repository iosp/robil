/* Auto-generated by genmsg_cpp for file /home/ariy/robil/C0_RobilTask/msg/RobilTaskGoal.msg */
#ifndef C0_ROBILTASK_MESSAGE_ROBILTASKGOAL_H
#define C0_ROBILTASK_MESSAGE_ROBILTASKGOAL_H
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


namespace C0_RobilTask
{
template <class ContainerAllocator>
struct RobilTaskGoal_ {
  typedef RobilTaskGoal_<ContainerAllocator> Type;

  RobilTaskGoal_()
  : name()
  , uid()
  , parameters()
  {
  }

  RobilTaskGoal_(const ContainerAllocator& _alloc)
  : name(_alloc)
  , uid(_alloc)
  , parameters(_alloc)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  name;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _uid_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  uid;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _parameters_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  parameters;


  typedef boost::shared_ptr< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct RobilTaskGoal
typedef  ::C0_RobilTask::RobilTaskGoal_<std::allocator<void> > RobilTaskGoal;

typedef boost::shared_ptr< ::C0_RobilTask::RobilTaskGoal> RobilTaskGoalPtr;
typedef boost::shared_ptr< ::C0_RobilTask::RobilTaskGoal const> RobilTaskGoalConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace C0_RobilTask

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> > {
  static const char* value() 
  {
    return "47a1520173b55d0b167022a5f87c0efd";
  }

  static const char* value(const  ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x47a1520173b55d0bULL;
  static const uint64_t static_value2 = 0x167022a5f87c0efdULL;
};

template<class ContainerAllocator>
struct DataType< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C0_RobilTask/RobilTaskGoal";
  }

  static const char* value(const  ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the goal\n\
string name\n\
string uid\n\
string parameters\n\
\n\
";
  }

  static const char* value(const  ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.name);
    stream.next(m.uid);
    stream.next(m.parameters);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct RobilTaskGoal_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::C0_RobilTask::RobilTaskGoal_<ContainerAllocator> & v) 
  {
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
    s << indent << "uid: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.uid);
    s << indent << "parameters: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.parameters);
  }
};


} // namespace message_operations
} // namespace ros

#endif // C0_ROBILTASK_MESSAGE_ROBILTASKGOAL_H

