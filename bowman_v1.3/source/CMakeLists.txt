include_directories(${BOWMANS_SOURCE_DIR}/source)
link_directories(${BOWMANS_BINARY_DIR}/source)

# set (RESOURCE_FILES Spoopies.ttf)
# message(STATUS "Resource FILES is: " ${RESOURCE_FILES})

file(GLOB_RECURSE SOURCEFILES "*.cpp")
message(STATUS "Sources are is: " ${SOURCEFILES})
# list (APPEND SOURCEFILES "Spoopies.ttf")

add_executable(${PROJECT_NAME} ${SOURCEFILES})
# message(STATUS "Value is: " ${BOWMANS_SOURCE_DIR})

set(RESOURCE_FILES
  Spoopies.ttf
  white.png
  space.png
  cross2.png
  )
install(FILES ${RESOURCE_FILES} DESTINATION ${BOWMANS_SOURCE_DIR}/build/source)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
