/* Auto-generated by genmsg_cpp for file /home/ariy/workspace/Executer/srv/btstack.srv */
#ifndef EXECUTER_SERVICE_BTSTACK_H
#define EXECUTER_SERVICE_BTSTACK_H
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




namespace Executer
{
template <class ContainerAllocator>
struct btstackRequest_ {
  typedef btstackRequest_<ContainerAllocator> Type;

  btstackRequest_()
  : tree_id()
  {
  }

  btstackRequest_(const ContainerAllocator& _alloc)
  : tree_id(_alloc)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _tree_id_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  tree_id;


  typedef boost::shared_ptr< ::Executer::btstackRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::Executer::btstackRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct btstackRequest
typedef  ::Executer::btstackRequest_<std::allocator<void> > btstackRequest;

typedef boost::shared_ptr< ::Executer::btstackRequest> btstackRequestPtr;
typedef boost::shared_ptr< ::Executer::btstackRequest const> btstackRequestConstPtr;


template <class ContainerAllocator>
struct btstackResponse_ {
  typedef btstackResponse_<ContainerAllocator> Type;

  btstackResponse_()
  : content()
  {
  }

  btstackResponse_(const ContainerAllocator& _alloc)
  : content(_alloc)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _content_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  content;


  typedef boost::shared_ptr< ::Executer::btstackResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::Executer::btstackResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct btstackResponse
typedef  ::Executer::btstackResponse_<std::allocator<void> > btstackResponse;

typedef boost::shared_ptr< ::Executer::btstackResponse> btstackResponsePtr;
typedef boost::shared_ptr< ::Executer::btstackResponse const> btstackResponseConstPtr;

struct btstack
{

typedef btstackRequest Request;
typedef btstackResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct btstack
} // namespace Executer

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::Executer::btstackRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::Executer::btstackRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::Executer::btstackRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "035d9dc2af2b0acc4c1fca0de404f272";
  }

  static const char* value(const  ::Executer::btstackRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x035d9dc2af2b0accULL;
  static const uint64_t static_value2 = 0x4c1fca0de404f272ULL;
};

template<class ContainerAllocator>
struct DataType< ::Executer::btstackRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Executer/btstackRequest";
  }

  static const char* value(const  ::Executer::btstackRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::Executer::btstackRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string tree_id\n\
\n\
";
  }

  static const char* value(const  ::Executer::btstackRequest_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::Executer::btstackResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::Executer::btstackResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::Executer::btstackResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "c2e84951ee6d0addf437bfddd5b19734";
  }

  static const char* value(const  ::Executer::btstackResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xc2e84951ee6d0addULL;
  static const uint64_t static_value2 = 0xf437bfddd5b19734ULL;
};

template<class ContainerAllocator>
struct DataType< ::Executer::btstackResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Executer/btstackResponse";
  }

  static const char* value(const  ::Executer::btstackResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::Executer::btstackResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string content\n\
\n\
\n\
";
  }

  static const char* value(const  ::Executer::btstackResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::Executer::btstackRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.tree_id);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct btstackRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::Executer::btstackResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.content);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct btstackResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<Executer::btstack> {
  static const char* value() 
  {
    return "4787e2d1c6f5996e8efbfd4e07122e4d";
  }

  static const char* value(const Executer::btstack&) { return value(); } 
};

template<>
struct DataType<Executer::btstack> {
  static const char* value() 
  {
    return "Executer/btstack";
  }

  static const char* value(const Executer::btstack&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<Executer::btstackRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4787e2d1c6f5996e8efbfd4e07122e4d";
  }

  static const char* value(const Executer::btstackRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<Executer::btstackRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Executer/btstack";
  }

  static const char* value(const Executer::btstackRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<Executer::btstackResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4787e2d1c6f5996e8efbfd4e07122e4d";
  }

  static const char* value(const Executer::btstackResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<Executer::btstackResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Executer/btstack";
  }

  static const char* value(const Executer::btstackResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // EXECUTER_SERVICE_BTSTACK_H

