
#define PRU_LOCK_OFFSET    0x480CA800  //head (moved by PRU)
#define ARM_LOCK_OFFSET    0x480CA804  //tail (moved by ARM)
#define STAT_LOCK_OFFSET   0x480CA808  //memory modified by PRU, read by ARM

#define SHBUF_SIZE          0x10000

#define SHBUF0_START        (0x90000000)
#define SHBUF1_START        (SHBUF0_START + SHBUF_SIZE)
#define SHBUF2_START        (SHBUF1_START + SHBUF_SIZE)
#define SHBUF3_START        (SHBUF2_START + SHBUF_SIZE)
#define SHBUF4_START        (SHBUF3_START + SHBUF_SIZE)

#define SHBUF_CTRL_BLOCK    (SHBUF4_START + SHBUF_SIZE)
#define SHBUF_TOTAL_BUFS    0x5

#define BYTES_PER_DWORD     4


