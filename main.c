/*
 * main.c
 *
 *  Created on: 2020 Sep 02 12:52:04
 *  Author: FORGE-15R
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "ext_lib/base.h"

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

volatile uint32_t pin_status;

static void tle94112el_enable(void);
static void tle94112el_disable(void);
static int32_t tle94112el_spi_transfer(uint8_t *tx_data, uint8_t *rx_data);

static const TLE94112EL_t TLE94112EL_0 =

  {

    .enable = tle94112el_enable,

    .disable = tle94112el_disable,

    .spi_transfer = tle94112el_spi_transfer

  };

TaskHandle_t FORWARD_Handle = NULL;
TaskHandle_t BACKWARD_Handle = NULL;
TaskHandle_t LEFT_Handle = NULL;
TaskHandle_t RIGHT_Handle = NULL;
TaskHandle_t OPEN_Handle = NULL;
TaskHandle_t CLOSE_Handle = NULL;
TaskHandle_t LIFT_Handle = NULL;
TaskHandle_t ROTATE_Handle = NULL;

SemaphoreHandle_t FORWARD_interruptSemaphore;
SemaphoreHandle_t BACKWARD_interruptSemaphore;
SemaphoreHandle_t LEFT_interruptSemaphore;
SemaphoreHandle_t RIGHT_interruptSemaphore;
SemaphoreHandle_t OPEN_interruptSemaphore;
SemaphoreHandle_t CLOSE_interruptSemaphore;
SemaphoreHandle_t LIFT_interruptSemaphore;
SemaphoreHandle_t ROTATE_interruptSemaphore;


void FORWARD_Task(void *p){

	while(1){

		if (xSemaphoreTake(FORWARD_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&FORWARD_INTERRUPT);
			if(pin_status==1){
				//FORWARD
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x99);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x99);
				  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );
			}
		}
	}
}

void BACKWARD_Task(void *p){

	while(1){

		if (xSemaphoreTake(BACKWARD_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&BACKWARD_INTERRUPT);
			if(pin_status==1){
				//BACKWARD
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x66);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x66);
				  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );
			}
		}
	}
}

void LEFT_Task(void *p){

	while(1){

		if (xSemaphoreTake(LEFT_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&LEFT_INTERRUPT);
			if(pin_status==1){
				//LEFT
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x66);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x99);
				  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );
			}
		}
	}
}

void RIGHT_Task(void *p){

	while(1){

		if (xSemaphoreTake(RIGHT_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&RIGHT_INTERRUPT);
			if(pin_status==1){
				//RIGHT
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x99);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x66);
				  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);
				  const TickType_t xDelay = 5 / portTICK_PERIOD_MS;
				  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );
			}
		}
	}
}

void OPEN_Task(void *p){

	while(1){

		if (xSemaphoreTake(OPEN_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&OPEN_INTERRUPT);
		     if(pin_status == 1)
		     {
		 	  	// sets the duty to 12%.
		    	// clamp open
		    	 PWM_SetDutyCycle(&PWM_CLAMP,1200);
		     }

		     else
		     {
		    	 // sets the channel duty to 0%.
		    	 // clamp maintain
		    	 PWM_SetDutyCycle(&PWM_CLAMP,0);
		     }

		 	pin_status = 0;

		}
	}
}

void CLOSE_Task(void *p){

	while(1){

		if (xSemaphoreTake(CLOSE_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&CLOSE_INTERRUPT);
		     if(pin_status == 1)
		     {
		 	  	// sets the duty to 2%.
		    	// clamp CLOSE
		    	 PWM_SetDutyCycle(&PWM_CLAMP,200);
		     }

		     else
		     {
		    	 // sets the channel duty to 0%.
		    	 // clamp maintain
		    	 PWM_SetDutyCycle(&PWM_CLAMP,0);
		     }

		 	pin_status = 0;

		}
	}
}

void LIFT_Task(void *p){

	while(1){

		if (xSemaphoreTake(LIFT_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&LIFT_INTERRUPT);
		     if(pin_status == 1)
		     {
		 	  	// sets the duty to 2%.
		    	// LIFT UP
		    	 PWM_SetDutyCycle(&PWM_LIFT,200);
		     }

		     else
		     {
		    	 // sets the channel duty to 10%.
		    	 // LIFT DOWN
		    	 PWM_SetDutyCycle(&PWM_LIFT,1000);
		     }

		 	pin_status = 0;

		}
	}
}

void ROTATE_Task(void *p){

	while(1){

		if (xSemaphoreTake(ROTATE_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&ROTATE_INTERRUPT);
		     if(pin_status == 1)
		     {
		 	  	// sets the duty to 2%.
		    	// FOR METAL
		    	 PWM_SetDutyCycle(&PWM_LIFT,200);
		    	 DIGITAL_IO_SetOutputHigh(&GREEN_LED);
		    	 DIGITAL_IO_SetOutputLow(&RED_LED);
		     }

		     else
		     {
		    	 // sets the channel duty to 12%.
		    	 // NON-METAL
		    	 PWM_SetDutyCycle(&PWM_LIFT,1200);
		    	 DIGITAL_IO_SetOutputLow(&GREEN_LED);
		    	 DIGITAL_IO_SetOutputHigh(&RED_LED);
		     }

		 	pin_status = 0;

		}
	}
}

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

	// ENABLE DC Motor Shield
	TLE94112EL_Enable(&TLE94112EL_0);

	// Initialize the FreeRTOS
	xTaskCreate(FORWARD_Task, "FORWARD", 200, NULL, tskIDLE_PRIORITY, &FORWARD_Handle);
	xTaskCreate(BACKWARD_Task, "BACKWARD", 200, NULL, tskIDLE_PRIORITY, &BACKWARD_Handle);
	xTaskCreate(LEFT_Task, "LEFT", 200, NULL, tskIDLE_PRIORITY, &LEFT_Handle);
	xTaskCreate(RIGHT_Task, "RIGHT", 200, NULL, tskIDLE_PRIORITY, &RIGHT_Handle);
	xTaskCreate(OPEN_Task, "FORWARD", 200, NULL, tskIDLE_PRIORITY, &OPEN_Handle);
	xTaskCreate(CLOSE_Task, "BACKWARD", 200, NULL, tskIDLE_PRIORITY, &CLOSE_Handle);
	xTaskCreate(LIFT_Task, "LEFT", 200, NULL, tskIDLE_PRIORITY, &LIFT_Handle);
	xTaskCreate(ROTATE_Task, "RIGHT", 200, NULL, tskIDLE_PRIORITY, &ROTATE_Handle);

	FORWARD_interruptSemaphore = xSemaphoreCreateBinary();
	BACKWARD_interruptSemaphore = xSemaphoreCreateBinary();
	LEFT_interruptSemaphore = xSemaphoreCreateBinary();
	RIGHT_interruptSemaphore = xSemaphoreCreateBinary();
	OPEN_interruptSemaphore = xSemaphoreCreateBinary();
	CLOSE_interruptSemaphore = xSemaphoreCreateBinary();
	LIFT_interruptSemaphore = xSemaphoreCreateBinary();
	ROTATE_interruptSemaphore = xSemaphoreCreateBinary();

	vTaskStartScheduler();
	// Initialize the FreeRTOS




  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {

  }
}

void FORWARD_IRQHandler(void){

	xSemaphoreGiveFromISR(FORWARD_interruptSemaphore, NULL);
}

void BACKWARD_IRQHandler(void){

	xSemaphoreGiveFromISR(BACKWARD_interruptSemaphore, NULL);
}

void LEFT_IRQHandler(void){

	xSemaphoreGiveFromISR(LEFT_interruptSemaphore, NULL);
}

void RIGHT_IRQHandler(void){

	xSemaphoreGiveFromISR(RIGHT_interruptSemaphore, NULL);
}

void OPEN_IRQHandler(void){

	xSemaphoreGiveFromISR(OPEN_interruptSemaphore, NULL);
}

void CLOSE_IRQHandler(void){

	xSemaphoreGiveFromISR(CLOSE_interruptSemaphore, NULL);
}

void LIFT_IRQHandler(void){

	xSemaphoreGiveFromISR(LIFT_interruptSemaphore, NULL);
}

void ROTATE_IRQHandler(void){

	xSemaphoreGiveFromISR(ROTATE_interruptSemaphore, NULL);
}


static void tle94112el_enable(void)

{

  DIGITAL_IO_SetOutputHigh(&TLE94112_ENABLE);

}

static void tle94112el_disable(void)

{

  DIGITAL_IO_SetOutputLow(&TLE94112_ENABLE);

}

static int32_t tle94112el_spi_transfer(uint8_t *tx_data, uint8_t *rx_data)

{

  XMC_SPI_CH_SetBitOrderLsbFirst(SPI_MASTER_0.channel);



  DIGITAL_IO_SetOutputLow(&TLE94112_CS);



  SPI_MASTER_Transfer(&SPI_MASTER_0, tx_data, rx_data, 2);

  while(SPI_MASTER_0.runtime->rx_busy);



  DIGITAL_IO_SetOutputHigh(&TLE94112_CS);



  return 0;

}
