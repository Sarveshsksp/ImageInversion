#include "xaxidma.h"
#include "xparameters.h"
#include "sleep.h"
#include "xil_cache.h"
#include <stdio.h>
#include "xil_types.h"
#include "imgdata.h" // Include imgdata.h that contains imgdata array
#include "imgdata2.h" // File created for writing the processed data array

#define imageSize (512 * 512)

u32 checkHalted(u32 baseAddress, u32 offset);

int main() {


	u32 status;

    // Dma config
    XAxiDma_Config *myDmaConfig;
    XAxiDma myDma;

    myDmaConfig = XAxiDma_LookupConfigBaseAddr(XPAR_AXI_DMA_0_BASEADDR);
    status = XAxiDma_CfgInitialize(&myDma, myDmaConfig);
    if (status != XST_SUCCESS) {
        printf("DMA initialization failed\n");
        return -1;
    }

    Xil_DCacheFlush();

    

    status = XAxiDma_SimpleTransfer(&myDma, (u32)imgdata2, imageSize, XAXIDMA_DEVICE_TO_DMA);
    if (status != XST_SUCCESS) {
        printf("DMA initialization failed\n");
        return -1;
    }


    status = XAxiDma_SimpleTransfer(&myDma, (u32)imgdata, imageSize, XAXIDMA_DMA_TO_DEVICE);
    if (status != XST_SUCCESS) {
        printf("DMA initialization failed\n");
        return -1;
    }

    status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x4);
    while (status != 1) {
        status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x4);
    }
    status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x34);
    while (status != 1) {
        status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x34);
    }
    printf("DMA transfer success..\n");
  
  // Reading/Displaying the processed data from the imgdata2 file
  
	for(u32 i=0; i<262144; i++){
		if( imgdata2[i] < 16)
		{xil_printf("0%x ",imgdata2[i]);}
		else
		{xil_printf("%x ",imgdata2[i]);}

	}

}

u32 checkHalted(u32 baseAddress, u32 offset) {
    u32 status;
    status = (XAxiDma_ReadReg(baseAddress, offset)) & XAXIDMA_HALTED_MASK;
    return status;
}
