FILE(REMOVE_RECURSE
  "msg_gen"
  "srv_gen"
  "msg_gen"
  "srv_gen"
  "src/C21_VisionAndLidar/msg"
  "src/C21_VisionAndLidar/srv"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "srv_gen/lisp/C21.lisp"
  "srv_gen/lisp/_package.lisp"
  "srv_gen/lisp/_package_C21.lisp"
  "srv_gen/lisp/C21_Pan.lisp"
  "srv_gen/lisp/_package.lisp"
  "srv_gen/lisp/_package_C21_Pan.lisp"
  "srv_gen/lisp/C21_Pic.lisp"
  "srv_gen/lisp/_package.lisp"
  "srv_gen/lisp/_package_C21_Pic.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
