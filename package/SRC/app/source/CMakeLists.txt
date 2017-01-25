file (GLOB MAIN_SOURCE_FILES "*.cpp")

# wxWidgets
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../externals/wxWidgets-3.1.0/install_dir)
message(STATUS "Root path: " ${CMAKE_FIND_ROOT_PATH})

set(wxWidgets_USE_DEBUG OFF)
set(wxWidgets_USE_STATIC ON)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

add_executable(ImagesComparer ${MAIN_SOURCE_FILES} ${FORMS_SOURCE_FILES} ../include/WindowPatch.h)
target_link_libraries(ImagesComparer ${wxWidgets_LIBRARIES})

install(DIRECTORY ../forms/icons DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../artifacts)
install(TARGETS ImagesComparer DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../artifacts)
