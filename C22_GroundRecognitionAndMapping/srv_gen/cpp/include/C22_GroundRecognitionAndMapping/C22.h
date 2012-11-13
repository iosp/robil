/* Auto-generated by genmsg_cpp for file /home/ariy/robil/C22_GroundRecognitionAndMapping/srv/C22.srv */
#ifndef C22_GROUNDRECOGNITIONANDMAPPING_SERVICE_C22_H
#define C22_GROUNDRECOGNITIONANDMAPPING_SERVICE_C22_H
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

#include "ros/service_traits.h"

#include "C22_GroundRecognitionAndMapping/C0C22_AZI.h"
#include "C22_GroundRecognitionAndMapping/C0C22_CAM.h"
#include "C22_GroundRecognitionAndMapping/C0C22_LAZ.h"
#include "C22_GroundRecognitionAndMapping/C0C22_SAF.h"


#include "C22_GroundRecognitionAndMapping/C22C0_PATH.h"

namespace C22_GroundRecognitionAndMapping
{
template <class ContainerAllocator>
struct C22Request_ {
  typedef C22Request_<ContainerAllocator> Type;

  C22Request_()
  : azimuth_msg()
  , camera_sample_rate_msg()
  , laser_sample_rate_msg()
  , safety_requirements()
  {
  }

  C22Request_(const ContainerAllocator& _alloc)
  : azimuth_msg(_alloc)
  , camera_sample_rate_msg(_alloc)
  , laser_sample_rate_msg(_alloc)
  , safety_requirements(_alloc)
  {
  }

  typedef  ::C22_GroundRecognitionAndMapping::C0C22_AZI_<ContainerAllocator>  _azimuth_msg_type;
   ::C22_GroundRecognitionAndMapping::C0C22_AZI_<ContainerAllocator>  azimuth_msg;

  typedef  ::C22_GroundRecognitionAndMapping::C0C22_CAM_<ContainerAllocator>  _camera_sample_rate_msg_type;
   ::C22_GroundRecognitionAndMapping::C0C22_CAM_<ContainerAllocator>  camera_sample_rate_msg;

  typedef  ::C22_GroundRecognitionAndMapping::C0C22_LAZ_<ContainerAllocator>  _laser_sample_rate_msg_type;
   ::C22_GroundRecognitionAndMapping::C0C22_LAZ_<ContainerAllocator>  laser_sample_rate_msg;

  typedef  ::C22_GroundRecognitionAndMapping::C0C22_SAF_<ContainerAllocator>  _safety_requirements_type;
   ::C22_GroundRecognitionAndMapping::C0C22_SAF_<ContainerAllocator>  safety_requirements;


  typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct C22Request
typedef  ::C22_GroundRecognitionAndMapping::C22Request_<std::allocator<void> > C22Request;

typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Request> C22RequestPtr;
typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Request const> C22RequestConstPtr;


template <class ContainerAllocator>
struct C22Response_ {
  typedef C22Response_<ContainerAllocator> Type;

  C22Response_()
  : drivingPath()
  {
  }

  C22Response_(const ContainerAllocator& _alloc)
  : drivingPath(_alloc)
  {
  }

  typedef  ::C22_GroundRecognitionAndMapping::C22C0_PATH_<ContainerAllocator>  _drivingPath_type;
   ::C22_GroundRecognitionAndMapping::C22C0_PATH_<ContainerAllocator>  drivingPath;


  typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct C22Response
typedef  ::C22_GroundRecognitionAndMapping::C22Response_<std::allocator<void> > C22Response;

typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Response> C22ResponsePtr;
typedef boost::shared_ptr< ::C22_GroundRecognitionAndMapping::C22Response const> C22ResponseConstPtr;

struct C22
{

typedef C22Request Request;
typedef C22Response Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct C22
} // namespace C22_GroundRecognitionAndMapping

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > {
  static const char* value() 
  {
    return "70e3cb910a6be1e3b12f117d0d8e5984";
  }

  static const char* value(const  ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x70e3cb910a6be1e3ULL;
  static const uint64_t static_value2 = 0xb12f117d0d8e5984ULL;
};

template<class ContainerAllocator>
struct DataType< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C22Request";
  }

  static const char* value(const  ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C0C22_AZI azimuth_msg\n\
C22_GroundRecognitionAndMapping/C0C22_CAM camera_sample_rate_msg\n\
C22_GroundRecognitionAndMapping/C0C22_LAZ laser_sample_rate_msg\n\
C22_GroundRecognitionAndMapping/C0C22_SAF safety_requirements\n\
\n\
================================================================================\n\
MSG: C22_GroundRecognitionAndMapping/C0C22_AZI\n\
float32 azimuth\n\
\n\
================================================================================\n\
MSG: C22_GroundRecognitionAndMapping/C0C22_CAM\n\
int32 frameRatePerSec\n\
\n\
================================================================================\n\
MSG: C22_GroundRecognitionAndMapping/C0C22_LAZ\n\
int32 sampleRatePerSec\n\
\n\
================================================================================\n\
MSG: C22_GroundRecognitionAndMapping/C0C22_SAF\n\
int32 safety_req\n\
\n\
";
  }

  static const char* value(const  ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > {
  static const char* value() 
  {
    return "8ab975951eb213cea8b3912fdea9e263";
  }

  static const char* value(const  ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x8ab975951eb213ceULL;
  static const uint64_t static_value2 = 0xa8b3912fdea9e263ULL;
};

template<class ContainerAllocator>
struct DataType< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C22Response";
  }

  static const char* value(const  ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C22C0_PATH drivingPath\n\
\n\
\n\
================================================================================\n\
MSG: C22_GroundRecognitionAndMapping/C22C0_PATH\n\
float32[] PATH_Left\n\
float32[] PATH_Right\n\
float32 PATH_Slope\n\
int32 PATH_ROU\n\
\n\
";
  }

  static const char* value(const  ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.azimuth_msg);
    stream.next(m.camera_sample_rate_msg);
    stream.next(m.laser_sample_rate_msg);
    stream.next(m.safety_requirements);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct C22Request_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.drivingPath);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct C22Response_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<C22_GroundRecognitionAndMapping::C22> {
  static const char* value() 
  {
    return "8c8585ab643e373df4d81a9496d25b57";
  }

  static const char* value(const C22_GroundRecognitionAndMapping::C22&) { return value(); } 
};

template<>
struct DataType<C22_GroundRecognitionAndMapping::C22> {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C22";
  }

  static const char* value(const C22_GroundRecognitionAndMapping::C22&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > {
  static const char* value() 
  {
    return "8c8585ab643e373df4d81a9496d25b57";
  }

  static const char* value(const C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C22";
  }

  static const char* value(const C22_GroundRecognitionAndMapping::C22Request_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > {
  static const char* value() 
  {
    return "8c8585ab643e373df4d81a9496d25b57";
  }

  static const char* value(const C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> > {
  static const char* value() 
  {
    return "C22_GroundRecognitionAndMapping/C22";
  }

  static const char* value(const C22_GroundRecognitionAndMapping::C22Response_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // C22_GROUNDRECOGNITIONANDMAPPING_SERVICE_C22_H

