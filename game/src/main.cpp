
#include "engine/core/settings.hpp"
#include "engine/core/utils.hpp"
#include "engine/debug/logger.hpp"
#include "engine/thread/block_process.hpp"

#include "core/build_config.hpp"

i32
main()
{
    try {
        vmk::Block_Process blocker(vmk::g_game_name);
        if (blocker.is_blocked()) {
            throw vmk::Exception_Handler(std::string("Error: ") + vmk::g_game_name + " is already running...");
        }

        std::ostringstream game_info;
        game_info << vmk::g_game_name << " | Version " << vmk::g_major_version << "." << vmk::g_minor_version << "."
                  << vmk::g_patch_version;

        vmk::Logger logger("log.dat");
        logger.log(vmk::Logger::Log_Level::L_INFO, "Starting " + game_info.str());

        vmk::Settings settings;
        logger.log(vmk::Logger::Log_Level::L_INFO, settings.show_summary());

        // Test code
        {
            std::string out{ "value" };

            out = vmk::Utils::to_upper(out);
            logger.log(vmk::Logger::Log_Level::L_INFO, out);

            out = vmk::Utils::to_lower(out);
            logger.log(vmk::Logger::Log_Level::L_INFO, out);

            out = "42";
            u32 u_out = vmk::Utils::to_u32(out);
            std::cout << u_out << std::endl;
        }
    }
    catch (vmk::Exception_Handler& exception) {
        std::cout << "Exception thrown: " << exception.get_message() << std::endl;
        vmk::Utils::press_any_key_to_quit();
        return Return_Code::RC_ERROR;
    }
    catch (...) {
        std::cout << __FUNCTION__ << " caught unknown exception" << std::endl; // NOLINT
        vmk::Utils::press_any_key_to_quit();
        return Return_Code::RC_ERROR;
    }

    vmk::Utils::press_any_key_to_quit();
    return Return_Code::RC_OK;
}
