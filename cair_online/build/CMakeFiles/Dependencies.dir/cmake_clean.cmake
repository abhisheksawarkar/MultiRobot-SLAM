FILE(REMOVE_RECURSE
  "CMakeFiles/Dependencies"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/Dependencies.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
