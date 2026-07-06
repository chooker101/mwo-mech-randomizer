add_executable(mwomr_cli)

target_link_libraries(mwomr_cli
PUBLIC
    CURL::libcurl
    mwomr_api
)

file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

target_include_directories(mwomr_cli
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(mwomr_cli
PRIVATE
    ${headers}
    ${sources}
)