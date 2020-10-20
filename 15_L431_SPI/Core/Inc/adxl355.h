#ifndef ADXL355_H_
#define ADXL355_H_
#include "main.h"
#include "spi.h"
#include "math.h"

/********************************* Definitions ********************************/
#define PI 3.145926

/* ADXL355 registers addresses */
#define DEVID_AD                 0x00
#define DEVID_MST                0x01
#define PARTID                   0x02
#define REVID                    0x03
#define STATUS                   0x04
#define FIFO_ENTRIES             0x05
#define TEMP2                    0x06
#define TEMP1                    0x07
#define XDATA3                   0x08
#define XDATA2                   0x09
#define XDATA1                   0x0A
#define YDATA3                   0x0B
#define YDATA2                   0x0C
#define YDATA1                   0x0D
#define ZDATA3                   0x0E
#define ZDATA2                   0x0F
#define ZDATA1                   0x10
#define FIFO_DATA                0x11
#define OFFSET_X_H               0x1E
#define OFFSET_X_L               0x1F
#define OFFSET_Y_H               0x20
#define OFFSET_Y_L               0x21
#define OFFSET_Z_H               0x22
#define OFFSET_Z_L               0x23
#define ACT_EN                   0x24
#define ACT_THRESH_H             0x25
#define ACT_THRESH_L             0x26
#define ACT_COUNT                0x27
#define FILTER                   0x28
#define FIFO_SAMPLES             0x29
#define INT_MAP                  0x2A
#define SYNC                     0x2B
#define RANGE                    0x2C
#define POWER_CTL                0x2D
#define SELF_TEST                0x2E
#define ADX_RESET                0x2F

/**************************** Configuration parameters **********************/

#define RST_CMD                 0x52

/* Temperature parameters */
#define ADXL355_TEMP_BIAS       (float)1852.0      /* Accelerometer temperature bias(in ADC codes) at 25 Deg C */
#define ADXL355_TEMP_SLOPE      (float)-9.05       /* Accelerometer temperature change from datasheet (LSB/degC) */

#define ADXL355_TEMP_XCOMP      (double)0.00004235
#define ADXL355_TEMP_YCOMP      (double)0.00004235
#define ADXL355_TEMP_ZCOMP      (double)0.00001765
#define ADXL355_TEMP_B          (double)0.001

/* Accelerometer parameters */
#define ADXL_RANGE         2     /* ADXL362 sensitivity: 2, 4, 8 [g] */

#define ACT_VALUE          50     /* Activity threshold value */

#define INACT_VALUE        50     /* Inactivity threshold value */

#define ACT_TIMER          100    /* Activity timer value in ms */

#define INACT_TIMER        10     /* Inactivity timer value in seconds */

#define SCALE_2G           256000.0

#define SCALE_4G           128000.0;

#define SCALE_8G           64000.0;

/****************************** Global Data ***********************************/

extern volatile int32_t i32SensorX;
extern volatile int32_t i32SensorY;
extern volatile int32_t i32SensorZ;

extern volatile uint32_t ui32SensorX;
extern volatile uint32_t ui32SensorY;
extern volatile uint32_t ui32SensorZ;
extern volatile uint32_t ui32SensorT;

extern volatile double  angleX;
extern volatile double  angleY;
extern volatile double  angleZ;

extern volatile double compensatedX;
extern volatile double compensatedY;
extern volatile double compensatedZ;

//extern volatile uint32_t ui32timer_counter;


/*************************** Internal types ***********************************/


/* Write data mode */
typedef enum {
   SPI_WRITE_ONE_REG = 1,         /* Write 1 ACC register */
   SPI_WRITE_TWO_REG,             /* Write 2 ACC register */
} enWriteData;

typedef enum {
   SPI_READ_ONE_REG = 1,            /* Read one ACC register */
   SPI_READ_TWO_REG,                /* Read two ACC registers */
   SPI_READ_THREE_REG,              /* Read X,Y,Z ACC registers */
} enRegsNum;


/**************************** Internal definitions *****************************/

/* Accelerometer write command */
#define ADXL355_WRITE         0x0

/* Accelerometer read command */
#define ADXL355_READ          0x1

/*************************** Functions prototypes *****************************/

void ADXL355_Init(void);
uint32_t ADXL355_SPI_Read(uint8_t ui8address, enRegsNum enRegs);
void ADXL355_SPI_Write(uint8_t ui8address, uint8_t ui8Data, uint8_t ui8Data2, enWriteData enMode);
void ADXL355_Start_Sensor(void);
void ADXL355_Stop_Sensor(void);
void ADXL355_Set_Range (uint8_t range);
uint32_t ADXL355_Read_Range (void);
void ADXL355_Data_Scan(void);
int32_t ADXL355_Acceleration_Data_Conversion (uint32_t ui32SensorData);
void ADXL355_Self_Test(void);
void ADXL355_Convert_Angle(int32_t i32SensorX, int32_t i32SensorY, int32_t i32SensorZ);
void ADXL355_Temp_Compensation(int32_t i32SensorX, int32_t i32SensorY, int32_t i32SensorZ);
#endif /* ADXL355_H_ */

