/*
 * TDC7200.h
 */

#ifndef TDC7200_H_
#define TDC7200_H_

typedef union TDC_u
    {
     float LSB;
     float tof_1; 
     float freq;
    }TDC_u;
    
typedef struct TDCvar_t
{
  uint32_t timed;
  uint32_t cald;  
  TDC_u val;
  
} TDCvar_t;

// TDC7200 ToF
const uint8_t TDC_READ = 0b10111111;
const uint8_t TDC_WRITE = 0b01000000; // 0x40

// TDC7200 Registers Time of Flight
#define TDC7200_SPI_REG_ADDR_MASK (0x1Fu)
#define TDC7200_SPI_REG_READ (0x00u)
#define TDC7200_SPI_REG_WRITE (0x40u)
#define TDC7200_SPI_REG_AUTOINC (0x80u)

#define TDC_CONFIG1_MODE2 (0x01u) << 1
#define TDC_CONFIG1_FORCECAL (0x01u) << 7
#define TDC_CONFIG1_STARTMEAS (0x01u)
#define TDC_CONFIG1_STOPFALLINGE (0x01u) << 4
#define TDC_CONFIG1_STARTFALLINGE (0x01u) << 3

#define TDC_CONFIG2_CAL2PER_2CLK (0x00u) << 6
#define TDC_CONFIG2_CAL2PER_10CLK (0x01u) << 6
#define TDC_CONFIG2_CAL2PER_20CLK (0x10u) << 6
#define TDC_CONFIG2_CAL2PER_40CLK (0x11u) << 6
#define TDC_CONFIG2_NUMSTOP_1 0x000u
#define TDC_CONFIG2_NUMSTOP_2 0x001u
#define TDC_CONFIG2_NUMSTOP_3 0x010u
#define TDC_CONFIG2_NUMSTOP_4 0x011u

#define TDC7200_REG_ADR_CONFIG1 (0x00u)
#define TDC7200_REG_ADR_CONFIG2 (0x01u)
#define TDC7200_REG_ADR_INT_STATUS (0x02u)
#define TDC7200_REG_ADR_INT_MASK (0x03u)
#define TDC7200_REG_ADR_COARSE_CNTR_OVF_H (0x04u)
#define TDC7200_REG_ADR_COARSE_CNTR_OVF_L (0x05u)
#define TDC7200_REG_ADR_CLOCK_CNTR_OVF_H (0x06u)
#define TDC7200_REG_ADR_CLOCK_CNTR_OVF_L (0x07u)
#define TDC7200_REG_ADR_CLOCK_CNTR_STOP_MASK_H (0x08u)
#define TDC7200_REG_ADR_CLOCK_CNTR_STOP_MASK_L (0x09u)
#define TDC7200_REG_ADR_TIME1 (0x10u)
#define TDC7200_REG_ADR_CLOCK_COUNT1 (0x11u)
#define TDC7200_REG_ADR_TIME2 (0x12u) // Measured Time 2
#define TDC7200_REG_ADR_CLOCK_COUNT2 (0x13u)
#define TDC7200_REG_ADR_TIME3 (0x14u)
#define TDC7200_REG_ADR_CLOCK_COUNT3 (0x15u)
#define TDC7200_REG_ADR_TIME4 (0x16u)
#define TDC7200_REG_ADR_CLOCK_COUNT4 (0x17u)
#define TDC7200_REG_ADR_TIME5 (0x18u)
#define TDC7200_REG_ADR_CLOCK_COUNT5 (0x19u)
#define TDC7200_REG_ADR_CLOCK_COUNTX(num) (TDC7200_REG_ADR_CLOCK_COUNT1 + 2 * ((num)-1))
#define TDC7200_REG_ADR_TIME6 (0x1Au)
#define TDC7200_REG_ADR_TIMEX(num) (TDC7200_REG_ADR_TIME1 + 2 * ((num)-1))
#define TDC7200_REG_ADR_CALIBRATION1 (0x1Bu)
#define TDC7200_REG_ADR_CALIBRATION2 (0x1Cu)

void SPI_WriteTDC(uint8_t address, uint8_t value);
uint32_t SPI_ReadTDC(uint8_t address); // read 24bit from TDC
uint8_t SPI_ReadSingleTDC(uint8_t address);

#endif /* TDC7200 */
