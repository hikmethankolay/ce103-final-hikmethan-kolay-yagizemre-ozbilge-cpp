# aka5g/CMakeLists.txt
set(ROOT src)
set(APPNAME car_maintenance_app)

message(STATUS "[${ROOT}/${APPNAME}] Module Processing...")

# Collect files without having to explicitly list each header and source file
file(GLOB APP_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

file(GLOB APP_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")

# Create named folders for the sources within the project
source_group("include" FILES ${APP_HEADERS})
source_group("src" FILES ${APP_SOURCES})

# Set Properties->General->Configuration Type to Dynamic Library (.dll/.so/.dylib)
add_executable(${APPNAME} ${APP_HEADERS} ${APP_SOURCES}) # for dynamic library use SHARED

target_include_directories(${APPNAME} PUBLIC
						   ${CMAKE_CURRENT_SOURCE_DIR}/../car_maintenance_lib/include
						   ${CMAKE_CURRENT_SOURCE_DIR}/include)


install(TARGETS ${APPNAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin )
		
		
message(STATUS "[${ROOT}/${APPNAME}] Added Executable target: ${APPNAME}")
