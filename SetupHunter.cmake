set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

#cmake_policy(SET CMP0077 OLD)
#set(HUNTER_STATUS_DEBUG ON)

include(FetchContent)
FetchContent_Declare(SetupHunter GIT_REPOSITORY https://github.com/cpp-pm/gate) # GIT_TAG "master") # "2fea25c8557f3c86502830d4b7d2c7445a043c7b"

#set(HUNTER_Boost_COMPONENTS test) 
set(HUNTER_pcre2_CMAKE_ARGS
    PCRE2_BUILD_PCRE2_8=OFF
    PCRE2_BUILD_PCRE2_16=ON
    PCRE2_BUILD_PCRE2_32=OFF
    PCRE2_SUPPORT_JIT=ON)
#set(HUNTER_PACKAGES pcre2 GTest Boost) 
set(HUNTER_PACKAGES benchmark)

FetchContent_MakeAvailable(SetupHunter)
