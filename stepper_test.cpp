/**
i * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Output PWM signals on pins 0 and 1

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

const uint EN_PIN=6;
const uint LM_STEP=2;
const uint LM_DIR=4;
const uint LED_PIN=25;


int main() {
  uint a=1;
  uint rpm=120;
  uint T=(int)(1000000/(400.0*rpm/60.0));
  gpio_init(LED_PIN);
  gpio_init(EN_PIN);
  gpio_init(LM_STEP);
  gpio_init(LM_DIR);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_set_dir(EN_PIN,  GPIO_OUT);
  gpio_set_dir(LM_STEP, GPIO_OUT);
  gpio_set_dir(LM_DIR,  GPIO_OUT);
  gpio_put(EN_PIN, 0);
  gpio_put(LM_DIR, 0);
  gpio_put(LM_STEP, 0);
  sleep_ms(1000);
  while(1) {
    for(uint i=0;i<5*1000000/T;i++)
    {
      gpio_put(LM_DIR, 0);
      gpio_put(LED_PIN, a);
      gpio_put(LM_STEP, 1);
      sleep_us(T/2);
      gpio_put(LM_STEP, 0);
      sleep_us(T/2);
      a++;
      a=a&1;
    }
    for(uint i=0;i<5*1000000/T;i++)
    {
      gpio_put(LM_DIR, 1);
      gpio_put(LED_PIN, a);
      gpio_put(LM_STEP, 1);
      sleep_us(T/2);
      gpio_put(LM_STEP, 0);
      sleep_us(T/2);
      a++;
      a=a&1;
    }

  }
  

#if 0  
    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(2, GPIO_FUNC_PWM);
    gpio_set_function(3, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(3);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 24999);
    pwm_set_clkdiv(slice_num, 100.0);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 2315);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1330);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    /// \end::setup_pwm[]
    sleep_ms(2000);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1330);
    sleep_ms(5000);
    while(true){
      pwm_set_chan_level(slice_num, PWM_CHAN_A, 1450);
      sleep_ms(2000);
      pwm_set_chan_level(slice_num, PWM_CHAN_A, 1330);
      sleep_ms(2000);
    }
    

    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.2450
#endif
}
