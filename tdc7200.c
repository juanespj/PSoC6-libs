/*
 * ws2812.c
 */

#include "cyhal.h"
#include "tdc7200.h"

// Write 16 bit reg
void SPI_WriteTDC(uint8_t address, uint8_t value)
{
  CY_SYS_PINS_CLEAR_PIN(TDC_CS__DR, TDC_CS_SHIFT);
  SPI_SpiUartWriteTxData(((address & TDC7200_SPI_REG_ADDR_MASK) | TDC7200_SPI_REG_WRITE | TDC7200_SPI_REG_AUTOINC));
  SPI_SpiUartWriteTxData(value);
  CyDelayUs(3); // wait to read //10prev
  CY_SYS_PINS_SET_PIN(TDC_CS__DR, TDC_CS_SHIFT);
}

uint32_t SPI_ReadTDC(uint8_t address) // 24 bit read
{
  uint32_t fulldata;
  CY_SYS_PINS_CLEAR_PIN(TDC_CS__DR, TDC_CS_SHIFT);
  address = ((address & TDC7200_SPI_REG_ADDR_MASK) | TDC7200_SPI_REG_READ | TDC7200_SPI_REG_AUTOINC);
  SPI_SpiUartWriteTxData(address);
  SPI_SpiUartClearRxBuffer(); // dont move
  SPI_SpiUartWriteTxData(0x00);
  SPI_SpiUartWriteTxData(0x00);
  SPI_SpiUartWriteTxData(0x00);

  CyDelayUs(5);
  CY_SYS_PINS_SET_PIN(TDC_CS__DR, TDC_CS_SHIFT);
  fulldata = SPI_SpiUartReadRxData() << 16 | (SPI_SpiUartReadRxData() << 8) | (SPI_SpiUartReadRxData());

  return fulldata;
}

uint8_t SPI_ReadSingleTDC(uint8_t address) // 24 bit read
{
  uint8_t fulldata = 0;
  // CY_SYS_PINS_CLEAR_PIN(TDC_CS__DR, TDC_CS_SHIFT);
  TDC_CS_Write(0u);
  SPI_SpiUartClearTxBuffer();
  address = (address & TDC7200_SPI_REG_ADDR_MASK) | TDC7200_SPI_REG_READ;
  SPI_SpiUartWriteTxData(address);

  // fulldata = fulldata<<8 |SPI_SpiUartReadRxData();
  SPI_SpiUartClearRxBuffer();
  SPI_SpiUartWriteTxData(0x00);
  CyDelayUs(4);
  fulldata = SPI_SpiUartReadRxData();
  // CY_SYS_PINS_SET_PIN(TDC_CS__DR, TDC_CS_SHIFT);
  TDC_CS_Write(1u);
  return fulldata;
}

