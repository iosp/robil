FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/C31_PathPlanner/msg"
  "../src/C31_PathPlanner/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/test-results"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/test-results.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
