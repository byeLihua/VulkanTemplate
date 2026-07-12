target_sources(VulkanApplication
    PRIVATE
        main.cpp
        application.cpp
        vk_manager.cpp
        window.cpp
)

add_subdirectory(platform)
