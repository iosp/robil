
(cl:in-package :asdf)

(defsystem "C45_PostureControl-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "PostureControlGoal" :depends-on ("_package_PostureControlGoal"))
    (:file "_package_PostureControlGoal" :depends-on ("_package"))
    (:file "PostureControlActionResult" :depends-on ("_package_PostureControlActionResult"))
    (:file "_package_PostureControlActionResult" :depends-on ("_package"))
    (:file "PostureControlActionFeedback" :depends-on ("_package_PostureControlActionFeedback"))
    (:file "_package_PostureControlActionFeedback" :depends-on ("_package"))
    (:file "PostureControlActionGoal" :depends-on ("_package_PostureControlActionGoal"))
    (:file "_package_PostureControlActionGoal" :depends-on ("_package"))
    (:file "PostureControlAction" :depends-on ("_package_PostureControlAction"))
    (:file "_package_PostureControlAction" :depends-on ("_package"))
    (:file "PostureControlFeedback" :depends-on ("_package_PostureControlFeedback"))
    (:file "_package_PostureControlFeedback" :depends-on ("_package"))
    (:file "PostureControlResult" :depends-on ("_package_PostureControlResult"))
    (:file "_package_PostureControlResult" :depends-on ("_package"))
  ))