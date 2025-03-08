#include <efi.h>
#include <efilib.h>
#include "../include/fs.h"  // For potential filesystem interactions

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    
    Print(L"Bootloader: Initializing...\n");

    // Get Loaded Image Protocol
    EFI_LOADED_IMAGE *LoadedImage;
    EFI_GUID LoadedImageProtocol = LOADED_IMAGE_PROTOCOL;
    EFI_STATUS Status = SystemTable->BootServices->HandleProtocol(
        ImageHandle, &LoadedImageProtocol, (void **)&LoadedImage);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Unable to get LoadedImageProtocol!\n");
        return Status;
    }

    // Get Simple File System Protocol
    EFI_GUID FileSystemProtocol = SIMPLE_FILE_SYSTEM_PROTOCOL;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    Status = SystemTable->BootServices->HandleProtocol(
        LoadedImage->DeviceHandle, &FileSystemProtocol, (void **)&FileSystem);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Unable to locate Simple File System Protocol!\n");
        return Status;
    }

    // Open the root directory
    EFI_FILE_PROTOCOL *Root;
    Status = FileSystem->OpenVolume(FileSystem, &Root);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Unable to open root volume!\n");
        return Status;
    }

    // Open the kernel file (e.g., kernel.elf)
    EFI_FILE_PROTOCOL *Kernel;
    Status = Root->Open(Root, &Kernel, L"kernel.elf", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Kernel file not found!\n");
        return Status;
    }
    
    // Get kernel file size
    EFI_FILE_INFO *FileInfo;
    UINTN FileInfoSize = sizeof(EFI_FILE_INFO) + 200;
    Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void **)&FileInfo);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Memory allocation for file info failed!\n");
        Kernel->Close(Kernel);
        return Status;
    }
    Status = Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, FileInfo);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Unable to get kernel file info!\n");
        SystemTable->BootServices->FreePool(FileInfo);
        Kernel->Close(Kernel);
        return Status;
    }
    UINTN KernelSize = FileInfo->FileSize;
    SystemTable->BootServices->FreePool(FileInfo);

    // Allocate memory for the kernel
    void *KernelBuffer;
    Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, KernelSize, &KernelBuffer);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Memory allocation for kernel failed!\n");
        Kernel->Close(Kernel);
        return Status;
    }

    // Read kernel into memory
    Status = Kernel->Read(Kernel, &KernelSize, KernelBuffer);
    Kernel->Close(Kernel);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Unable to read kernel file!\n");
        SystemTable->BootServices->FreePool(KernelBuffer);
        return Status;
    }
    Print(L"Kernel loaded successfully.\n");

    // Exit Boot Services
    UINTN MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
    UINTN MapKey, DescriptorSize;
    UINT32 DescriptorVersion;

    // Get the memory map size
    Status = SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (Status != EFI_BUFFER_TOO_SMALL) {
        Print(L"Error: Unable to get memory map size!\n");
        SystemTable->BootServices->FreePool(KernelBuffer);
        return Status;
    }

    // Allocate memory for the memory map
    Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, MemoryMapSize, (void **)&MemoryMap);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Memory allocation for memory map failed!\n");
        SystemTable->BootServices->FreePool(KernelBuffer);
        return Status;
    }

    // Get the memory map
    Status = SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Unable to get memory map!\n");
        SystemTable->BootServices->FreePool(MemoryMap);
        SystemTable->BootServices->FreePool(KernelBuffer);
        return Status;
    }

    // Exit boot services
    Status = SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);
    if (EFI_ERROR(Status)) {
        Print(L"Error: Failed to exit boot services!\n");
        SystemTable->BootServices->FreePool(MemoryMap);
        SystemTable->BootServices->FreePool(KernelBuffer);
        return Status;
    }

    // Jump to the kernel entry point
    void (*KernelEntry)() = (void (*)())KernelBuffer;
    KernelEntry();

    return EFI_SUCCESS;
}       