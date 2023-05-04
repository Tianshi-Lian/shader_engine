#include "engine/engine.hpp"

#include "engine/debug/logger.hpp"
#include "engine/thread/block_process.hpp"

i32
main()
{
    try {
        std::string game_name{ "Shader Engine" };

        vmk::Block_Process blocker(game_name);
        if (blocker.is_blocked()) {
            std::cout << "Error: " << game_name << " is already running..." << std::endl;
            vmk::press_any_key_to_quit();
            return Return_Code::RC_OK;
        }

        vmk::Logger logger("logs/log.dat");
        logger.log(vmk::Logger::Log_Level::L_INFO, game_name);
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
