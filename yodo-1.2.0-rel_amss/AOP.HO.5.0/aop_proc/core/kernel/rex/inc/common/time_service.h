#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "comdef.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------
#define XO_FREQUENCY_IN_HZ     (19200000) //19.2Mhz
#define SLEEP_FREQUENCY_IN_HZ  (32768)    // 32Khz
#define ONE_SECOND (19200000)
#define ONE_MILLISECOND (19200)
#define XO_FREQUENCY_IN_KHZ  (XO_FREQUENCY_IN_HZ/1000)
#define USEC_TO_TICKS(x) (((x)*192)/10)
#define MSEC_TO_TICKS(x) ((x)*ONE_MILLISECOND)
#define ONE_MICROSECOND (USEC_TO_TICKS(1))

//---------------------------------------------------------------------------
// Feature defines
//---------------------------------------------------------------------------
#if defined(QCTDD06638432)
 #define QTMR_UNRELIABLE
 #define QTMR_RELIABLE_BITS (0xFFFFFFFFFFFFFC00LL)
#endif
//---------------------------------------------------------------------------
//  Type Definitions
//---------------------------------------------------------------------------
typedef enum
{
  TIMER_SUCCESS = 0,
  TIMER_OUTOFSPACE_ERROR = -1,
  TIMER_NOTFOUND_ERROR = -2,
  TIMER_DURATION_ZERO_ERROR = -3,
}timer_result;

// Pointer to a function returning Void taking a uint64 - used for timers.
typedef void (*PFV_W64)(uint64 lateness);

/**
 * <!-- time_service_init -->
 *
 * @brief QTMRF1 init, needs to be called before
 *        aop_register_timer_cb
 *
**/
void aop_timer_service_init(void);

timer_result aop_register_dog_cb(uint32 period, PFV_W64 callback, bool is_persistent);

timer_result aop_cancel_dog_cb(PFV_W64 callback);

/**
 * <!-- time_service_init -->
 *
 * @brief QTMRF0 init
 *
**/
void time_service_init(void);

/**
 * <!-- time_service_now -->
 *
 * @brief Returns physical count val
 *
**/
uint64 time_service_now(void);

/**
 * <!-- busywait -->
 *
 * @brief busywaits on xo ticks if pause time > BUSYWAIT_THRESHOLD_ON_XO_US 
 *        or else waits using systicks running at PROC_CLK. If xo is on through
 *        this busywait, and if had pause time is within SYSTICK_CALIB_THRES_us
 *        and SYSTICK_CALIB_MAX_THRES_us, attempts to calibrate systick timer
 *        with xo ticks within SYSTICK_CALIB_STEP_TICKS margin.
 * @param pause_time_us: busy wait time in usec.
 * @return void
 */
void busywait (uint32 pause_time_us);

/**
 * <!-- aop_timer_check -->
 *
 * @brief Determine if any callbacks are necessary
 *
**/
void aop_timer_check(void);

/**
 * <!-- aop_cancel_timer_cb -->
 *
 * @brief Cancel a previously registered callback function
 *
 * @param[in] callback
 * 
**/
timer_result aop_cancel_timer_cb(PFV_W64 callback);

/**
 * <!-- aop_register_timer_cb -->
 *
 * @brief Register a function to be called from the idle thread after a period of time
 *
 * @param[in] period   - The number of ticks in the future to set the timer
 * @param[in] callback - The function to call. 
 * @param[in] is_persistent - if true, timer remain enabled
 *       until cancelled
 * 
**/
timer_result aop_register_timer_cb(uint32 period, PFV_W64 callback, bool is_persistent);

/**
 * <!-- time_service_now2 -->
 *
 * @brief time service now + additional details about time
 *
**/
uint64_t time_service_now2(bool* is_xo_on, uint32* systicks_now);

/**
 * <!-- get_systicks_per_us -->
 *
 * @brief get last calib val
 *
**/
uint32 get_systicks_per_us(void);

/**
 * <!-- get_aop_min_timer -->
 *
 * @brief Gets current min time
 *
**/
uint64 get_aop_min_timer(void);

#ifdef __cplusplus
}
#endif

#endif // TIME_SERVICE_H
