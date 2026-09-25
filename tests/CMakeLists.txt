add_executable(withland_core_tests mainTest.cpp)
target_link_libraries(withland_core_tests PRIVATE Withland::Core)
withland_apply_warnings(withland_core_tests)

add_test(NAME core_tests COMMAND withland_core_tests)
set_tests_properties(core_tests PROPERTIES
    TIMEOUT 10
    FAIL_REGULAR_EXPRESSION "ASSERT FAILED"
)