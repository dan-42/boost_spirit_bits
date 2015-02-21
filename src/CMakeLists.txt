#------------------------------------
# Dependencies
#------------------------------------
# Boost
set(BOOST_ALL_DYN_LINK ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)    
find_package(Boost 1.55  REQUIRED )
include_directories (${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_LIST_DIR} )

add_executable(main  main.cpp )
target_link_libraries(main ${Boost_LIBRARIES} ${PSAPI_LIBRARIES})




