# Project name
project(quadratic_equation)

# Sources
set(SRC_QE quadratic_equation.c)

# Create static lib
add_library(${PROJECT_NAME}_lib STATIC ${SRC_QE})

# Create dinamic lib
# add_library(${PROJECT_NAME}_lib SHARED ${SRC_QE})

# Linking math lib
target_link_libraries(${PROJECT_NAME}_lib m)
