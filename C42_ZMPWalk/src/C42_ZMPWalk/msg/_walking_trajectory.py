"""autogenerated by genpy from C42_ZMPWalk/walking_trajectory.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import C42_ZMPWalk.msg

class walking_trajectory(genpy.Message):
  _md5sum = "b7a94b58ab85b0e768b1464d4dbe6582"
  _type = "C42_ZMPWalk/walking_trajectory"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# This message contains information of desired limb positions and orientation
# to be used by Inverse Kinematics function.
# The positions and orientations are relative to "forward stance foot" if not stated different.
# => stance_foot (x,y,z,r,p,w)=(0,0,0,0,0,0)
# x-forward, y-left side of robot, z-up, r-roll around x, p-pitch around y, w-yaw around z
# Units are [meter] and [rad]. 

# Stance leg information:
Position      stance_hip    # desired stance hip position (x,y,z) usage e.g: stance_hip.x
Orientation   pelvis_d      # desired pelvis orientation (r,p,w), to adjust robots posture 

# Swing leg information:
Pos_and_Ori   swing_foot    # desired swing foot position and orientation (x,y,z,r,p,w), 
                            # when swing foot is on the ground changes to measured (x,y,z,r,p,w).
Position      swing_hip     # desired swing hip position (x,y,z) 
Orientation   pelvis_m      # measured pelvis orientation(r,p,w) 

# ZMP preview controller:
Position      zmp_ref       # ZMP reference position (x,y,z) in "world" system. z=const 
Position      zmp_pc        # ZMP from preview controller, position (x,y,z) in "world" system. z=const

# COM information:
Position      com_ref       # desired COM position (x,y,z) in "world" system
Position      com_dot_ref   # desired COM velocity (x,y,z) [m/sec] in "world" system
Position      com_m         # measured COM position (x,y,z)

# Step phase information:
int32        step_phase     # 1 = Double-Support left leg in front, 2 = lift right swing leg
                            # 3 = Double-Support right leg in front, 4 = lift left swing leg 
# Orientation Correction
LeftRight    hip_z_orientation   # correction for hip w angle         

# for debug use:
Position      stance_hip_m  # measured stance hip position (x,y,z)
Position      swing_hip_m   # measured swing hip position (x,y,z)
Pos_and_Ori   swing_foot_m  # measured swing foot position and orientation (x,y,z,r,p,w)

# walking parameters 
float64 	step_length
float64 	step_width
float64 	step_height
float64 	zmp_width
float64 	step_time
float64 	bend_knees

================================================================================
MSG: C42_ZMPWalk/Position
float64 x
float64 y
float64 z

================================================================================
MSG: C42_ZMPWalk/Orientation
float64 r
float64 p
float64 w

================================================================================
MSG: C42_ZMPWalk/Pos_and_Ori
float64 x
float64 y
float64 z
float64 r
float64 p
float64 w

================================================================================
MSG: C42_ZMPWalk/LeftRight
float64 left
float64 right


"""
  __slots__ = ['stance_hip','pelvis_d','swing_foot','swing_hip','pelvis_m','zmp_ref','zmp_pc','com_ref','com_dot_ref','com_m','step_phase','hip_z_orientation','stance_hip_m','swing_hip_m','swing_foot_m','step_length','step_width','step_height','zmp_width','step_time','bend_knees']
  _slot_types = ['C42_ZMPWalk/Position','C42_ZMPWalk/Orientation','C42_ZMPWalk/Pos_and_Ori','C42_ZMPWalk/Position','C42_ZMPWalk/Orientation','C42_ZMPWalk/Position','C42_ZMPWalk/Position','C42_ZMPWalk/Position','C42_ZMPWalk/Position','C42_ZMPWalk/Position','int32','C42_ZMPWalk/LeftRight','C42_ZMPWalk/Position','C42_ZMPWalk/Position','C42_ZMPWalk/Pos_and_Ori','float64','float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       stance_hip,pelvis_d,swing_foot,swing_hip,pelvis_m,zmp_ref,zmp_pc,com_ref,com_dot_ref,com_m,step_phase,hip_z_orientation,stance_hip_m,swing_hip_m,swing_foot_m,step_length,step_width,step_height,zmp_width,step_time,bend_knees

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(walking_trajectory, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.stance_hip is None:
        self.stance_hip = C42_ZMPWalk.msg.Position()
      if self.pelvis_d is None:
        self.pelvis_d = C42_ZMPWalk.msg.Orientation()
      if self.swing_foot is None:
        self.swing_foot = C42_ZMPWalk.msg.Pos_and_Ori()
      if self.swing_hip is None:
        self.swing_hip = C42_ZMPWalk.msg.Position()
      if self.pelvis_m is None:
        self.pelvis_m = C42_ZMPWalk.msg.Orientation()
      if self.zmp_ref is None:
        self.zmp_ref = C42_ZMPWalk.msg.Position()
      if self.zmp_pc is None:
        self.zmp_pc = C42_ZMPWalk.msg.Position()
      if self.com_ref is None:
        self.com_ref = C42_ZMPWalk.msg.Position()
      if self.com_dot_ref is None:
        self.com_dot_ref = C42_ZMPWalk.msg.Position()
      if self.com_m is None:
        self.com_m = C42_ZMPWalk.msg.Position()
      if self.step_phase is None:
        self.step_phase = 0
      if self.hip_z_orientation is None:
        self.hip_z_orientation = C42_ZMPWalk.msg.LeftRight()
      if self.stance_hip_m is None:
        self.stance_hip_m = C42_ZMPWalk.msg.Position()
      if self.swing_hip_m is None:
        self.swing_hip_m = C42_ZMPWalk.msg.Position()
      if self.swing_foot_m is None:
        self.swing_foot_m = C42_ZMPWalk.msg.Pos_and_Ori()
      if self.step_length is None:
        self.step_length = 0.
      if self.step_width is None:
        self.step_width = 0.
      if self.step_height is None:
        self.step_height = 0.
      if self.zmp_width is None:
        self.zmp_width = 0.
      if self.step_time is None:
        self.step_time = 0.
      if self.bend_knees is None:
        self.bend_knees = 0.
    else:
      self.stance_hip = C42_ZMPWalk.msg.Position()
      self.pelvis_d = C42_ZMPWalk.msg.Orientation()
      self.swing_foot = C42_ZMPWalk.msg.Pos_and_Ori()
      self.swing_hip = C42_ZMPWalk.msg.Position()
      self.pelvis_m = C42_ZMPWalk.msg.Orientation()
      self.zmp_ref = C42_ZMPWalk.msg.Position()
      self.zmp_pc = C42_ZMPWalk.msg.Position()
      self.com_ref = C42_ZMPWalk.msg.Position()
      self.com_dot_ref = C42_ZMPWalk.msg.Position()
      self.com_m = C42_ZMPWalk.msg.Position()
      self.step_phase = 0
      self.hip_z_orientation = C42_ZMPWalk.msg.LeftRight()
      self.stance_hip_m = C42_ZMPWalk.msg.Position()
      self.swing_hip_m = C42_ZMPWalk.msg.Position()
      self.swing_foot_m = C42_ZMPWalk.msg.Pos_and_Ori()
      self.step_length = 0.
      self.step_width = 0.
      self.step_height = 0.
      self.zmp_width = 0.
      self.step_time = 0.
      self.bend_knees = 0.

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
      buff.write(_struct_33di20d.pack(_x.stance_hip.x, _x.stance_hip.y, _x.stance_hip.z, _x.pelvis_d.r, _x.pelvis_d.p, _x.pelvis_d.w, _x.swing_foot.x, _x.swing_foot.y, _x.swing_foot.z, _x.swing_foot.r, _x.swing_foot.p, _x.swing_foot.w, _x.swing_hip.x, _x.swing_hip.y, _x.swing_hip.z, _x.pelvis_m.r, _x.pelvis_m.p, _x.pelvis_m.w, _x.zmp_ref.x, _x.zmp_ref.y, _x.zmp_ref.z, _x.zmp_pc.x, _x.zmp_pc.y, _x.zmp_pc.z, _x.com_ref.x, _x.com_ref.y, _x.com_ref.z, _x.com_dot_ref.x, _x.com_dot_ref.y, _x.com_dot_ref.z, _x.com_m.x, _x.com_m.y, _x.com_m.z, _x.step_phase, _x.hip_z_orientation.left, _x.hip_z_orientation.right, _x.stance_hip_m.x, _x.stance_hip_m.y, _x.stance_hip_m.z, _x.swing_hip_m.x, _x.swing_hip_m.y, _x.swing_hip_m.z, _x.swing_foot_m.x, _x.swing_foot_m.y, _x.swing_foot_m.z, _x.swing_foot_m.r, _x.swing_foot_m.p, _x.swing_foot_m.w, _x.step_length, _x.step_width, _x.step_height, _x.zmp_width, _x.step_time, _x.bend_knees))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.stance_hip is None:
        self.stance_hip = C42_ZMPWalk.msg.Position()
      if self.pelvis_d is None:
        self.pelvis_d = C42_ZMPWalk.msg.Orientation()
      if self.swing_foot is None:
        self.swing_foot = C42_ZMPWalk.msg.Pos_and_Ori()
      if self.swing_hip is None:
        self.swing_hip = C42_ZMPWalk.msg.Position()
      if self.pelvis_m is None:
        self.pelvis_m = C42_ZMPWalk.msg.Orientation()
      if self.zmp_ref is None:
        self.zmp_ref = C42_ZMPWalk.msg.Position()
      if self.zmp_pc is None:
        self.zmp_pc = C42_ZMPWalk.msg.Position()
      if self.com_ref is None:
        self.com_ref = C42_ZMPWalk.msg.Position()
      if self.com_dot_ref is None:
        self.com_dot_ref = C42_ZMPWalk.msg.Position()
      if self.com_m is None:
        self.com_m = C42_ZMPWalk.msg.Position()
      if self.hip_z_orientation is None:
        self.hip_z_orientation = C42_ZMPWalk.msg.LeftRight()
      if self.stance_hip_m is None:
        self.stance_hip_m = C42_ZMPWalk.msg.Position()
      if self.swing_hip_m is None:
        self.swing_hip_m = C42_ZMPWalk.msg.Position()
      if self.swing_foot_m is None:
        self.swing_foot_m = C42_ZMPWalk.msg.Pos_and_Ori()
      end = 0
      _x = self
      start = end
      end += 428
      (_x.stance_hip.x, _x.stance_hip.y, _x.stance_hip.z, _x.pelvis_d.r, _x.pelvis_d.p, _x.pelvis_d.w, _x.swing_foot.x, _x.swing_foot.y, _x.swing_foot.z, _x.swing_foot.r, _x.swing_foot.p, _x.swing_foot.w, _x.swing_hip.x, _x.swing_hip.y, _x.swing_hip.z, _x.pelvis_m.r, _x.pelvis_m.p, _x.pelvis_m.w, _x.zmp_ref.x, _x.zmp_ref.y, _x.zmp_ref.z, _x.zmp_pc.x, _x.zmp_pc.y, _x.zmp_pc.z, _x.com_ref.x, _x.com_ref.y, _x.com_ref.z, _x.com_dot_ref.x, _x.com_dot_ref.y, _x.com_dot_ref.z, _x.com_m.x, _x.com_m.y, _x.com_m.z, _x.step_phase, _x.hip_z_orientation.left, _x.hip_z_orientation.right, _x.stance_hip_m.x, _x.stance_hip_m.y, _x.stance_hip_m.z, _x.swing_hip_m.x, _x.swing_hip_m.y, _x.swing_hip_m.z, _x.swing_foot_m.x, _x.swing_foot_m.y, _x.swing_foot_m.z, _x.swing_foot_m.r, _x.swing_foot_m.p, _x.swing_foot_m.w, _x.step_length, _x.step_width, _x.step_height, _x.zmp_width, _x.step_time, _x.bend_knees,) = _struct_33di20d.unpack(str[start:end])
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
      buff.write(_struct_33di20d.pack(_x.stance_hip.x, _x.stance_hip.y, _x.stance_hip.z, _x.pelvis_d.r, _x.pelvis_d.p, _x.pelvis_d.w, _x.swing_foot.x, _x.swing_foot.y, _x.swing_foot.z, _x.swing_foot.r, _x.swing_foot.p, _x.swing_foot.w, _x.swing_hip.x, _x.swing_hip.y, _x.swing_hip.z, _x.pelvis_m.r, _x.pelvis_m.p, _x.pelvis_m.w, _x.zmp_ref.x, _x.zmp_ref.y, _x.zmp_ref.z, _x.zmp_pc.x, _x.zmp_pc.y, _x.zmp_pc.z, _x.com_ref.x, _x.com_ref.y, _x.com_ref.z, _x.com_dot_ref.x, _x.com_dot_ref.y, _x.com_dot_ref.z, _x.com_m.x, _x.com_m.y, _x.com_m.z, _x.step_phase, _x.hip_z_orientation.left, _x.hip_z_orientation.right, _x.stance_hip_m.x, _x.stance_hip_m.y, _x.stance_hip_m.z, _x.swing_hip_m.x, _x.swing_hip_m.y, _x.swing_hip_m.z, _x.swing_foot_m.x, _x.swing_foot_m.y, _x.swing_foot_m.z, _x.swing_foot_m.r, _x.swing_foot_m.p, _x.swing_foot_m.w, _x.step_length, _x.step_width, _x.step_height, _x.zmp_width, _x.step_time, _x.bend_knees))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.stance_hip is None:
        self.stance_hip = C42_ZMPWalk.msg.Position()
      if self.pelvis_d is None:
        self.pelvis_d = C42_ZMPWalk.msg.Orientation()
      if self.swing_foot is None:
        self.swing_foot = C42_ZMPWalk.msg.Pos_and_Ori()
      if self.swing_hip is None:
        self.swing_hip = C42_ZMPWalk.msg.Position()
      if self.pelvis_m is None:
        self.pelvis_m = C42_ZMPWalk.msg.Orientation()
      if self.zmp_ref is None:
        self.zmp_ref = C42_ZMPWalk.msg.Position()
      if self.zmp_pc is None:
        self.zmp_pc = C42_ZMPWalk.msg.Position()
      if self.com_ref is None:
        self.com_ref = C42_ZMPWalk.msg.Position()
      if self.com_dot_ref is None:
        self.com_dot_ref = C42_ZMPWalk.msg.Position()
      if self.com_m is None:
        self.com_m = C42_ZMPWalk.msg.Position()
      if self.hip_z_orientation is None:
        self.hip_z_orientation = C42_ZMPWalk.msg.LeftRight()
      if self.stance_hip_m is None:
        self.stance_hip_m = C42_ZMPWalk.msg.Position()
      if self.swing_hip_m is None:
        self.swing_hip_m = C42_ZMPWalk.msg.Position()
      if self.swing_foot_m is None:
        self.swing_foot_m = C42_ZMPWalk.msg.Pos_and_Ori()
      end = 0
      _x = self
      start = end
      end += 428
      (_x.stance_hip.x, _x.stance_hip.y, _x.stance_hip.z, _x.pelvis_d.r, _x.pelvis_d.p, _x.pelvis_d.w, _x.swing_foot.x, _x.swing_foot.y, _x.swing_foot.z, _x.swing_foot.r, _x.swing_foot.p, _x.swing_foot.w, _x.swing_hip.x, _x.swing_hip.y, _x.swing_hip.z, _x.pelvis_m.r, _x.pelvis_m.p, _x.pelvis_m.w, _x.zmp_ref.x, _x.zmp_ref.y, _x.zmp_ref.z, _x.zmp_pc.x, _x.zmp_pc.y, _x.zmp_pc.z, _x.com_ref.x, _x.com_ref.y, _x.com_ref.z, _x.com_dot_ref.x, _x.com_dot_ref.y, _x.com_dot_ref.z, _x.com_m.x, _x.com_m.y, _x.com_m.z, _x.step_phase, _x.hip_z_orientation.left, _x.hip_z_orientation.right, _x.stance_hip_m.x, _x.stance_hip_m.y, _x.stance_hip_m.z, _x.swing_hip_m.x, _x.swing_hip_m.y, _x.swing_hip_m.z, _x.swing_foot_m.x, _x.swing_foot_m.y, _x.swing_foot_m.z, _x.swing_foot_m.r, _x.swing_foot_m.p, _x.swing_foot_m.w, _x.step_length, _x.step_width, _x.step_height, _x.zmp_width, _x.step_time, _x.bend_knees,) = _struct_33di20d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_33di20d = struct.Struct("<33di20d")
