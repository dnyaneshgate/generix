FILE(REMOVE_RECURSE
  "CMakeFiles/*.o"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/*.o.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
