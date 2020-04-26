if(NOT TARGET PretzelGui)
    # Define ${Cinder-Notifications_SOURCE_PATH}. ${CMAKE_CURRENT_LIST_DIR} is just the current directory.
    get_filename_component(PretzelGui_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE)

    # Define ${CINDER_PATH} as usual.
    get_filename_component(CINDER_PATH "../../../../../.." ABSOLUTE)

    # Make a list of source files and define that to be ${SOURCE_LIST}.
    file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
            "${PretzelGui_SOURCE_PATH}/**/*.h"
            "${PretzelGui_SOURCE_PATH}/**/*.hpp"
            "${PretzelGui_SOURCE_PATH}/**/*.H"
            "${PretzelGui_SOURCE_PATH}/**/*.cc"
            "${PretzelGui_SOURCE_PATH}/**/*.cpp"
            "${PretzelGui_SOURCE_PATH}/**/*.C"
            "${PretzelGui_SOURCE_PATH}/**/*.c")

    set_source_files_properties("${PretzelGui_SOURCE_PATH}/pretzel/PretzelGlobal.cpp" PROPERTIES COMPILE_FLAGS "-x objective-c++")



    # Create the library!
    add_library(PretzelGui ${SOURCE_LIST})

    # Add include directories.
    # Notice that `cinderblock.xml` has `<includePath>src</includePath>`.
    # So you need to set `../../src/` to include.
    target_include_directories(PretzelGui PUBLIC "../../../../src")
    target_include_directories(PretzelGui SYSTEM BEFORE PUBLIC "/Users/katiesanders/Downloads/cinder_0.9.2_mac/blocks/PretzelGui/src")
    target_include_directories(PretzelGui PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/../../src/pretzel"
            "${CMAKE_CURRENT_LIST_DIR}/../../src/modules"
            "${CMAKE_CURRENT_LIST_DIR}/../../src/components"
            )


    # If your Cinder block has no source code but instead pre-build libraries,
    # you can specify all of them here (uncomment the below line and adjust to your needs).
    # Make sure to use the libraries for the right platform.
    # # target_link_libraries(Cinder-Notifications ${Cinder-OpenCV_SOURCE_PATH}/lib/libopencv_core.a)

    # This part is optional, depending on if the library needs libcinder.
    if(NOT TARGET cinder)
        include("${CINDER_PATH}/proj/cmake/configure.cmake")
        find_package(cinder REQUIRED PATHS
                "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
                "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}")
    endif()
    target_link_libraries(PretzelGui PRIVATE cinder)
    # End optional part.

endif()