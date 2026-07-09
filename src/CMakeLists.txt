target_sources(VulkanApplication
    PRIVATE
        main.cpp
        vulkan_application.cpp
        window.cpp
)

add_subdirectory(platform)
