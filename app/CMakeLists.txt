# Main executable. Uses withland's core library.
# Falls back to a placeholder main() until app/main.cpp exists.

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(withland main.cpp)
else()
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp"
         "int main() { return 0; }\n")
    add_executable(withland "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp")
    message(STATUS "app: using placeholder main() — add app/main.cpp to override")
endif()

target_link_libraries(withland PRIVATE Withland::Core)

withland_apply_warnings(withland)
withland_apply_sanitizers(withland)

set_target_properties(withland PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
)