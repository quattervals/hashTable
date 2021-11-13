# Make an automatic library - will be static or dynamic based on user setting
add_library(HashLib
  HashTable.cpp
  helpers.cpp )


# All users of this library will need at least C++xx
target_compile_features(HashLib PUBLIC cxx_std_20)
