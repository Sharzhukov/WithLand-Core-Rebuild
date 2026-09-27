# Sandbox — a small playground for manual testing.

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(withland_sandbox main.cpp)
else()
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp"
         "int main() { return 0; }\n")
    add_executable(withland_sandbox "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp")
    message(STATUS "sandbox: using placeholder main() — add sandbox/main.cpp to override")
endif()

target_link_libraries(withland_sandbox PRIVATE Withland::Core)

withland_apply_warnings(withland_sandbox)
withland_apply_sanitizers(withland_sandbox)

set_target_properties(withland_sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
)