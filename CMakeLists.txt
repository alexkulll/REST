cmake_minimum_required(VERSION 3.10)
project(CPP_REST_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Если хотите подавить предупреждение FindBoost:
# cmake_policy(SET CMP0167 NEW)

# Находим Boost (только компонент system, Beast/Asio header-only)
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Находим JSON
find_package(nlohmann_json CONFIG REQUIRED)

# Находим Catch2 (vcpkg catch2 предоставляет цель Catch2::Catch2WithMain)
find_package(Catch2 CONFIG REQUIRED)

# основной сервер
add_executable(rest_server main.cpp)

if(WIN32)
    target_link_libraries(rest_server PRIVATE ws2_32)
endif()
target_link_libraries(rest_server
    PRIVATE
        Boost::system
        nlohmann_json::nlohmann_json
)

# юниттесты
enable_testing()
add_executable(tests test_tasks.cpp)

if(WIN32)
    target_link_libraries(tests PRIVATE ws2_32)
endif()
target_link_libraries(tests
    PRIVATE
        Boost::system
        nlohmann_json::nlohmann_json
        Catch2::Catch2WithMain
)

add_test(NAME all_unit_tests COMMAND tests)
