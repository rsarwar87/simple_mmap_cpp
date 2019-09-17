/// Common commands for all bitstreams
///
/// (c) Koheron

#include <array>
#include <cstring>
#include "qspi.hpp"

//#include "memory_manager.hpp"
int main() {
  // ctl.write<reg::led>(value);

  // cout << ctl.read<reg::led>();
  MemoryManager mm;
  mm.open();

  Memory<mem::gpio> gpio(mm.get<mem::gpio>());
  gpio.write<reg::gpio::DATA0>(0xF);

  spi_device spi(0, 0, 0, &mm);
  uint8_t data = 0x0;
  spi.read(0x0, &data);
};

