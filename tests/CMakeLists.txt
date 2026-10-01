add_executable(civicdesk_tests
    main.cpp
    test_domain.cpp
    test_validation.cpp
    test_specifications.cpp
    test_report_service.cpp
    test_infrastructure.cpp
    test_presentation.cpp)

# doctest is third-party code: SYSTEM keeps its own warnings out of our build.
target_include_directories(civicdesk_tests SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/third_party)
target_include_directories(civicdesk_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(civicdesk_tests PRIVATE civicdesk_core civicdesk_warnings)

add_test(NAME civicdesk_tests COMMAND civicdesk_tests)
