/* Linker script to configure memory regions for builds without SoftDevice.
 *
 * The SoftDevice is not flashed, so the application is linked right after
 * the MBR at 0x1000. The MBR forwards to the application when no
 * SoftDevice is present. RAM is used entirely by the application.
 */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  /* Bootloader region starts at 0xF4000, bootloader settings at 0xFF000 */
  FLASH (rx)     : ORIGIN = 0x1000, LENGTH = 0xF4000 - 0x1000

  RAM (rwx) :  ORIGIN = 0x20000000, LENGTH = 0x20040000 - 0x20000000
}

SECTIONS
{
  . = ALIGN(4);
  .svc_data :
  {
    PROVIDE(__start_svc_data = .);
    KEEP(*(.svc_data))
    PROVIDE(__stop_svc_data = .);
  } > RAM

  .fs_data :
  {
    PROVIDE(__start_fs_data = .);
    KEEP(*(.fs_data))
    PROVIDE(__stop_fs_data = .);
  } > RAM
} INSERT AFTER .data;

INCLUDE "nrf52_common.ld"
