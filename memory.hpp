#ifndef __DRIVERS_MEMORY_HPP__
#define __DRIVERS_MEMORY_HPP__

#include <array>
#include <tuple>
#include <cstdint>

extern "C" {
  #include <sys/mman.h> // PROT_READ, PROT_WRITE
}

namespace mem {
constexpr size_t spi = 0;
constexpr uintptr_t spi_addr = 0x41E00000;
constexpr uint32_t spi_range = 4*1024;
constexpr uint32_t spi_nblocks = 1;
constexpr size_t gpio = 1;
constexpr uintptr_t gpio_addr = 0x50001000;
constexpr uint32_t gpio_range = 4*1024;
constexpr uint32_t gpio_nblocks = 1;
constexpr size_t xadc = 2;
constexpr uintptr_t xadc_addr = 0x43C00000;
constexpr uint32_t xadc_range = 64*1024;
constexpr uint32_t xadc_nblocks = 1;
constexpr size_t adc = 3;
constexpr uintptr_t adc_addr = 0x40000000;
constexpr uint32_t adc_range = 64*1024;
constexpr uint32_t adc_nblocks = 1;
constexpr size_t dac = 4;
constexpr uintptr_t dac_addr = 0x40040000;
constexpr uint32_t dac_range = 64*1024;
constexpr uint32_t dac_nblocks = 1;


constexpr size_t count = 5;

constexpr std::array<std::tuple<uintptr_t, uint32_t, uint32_t, uint32_t>, count> memory_array = {{
    std::make_tuple(spi_addr, spi_range, PROT_READ|PROT_WRITE, spi_nblocks),
        std::make_tuple(gpio_addr, gpio_range, PROT_READ|PROT_WRITE, gpio_nblocks),
        std::make_tuple(xadc_addr, xadc_range, PROT_READ|PROT_WRITE, xadc_nblocks),
        std::make_tuple(adc_addr, adc_range, PROT_READ|PROT_WRITE, adc_nblocks),
        std::make_tuple(dac_addr, dac_range, PROT_READ|PROT_WRITE, dac_nblocks)
        }};

} // namespace mem

namespace reg {
// -- Control offsets
/*constexpr uint32_t led = 0;
static_assert(led < mem::control_range, "Invalid control register offset led");
constexpr uint32_t trig = 4;
static_assert(trig < mem::control_range, "Invalid control register offset trig");

// -- Status offsets
constexpr uint32_t reg1 = 0;
static_assert(reg1 < mem::status_range, "Invalid status register offset reg1");
*/
namespace spi{
constexpr uint32_t SRR = 0x40;
constexpr uint32_t SPI_CTRL = 0x60;
constexpr uint32_t SPI_STATUS = 0x64;
constexpr uint32_t TX_FIFO = 0x68;
constexpr uint32_t RX_FIFO = 0x6C;
constexpr uint32_t CHIP_SELCT = 0x70;
}

namespace gpio{
constexpr uint32_t DATA0 = 0x0;
constexpr uint32_t TSTATE0 = 0x4;
constexpr uint32_t DATA1 = 0x8;
constexpr uint32_t TSTATE1 = 0xC;
}
} // namespace reg


#endif // __DRIVERS_MEMORY_HPP__
