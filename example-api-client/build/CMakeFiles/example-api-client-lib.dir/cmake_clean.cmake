file(REMOVE_RECURSE
  "libexample-api-client-lib.a"
  "libexample-api-client-lib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/example-api-client-lib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
