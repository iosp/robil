"""autogenerated by genpy from C25_GlobalPosition/C25Request.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import C25_GlobalPosition.msg

class C25Request(genpy.Message):
  _md5sum = "eb67ba7f1b59ebf2ae5f1ea7ca5cac8d"
  _type = "C25_GlobalPosition/C25Request"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """C25_GlobalPosition/C0C25_AZI azimuth
C25_GlobalPosition/C0C25_CAM camera_sample_rate
C25_GlobalPosition/C0C25_LAZ laser_sample_rate

================================================================================
MSG: C25_GlobalPosition/C0C25_AZI
float32 azimuth

================================================================================
MSG: C25_GlobalPosition/C0C25_CAM
int32 frameRatePerSec

================================================================================
MSG: C25_GlobalPosition/C0C25_LAZ
int32 sampleRatePerSec

"""
  __slots__ = ['azimuth','camera_sample_rate','laser_sample_rate']
  _slot_types = ['C25_GlobalPosition/C0C25_AZI','C25_GlobalPosition/C0C25_CAM','C25_GlobalPosition/C0C25_LAZ']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       azimuth,camera_sample_rate,laser_sample_rate

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(C25Request, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.azimuth is None:
        self.azimuth = C25_GlobalPosition.msg.C0C25_AZI()
      if self.camera_sample_rate is None:
        self.camera_sample_rate = C25_GlobalPosition.msg.C0C25_CAM()
      if self.laser_sample_rate is None:
        self.laser_sample_rate = C25_GlobalPosition.msg.C0C25_LAZ()
    else:
      self.azimuth = C25_GlobalPosition.msg.C0C25_AZI()
      self.camera_sample_rate = C25_GlobalPosition.msg.C0C25_CAM()
      self.laser_sample_rate = C25_GlobalPosition.msg.C0C25_LAZ()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_f2i.pack(_x.azimuth.azimuth, _x.camera_sample_rate.frameRatePerSec, _x.laser_sample_rate.sampleRatePerSec))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.azimuth is None:
        self.azimuth = C25_GlobalPosition.msg.C0C25_AZI()
      if self.camera_sample_rate is None:
        self.camera_sample_rate = C25_GlobalPosition.msg.C0C25_CAM()
      if self.laser_sample_rate is None:
        self.laser_sample_rate = C25_GlobalPosition.msg.C0C25_LAZ()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.azimuth.azimuth, _x.camera_sample_rate.frameRatePerSec, _x.laser_sample_rate.sampleRatePerSec,) = _struct_f2i.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_f2i.pack(_x.azimuth.azimuth, _x.camera_sample_rate.frameRatePerSec, _x.laser_sample_rate.sampleRatePerSec))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.azimuth is None:
        self.azimuth = C25_GlobalPosition.msg.C0C25_AZI()
      if self.camera_sample_rate is None:
        self.camera_sample_rate = C25_GlobalPosition.msg.C0C25_CAM()
      if self.laser_sample_rate is None:
        self.laser_sample_rate = C25_GlobalPosition.msg.C0C25_LAZ()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.azimuth.azimuth, _x.camera_sample_rate.frameRatePerSec, _x.laser_sample_rate.sampleRatePerSec,) = _struct_f2i.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_f2i = struct.Struct("<f2i")
"""autogenerated by genpy from C25_GlobalPosition/C25Response.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import nav_msgs.msg
import std_msgs.msg
import C25_GlobalPosition.msg
import sensor_msgs.msg

class C25Response(genpy.Message):
  _md5sum = "3dbce8b9ad8002363ae61045a0bc8b62"
  _type = "C25_GlobalPosition/C25Response"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """C25_GlobalPosition/C25C0_ROP robotPosition
C25_GlobalPosition/C25C0_OPO qualityOfError


================================================================================
MSG: C25_GlobalPosition/C25C0_ROP
sensor_msgs/Imu imu
nav_msgs/Odometry pose
================================================================================
MSG: sensor_msgs/Imu
# This is a message to hold data from an IMU (Inertial Measurement Unit)
#
# Accelerations should be in m/s^2 (not in g's), and rotational velocity should be in rad/sec
#
# If the covariance of the measurement is known, it should be filled in (if all you know is the variance of each measurement, e.g. from the datasheet, just put those along the diagonal)
# A covariance matrix of all zeros will be interpreted as "covariance unknown", and to use the data a covariance will have to be assumed or gotten from some other source
#
# If you have no estimate for one of the data elements (e.g. your IMU doesn't produce an orientation estimate), please set element 0 of the associated covariance matrix to -1
# If you are interpreting this message, please check for a value of -1 in the first element of each covariance matrix, and disregard the associated estimate.

Header header

geometry_msgs/Quaternion orientation
float64[9] orientation_covariance # Row major about x, y, z axes

geometry_msgs/Vector3 angular_velocity
float64[9] angular_velocity_covariance # Row major about x, y, z axes

geometry_msgs/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance # Row major x, y z 

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.secs: seconds (stamp_secs) since epoch
# * stamp.nsecs: nanoseconds since stamp_secs
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 

float64 x
float64 y
float64 z
================================================================================
MSG: nav_msgs/Odometry
# This represents an estimate of a position and velocity in free space.  
# The pose in this message should be specified in the coordinate frame given by header.frame_id.
# The twist in this message should be specified in the coordinate frame given by the child_frame_id
Header header
string child_frame_id
geometry_msgs/PoseWithCovariance pose
geometry_msgs/TwistWithCovariance twist

================================================================================
MSG: geometry_msgs/PoseWithCovariance
# This represents a pose in free space with uncertainty.

Pose pose

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/TwistWithCovariance
# This expresses velocity in free space with uncertianty.

Twist twist

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into it's linear and angular parts. 
Vector3  linear
Vector3  angular

================================================================================
MSG: C25_GlobalPosition/C25C0_OPO
float32 qualityOfPosition

"""
  __slots__ = ['robotPosition','qualityOfError']
  _slot_types = ['C25_GlobalPosition/C25C0_ROP','C25_GlobalPosition/C25C0_OPO']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       robotPosition,qualityOfError

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(C25Response, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.robotPosition is None:
        self.robotPosition = C25_GlobalPosition.msg.C25C0_ROP()
      if self.qualityOfError is None:
        self.qualityOfError = C25_GlobalPosition.msg.C25C0_OPO()
    else:
      self.robotPosition = C25_GlobalPosition.msg.C25C0_ROP()
      self.qualityOfError = C25_GlobalPosition.msg.C25C0_OPO()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.robotPosition.imu.header.seq, _x.robotPosition.imu.header.stamp.secs, _x.robotPosition.imu.header.stamp.nsecs))
      _x = self.robotPosition.imu.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_4d.pack(_x.robotPosition.imu.orientation.x, _x.robotPosition.imu.orientation.y, _x.robotPosition.imu.orientation.z, _x.robotPosition.imu.orientation.w))
      buff.write(_struct_9d.pack(*self.robotPosition.imu.orientation_covariance))
      _x = self
      buff.write(_struct_3d.pack(_x.robotPosition.imu.angular_velocity.x, _x.robotPosition.imu.angular_velocity.y, _x.robotPosition.imu.angular_velocity.z))
      buff.write(_struct_9d.pack(*self.robotPosition.imu.angular_velocity_covariance))
      _x = self
      buff.write(_struct_3d.pack(_x.robotPosition.imu.linear_acceleration.x, _x.robotPosition.imu.linear_acceleration.y, _x.robotPosition.imu.linear_acceleration.z))
      buff.write(_struct_9d.pack(*self.robotPosition.imu.linear_acceleration_covariance))
      _x = self
      buff.write(_struct_3I.pack(_x.robotPosition.pose.header.seq, _x.robotPosition.pose.header.stamp.secs, _x.robotPosition.pose.header.stamp.nsecs))
      _x = self.robotPosition.pose.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.robotPosition.pose.child_frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_7d.pack(_x.robotPosition.pose.pose.pose.position.x, _x.robotPosition.pose.pose.pose.position.y, _x.robotPosition.pose.pose.pose.position.z, _x.robotPosition.pose.pose.pose.orientation.x, _x.robotPosition.pose.pose.pose.orientation.y, _x.robotPosition.pose.pose.pose.orientation.z, _x.robotPosition.pose.pose.pose.orientation.w))
      buff.write(_struct_36d.pack(*self.robotPosition.pose.pose.covariance))
      _x = self
      buff.write(_struct_6d.pack(_x.robotPosition.pose.twist.twist.linear.x, _x.robotPosition.pose.twist.twist.linear.y, _x.robotPosition.pose.twist.twist.linear.z, _x.robotPosition.pose.twist.twist.angular.x, _x.robotPosition.pose.twist.twist.angular.y, _x.robotPosition.pose.twist.twist.angular.z))
      buff.write(_struct_36d.pack(*self.robotPosition.pose.twist.covariance))
      buff.write(_struct_f.pack(self.qualityOfError.qualityOfPosition))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.robotPosition is None:
        self.robotPosition = C25_GlobalPosition.msg.C25C0_ROP()
      if self.qualityOfError is None:
        self.qualityOfError = C25_GlobalPosition.msg.C25C0_OPO()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.robotPosition.imu.header.seq, _x.robotPosition.imu.header.stamp.secs, _x.robotPosition.imu.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.robotPosition.imu.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.robotPosition.imu.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 32
      (_x.robotPosition.imu.orientation.x, _x.robotPosition.imu.orientation.y, _x.robotPosition.imu.orientation.z, _x.robotPosition.imu.orientation.w,) = _struct_4d.unpack(str[start:end])
      start = end
      end += 72
      self.robotPosition.imu.orientation_covariance = _struct_9d.unpack(str[start:end])
      _x = self
      start = end
      end += 24
      (_x.robotPosition.imu.angular_velocity.x, _x.robotPosition.imu.angular_velocity.y, _x.robotPosition.imu.angular_velocity.z,) = _struct_3d.unpack(str[start:end])
      start = end
      end += 72
      self.robotPosition.imu.angular_velocity_covariance = _struct_9d.unpack(str[start:end])
      _x = self
      start = end
      end += 24
      (_x.robotPosition.imu.linear_acceleration.x, _x.robotPosition.imu.linear_acceleration.y, _x.robotPosition.imu.linear_acceleration.z,) = _struct_3d.unpack(str[start:end])
      start = end
      end += 72
      self.robotPosition.imu.linear_acceleration_covariance = _struct_9d.unpack(str[start:end])
      _x = self
      start = end
      end += 12
      (_x.robotPosition.pose.header.seq, _x.robotPosition.pose.header.stamp.secs, _x.robotPosition.pose.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.robotPosition.pose.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.robotPosition.pose.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.robotPosition.pose.child_frame_id = str[start:end].decode('utf-8')
      else:
        self.robotPosition.pose.child_frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.robotPosition.pose.pose.pose.position.x, _x.robotPosition.pose.pose.pose.position.y, _x.robotPosition.pose.pose.pose.position.z, _x.robotPosition.pose.pose.pose.orientation.x, _x.robotPosition.pose.pose.pose.orientation.y, _x.robotPosition.pose.pose.pose.orientation.z, _x.robotPosition.pose.pose.pose.orientation.w,) = _struct_7d.unpack(str[start:end])
      start = end
      end += 288
      self.robotPosition.pose.pose.covariance = _struct_36d.unpack(str[start:end])
      _x = self
      start = end
      end += 48
      (_x.robotPosition.pose.twist.twist.linear.x, _x.robotPosition.pose.twist.twist.linear.y, _x.robotPosition.pose.twist.twist.linear.z, _x.robotPosition.pose.twist.twist.angular.x, _x.robotPosition.pose.twist.twist.angular.y, _x.robotPosition.pose.twist.twist.angular.z,) = _struct_6d.unpack(str[start:end])
      start = end
      end += 288
      self.robotPosition.pose.twist.covariance = _struct_36d.unpack(str[start:end])
      start = end
      end += 4
      (self.qualityOfError.qualityOfPosition,) = _struct_f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.robotPosition.imu.header.seq, _x.robotPosition.imu.header.stamp.secs, _x.robotPosition.imu.header.stamp.nsecs))
      _x = self.robotPosition.imu.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_4d.pack(_x.robotPosition.imu.orientation.x, _x.robotPosition.imu.orientation.y, _x.robotPosition.imu.orientation.z, _x.robotPosition.imu.orientation.w))
      buff.write(self.robotPosition.imu.orientation_covariance.tostring())
      _x = self
      buff.write(_struct_3d.pack(_x.robotPosition.imu.angular_velocity.x, _x.robotPosition.imu.angular_velocity.y, _x.robotPosition.imu.angular_velocity.z))
      buff.write(self.robotPosition.imu.angular_velocity_covariance.tostring())
      _x = self
      buff.write(_struct_3d.pack(_x.robotPosition.imu.linear_acceleration.x, _x.robotPosition.imu.linear_acceleration.y, _x.robotPosition.imu.linear_acceleration.z))
      buff.write(self.robotPosition.imu.linear_acceleration_covariance.tostring())
      _x = self
      buff.write(_struct_3I.pack(_x.robotPosition.pose.header.seq, _x.robotPosition.pose.header.stamp.secs, _x.robotPosition.pose.header.stamp.nsecs))
      _x = self.robotPosition.pose.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.robotPosition.pose.child_frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_7d.pack(_x.robotPosition.pose.pose.pose.position.x, _x.robotPosition.pose.pose.pose.position.y, _x.robotPosition.pose.pose.pose.position.z, _x.robotPosition.pose.pose.pose.orientation.x, _x.robotPosition.pose.pose.pose.orientation.y, _x.robotPosition.pose.pose.pose.orientation.z, _x.robotPosition.pose.pose.pose.orientation.w))
      buff.write(self.robotPosition.pose.pose.covariance.tostring())
      _x = self
      buff.write(_struct_6d.pack(_x.robotPosition.pose.twist.twist.linear.x, _x.robotPosition.pose.twist.twist.linear.y, _x.robotPosition.pose.twist.twist.linear.z, _x.robotPosition.pose.twist.twist.angular.x, _x.robotPosition.pose.twist.twist.angular.y, _x.robotPosition.pose.twist.twist.angular.z))
      buff.write(self.robotPosition.pose.twist.covariance.tostring())
      buff.write(_struct_f.pack(self.qualityOfError.qualityOfPosition))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.robotPosition is None:
        self.robotPosition = C25_GlobalPosition.msg.C25C0_ROP()
      if self.qualityOfError is None:
        self.qualityOfError = C25_GlobalPosition.msg.C25C0_OPO()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.robotPosition.imu.header.seq, _x.robotPosition.imu.header.stamp.secs, _x.robotPosition.imu.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.robotPosition.imu.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.robotPosition.imu.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 32
      (_x.robotPosition.imu.orientation.x, _x.robotPosition.imu.orientation.y, _x.robotPosition.imu.orientation.z, _x.robotPosition.imu.orientation.w,) = _struct_4d.unpack(str[start:end])
      start = end
      end += 72
      self.robotPosition.imu.orientation_covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=9)
      _x = self
      start = end
      end += 24
      (_x.robotPosition.imu.angular_velocity.x, _x.robotPosition.imu.angular_velocity.y, _x.robotPosition.imu.angular_velocity.z,) = _struct_3d.unpack(str[start:end])
      start = end
      end += 72
      self.robotPosition.imu.angular_velocity_covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=9)
      _x = self
      start = end
      end += 24
      (_x.robotPosition.imu.linear_acceleration.x, _x.robotPosition.imu.linear_acceleration.y, _x.robotPosition.imu.linear_acceleration.z,) = _struct_3d.unpack(str[start:end])
      start = end
      end += 72
      self.robotPosition.imu.linear_acceleration_covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=9)
      _x = self
      start = end
      end += 12
      (_x.robotPosition.pose.header.seq, _x.robotPosition.pose.header.stamp.secs, _x.robotPosition.pose.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.robotPosition.pose.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.robotPosition.pose.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.robotPosition.pose.child_frame_id = str[start:end].decode('utf-8')
      else:
        self.robotPosition.pose.child_frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.robotPosition.pose.pose.pose.position.x, _x.robotPosition.pose.pose.pose.position.y, _x.robotPosition.pose.pose.pose.position.z, _x.robotPosition.pose.pose.pose.orientation.x, _x.robotPosition.pose.pose.pose.orientation.y, _x.robotPosition.pose.pose.pose.orientation.z, _x.robotPosition.pose.pose.pose.orientation.w,) = _struct_7d.unpack(str[start:end])
      start = end
      end += 288
      self.robotPosition.pose.pose.covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=36)
      _x = self
      start = end
      end += 48
      (_x.robotPosition.pose.twist.twist.linear.x, _x.robotPosition.pose.twist.twist.linear.y, _x.robotPosition.pose.twist.twist.linear.z, _x.robotPosition.pose.twist.twist.angular.x, _x.robotPosition.pose.twist.twist.angular.y, _x.robotPosition.pose.twist.twist.angular.z,) = _struct_6d.unpack(str[start:end])
      start = end
      end += 288
      self.robotPosition.pose.twist.covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=36)
      start = end
      end += 4
      (self.qualityOfError.qualityOfPosition,) = _struct_f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_7d = struct.Struct("<7d")
_struct_6d = struct.Struct("<6d")
_struct_f = struct.Struct("<f")
_struct_36d = struct.Struct("<36d")
_struct_9d = struct.Struct("<9d")
_struct_3I = struct.Struct("<3I")
_struct_4d = struct.Struct("<4d")
_struct_3d = struct.Struct("<3d")
class C25(object):
  _type          = 'C25_GlobalPosition/C25'
  _md5sum = '053887982b6555df9b370f618535b17e'
  _request_class  = C25Request
  _response_class = C25Response
