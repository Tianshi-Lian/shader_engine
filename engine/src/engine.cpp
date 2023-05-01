#include "engine.hpp"

namespace vmk {

void
press_any_key_to_quit()
{
    std::cout << "Press any key to quit...";
    _getch();
}

}
