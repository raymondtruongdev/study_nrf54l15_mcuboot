

#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000
#define LED0          DT_ALIAS(led2)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0, gpios);

void boot_banner(void) {
  // Zephyr định nghĩa hàm boot_banner với thuộc tính "weak" ,
  // cho phép bạn dễ dàng "ghi đè" nên có thể customize banner bằng cách định nghĩa lại hàm boot_banner()
  printk("\n");
  printk("=======   =======     ========          ========   ========\n");
  printk("  = =           ===   ===    ===       ===    ===  ===     \n");
  printk("  = =      =======    ===    ===       ===    ===  ========\n");
  printk("  = =     ===         ===    ===       ===    ===       ===\n");
  printk("  = =      =======    ========          ========   ========\n");
  printk("\n");
}

int main() {
  printk("===== START MAIN.C APPLICATION ROM =====\n");
  int  ret;
  bool led_state = true;

  if (!gpio_is_ready_dt(&led)) {
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0) {
    return 0;
  }

  while (1) {
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0) {
      return 0;
    }
    led_state = !led_state;
    // printf("LED state: %s\n", led_state ? "ON" : "OFF");
    k_msleep(SLEEP_TIME_MS);
  }

  return 0;
}
