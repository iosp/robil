FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/C21_VisionAndLidar/msg"
  "../src/C21_VisionAndLidar/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C21C0_3DR.h"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C0C21_SIZ.h"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C0C21_RES.h"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C0C21_LAZ.h"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C21C0_3DF.h"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C0C21_CAM.h"
  "../msg_gen/cpp/include/C21_VisionAndLidar/C0C21_AZI.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
