## Dependencies ## ====================================================================
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED) # Required for GTest
#    message(STATUS ${GTEST_LIBRARIES})
#    message(STATUS ${GTEST_INCLUDE_DIRS})
#    message(STATUS ${GTEST_FOUND})
#    message(STATUS ${CMAKE_THREAD_LIBS_INIT})
## ============ ## ====================================================================

## Target tests ## ================================================================
add_executable(${FIREFLY_CORE_TARGET}_test
        OperationSaver.cpp
        main_test.cpp)

# Installation
install(TARGETS ${FIREFLY_CORE_TARGET}_test DESTINATION bin)

target_link_libraries(${FIREFLY_CORE_TARGET}_test
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_LIBRARIES}
        ${FIREFLY_CORE_TARGET})
target_include_directories(${FIREFLY_CORE_TARGET}_test
        PRIVATE ${GTest_INCLUDE_DIRS})
add_dependencies(${FIREFLY_CORE_TARGET}_test ${FIREFLY_CORE_TARGET})
## ============ ## ====================================================================