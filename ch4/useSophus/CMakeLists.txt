cmake_minimum_required( VERSION 2.8 )
project( useSophus )

# 为使用sophus，您需要使用find_package命令找到它
find_package( Sophus REQUIRED )
include_directories( 
    "/usr/include/eigen3"
    ${Sophus_INCLUDE_DIRS}
 )

set(Sophus_LIBRARIES libSophus.so)

add_executable( useSophus useSophus.cpp )
target_link_libraries( useSophus ${Sophus_LIBRARIES}  )