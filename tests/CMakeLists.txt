# Test runner. Currently a placeholder — swap for Catch2 / GoogleTest
# once the first real test source is added.

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(withland_core_tests main.cpp)
    target_link_libraries(withland_core_tests PRIVATE Withland::Core)
    withland_apply_warnings(withland_core_tests)
    withland_apply_sanitizers(withland_core_tests)
else()
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp"
         "int main() { return 0; }\n")
    add_executable(withland_core_tests "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp")
    message(STATUS "tests: using placeholder — add tests/main.cpp to override")
endif()

set_target_properties(withland_core_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
)

add_test(NAME withland_core_tests COMMAND withland_core_tests)