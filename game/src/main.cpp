#include "engine/engine.hpp"

i32
main()
{
    try {
        std::cout << "Shader Engine" << std::endl;
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
