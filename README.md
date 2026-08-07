# MyBootloader

Project sử dụng **nRF54L15 DK** với **MCUboot** thông qua **Sysbuild**.

## Sysbuild Configuration

**File:** `sysbuild.conf`

```conf
SB_CONFIG_BOOTLOADER_MCUBOOT=y
SB_CONFIG_MCUBOOT_MODE_SINGLE_APP=y
```

## Sử dụng UART20:
| Parameter | Value |
| --------- | ----- |
| TX Pin    | P1.11 |
| RX Pin    | P1.12 |
| Baud Rate | 115200|


