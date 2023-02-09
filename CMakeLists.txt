cmake_minimum_required(VERSION 3.20)

project(CppCalf VERSION 0.1)
set(LIB_NAME cppcalf)
set(PROJECT_TARGETS ${PROJECT_NAME}Targets)

# 创建 header-only 的接口库
add_library(${LIB_NAME} INTERFACE)

# 指定库包含目录，并为构建和安装分别指定不同的目录
target_include_directories(${LIB_NAME} INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${PROJECT_NAME}/include>
)

# 生成 cmake 配置
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${PROJECT_NAME}/cmake
)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

# 安装配置
install(TARGETS ${LIB_NAME}
    EXPORT ${PROJECT_TARGETS}
    LIBRARY DESTINATION lib  # 动态库安装路径
    ARCHIVE DESTINATION lib  # 静态库安装路径
    RUNTIME DESTINATION bin  # 可执行文件安装路径
    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)
install(EXPORT ${PROJECT_TARGETS}
    FILE ${PROJECT_TARGETS}.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${PROJECT_NAME}/cmake
)
install(FILES 
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    DESTINATION ${PROJECT_NAME}/cmake
)
install(DIRECTORY
    "${PROJECT_SOURCE_DIR}/include/calf" 
    DESTINATION ${PROJECT_NAME}/include
)
