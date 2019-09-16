/// Common commands for all bitstreams
///
/// (c) Koheron


#include <cstring>
#include <array>

extern "C" {
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
  #include <ifaddrs.h>
}

#include "memory_manager.hpp"
int main ()
{
        //ctl.write<reg::led>(value);

        //cout << ctl.read<reg::led>();
    MemoryManager mm; 
    mm.open();

    Memory<mem::spi> spi (mm.get<mem::spi>());
    Memory<mem::gpio>gpio (mm.get<mem::gpio>());
    int value = 989;
    gpio.write<reg::gpio::DATA0>(value);
};

