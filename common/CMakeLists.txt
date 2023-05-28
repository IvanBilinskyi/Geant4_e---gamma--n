find_package(Boost REQUIRED COMPONENTS program_options filesystem)

find_package(indicators CONFIG REQUIRED)

configure_file(config.h.in config.h)

add_library(common
        ProgressBar.cpp
        ProgressBar.h
        StringTools.h
        ProgramOptions.cpp
        ProgramOptions.h
        config.h)
target_link_libraries(common
        Boost::program_options
        Boost::filesystem
        indicators::indicators
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})