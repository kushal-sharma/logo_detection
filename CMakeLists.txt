project(flickr_logos)
cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)
find_package(Boost 1.67 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(index index.cpp)
add_executable(vocab vocab.cpp)
add_executable(test test.cpp)
add_executable(init init.cpp)
add_executable(orb orb.cpp)
add_executable(index_file index_file.cpp)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

target_link_libraries(index ${OpenCV_LIBRARIES})
target_link_libraries(index ${Boost_LIBRARIES})

target_link_libraries(vocab ${OpenCV_LIBRARIES})
target_link_libraries(vocab ${Boost_LIBRARIES})

target_link_libraries(test ${OpenCV_LIBRARIES})
target_link_libraries(test ${Boost_LIBRARIES})

target_link_libraries(init ${OpenCV_LIBRARIES})
target_link_libraries(init ${Boost_LIBRARIES})

target_link_libraries(orb ${OpenCV_LIBRARIES})
target_link_libraries(orb ${Boost_LIBRARIES})

target_link_libraries(index_file ${OpenCV_LIBRARIES})
target_link_libraries(index_file ${Boost_LIBRARIES})
