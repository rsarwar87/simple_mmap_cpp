#ifndef SPI_H
#define SPI_H

#include "memory_manager.hpp"

class spi_device {
 public:
  bool m_short_address;
  uint8_t m_header;
  uint8_t m_shift;

  spi_device(int c_select, int c_pha, int c_pol, MemoryManager *mm)
      : spi(mm->get<mem::spi>()) {
    m_cpha = c_pha & 0xF;
    m_cpol = c_pol & 0xF;
    m_chip_select = c_select & 0xF;
    m_short_address = 0;
    m_header = 0;
    if (m_header != 0x0)
      m_shift = 1;
    else
      m_shift = 0;
  }

  int read(uint16_t addr, uint8_t *data, bool debug = false) {
    prepare_buffer(addr, data, 1, debug);
  }

  int write(uint16_t addr, uint8_t *data, bool debug = false) {
    prepare_buffer(addr, data, 0, debug);
  }

 private:
  int issue_cmd(uint8_t *buffer, int n_bytes = 4) {
    while ((spi.read<reg::spi::SPI_STATUS>() & 0x1) != 0x1)
      spi.read<reg::spi::RX_FIFO>();

    spi.write<reg::spi::CHIP_SELECT>(m_chip_select);
    spi.write<reg::spi::SPI_CTRL>(0x086 | (m_cpol << 3) | (m_cpha << 4));

    for (int i = 0; i < n_bytes; i++) {
      buffer[i] = spi.read<reg::spi::TX_FIFO>();

      while ((spi.read<reg::spi::SPI_STATUS>() & 0x1) == 0x1)
        ;
      buffer[i] = spi.read<reg::spi::RX_FIFO>() & 0xff;
    }

    spi.write<reg::spi::CHIP_SELECT>(0xFF);
    spi.write<reg::spi::SPI_CTRL>(0x186 | (m_cpol << 3) | (m_cpha << 4));
  }

  void prepare_buffer(uint16_t addr, uint8_t *data, bool read = 0,
                      bool print = false) {
    uint8_t buf[4];
    buf[0] = m_header;
    buf[3] = 0;
    buf[0 + m_shift] = (read << 7) | (addr >> 8);
    buf[1 + m_shift] = (addr && 0xFF);
    buf[2 + m_shift] = (*data);
    issue_cmd(buf);
    *data = buf[2 + m_shift];
  }

  Memory<mem::spi> &spi;

  uint8_t m_chip_select;
  uint32_t m_cpha;
  uint32_t m_cpol;
};

#endif
