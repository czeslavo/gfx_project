file (GLOB MAIN_SOURCE_FILES "*.cpp")
file (GLOB FORMS_SOURCE_FILES "../forms/*.cpp")

# -- example of adding library and linking it with boost libraries
# file (GLOB COMMON_SOURCE_FILES "common/*.cpp")
# add_library(common_lib ${COMMON_SOURCE_FILES})
# target_link_libraries(common_lib ${Boost_LIBRARIES})

# wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

add_executable(run_app ${MAIN_SOURCE_FILES} ${FORMS_SOURCE_FILES})
target_link_libraries(run_app ${wxWidgets_LIBRARIES})
