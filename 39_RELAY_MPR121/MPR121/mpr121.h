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

#define   ELE_L            0x00
#define   ELE_H            0x01
#define   OOR_STATU        0x02
#define   ELEPROX          0x03
#define   ELE0_L           0x04
#define   ELE0_H           0x05
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
#define   E0BV             0x1E
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
#define   MHD_R            0x2B
#define   NHD_R            0x2C
#define   NCL_R            0x2D
#define   FDL_R            0x2E
#define   MHD_F            0x2F
#define   NHD_F            0x30
#define   NCL_F            0x31
#define   FDL_F            0x32
#define   NHD_T            0x33
#define   NCL_T            0x34
#define   FDL_T            0x35
#define   MHDPROXR         0x36
#define   NHDPROXR         0x37
#define   NCLPROXR         0x38
#define   FDLPROXR         0x39
#define   MHDPROXF         0x3A
#define   NHDPROXF         0x3B
#define   NCLPROXF         0x3C
#define   FDLPROXF         0x3D
#define   NHDPROXT         0x3E
#define   NCLPROXT         0x3F
#define   FDLPROXT         0x40
#define   ELE0_T           0x41
#define   ELE0_R           0x42
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
#define   DEBOUNCE         0x5B
#define   FIL_CFG1         0x5C
#define   FIL_CFG2         0x5D
#define   ELE_CFG          0x5E
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
#define   CDT0_1           0x6C
#define   CDT2_3           0x6D
#define   CDT4_5           0x6E
#define   CDT6_7           0x6F
#define   CDT8_9           0x70
#define   CDT10_11         0x71
#define   CDTPROX          0x72
#define   GPIO_CTRL0       0x73
#define   GPIO_CTRL1       0x74
#define   GPIO_DATA        0x75
#define   GPIO_DIR         0x76
#define   GPIO_EN          0x77
#define   GPIO_SET         0x78
#define   GPIO_CLEAR       0x79
#define   GPIO_TOGGLE      0x7A
#define   AUTO_CFG0        0x7B
#define   AUTO_CFG_CTRL    0x7C
#define   AUTO_CFGU        0x7D
#define   AUTO_CFGL        0x7E
#define   AUTO_CFGT        0x7F
#define   SRST             0x80
#define   TOU_THRESH       0x0F
#define   REL_THRESH       0x09


void MPR121_init(void);
unsigned char MPR121_read(unsigned char address);
void MPR121_write(unsigned char address, unsigned char value);

#endif /* MPR121_MPR121_H_ */
