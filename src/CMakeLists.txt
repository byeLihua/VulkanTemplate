target_sources(VulkanApplication
    PRIVATE
        main.cpp
        application.cpp
        vk_manager.cpp
)

add_subdirectory(platform)
