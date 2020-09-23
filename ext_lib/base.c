#include "base.h"

int32_t TLE94112EL_SetHBRegdata(const TLE94112EL_t *const handler, uint8_t TLE94112EL_HB_ACT_X_CTRL, uint8_t regdata)
{
  if ((TLE94112EL_HB_ACT_X_CTRL >= 0x04)|(TLE94112EL_HB_ACT_X_CTRL <= 0x00))
  {
	return -1;
  }

  uint8_t tx_data[2];
  uint8_t rx_data[2];
  uint8_t addr;

	switch(TLE94112EL_HB_ACT_X_CTRL){

		case 1:
			addr = TLE94112EL_HB_ACT_1_CTRL;
			break;

		case 2:
			addr = TLE94112EL_HB_ACT_2_CTRL;
			break;

		case 3:
			addr = TLE94112EL_HB_ACT_3_CTRL;
			break;

	}

	  //write
	  tx_data[0] = addr | 0x80;
	  tx_data[1] = regdata;

	  handler->spi_transfer(tx_data, rx_data);

  return rx_data[0];
}

