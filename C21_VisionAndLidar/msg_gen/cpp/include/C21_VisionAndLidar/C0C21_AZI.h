/* Auto-generated by genmsg_cpp for file /home/ariy/robil/C21_VisionAndLidar/msg/C0C21_AZI.msg */
#ifndef C21_VISIONANDLIDAR_MESSAGE_C0C21_AZI_H
#define C21_VISIONANDLIDAR_MESSAGE_C0C21_AZI_H
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


namespace C21_VisionAndLidar
{
template <class ContainerAllocator>
struct C0C21_AZI_ {
  typedef C0C21_AZI_<ContainerAllocator> Type;

  C0C21_AZI_()
  : azimuth(0.0)
  {
  }

  C0C21_AZI_(const ContainerAllocator& _alloc)
  : azimuth(0.0)
  {
  }

  typedef float _azimuth_type;
  float azimuth;


  typedef boost::shared_ptr< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct C0C21_AZI
typedef  ::C21_VisionAndLidar::C0C21_AZI_<std::allocator<void> > C0C21_AZI;

typedef boost::shared_ptr< ::C21_VisionAndLidar::C0C21_AZI> C0C21_AZIPtr;
typedef boost::shared_ptr< ::C21_VisionAndLidar::C0C21_AZI const> C0C21_AZIConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace C21_VisionAndLidar

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1ad4832faa8759062b7c12092a041b10";
  }

  static const char* value(const  ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x1ad4832faa875906ULL;
  static const uint64_t static_value2 = 0x2b7c12092a041b10ULL;
};

template<class ContainerAllocator>
struct DataType< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C21_VisionAndLidar/C0C21_AZI";
  }

  static const char* value(const  ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float32 azimuth\n\
\n\
";
  }

  static const char* value(const  ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.azimuth);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct C0C21_AZI_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::C21_VisionAndLidar::C0C21_AZI_<ContainerAllocator> & v) 
  {
    s << indent << "azimuth: ";
    Printer<float>::stream(s, indent + "  ", v.azimuth);
  }
};


} // namespace message_operations
} // namespace ros

#endif // C21_VISIONANDLIDAR_MESSAGE_C0C21_AZI_H

