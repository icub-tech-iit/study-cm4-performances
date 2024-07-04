# Performances
We have measured the execution speed of some pieces of code on the CM4 cores of two development boards, the [STM32G474E-EVAL](https://www.st.com/en/evaluation-tools/stm32g474e-eval.html) and the [STM32H745I-DISCO](https://www.st.com/en/evaluation-tools/stm32h745i-disco.html) and we have observed that they differ.

After compensation of the different clock speed (the former is 170 MHz and the latter 200 MHz) we have observed that the CM4 on the STM32G4745E-EVAL is more performant of up to 10%.

## The tests

The tests we run use math operations with random access to RAM. We have kept the original settings of template projects provided by ST and used the armclang compiler version 6.19 with -Ospeed optimization.



It is possible to re run the tests by following the document in [here](../code/how-to-run-tests.md).



## The results

The following tables reports comparisons of execution time of the selected tests on two different CM4 targets (G4 and H7) with FLASH and RAM execution. 

### The measures

To provide a fair comparison between the two different max clock speeds (170 MHz and 200 MHz) we also show the case of the G4 with a compensation factor of 200/170 = 0.85 as if the G4 executed at 200 MHz. We also run the CM4 of the H7 at the same 170 MHz speed as the G4.

| CM4 Target | Clock speed | Execution on | Compensation   | TEST1 [us] | TEST2 [us] | TEST3 [us] |
| ---------- | ----------- | ------------ | -------------- | ---------- | ---------- | ---------- |
| G4         | 170 MHz     | FLASH        | none           | 1370       | 2106       | 110        |
| G4         | 170 MHz     | FLASH        | 170/200 = 0.85 | 1164       | 1790       | 93         |
| H7         | 200 MHz     | FLASH        | N/A            | 1287       | 1970       | 98         |
| H7         | 200 MHz     | RAM          | N/A            | 1288       | 1969       | 98         |
| H7         | 170 MHz     | FLASH        | none           | 1510       | 2320       | 115        |

**Table 1**. The columns contains results for different code tests all optimized at `-Ospeed` and run on two different CM4 cores. The RAM execution on H7 does not improve speeds vs its FLASH execution. 



### The analysis



From **Table 1** we see that the CM4 core of the H7 @ 200 MHz executes floating point computations slower (it takes more execution time) than the G4 with clock speed compensation.

As the clock speed compensation done byy applying a suitable gain factor may arouse doubts, we repeated the comparison using the same speed for both cores.

In both case we achieved the same effect: the CM4 core on the H7 executes floating point computations slower. 



Following table contains the comparison of the above two cases for the three tests. We report the increment of execution time of the slower $T_2$ vs the faster $T_1$, where $ T_2 > T_1 $  in this way:

$$ increment = {100 * (T_2 - T_1) \over T_1} $$



| CM4 Target                           | Increment  [%]     |                    |                  |
| ------------------------------------ | ------------------ | ------------------ | ---------------- |
|                                      | **TEST1**          | **TEST2**          | **TEST2**        |
|                                      |                    |                    |                  |
| H7 FLASH @ 200 MHz vs G4 compensated | +10.56% of 1164 us | +10% of 1790 us    | +5.37% of 93 us  |
| H7 FLASH @ 170 MHz vs G4 @ 170 MHz   | +10.22% of 1370 us | +10.16% of 2106 us | +4.54% of 110 us |

**Table 2**. It reports the increment in execution time of the CM4 core running on the H7 vs the faster CM4 on G4. In this table a positive increment (+10%) means that the H7-CM4 core executes slower a test (it takes 10% more time to execute) than the CM4 on STM32G4.

