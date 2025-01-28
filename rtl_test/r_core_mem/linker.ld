
MEMORY {
    txt1 : ORIGIN = 0x10000000, LENGTH = 0x1000000
    txt2 : ORIGIN = 0x12000000, LENGTH = 0x1000000
    txt3 : ORIGIN = 0x14000000, LENGTH = 0x1000000
    txt4 : ORIGIN = 0x16000000, LENGTH = 0x1000000
    txt5 : ORIGIN = 0x18000000, LENGTH = 0x1000000
    txt6 : ORIGIN = 0x1a000000, LENGTH = 0x1000000
    txt7 : ORIGIN = 0x1c000000, LENGTH = 0x1000000
    txt8 : ORIGIN = 0x1e000000, LENGTH = 0x1000000
    txt9 :  ORIGIN = 0x20000000, LENGTH = 0x1000000
    txt10 : ORIGIN = 0x22000000, LENGTH = 0x1000000
    txt11 : ORIGIN = 0x24000000, LENGTH = 0x1000000
    txt12 : ORIGIN = 0x26000000, LENGTH = 0x1000000
    txt13 : ORIGIN = 0x28000000, LENGTH = 0x1000000
    txt14 : ORIGIN = 0x2a000000, LENGTH = 0x1000000
    txt15 : ORIGIN = 0x2c000000, LENGTH = 0x1000000
    txt16 : ORIGIN = 0x2e000000, LENGTH = 0x1000000
}

SECTIONS {
  .text0 : { *(.text) } > txt1
  .text1 : { *(.text) } > txt2
  .text2 : { *(.text) } > txt3
  .text3 : { *(.text) } > txt4
  .text4 : { *(.text) } > txt5
  .text5 : { *(.text) } > txt6
  .text6 : { *(.text) } > txt7
  .text7 : { *(.text) } > txt8
  .text8 : { *(.text) } > txt9
  .text9 : { *(.text) } > txt10
  .text10 : { *(.text) } > txt11
  .text11 : { *(.text) } > txt12
  .text12 : { *(.text) } > txt13
  .text13 : { *(.text) } > txt14
  .text14 : { *(.data) } > txt15
  .text15 : { *(.bss) } > txt16
}
