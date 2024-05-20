include(FetchContent)

FetchContent_Declare(
 	bgfx
  	GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake
  	GIT_TAG v1.127.8725-465
)

set( BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory(bgfx)
