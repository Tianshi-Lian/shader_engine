target_sources(${LIB_NAME} PRIVATE
    engine.cpp
    core/exception_handler.cpp
    core/settings.cpp
    core/singleton.cpp
    debug/logger.cpp
    filesystem/file_handler.cpp
    filesystem/text_file_writer.cpp
    thread/block_process.cpp
    thread/block_thread.cpp
)
