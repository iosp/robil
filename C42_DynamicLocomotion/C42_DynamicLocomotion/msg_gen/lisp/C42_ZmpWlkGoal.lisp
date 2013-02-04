; Auto-generated. Do not edit!


(cl:in-package C42_DynamicLocomotion-msg)


;//! \htmlinclude C42_ZmpWlkGoal.msg.html

(cl:defclass <C42_ZmpWlkGoal> (roslisp-msg-protocol:ros-message)
  ((goal_pos
    :reader goal_pos
    :initarg :goal_pos
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (tol
    :reader tol
    :initarg :tol
    :type cl:float
    :initform 0.0))
)

(cl:defclass C42_ZmpWlkGoal (<C42_ZmpWlkGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <C42_ZmpWlkGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'C42_ZmpWlkGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name C42_DynamicLocomotion-msg:<C42_ZmpWlkGoal> is deprecated: use C42_DynamicLocomotion-msg:C42_ZmpWlkGoal instead.")))

(cl:ensure-generic-function 'goal_pos-val :lambda-list '(m))
(cl:defmethod goal_pos-val ((m <C42_ZmpWlkGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader C42_DynamicLocomotion-msg:goal_pos-val is deprecated.  Use C42_DynamicLocomotion-msg:goal_pos instead.")
  (goal_pos m))

(cl:ensure-generic-function 'tol-val :lambda-list '(m))
(cl:defmethod tol-val ((m <C42_ZmpWlkGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader C42_DynamicLocomotion-msg:tol-val is deprecated.  Use C42_DynamicLocomotion-msg:tol instead.")
  (tol m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <C42_ZmpWlkGoal>) ostream)
  "Serializes a message object of type '<C42_ZmpWlkGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_pos) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'tol))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <C42_ZmpWlkGoal>) istream)
  "Deserializes a message object of type '<C42_ZmpWlkGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_pos) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tol) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<C42_ZmpWlkGoal>)))
  "Returns string type for a message object of type '<C42_ZmpWlkGoal>"
  "C42_DynamicLocomotion/C42_ZmpWlkGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'C42_ZmpWlkGoal)))
  "Returns string type for a message object of type 'C42_ZmpWlkGoal"
  "C42_DynamicLocomotion/C42_ZmpWlkGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<C42_ZmpWlkGoal>)))
  "Returns md5sum for a message object of type '<C42_ZmpWlkGoal>"
  "1401675520343c88fc779bbdd18e30b8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'C42_ZmpWlkGoal)))
  "Returns md5sum for a message object of type 'C42_ZmpWlkGoal"
  "1401675520343c88fc779bbdd18e30b8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<C42_ZmpWlkGoal>)))
  "Returns full string definition for message of type '<C42_ZmpWlkGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal position and orientation~%geometry_msgs/Pose2D goal_pos~%float64 tol~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'C42_ZmpWlkGoal)))
  "Returns full string definition for message of type 'C42_ZmpWlkGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal position and orientation~%geometry_msgs/Pose2D goal_pos~%float64 tol~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <C42_ZmpWlkGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_pos))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <C42_ZmpWlkGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'C42_ZmpWlkGoal
    (cl:cons ':goal_pos (goal_pos msg))
    (cl:cons ':tol (tol msg))
))