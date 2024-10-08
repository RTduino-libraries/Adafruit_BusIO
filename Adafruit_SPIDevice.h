/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: MIT
 *
 * https://github.com/RTduino/RTduino
 * https://gitee.com/rtduino/RTduino
 *
 * Change Logs:
 * Date           Author       Notes
 *            Adafruit Team    First version
 * 2022-02-19     Meco Man     port to RTduino
 */

#ifndef Adafruit_SPIDevice_h
#define Adafruit_SPIDevice_h

#include <Arduino.h>

#ifdef RTDUINO_USING_SPI

#include <SPI.h>

typedef enum _BitOrder {
  SPI_BITORDER_MSBFIRST = MSBFIRST,
  SPI_BITORDER_LSBFIRST = LSBFIRST,
} BusIOBitOrder;

/**! The class which defines how we will talk to this device over SPI **/
class Adafruit_SPIDevice {
public:
  Adafruit_SPIDevice(int8_t cspin, uint32_t freq = 1000000,
                     BusIOBitOrder dataOrder = SPI_BITORDER_MSBFIRST,
                     uint8_t dataMode = SPI_MODE0, SPIClass *theSPI = &SPI);

  Adafruit_SPIDevice(int8_t cspin, int8_t sck, int8_t miso, int8_t mosi,
                     uint32_t freq = 1000000,
                     BusIOBitOrder dataOrder = SPI_BITORDER_MSBFIRST,
                     uint8_t dataMode = SPI_MODE0);
  ~Adafruit_SPIDevice();

  bool begin(void);
  bool read(uint8_t *buffer, size_t len, uint8_t sendvalue = 0xFF);
  bool write(const uint8_t *buffer, size_t len,
             const uint8_t *prefix_buffer = NULL, size_t prefix_len = 0);
  bool write_then_read(const uint8_t *write_buffer, size_t write_len,
                       uint8_t *read_buffer, size_t read_len,
                       uint8_t sendvalue = 0xFF);
  bool write_and_read(uint8_t *buffer, size_t len);

  uint8_t transfer(uint8_t send);
  void transfer(uint8_t *buffer, size_t len);
  void beginTransaction(void);
  void endTransaction(void);
  void beginTransactionWithAssertingCS();
  void endTransactionWithDeassertingCS();

private:
  SPIClass *_spi;
  SPISettings *_spiSetting;
  uint32_t _freq;
  BusIOBitOrder _dataOrder;
  uint8_t _dataMode;
  void setChipSelect(int value);
  int8_t _cs, _sck, _mosi, _miso;
};

#endif /* RTDUINO_USING_SPI */
#endif // Adafruit_SPIDevice_h
