cmake_minimum_required(VERSION 4.4.0)

project(VulkanTemplate)

find_package(Vulkan REQUIRED)

add_executable(VulkanApplication)

target_include_directories(VulkanApplication
    PUBLIC
        ${Vulkan_INCLUDE_DIR}
        include
)

target_link_libraries(VulkanApplication
    PUBLIC
        Vulkan::Vulkan
)

set_target_properties(VulkanApplication
    PROPERTIES
        CXX_STANDARD 20
)

add_subdirectory(src)
