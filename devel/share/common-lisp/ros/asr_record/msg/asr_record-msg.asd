
(cl:in-package :asdf)

(defsystem "asr_record-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "sr_order" :depends-on ("_package_sr_order"))
    (:file "_package_sr_order" :depends-on ("_package"))
  ))