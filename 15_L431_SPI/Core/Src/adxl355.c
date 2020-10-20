#include "adxl355.h"

#define DEBUG_MODE

int32_t volatile i32SensorX;
int32_t volatile i32SensorY;
int32_t volatile i32SensorZ;
int32_t volatile i32SensorT;
uint32_t volatile ui32SensorX;
uint32_t volatile ui32SensorY;
uint32_t volatile ui32SensorZ;
uint32_t volatile ui32SensorT;

double volatile angleX;
double volatile angleY;
double volatile angleZ;

double volatile compensatedX;
double volatile compensatedY;
double volatile compensatedZ;

uint8_t null_val = 0;

/**
  * @brief  Test whether the ADXL355 is online .
  * @param  None.
  * @retval None.
  */
void ADXL355_Init(void)
{
   uint32_t volatile ui32test = ADXL355_SPI_Read(DEVID_AD, SPI_READ_ONE_REG);                 /* Read the ID register */
   uint32_t volatile ui32test2 = ADXL355_SPI_Read(DEVID_MST, SPI_READ_ONE_REG);               /* Read the ID register */
   uint32_t volatile ui32test3 = ADXL355_SPI_Read(PARTID, SPI_READ_ONE_REG);                  /* Read the ID register */
   uint32_t volatile ui32test4 = ADXL355_SPI_Read(REVID, SPI_READ_ONE_REG);                   /* Read the ID register */

   if ((ui32test == 0xAD) && (ui32test2 == 0x1D) && (ui32test3 == 0xED) && (ui32test4 == 0x01))
   {
#if defined(DEBUG_MODE)
//        printf("\n\rReset and initialized.\n\r");
#endif
        ADXL355_SPI_Write(ADX_RESET, RST_CMD, null_val, SPI_WRITE_ONE_REG);           //reset
   }
   else{
	   //	   printf("Error initializing\n\r");
   }

}

/**
  * @brief  Use SPI to read data from ADXL355 register.
  * @param  ui8address: register address.
  * @retval if read success return data, if not return 0x00.
  */
uint32_t ADXL355_SPI_Read(uint8_t ui8address, enRegsNum enRegs)
{
    HAL_StatusTypeDef status;
    uint32_t returnData;
    uint8_t txData;
    uint8_t rxBuff[3] = {0};
    uint32_t ui32valueL = 0;
    uint32_t ui32valueM __attribute__((unused)) = 0;
    uint32_t ui32valueH = 0;

    txData = (ui8address << 1) | ADXL355_READ;
    if (enRegs == SPI_READ_ONE_REG)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

        status = HAL_SPI_Transmit (&hspi2, &txData, 1, 100);

        status = HAL_SPI_Receive (&hspi2, rxBuff, 1, 100);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        if (status == HAL_OK)
        {
            returnData = rxBuff[0];

            return returnData;
        }
        else
        {
#if defined(DEBUG_MODE)
//            DEBUG_PRINT("\r\nError Reading SPI_READ_ONE_REG: Invalid HAL_STATUS\r\n");
#endif
            return 0x00;
        }
    }

    if (enRegs == SPI_READ_TWO_REG)                             /* Only used for Temp & X,Y,Z offset and threshold registers*/
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

        status = HAL_SPI_Transmit (&hspi2, &txData, 1, 100);

        status = HAL_SPI_Receive (&hspi2, rxBuff, 2, 100);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        if (status == HAL_OK)
        {
            ui32valueH = rxBuff[0];

            ui32valueL = rxBuff[1];

            returnData = (ui32valueH << 8) + ui32valueL;

            return returnData;
        }
        else
        {
#if defined(DEBUG_MODE)
//            DEBUG_PRINT("\r\nError Reading SPI_READ_TWO_REG: Invalid HAL_STATUS\r\n");
#endif
            return 0x00;
        }
    }

    if (enRegs == SPI_READ_THREE_REG)                             /* Only used for Temp & X,Y,Z offset and threshold registers*/
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

        status = HAL_SPI_Transmit (&hspi2, &txData, 1, 100);

        status = HAL_SPI_Receive (&hspi2, rxBuff, 3, 100);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        if (status == HAL_OK)
        {
            ui32valueH = rxBuff[0];

            ui32valueM = rxBuff[1];

            ui32valueL = rxBuff[2];

            returnData = (ui32valueH << 16) + (ui32valueM << 8) + ui32valueL;

            return returnData;
        }
        else
        {
#if defined(DEBUG_MODE)
//            DEBUG_PRINT("\r\nError Reading SPI_READ_THREE_REG: Invalid HAL_STATUS\r\n");
#endif
            return 0x00;
        }
    }

//    HAL_StatusTypeDef status;
//    uint8_t recieveData;
//    uint8_t txData;

//    txData = (ui8address << 1) | ADXL355_READ;
//    
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

//    status = HAL_SPI_Transmit (&hspi1, &txData, 1, 100);

//    status = HAL_SPI_Receive (&hspi1, &recieveData, 1, 100);

//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

//    if (status == HAL_OK)
//        return recieveData;
//    else
//    {
//#if defined(DEBUG_MODE)
//        DEBUG_PRINT("\r\nError Reading: Invalid HAL_STATUS\r\n");
//#endif
//        return 0x00;
//    }
    return 0x00;
}

/**
  * @brief  Use SPI to write data to ADXL355 register.
  * @param  ui8address: register address.
  *         ui8Data: data to write.
  *         enMode： enMode can only be  SPI_WRITE_ONE_REG SPI_WRITE_TWO_REG.
  * @retval None.
  */
void ADXL355_SPI_Write(uint8_t ui8address, uint8_t ui8Data, uint8_t ui8Data2, enWriteData enMode)
{

    HAL_StatusTypeDef status;
    uint8_t address;

    address = ((ui8address << 1) | ADXL355_WRITE);

    if (enMode == SPI_WRITE_ONE_REG)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

        status = HAL_SPI_Transmit (&hspi2, &address, 1, 100);
        status = HAL_SPI_Transmit (&hspi2, &ui8Data, 1, 100);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        if (status != HAL_OK)
        {
        	//            DEBUG_PRINT("\r\nError writing: Invalid HAL STATUS\r\n");
        }

    }

    if (enMode == SPI_WRITE_TWO_REG)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

        status = HAL_SPI_Transmit (&hspi2, &address, 1, 100);
        status = HAL_SPI_Transmit (&hspi2, &ui8Data, 1, 100);
        status = HAL_SPI_Transmit (&hspi2, &ui8Data2, 1, 100);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        if (status != HAL_OK)
        {
//        	DEBUG_PRINT("\r\nError writing: Invalid HAL STATUS\r\n");
        }

    }
}

/**
  * @brief  Start ADXL355 measure.
  * @param  None.
  * @retval None.
  */
void ADXL355_Start_Sensor(void)
{
   uint8_t ui8temp;

   ui8temp = (uint8_t)ADXL355_SPI_Read(POWER_CTL, SPI_READ_ONE_REG);                /* Read POWER_CTL register, before modifying it */

   ui8temp = ui8temp & 0xFE;                                                        /* Set measurement bit in POWER_CTL register */

   ADXL355_SPI_Write(POWER_CTL, ui8temp, null_val, SPI_WRITE_ONE_REG);              /* Write the new value to POWER_CTL register */

#if defined(DEBUG_MODE)
   //DEBUG_PRINT("\n\rSensors started.\n\r");
#endif

}

/**
  * @brief  Stop ADXL355 measure.
  * @param  None.
  * @retval None.
  */
void ADXL355_Stop_Sensor(void)
{
   uint8_t ui8temp;

   ui8temp = (uint8_t)ADXL355_SPI_Read(POWER_CTL, SPI_READ_ONE_REG);                /*Read POWER_CTL register, before modifying it */

   ui8temp = ui8temp | 0x01;                                                        /* Clear measurement bit in POWER_CTL register */

   ADXL355_SPI_Write(POWER_CTL, ui8temp, null_val, SPI_WRITE_ONE_REG);              /* Write the new value to POWER_CTL register */

#if defined(DEBUG_MODE)
   //DEBUG_PRINT("\n\rSensors stopped.\n\r");
#endif
}

/**
  * @brief  Set ADXL355 gravity acceleration range.
  * @param  range: where range can be (2, 4, 8) 
  * @retval None.
  */
void ADXL355_Set_Range (uint8_t range)
{
    uint32_t val = ADXL355_SPI_Read(RANGE, SPI_READ_ONE_REG);

    switch ( range )
    {
        case 2 :
            val = (val & 0xFFFFFFFC) | 0x01;
            break;

        case 4 :
            val = (val & 0xFFFFFFFC) | 0x02;
            break;

        case 8:
            val = (val & 0xFFFFFFFC) | 0x03;
            break;

        default :
#if defined(DEBUG_MODE)
//            DEBUG_PRINT("\n\rInvalid input - only 2, 4, or 8 for the range\n\r");
#endif
            break;
    }
    ADXL355_SPI_Write(RANGE, val, null_val, SPI_WRITE_ONE_REG);
}

/**
  * @brief  Read ADXL355 gravity acceleration range.
  * @param  None
  * @retval Return ADXL355 gravity acceleration range(2, 4, 8).
  */
uint32_t ADXL355_Read_Range (void)
{
    uint32_t range;
    range = ADXL355_SPI_Read(RANGE, SPI_READ_ONE_REG);
    range = range & 0x03;

    if ( range == 0x01 )
        return 2;
    else if ( range == 0x02 )
        return 4;
    else if ( range == 0x03 )
        return 8;
    else return 0;          //error return
}

/**
  * @brief  Scan ADXL355 acceleration and temperature data once.
  * @param  None.
  * @retval None.
  */
void ADXL355_Data_Scan(void)
{
//    uint32_t xdata3, xdata2, xdata1,    \
//             ydata3, ydata2, ydata1,    \
//             zdata3, zdata2, zdata1,    \
//             temp2,  temp1;

//    xdata3 = ADXL355_SPI_Read(XDATA3, SPI_READ_ONE_REG);
//    xdata2 = ADXL355_SPI_Read(XDATA2, SPI_READ_ONE_REG);
//    xdata1 = ADXL355_SPI_Read(XDATA1, SPI_READ_ONE_REG);

//    ydata3 = ADXL355_SPI_Read(YDATA3, SPI_READ_ONE_REG);
//    ydata2 = ADXL355_SPI_Read(YDATA2, SPI_READ_ONE_REG);
//    ydata1 = ADXL355_SPI_Read(YDATA1, SPI_READ_ONE_REG);

//    zdata3 = ADXL355_SPI_Read(ZDATA3, SPI_READ_ONE_REG);
//    zdata2 = ADXL355_SPI_Read(ZDATA2, SPI_READ_ONE_REG);
//    zdata1 = ADXL355_SPI_Read(ZDATA1, SPI_READ_ONE_REG);

//    temp2 = ADXL355_SPI_Read(TEMP2, SPI_READ_ONE_REG);
//    temp1 = ADXL355_SPI_Read(TEMP1, SPI_READ_ONE_REG);

    ui32SensorX = ADXL355_SPI_Read(XDATA3, SPI_READ_THREE_REG);;
    ui32SensorY = ADXL355_SPI_Read(YDATA3, SPI_READ_THREE_REG);
    ui32SensorZ = ADXL355_SPI_Read(ZDATA3, SPI_READ_THREE_REG);
    ui32SensorT = ADXL355_SPI_Read(TEMP2, SPI_READ_TWO_REG);
    
    i32SensorX = ADXL355_Acceleration_Data_Conversion(ui32SensorX);
    i32SensorY = ADXL355_Acceleration_Data_Conversion(ui32SensorY);
    i32SensorZ = ADXL355_Acceleration_Data_Conversion(ui32SensorZ);
}

/**
  * @brief  Converts acceleration unsigned types to signed types.
  * @param  None.
  * @retval None.
  */
int32_t ADXL355_Acceleration_Data_Conversion (uint32_t ui32SensorData)
{
    int32_t volatile i32Conversion = 0;

   ui32SensorData = ( ui32SensorData >> 4);

   ui32SensorData = (ui32SensorData & 0x000FFFFF);

   if((ui32SensorData & 0x00080000) == 0x00080000)         //checking if most sig bit is set
   {
        i32Conversion = (ui32SensorData | 0xFFF00000);     //if its set, we try to make it negative
   }
   else
   {
        i32Conversion = ui32SensorData;
   }
   return i32Conversion;
}

/**
  * @brief  Check whether the mechanical part and the electronic part function normally
  *         through the input of the forced stress.
  *         Self test typical value X-Axis: 0.3g, Y-Axis: 0.3g, Z-Axis: 1.5g.
  * @param  None.
  * @retval None.
  */
void ADXL355_Self_Test()
{
    ADXL355_Start_Sensor();
    ADXL355_SPI_Write(SELF_TEST, 0x03, null_val, SPI_WRITE_ONE_REG);
    HAL_Delay(5);                                                      //Avoid first read errors
    ADXL355_Data_Scan();
#if defined(DEBUG_MODE)
    DEBUG_PRINT("\nSensorX is: %.5f\n", (double)i32SensorX/ SCALE_2G);
    DEBUG_PRINT("\nSensorY is: %.5f\n", (double)i32SensorY/ SCALE_2G);
    DEBUG_PRINT("\nSensorZ is: %.5f\n", (double)i32SensorZ/ SCALE_2G);
#endif
    ADXL355_SPI_Write(SELF_TEST, 0x00, null_val, SPI_WRITE_ONE_REG);
    ADXL355_Stop_Sensor();
}

/**
  * @brief  Convert the measured gravimetric value into an angular value.
  * @param  i32SensorX: X-Axis measured value, i32SensorY:Y-Axis measured value i32SensorZ:Z-Axis measured value.
  * @retval None.
  */
void ADXL355_Convert_Angle(int32_t i32SensorX, int32_t i32SensorY, int32_t i32SensorZ)
{
      angleX = atan(i32SensorX/(sqrt(pow(i32SensorY,2)+pow(i32SensorZ,2))));
      angleX *= (180.0/PI);

      angleY = atan(i32SensorY/(sqrt(pow(i32SensorX,2)+pow(i32SensorZ,2))));
      angleY *= (180.0/PI);

      angleZ = atan((sqrt(pow(i32SensorX,2)+pow(i32SensorY,2)))/i32SensorZ);
      angleZ *= (180.0/PI);

#if defined(DEBUG_MODE)
      DEBUG_PRINT("\r\nangleX= %.6f", angleX);
      DEBUG_PRINT("\r\nangleY= %.6f", angleY);
      DEBUG_PRINT("\r\nangleZ= %.6f", angleZ);
#endif
}

/**
  * @brief  For temperature compensation, The result is stored in compensatedX, compensatedY, compensatedZ.
  * @param  i32SensorX: X-Axis measured value, i32SensorY:Y-Axis measured value i32SensorZ:Z-Axis measured value.
  * @retval None.
  */
void ADXL355_Temp_Compensation(int32_t i32SensorX, int32_t i32SensorY, int32_t i32SensorZ)
{
    float volatile f32temp = ((((float)ui32SensorT - ADXL355_TEMP_BIAS)) / ADXL355_TEMP_SLOPE) + 25.0;
    double xerror = ADXL355_TEMP_XCOMP* f32temp - ADXL355_TEMP_B;
    double yerror = ADXL355_TEMP_YCOMP* f32temp - ADXL355_TEMP_B;
    double zerror = ADXL355_TEMP_ZCOMP* f32temp - ADXL355_TEMP_B;
    compensatedX = (1-xerror)*(double)i32SensorX;
    compensatedY = (1-yerror)*(double)i32SensorY;
    compensatedZ = (1-zerror)*(double)i32SensorZ;
}



