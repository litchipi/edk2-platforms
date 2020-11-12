/** @file

  Copyright (c) 2020, Linaro Ltd. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef OPTEE_RPMB_FVB_H_
#define OPTEE_RPMB_FVB_H_

/**
 Those are not currently defined in any spec, it's an internal
 contract between OP-TEE and EDK2.
 For more details check core/arch/arm/include/kernel/stmm_sp.h in OP-TEE
**/
#define SP_SVC_RPMB_READ_64             0xC4000066
#define SP_SVC_RPMB_WRITE_64            0xC4000067

#define SP_SVC_RPMB_READ_32             0x84000066
#define SP_SVC_RPMB_WRITE_32            0x84000067

#ifdef MDE_CPU_AARCH64
#define SP_SVC_RPMB_READ                SP_SVC_RPMB_READ_64
#define SP_SVC_RPMB_WRITE               SP_SVC_RPMB_WRITE_64
#endif
#ifdef MDE_CPU_ARM
#define SP_SVC_RPMB_READ                SP_SVC_RPMB_READ_32
#define SP_SVC_RPMB_WRITE               SP_SVC_RPMB_WRITE_32
#endif

#define FLASH_SIGNATURE            SIGNATURE_32('r', 'p', 'm', 'b')
#define INSTANCE_FROM_FVB_THIS(a)  CR(a, MEM_INSTANCE, FvbProtocol, \
                                      FLASH_SIGNATURE)

typedef struct _MEM_INSTANCE         MEM_INSTANCE;
typedef EFI_STATUS (*MEM_INITIALIZE) (MEM_INSTANCE* Instance);

/**
  This struct is used by the RPMB driver. Since the upper EDK2 layers
  expect byte addressable memory, we allocate a memory area of certain
  size and sync it to the hardware on reads/writes.

  @param[in] Signature        Internal signature used to discover the instance
  @param[in] Initialize       Function used to initialize the instance
  @param[in] Initialized      Set to true if initialized
  @param[in] FvbProtocol      FVB protocol of the instance
  @param[in] Handle           Handle to install
  @param[in] MemBaseAddress   Physical address of the beggining of the allocated memory
  @param[in] BlockSize        Blocksize
  @param[in] NBlocks          Number of allocated blocks
**/
struct _MEM_INSTANCE
{
    UINT32                              Signature;
    MEM_INITIALIZE                      Initialize;
    BOOLEAN                             Initialized;
    EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL  FvbProtocol;
    EFI_HANDLE                          Handle;
    EFI_PHYSICAL_ADDRESS                MemBaseAddress;
    UINT16                              BlockSize;
    UINT16                              NBlocks;
};

#endif
