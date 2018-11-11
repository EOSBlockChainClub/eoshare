add_contract(eoshare eoshare ${CMAKE_CURRENT_SOURCE_DIR}/src/eoshare.cpp)
target_include_directories(eoshare.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eoshare.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
