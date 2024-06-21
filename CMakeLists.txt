cmake_minimum_required (VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang++")
project (MLCXC)

#includes
include_directories("ctranslate2_bin/sentencepiece/include")
include_directories("ctranslate2_bin/include")
include_directories("include")

#libs
link_directories("ctranslate2_bin/Debug_OpenBLAS/lib")
link_directories("ctranslate2_bin/sentencepiece/lib")

# Set the directory where your executable will be built
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Set the directory where your DLLs are located
set(DLL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/dlls)

# Set the directory where DLLs will be copied to
set(DLL_DESTINATION_DIR ${EXECUTABLE_OUTPUT_PATH})

message( "taxoxiortatasdasdadasda")

message(STATUS "DLL_SOURCE_DIR: ${DLL_SOURCE_DIR}")
message(STATUS "DLL_DESTINATION_DIR: ${DLL_DESTINATION_DIR}")

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*" "src/fileManager/*" "src/tokenManager/*" "src/translator/*" "src/processCaller/*")
add_executable(main ${SOURCES})
target_link_libraries(main "ctranslate2" "sentencepiece") 

#  target_precompile_headers()

# Add a custom command to copy DLLs to the executable directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${DLL_SOURCE_DIR} ${DLL_DESTINATION_DIR}
    COMMENT "Copying DLLs to executable directory..."
)