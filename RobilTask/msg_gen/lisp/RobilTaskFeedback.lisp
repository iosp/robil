; Auto-generated. Do not edit!


(cl:in-package RobilTask-msg)


;//! \htmlinclude RobilTaskFeedback.msg.html

(cl:defclass <RobilTaskFeedback> (roslisp-msg-protocol:ros-message)
  ((complete
    :reader complete
    :initarg :complete
    :type cl:float
    :initform 0.0))
)

(cl:defclass RobilTaskFeedback (<RobilTaskFeedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobilTaskFeedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobilTaskFeedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name RobilTask-msg:<RobilTaskFeedback> is deprecated: use RobilTask-msg:RobilTaskFeedback instead.")))

(cl:ensure-generic-function 'complete-val :lambda-list '(m))
(cl:defmethod complete-val ((m <RobilTaskFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader RobilTask-msg:complete-val is deprecated.  Use RobilTask-msg:complete instead.")
  (complete m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobilTaskFeedback>) ostream)
  "Serializes a message object of type '<RobilTaskFeedback>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'complete))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobilTaskFeedback>) istream)
  "Deserializes a message object of type '<RobilTaskFeedback>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'complete) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RobilTaskFeedback>)))
  "Returns string type for a message object of type '<RobilTaskFeedback>"
  "RobilTask/RobilTaskFeedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobilTaskFeedback)))
  "Returns string type for a message object of type 'RobilTaskFeedback"
  "RobilTask/RobilTaskFeedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RobilTaskFeedback>)))
  "Returns md5sum for a message object of type '<RobilTaskFeedback>"
  "400345d77a70d48b24323a6a2a59ab1e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobilTaskFeedback)))
  "Returns md5sum for a message object of type 'RobilTaskFeedback"
  "400345d77a70d48b24323a6a2a59ab1e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobilTaskFeedback>)))
  "Returns full string definition for message of type '<RobilTaskFeedback>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define a feedback message~%float32 complete~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobilTaskFeedback)))
  "Returns full string definition for message of type 'RobilTaskFeedback"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define a feedback message~%float32 complete~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobilTaskFeedback>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobilTaskFeedback>))
  "Converts a ROS message object to a list"
  (cl:list 'RobilTaskFeedback
    (cl:cons ':complete (complete msg))
))
