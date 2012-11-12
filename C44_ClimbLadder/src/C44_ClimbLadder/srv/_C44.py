"""autogenerated by genpy from C44_ClimbLadder/C44Request.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import C44_ClimbLadder.msg

class C44Request(genpy.Message):
  _md5sum = "24ca5df1c755e634d4f8aec87d55c1b0"
  _type = "C44_ClimbLadder/C44Request"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """C44_ClimbLadder/C23C44_LDIM ladder_dimensions_msg
C44_ClimbLadder/C23C44_DIS distance_between_steps_msg

================================================================================
MSG: C44_ClimbLadder/C23C44_LDIM
float32[] ladder_dimensions

================================================================================
MSG: C44_ClimbLadder/C23C44_DIS
float32 distance_between_steps

"""
  __slots__ = ['ladder_dimensions_msg','distance_between_steps_msg']
  _slot_types = ['C44_ClimbLadder/C23C44_LDIM','C44_ClimbLadder/C23C44_DIS']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       ladder_dimensions_msg,distance_between_steps_msg

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(C44Request, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.ladder_dimensions_msg is None:
        self.ladder_dimensions_msg = C44_ClimbLadder.msg.C23C44_LDIM()
      if self.distance_between_steps_msg is None:
        self.distance_between_steps_msg = C44_ClimbLadder.msg.C23C44_DIS()
    else:
      self.ladder_dimensions_msg = C44_ClimbLadder.msg.C23C44_LDIM()
      self.distance_between_steps_msg = C44_ClimbLadder.msg.C23C44_DIS()

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
      length = len(self.ladder_dimensions_msg.ladder_dimensions)
      buff.write(_struct_I.pack(length))
      pattern = '<%sf'%length
      buff.write(struct.pack(pattern, *self.ladder_dimensions_msg.ladder_dimensions))
      buff.write(_struct_f.pack(self.distance_between_steps_msg.distance_between_steps))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.ladder_dimensions_msg is None:
        self.ladder_dimensions_msg = C44_ClimbLadder.msg.C23C44_LDIM()
      if self.distance_between_steps_msg is None:
        self.distance_between_steps_msg = C44_ClimbLadder.msg.C23C44_DIS()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sf'%length
      start = end
      end += struct.calcsize(pattern)
      self.ladder_dimensions_msg.ladder_dimensions = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (self.distance_between_steps_msg.distance_between_steps,) = _struct_f.unpack(str[start:end])
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
      length = len(self.ladder_dimensions_msg.ladder_dimensions)
      buff.write(_struct_I.pack(length))
      pattern = '<%sf'%length
      buff.write(self.ladder_dimensions_msg.ladder_dimensions.tostring())
      buff.write(_struct_f.pack(self.distance_between_steps_msg.distance_between_steps))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.ladder_dimensions_msg is None:
        self.ladder_dimensions_msg = C44_ClimbLadder.msg.C23C44_LDIM()
      if self.distance_between_steps_msg is None:
        self.distance_between_steps_msg = C44_ClimbLadder.msg.C23C44_DIS()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sf'%length
      start = end
      end += struct.calcsize(pattern)
      self.ladder_dimensions_msg.ladder_dimensions = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=length)
      start = end
      end += 4
      (self.distance_between_steps_msg.distance_between_steps,) = _struct_f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_f = struct.Struct("<f")
"""autogenerated by genpy from C44_ClimbLadder/C44Response.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import C44_ClimbLadder.msg

class C44Response(genpy.Message):
  _md5sum = "4fb75a3eea0239edca2121454cdf62e3"
  _type = "C44_ClimbLadder/C44Response"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """C44_ClimbLadder/C44C0_CLS climb_a_ladder_Success_msg



================================================================================
MSG: C44_ClimbLadder/C44C0_CLS
bool climb_a_ladder_success

"""
  __slots__ = ['climb_a_ladder_Success_msg']
  _slot_types = ['C44_ClimbLadder/C44C0_CLS']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       climb_a_ladder_Success_msg

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(C44Response, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.climb_a_ladder_Success_msg is None:
        self.climb_a_ladder_Success_msg = C44_ClimbLadder.msg.C44C0_CLS()
    else:
      self.climb_a_ladder_Success_msg = C44_ClimbLadder.msg.C44C0_CLS()

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
      buff.write(_struct_B.pack(self.climb_a_ladder_Success_msg.climb_a_ladder_success))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.climb_a_ladder_Success_msg is None:
        self.climb_a_ladder_Success_msg = C44_ClimbLadder.msg.C44C0_CLS()
      end = 0
      start = end
      end += 1
      (self.climb_a_ladder_Success_msg.climb_a_ladder_success,) = _struct_B.unpack(str[start:end])
      self.climb_a_ladder_Success_msg.climb_a_ladder_success = bool(self.climb_a_ladder_Success_msg.climb_a_ladder_success)
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
      buff.write(_struct_B.pack(self.climb_a_ladder_Success_msg.climb_a_ladder_success))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.climb_a_ladder_Success_msg is None:
        self.climb_a_ladder_Success_msg = C44_ClimbLadder.msg.C44C0_CLS()
      end = 0
      start = end
      end += 1
      (self.climb_a_ladder_Success_msg.climb_a_ladder_success,) = _struct_B.unpack(str[start:end])
      self.climb_a_ladder_Success_msg.climb_a_ladder_success = bool(self.climb_a_ladder_Success_msg.climb_a_ladder_success)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_B = struct.Struct("<B")
class C44(object):
  _type          = 'C44_ClimbLadder/C44'
  _md5sum = 'a70e7b52412f77b8f72fb49133206e55'
  _request_class  = C44Request
  _response_class = C44Response
