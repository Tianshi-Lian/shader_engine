
#include "engine/core/settings.hpp"
#include "engine/core/utils.hpp"
#include "engine/debug/logger.hpp"
#include "engine/thread/block_process.hpp"

#include "core/build_config.hpp"

i32
main(i32 argc, char* argv[])
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
        // Debug settings
        {
            settings.set_windowed_mode(true);
            settings.set_rng_seed(1337);
            settings.set_stat_logging(true);
        }

        // Handle cmd line args
        {
            bool parse_error = false;
            for (i32 i = 1; i < argc; ++i) {
                std::string arg = std::string(argv[i]);
                arg = vmk::Utils::to_lower(arg);

                if (arg == "/?" || arg == "help") {
                    std::ostringstream help_stream;
                    help_stream << vmk::g_game_name << " arguments:\n";
                    help_stream << "    seed <n>   | Supply seed value to initialize random number generator\n";
                    help_stream << "    windowed   | Run the application in windowed mode\n";
                    help_stream << "    stats      | Log game statistics during runtime\n";
                    logger.log(vmk::Logger::Log_Level::L_INFO, help_stream);

                    vmk::Utils::press_any_key_to_quit();
                    return Return_Code::RC_OK;
                }
                else if (arg == "seed") {
                    u32 seed_value = 0;
                    if (i + 1 < argc) {
                        std::string seed_arg = std::string(argv[i + 1]);
                        seed_value = vmk::Utils::to_u32(seed_arg);

                        if (seed_value == 0) {
                            logger.log(vmk::Logger::Log_Level::L_ERROR, "Missing value for seed argument, or 0 specified.");
                            parse_error = true;
                        }
                        else {
                            settings.set_rng_seed(seed_value);
                            ++i;
                        }
                    }
                    else {
                        logger.log(vmk::Logger::Log_Level::L_ERROR, "Missing value for seed argument, or 0 specified.");
                        parse_error = true;
                    }
                }
                else if (arg == "windowed") {
                    settings.set_windowed_mode(true);
                }
                else if (arg == "stats") {
                    settings.set_stat_logging(true);
                }
                else {
                    logger.log(vmk::Logger::Log_Level::L_WARNING, "Unrecognized argument: " + arg);
                }
            }

            if (parse_error) {
                vmk::Utils::press_any_key_to_quit();
                return Return_Code::RC_OK;
            }
        }

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
