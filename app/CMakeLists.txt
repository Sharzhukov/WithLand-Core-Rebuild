add_executable(withland main.cpp)
target_link_libraries(withland PRIVATE Withland::Core)
withland_apply_warnings(withland)

install(TARGETS withland
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)