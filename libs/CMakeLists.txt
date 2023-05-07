set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# GLM
# https://github.com/g-truc/glm
add_library(glm INTERFACE)
target_include_directories(glm SYSTEM INTERFACE "glm"
)
