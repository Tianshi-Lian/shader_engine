#include "engine/engine.hpp"

#include "engine/core/settings.hpp"
#include "engine/debug/logger.hpp"
#include "engine/thread/block_process.hpp"

#include "core/build_config.hpp"

i32
main()
{
    try {
        vmk::Block_Process blocker(vmk::g_game_name);
        if (blocker.is_blocked()) {
            std::cout << "Error: " << vmk::g_game_name << " is already running..." << std::endl;
            vmk::press_any_key_to_quit();
            return Return_Code::RC_OK;
        }

        std::ostringstream game_info;
        game_info << vmk::g_game_name << " | Version " << vmk::g_major_version << "." << vmk::g_minor_version << "."
                  << vmk::g_patch_version;

        vmk::Logger logger("log.dat");
        logger.log(vmk::Logger::Log_Level::L_INFO, "Starting " + game_info.str());

        vmk::Settings settings;
        logger.log(vmk::Logger::Log_Level::L_INFO, settings.show_summary());
    }
    catch (vmk::Exception_Handler& exception) {
        std::cout << "Exception thrown: " << exception.get_message() << std::endl;
        vmk::press_any_key_to_quit();
        return Return_Code::RC_ERROR;
    }
    catch (...) {
        std::cout << __FUNCTION__ << " caught unknown exception" << std::endl; // NOLINT
        vmk::press_any_key_to_quit();
        return Return_Code::RC_ERROR;
    }

    vmk::press_any_key_to_quit();
    return Return_Code::RC_OK;
}
