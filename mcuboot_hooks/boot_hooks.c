#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "boot_hooks.h"

__weak void mcuboot_pre_jump_hook(void)

{
  printk("\n");
  printk("======================================\n");
  printk("== PRINT HOOK MESSAGE IN MCUBOOT =====\n");
  printk("======================================\n");
  printk("\n");
  printk("=======   =======     ========          ========   ========\n");
  printk("  = =           ===   ===    ===       ===    ===  ===     \n");
  printk("  = =      =======    ===    ===       ===    ===  ========\n");
  printk("  = =     ===         ===    ===       ===    ===       ===\n");
  printk("  = =      =======    ========          ========   ========\n");
  printk("\n");
}