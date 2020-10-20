/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IR_RX_Pin GPIO_PIN_8
#define IR_RX_GPIO_Port GPIOF
#define IR_TX_Pin GPIO_PIN_9
#define IR_TX_GPIO_Port GPIOF
#define LIMIT_KEY_Pin GPIO_PIN_10
#define LIMIT_KEY_GPIO_Port GPIOF
#define TOKEN0_Pin GPIO_PIN_13
#define TOKEN0_GPIO_Port GPIOE
#define TOKEN1_Pin GPIO_PIN_14
#define TOKEN1_GPIO_Port GPIOE
#define TOKEN2_Pin GPIO_PIN_15
#define TOKEN2_GPIO_Port GPIOE
#define RS485_DE_Pin GPIO_PIN_14
#define RS485_DE_GPIO_Port GPIOB
#define AM400_POWER_Pin GPIO_PIN_10
#define AM400_POWER_GPIO_Port GPIOD
#define AM400_RESET_Pin GPIO_PIN_11
#define AM400_RESET_GPIO_Port GPIOD
#define AM400_USIMA_Pin GPIO_PIN_12
#define AM400_USIMA_GPIO_Port GPIOD
#define AM400_USIMB_Pin GPIO_PIN_13
#define AM400_USIMB_GPIO_Port GPIOD
#define BEEP_Pin GPIO_PIN_15
#define BEEP_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_2
#define LED0_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOG
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOG
#define KEY0_Pin GPIO_PIN_5
#define KEY0_GPIO_Port GPIOG
#define KEY1_Pin GPIO_PIN_6
#define KEY1_GPIO_Port GPIOG
#define MOTOR_DRIVE_ENA_Pin GPIO_PIN_7
#define MOTOR_DRIVE_ENA_GPIO_Port GPIOG
#define MOTOR_DRIVE_DIR_Pin GPIO_PIN_8
#define MOTOR_DRIVE_DIR_GPIO_Port GPIOG
#define AD7280A_ALERT_Pin GPIO_PIN_3
#define AD7280A_ALERT_GPIO_Port GPIOD
#define AD7280A_CNVST_Pin GPIO_PIN_4
#define AD7280A_CNVST_GPIO_Port GPIOD
#define AD7280A_PD_Pin GPIO_PIN_5
#define AD7280A_PD_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
