cmake_minimum_required(VERSION 3.20)

set(PostgreSQL_ADDITIONAL_VERSIONS "16")

project (PostgresCPP)

add_subdirectory ("E:\\c++\\libpqxx-7.8.1" libpqxx-build)

add_executable(PostgresCPP main.cpp)

target_compile_features(PostgresCPP PRIVATE cxx_std_17)

target_link_libraries(PostgresCPP  PRIVATE pqxx)