[Defines]
  PLATFORM_NAME           = UefiResearch1
  PLATFORM_GUID           = DEADBEEF-1234-5678-9ABC-DEF012345678
  PLATFORM_VERSION        = 0.1
  DSC_SPECIFICATION       = 0x00010005
  OUTPUT_DIRECTORY        = Build/UefiResearch1
  SUPPORTED_ARCHITECTURES = X64
  BUILD_TARGETS           = RELEASE
  SKUID_IDENTIFIER        = DEFAULT

[LibraryClasses]
  UefiLib                       | MdePkg/Library/UefiLib/UefiLib.inf
  PrintLib                      | MdePkg/Library/BasePrintLib/BasePrintLib.inf
  PcdLib                        | MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  MemoryAllocationLib           | MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  DebugLib                      | MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
  BaseMemoryLib                 | MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  BaseLib                       | MdePkg/Library/BaseLib/BaseLib.inf
  UefiBootServicesTableLib      | MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  DevicePathLib                 | MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiRuntimeServicesTableLib   | MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  RegisterFilterLib             | MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
  BaseDebugPrintErrorLevelLib   | MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  DebugPrintErrorLevelLib       | MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  UefiApplicationEntryPoint     | MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  StackCheckLib                 | MdePkg/Library/StackCheckLibNull/StackCheckLibNull.inf


[Packages]
  MdePkg/MdePkg.dec

[Components]
  UefiResearch1/UefiResearch1.inf
