add_library(mwomr_api)

file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

target_include_directories(mwomr_api
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(mwomr_api
PRIVATE
    ${headers}
    ${sources}
)