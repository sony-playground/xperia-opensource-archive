#include <HALhwio.h>
#include <HALbootHWIO.h>

#include <boot_timer_hw_if.h>
#include <boot_target.h>

uint32 __boot_get_timestamp(void)
{
  volatile uint32 curr_count;
  curr_count = HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_IN;
  return CALCULATE_TIMESTAMP(curr_count);
}


boot_timer_hw_if_type timer_hw_if = {
  __boot_get_timestamp
};

