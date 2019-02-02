/*
 * mpr121.h
 *
 *  Created on: 18 kwi 2017
 *      Author: Daniel
 */

#ifndef MPR121_MPR121_H_
#define MPR121_MPR121_H_

#define   MPR121addr       0x5A

#define   Write_MPR121_addr     0xB4
#define   Read_MPR121_addr      0xB5

//Touch Status Registers (0x00-0x01)
#define   ELE_L            0x00		//Touch Status low byte
#define   ELE_H            0x01		//Touch Status high byte
//Out Of Range Status
#define   OOR_STATU        0x02
#define   ELEPROX          0x03
//Electrode Filtered Data Register (0x04-0x1D)
#define   ELE0_L           0x04		//Electrode Filered Data Register low byte (10-bit filtered data form 2nd stage filter)
#define   ELE0_H           0x05		//Electrode Filered Data Register high byte
#define   ELE1_L           0x06
#define   ELE1_H           0x07
#define   ELE2_L           0x08
#define   ELE2_H           0x09
#define   ELE3_L           0x0A
#define   ELE3_H           0x0B
#define   ELE4_L           0x0C
#define   ELE4_H           0x0D
#define   ELE5_L           0x0E
#define   ELE5_H           0x0F
#define   ELE6_L           0x10
#define   ELE6_H           0x11
#define   ELE7_L           0x12
#define   ELE7_H           0x13
#define   ELE8_L           0x14
#define   ELE8_H           0x15
#define   ELE9_L           0x16
#define   ELE9_H           0x17
#define   ELE10_L          0x18
#define   ELE10_H          0x19
#define   ELE11_L          0x1A
#define   ELE11_H          0x1B
#define   EFDPROX_L        0x1C
#define   EFDPROX_H        0x1D
//Baseline Value Register (0x1E-0x2A)
#define   E0BV             0x1E		//ELE0 Baseline Value (10-bit value; touch/release detection is made based on comparison ExBV and ELEx)
#define   E1BV             0x1F
#define   E2BV             0x20
#define   E3BV             0x21
#define   E4BV             0x22
#define   E5BV             0x23
#define   E6BV             0x24
#define   E7BV             0x25
#define   E8BV             0x26
#define   E9BV             0x27
#define   E10BV            0x28
#define   E11BV            0x29
#define   EPROXBV          0x2A
// BFC - Baseline Control Register (0x2B-0x2A) (R - Rising, F - Falling, T - Touched)
#define   MHD_R            0x2B		//Maximum Half Delta - determines the largest magnitude of variation to pass through the baseline filter (1-63)
#define   NHD_R            0x2C		//Noise Half Delta - determines the incremental change when non-noise drift is detected (1-63)
#define   NCL_R            0x2D		//Noise Count Limit - determines the number of samples consecutively greater than the MHD. Necessary to determine that it is not noise (0-255)
#define   FDL_R            0x2E		//Filter Delay Count Limit - determines the operation rate of the filter. A larger count limit means the filter delay is operating more slowly (0-255)
#define   MHD_F            0x2F
#define   NHD_F            0x30
#define   NCL_F            0x31
#define   FDL_F            0x32
#define   NHD_T            0x33
#define   NCL_T            0x34
#define   FDL_T            0x35
#define   MHD_PROX_R       0x36
#define   NHD_PROX_R       0x37
#define   NCL_PROX_R       0x38
#define   FDL_PROX_R       0x39
#define   MHD_PROX_F       0x3A
#define   NHD_PROX_F       0x3B
#define   NCL_PROX_F       0x3C
#define   FDL_PROX_F       0x3D
#define   NHD_PROX_T       0x3E
#define   NCL_PROX_T       0x3F
#define   FDL_PROX_T       0x40
// Touch/Release Threshold (0x41-0x5A)
// Touch condition: Baseline - Electrode filtered data > Touch threshold
// Release condition: Baseline - Electrode filtered data < Release threshold
#define   ELE0_T           0x41		//Electrode touch threshold (0-0xff)
#define   ELE0_R           0x42		//Electrode release threshold (0-0xff)
#define   ELE1_T           0x43
#define   ELE1_R           0x44
#define   ELE2_T           0x45
#define   ELE2_R           0x46
#define   ELE3_T           0x47
#define   ELE3_R           0x48
#define   ELE4_T           0x49
#define   ELE4_R           0x4A
#define   ELE5_T           0x4B
#define   ELE5_R           0x4C
#define   ELE6_T           0x4D
#define   ELE6_R           0x4E
#define   ELE7_T           0x4F
#define   ELE7_R           0x50
#define   ELE8_T           0x51
#define   ELE8_R           0x52
#define   ELE9_T           0x53
#define   ELE9_R           0x54
#define   ELE10_T          0x55
#define   ELE10_R          0x56
#define   ELE11_T          0x57
#define   ELE11_R          0x58
#define   EPROXTTH         0x59
#define   EPROXRTH         0x5A
//Debounce Register (0x5B)
#define   DEBOUNCE         0x5B
//Filter and Global CDC CDT Configuration (0x5C, 0x5D)
//FFI - First Filter Iterations
//CDC - Charge Discharge Current
//CDT - Charge Discharge Time
//SFI - Second Filter Iterations
//ESI - Electrode Filter Iterations
#define   FIL_CFG1         0x5C
#define   FIL_CFG2         0x5D
//Electrode Configuration (0x5E)
//CL - Calibration Lock
//ELEPROX_EN - Proximity Enable
//ELE_EN - Electrode Enable
#define   ELE_CFG          0x5E
//Electrode Charge Current Register (0x5F-0x6B) - sets charge current applied to each channel from range 0-63uA (0x00-0x3F)
#define   CDC0             0x5F
#define   CDC1             0x60
#define   CDC2             0x61
#define   CDC3             0x62
#define   CDC4             0x63
#define   CDC5             0x64
#define   CDC6             0x65
#define   CDC7             0x66
#define   CDC8             0x67
#define   CDC9             0x68
#define   CDC10            0x69
#define   CDC11            0x6A
#define   CDCPROX          0x6B
//Electrode Charge Time Register (0x6C-0x72) - Sets the charge time applied to each channel, from range 0-32us (0b000-0b111)
#define   CDT0_1           0x6C
#define   CDT2_3           0x6D
#define   CDT4_5           0x6E
#define   CDT6_7           0x6F
#define   CDT8_9           0x70
#define   CDT10_11         0x71
#define   CDTPROX          0x72
//
#define   GPIO_CTRL0       0x73
#define   GPIO_CTRL1       0x74
#define   GPIO_DATA        0x75
#define   GPIO_DIR         0x76
#define   GPIO_EN          0x77
#define   GPIO_SET         0x78
#define   GPIO_CLEAR       0x79
#define   GPIO_TOGGLE      0x7A
//Auto-Configuration Registers (0x7B-0x7F)
#define   AUTO_CFG0        0x7B		//FFI, ACE, ARE, BVA, RETRY
#define   AUTO_CFG_CTRL    0x7C		//SCTS, ACFIE, ARFIE, OORIE
#define   AUTO_CFGU        0x7D		//Up-Side Limit Register
#define   AUTO_CFGL        0x7E		//Low-Side Limit Register
#define   AUTO_CFGT        0x7F		//Target Level Register
//Soft Reset Register (0x80)
#define   SOFT_RST         0x80		//Write 0x63 to reset

//The same touch/release thresholds for every pin
#define   TOU_THRESH       0x5F
#define   REL_THRESH       0x09

void MPR121_init(void);
unsigned char MPR121_read(unsigned char address);
void MPR121_write(unsigned char address, unsigned char value);

#endif /* MPR121_MPR121_H_ */
