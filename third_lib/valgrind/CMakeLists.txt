set(CUSTOM_CMAKE_C_FLAGS "")
set(CUSTOM_CMAKE_CXX_FLAGS "")

include(ExternalProject)

ExternalProject_Add(valgrind
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/valgrind-3.23.0
    CONFIGURE_COMMAND
        ${CMAKE_COMMAND} -E echo "Configuring Valgrind" &&
        <SOURCE_DIR>/configure --prefix=${CMAKE_INSTALL_PREFIX} CC=${CMAKE_C_COMPILER}
        --enable-only-core
        --enable-only-core-deps
        --disable-shared
        --disable-callgrind
        --disable-cachegrind
        --disable-helgrind
        --disable-drd
        --disable-sgcheck
        --disable-exp-sgcheck
        --disable-dhat
        --disable-massif
        --disable-lackey
        --disable-none
        --disable-memcheck-amd64-solaris
        --disable-memcheck-x86-solaris
        --disable-memcheck-darwin
        --disable-auxprogs
        --disable-manpage-build
        --disable-mpi
        --disable-ubsan
        --disable-lto
        --disable-debuginfod
    BUILD_COMMAND
        ${CMAKE_COMMAND} -E echo "Building Valgrind" &&
        ${CMAKE_MAKE_PROGRAM}
    INSTALL_COMMAND
        ${CMAKE_COMMAND} -E echo "Installing Valgrind" &&
        ${CMAKE_MAKE_PROGRAM} -n install &&
        ${CMAKE_MAKE_PROGRAM} install
    # BUILD_ALWAYS 1
)
