# Improvements
In here we report the improvements obtained by the received suggestions.

So far, the suggestion from by [STOne-32](https://community.st.com/t5/user/viewprofilepage/user-id/465) enabled a significant improvements on all the three tests. Now TEST3 runs the same on both cores, TEST2 is worse on H7 of a small 1.5% and the TEST1 dropped from 10% down to 5%. 








## The first improvement

After a suggestion by [STOne-32](https://community.st.com/t5/user/viewprofilepage/user-id/465) we have observed some improvements.

As suggested, I tested execution of the program in RAM but using two different SRAM banks: SRAM1@1000_0000 contains all RO (code and constants) and SRAM2 @3002_0000 contains all RW data (stack, heap, global variables).

In here the used scatter file.

```assembly
LR_ROM1 0x10000000 0x00020000  {    ; load region size_region
  ER_ROM1 0x10000000 0x00020000  {  ; load address = execution address
   *.o (RESET, +First)
   *(InRoot$$Sections)
   .ANY (+RO)
   .ANY (+XO)
  }
  RW_IRAM2 0x30020000 0x00020000  {  ; RW data
   .ANY (+RW +ZI)
  }
}
```

**Code Listing**. The scatter file for the H7-CM4 places all RO + startup in SRAM1 and all RW in SRAM2. The generated binary is then linked to the binary of the H7-CM7 that at startup will place everything in the two banks for the use of the CM4.

In here are the updated results and comparisons vs G4.

| CM4 Target | Clock speed | Execution on                                        | Compensation   | TEST1 [us] | TEST2 [us] | TEST3 [us] |
| ---------- | ----------- | --------------------------------------------------- | -------------- | ---------- | ---------- | ---------- |
| G4         | 170 MHz     | FLASH                                               | none           | 1370       | 2106       | 110        |
| G4         | 170 MHz     | FLASH                                               | 170/200 = 0.85 | 1164       | 1790       | 93         |
| H7         | 200 MHz     | FLASH                                               | N/A            | 1287       | 1970       | 98         |
| H7         | 200 MHz     | RAM                                                 | N/A            | 1288       | 1969       | 98         |
| H7         | 170 MHz     | FLASH                                               | none           | 1510       | 2320       | 115        |
| H7         | 200 MHz     | RAM (RO on SRAM1@1000_0000, RW on SRAM2 @3002_0000) | none           | 1222       | 1817       | 93         |

**Table 1**. The columns contains results for different code tests all optimized at `-Ospeed` and run on two different CM4 cores. The RAM execution on H7 does not improve speeds vs its FLASH execution. It actually improves if we use two different banks for RO and RW.



| CM4 Target                                 | Increment  [%]     |                  |                    |
| ------------------------------------------ | ------------------ | ---------------- | ------------------ |
|                                            | **TEST1**          | **TEST2**        | **TEST2**          |
|                                            |                    |                  |                    |
| H7 FLASH @ 200 MHz vs G4 compensated       | +10.56% of 1164 us | +10% of 1790 us  | +5.37% of 93 us    |
| H7 SRAM1-SRAM2 @ 200 MHz vs G4 compensated | +5% of 1164 us     | +1.5% of 1790 us | ***no increment*** |

**Table 2**. It reports the increment in execution time of the CM4 core running on the H7 vs the faster CM4 on G4, where $$increment = {100 * (T_2 - T_1) \over T_1}$$. In this table a positive increment (+10%) means that the H7-CM4 core executes slower a test (it takes 10% more time to execute) than the CM4 on STM32G4.