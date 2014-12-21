
# enable c++11
add_definitions(-std=c++11)

include_directories(.)

# for json lib
include_directories(${CMAKE_SOURCE_DIR}/json)
include_directories(${CMAKE_BINARY_DIR}/json)

# for curl cpp
include_directories(${CURLCPP_SOURCE_DIR}/include)

file(GLOB src *.cc)
file(GLOB headers *.h)

add_executable(pushover-client
  ${src}
  ${headers})

target_link_libraries(
  pushover-client
  json
  curlcpp)

add_dependencies(
  pushover-client
  json
  curlcpp)