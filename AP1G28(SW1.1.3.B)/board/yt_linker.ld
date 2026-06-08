/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file yt_linker.ld
 * @brief 
 * 
 */



























/* MEMORY MAP */
MEMORY
{
    SecurtBoot   (RX) : ORIGIN = 0x0, LENGTH = 0x10000
    Bootloader   (RX) : ORIGIN = 0x10000, LENGTH = 0x1fb00
    BootFlash_Storage   (RX) : ORIGIN = 0x2fb00, LENGTH = 0x100
    AppBootInteract   (RX) : ORIGIN = 0x2fc00, LENGTH = 0x400
    ApplHeader   (RX) : ORIGIN = 0x30000, LENGTH = 0x20
    Appl_IVT   (RX) : ORIGIN = 0x30020, LENGTH = 0x3e0
    BootAppInteract   (RX) : ORIGIN = 0x30400, LENGTH = 0x400
    AppFlash_Storage   (RX) : ORIGIN = 0x30800, LENGTH = 0x100
    App1   (RX) : ORIGIN = 0x30900, LENGTH = 0x4ef00
    BVT1   (RX) : ORIGIN = 0x7f800, LENGTH = 0x800
    App2   (RX) : ORIGIN = 0x80000, LENGTH = 0x7f000
    BVT2   (RX) : ORIGIN = 0xff000, LENGTH = 0x800
    App3   (RX) : ORIGIN = 0xff800, LENGTH = 0x800
    IVT_RAM   (RW) : ORIGIN = 0x1fff0000, LENGTH = 0x400
    UserKAM   (RW) : ORIGIN = 0x1fff0400, LENGTH = 0x100
    RAM   (RW) : ORIGIN = 0x1fff0500, LENGTH = 0x1f700
    STACK   (RW) : ORIGIN = 0x2000fc00, LENGTH = 0x400
}
/* SECTIONS */
SECTIONS
{

    .TEXT  : {
        
        . = ALIGN(8);
        TEXT_start = .;
        UserResetHandler_region_start = .;
        KEEP(*(.UserResetHandler))
        UserResetHandler_region_end = .;
        
        TEXT_end = .;
    } > SecurtBoot
   
    



    .BootFlash_Storage  : {
        
        BootFlash_Storage_start = .;
        BootFlash_Storage_region_start = .;
        *(.BootFlash_Storage)
        BootFlash_Storage_region_end = .;
        
        BootFlash_Storage_end = .;
    } > BootFlash_Storage
   
    



    .AppBootInteract  : {
        
        . = ALIGN(4);
        AppBootInteract_start = .;
        AppBootInteract_region_start = .;
        AppBootStart = .; 
        KEEP(*(.AppBootInteract))
        AppBootInteract_region_end = .;
         AppBootEnd = .; 
        AppBootInteract_end = .;
    } > AppBootInteract
   
    



    .IVT  : {
        
        IVT_start = .;
        isr_vector_region_start = .;
        KEEP(*(.isr_vector))
        isr_vector_region_end = .;
        
        IVT_end = .;
    } > Appl_IVT
   
    



    .BootAppInteract  : {
        
        BootAppInteract_start = .;
        BootAppInteract_region_start = .;
        KEEP(*(.BootAppInteract))
        BootAppInteract_region_end = .;
        
        BootAppInteract_end = .;
    } > BootAppInteract
   
    



    .AppFlash_Storage  : {
        
        AppFlash_Storage_start = .;
        AppFlash_Storage_region_start = .;
        *(.AppFlash_Storage)
        AppFlash_Storage_region_end = .;
        
        AppFlash_Storage_end = .;
    } > AppFlash_Storage
   
    



    .TEXT  : {
        
        TEXT_start = .;
        rodata_region_start = .;
        *(.rodata)
        *(.rodata*)
        rodata_region_end = .;
        
        text_region_start = .;
        *(.text)
        *(.text*)
        text_region_end = .;
        
        TEXT_end = .;
    } > App1
   
    



    .ARM  : {
        
        ARM_start = .;
        ARM.exidx_region_start = .;
        *(.ARM.exidx)
        *(.ARM.exidx*)
        ARM.exidx_region_end = .;
        
        ARM_end = .;
    } > App1
   
    



    CODE_RAM_rom_start_not_align = .;
    CODE_RAM_rom_start = CODE_RAM_rom_start_not_align + (4 - CODE_RAM_rom_start_not_align % 4);
   
    CODE_RAM_rom_end = CODE_RAM_rom_start + CODE_RAM_ram_end - CODE_RAM_ram_start;




    DATA_RAM_rom_start_not_align = CODE_RAM_rom_end;
    DATA_RAM_rom_start = DATA_RAM_rom_start_not_align + (4 - DATA_RAM_rom_start_not_align % 4);
   
    DATA_RAM_rom_end = DATA_RAM_rom_start + DATA_RAM_ram_end - DATA_RAM_ram_start;




    .BVT  : {
        
        BVT_start = .;
        . = ALIGN(4);
        bvt_header_region_start = .;
        KEEP(*(.bvt_header))
        bvt_header_region_end = .;
        
        . = ALIGN(16);
        sb_config_group_region_start = .;
        KEEP(*(.sb_config_group))
        sb_config_group_region_end = .;
        
        . = ALIGN(16);
        sb_config_section_region_start = .;
        KEEP(*(.sb_config_section))
        sb_config_section_region_end = .;
        
        . = ALIGN(16);
        sb_cmac_region_start = .;
        KEEP(*(.sb_cmac))
        sb_cmac_region_end = .;
        
        BVT_end = .;
    } > BVT1
   
    



    .TEXT  : {
        
        TEXT_start = .;
        rodata_region_start = .;
        *(.rodata)
        *(.rodata*)
        rodata_region_end = .;
        
        text_region_start = .;
        *(.text)
        text_region_end = .;
        
        TEXT_end = .;
    } > App2
   
    



    .ARM  : {
        
        ARM_start = .;
        ARM.exidx_region_start = .;
        *(.ARM.exidx)
        *(.ARM.exidx*)
        ARM.exidx_region_end = .;
        
        ARM_end = .;
    } > App2
   
    



    NamDE_RAM2_rom_start_not_align = .;
    NamDE_RAM2_rom_start = NamDE_RAM2_rom_start_not_align + (4 - NamDE_RAM2_rom_start_not_align % 4);
   
    NamDE_RAM2_rom_end = NamDE_RAM2_rom_start + NamDE_RAM2_ram_end - NamDE_RAM2_ram_start;




    DATA_RAM2_rom_start_not_align = NamDE_RAM2_rom_end;
    DATA_RAM2_rom_start = DATA_RAM2_rom_start_not_align + (4 - DATA_RAM2_rom_start_not_align % 4);
   
    DATA_RAM2_rom_end = DATA_RAM2_rom_start + DATA_RAM2_ram_end - DATA_RAM2_ram_start;




    .IVT_RAM  : {
        
        . = ALIGN(1024);
        IVT_RAM_start = .;
        . += 0X400;
        IVT_RAM_end = .;
    } > IVT_RAM
   
    



    .DataKam  (NOLOAD): {
        
        DataKam_start = .;
        RegionKam_region_start = .;
        *(.RegionKam)
        RegionKam_region_end = .;
        
        DataKam_end = .;
    } > UserKAM
   
    



    .BSS  (NOLOAD): {
        
        BSS_start = .;
        bss_region_start = .;
        *(.bss)
        *(.bss*)
        bss_region_end = .;
        
        BSS_end = .;
    } > RAM
   
    



    .CODE_RAM  : AT(CODE_RAM_rom_start) {
        
        . = ALIGN(4);
        CODE_RAM_ram_start = .;
        CODE_RAM_start = .;
        code_ram_region_start = .;
        *(.code_ram)
        code_ram_region_end = .;
        
        CODE_RAM_end = .;
        CODE_RAM_ram_end = .;
    } > RAM
   
    
    ASSERT((CODE_RAM_ram_end - CODE_RAM_ram_start) == (CODE_RAM_rom_end - CODE_RAM_rom_start), "Copy Section CODE_RAM Size non-aligned")



    .DATA_RAM  : AT(DATA_RAM_rom_start) {
        
        . = ALIGN(4);
        DATA_RAM_ram_start = .;
        DATA_RAM_start = .;
        data_region_start = .;
        *(.data)
        *(.data*)
        data_region_end = .;
        
        DATA_RAM_end = .;
        DATA_RAM_ram_end = .;
    } > RAM
   
    
    ASSERT((DATA_RAM_ram_end - DATA_RAM_ram_start) == (DATA_RAM_rom_end - DATA_RAM_rom_start), "Copy Section DATA_RAM Size non-aligned")



    .DATA_RAM2  : AT(DATA_RAM2_rom_start) {
        
        . = ALIGN(4);
        DATA_RAM2_ram_start = .;
        DATA_RAM2_start = .;
        DATA_RAM2_end = .;
        DATA_RAM2_ram_end = .;
    } > RAM
   
    
    ASSERT((DATA_RAM2_ram_end - DATA_RAM2_ram_start) == (DATA_RAM2_rom_end - DATA_RAM2_rom_start), "Copy Section DATA_RAM2 Size non-aligned")



    .NamDE_RAM2  : AT(NamDE_RAM2_rom_start) {
        
        . = ALIGN(4);
        NamDE_RAM2_ram_start = .;
        NamDE_RAM2_start = .;
        NamDE_RAM2_end = .;
        NamDE_RAM2_ram_end = .;
    } > RAM
   
    
    ASSERT((NamDE_RAM2_ram_end - NamDE_RAM2_ram_start) == (NamDE_RAM2_rom_end - NamDE_RAM2_rom_start), "Copy Section NamDE_RAM2 Size non-aligned")



    .STACK  : {
        
        STACK_start = .;
        . += 1024;
        STACK_end = .;
    } > STACK
   
    


    SecurtBoot_memory_start = ORIGIN(SecurtBoot);
    SecurtBoot_memory_end = ORIGIN(SecurtBoot) + LENGTH(SecurtBoot);
    SecurtBoot_memory_size = LENGTH(SecurtBoot);
    Bootloader_memory_start = ORIGIN(Bootloader);
    Bootloader_memory_end = ORIGIN(Bootloader) + LENGTH(Bootloader);
    Bootloader_memory_size = LENGTH(Bootloader);
    BootFlash_Storage_memory_start = ORIGIN(BootFlash_Storage);
    BootFlash_Storage_memory_end = ORIGIN(BootFlash_Storage) + LENGTH(BootFlash_Storage);
    BootFlash_Storage_memory_size = LENGTH(BootFlash_Storage);
    AppBootInteract_memory_start = ORIGIN(AppBootInteract);
    AppBootInteract_memory_end = ORIGIN(AppBootInteract) + LENGTH(AppBootInteract);
    AppBootInteract_memory_size = LENGTH(AppBootInteract);
    ApplHeader_memory_start = ORIGIN(ApplHeader);
    ApplHeader_memory_end = ORIGIN(ApplHeader) + LENGTH(ApplHeader);
    ApplHeader_memory_size = LENGTH(ApplHeader);
    Appl_IVT_memory_start = ORIGIN(Appl_IVT);
    Appl_IVT_memory_end = ORIGIN(Appl_IVT) + LENGTH(Appl_IVT);
    Appl_IVT_memory_size = LENGTH(Appl_IVT);
    BootAppInteract_memory_start = ORIGIN(BootAppInteract);
    BootAppInteract_memory_end = ORIGIN(BootAppInteract) + LENGTH(BootAppInteract);
    BootAppInteract_memory_size = LENGTH(BootAppInteract);
    AppFlash_Storage_memory_start = ORIGIN(AppFlash_Storage);
    AppFlash_Storage_memory_end = ORIGIN(AppFlash_Storage) + LENGTH(AppFlash_Storage);
    AppFlash_Storage_memory_size = LENGTH(AppFlash_Storage);
    App1_memory_start = ORIGIN(App1);
    App1_memory_end = ORIGIN(App1) + LENGTH(App1);
    App1_memory_size = LENGTH(App1);
    BVT1_memory_start = ORIGIN(BVT1);
    BVT1_memory_end = ORIGIN(BVT1) + LENGTH(BVT1);
    BVT1_memory_size = LENGTH(BVT1);
    App2_memory_start = ORIGIN(App2);
    App2_memory_end = ORIGIN(App2) + LENGTH(App2);
    App2_memory_size = LENGTH(App2);
    BVT2_memory_start = ORIGIN(BVT2);
    BVT2_memory_end = ORIGIN(BVT2) + LENGTH(BVT2);
    BVT2_memory_size = LENGTH(BVT2);
    App3_memory_start = ORIGIN(App3);
    App3_memory_end = ORIGIN(App3) + LENGTH(App3);
    App3_memory_size = LENGTH(App3);
    IVT_RAM_memory_start = ORIGIN(IVT_RAM);
    IVT_RAM_memory_end = ORIGIN(IVT_RAM) + LENGTH(IVT_RAM);
    IVT_RAM_memory_size = LENGTH(IVT_RAM);
    UserKAM_memory_start = ORIGIN(UserKAM);
    UserKAM_memory_end = ORIGIN(UserKAM) + LENGTH(UserKAM);
    UserKAM_memory_size = LENGTH(UserKAM);
    RAM_memory_start = ORIGIN(RAM);
    RAM_memory_end = ORIGIN(RAM) + LENGTH(RAM);
    RAM_memory_size = LENGTH(RAM);
    STACK_memory_start = ORIGIN(STACK);
    STACK_memory_end = ORIGIN(STACK) + LENGTH(STACK);
    STACK_memory_size = LENGTH(STACK);
}