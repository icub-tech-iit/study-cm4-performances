# STM32 Performance Comparison of CM4 cores
This repository explores the performance of the CM4 cores in STM32G474 and STM32H745 microcontrollers (MCUs) used for motor control in our robots.



## The Challenge

We encountered an unexpected issue. Our existing FOC motor control code, which performs single-precision floating-point operations, ran poorly when transferred from the `amcblcd` board (using a 168 MHz STM32G474 CM4 core) to the `amc` board (equipped with a 200 MHz STM32H745 CM4 core). The latter after compensation of different clock speed has an execution time increase of about 10%. This surprised us!



## Code Details

Generated from a MATLAB model, the code relies heavily on floating point calculation calculations, which are executed within an interrupt handler (a special code section) triggered upon completion of DMA data transfer.



## Investigating the Issue

To understand the cause of the performance difference, we conducted a series of comparative tests on our custom boards, which include additional hardware and complex software like a multithreaded operating system.

The initial tests focused on measuring the execution time of the original motor control code. We later expanded the scope to include more general single-precision math code.



## Sharing and Collaboration

To share our findings and gain insights from the community, we ported the general tests to development boards from STMicroelectronics featuring the same MCUs as our robot boards.



## Repository Breakdown

- The `docs` folder contains the [results](./docs/performances.md) we measured on both boards.
- The `code` folder contains [instructions](./code/how-to-run-tests.md) on integrating our code with the official ST code available online for these MCUs. 



## Community Input Wanted

If you have information about the supposed lower performance of the H7-CM4 compared to the G4, suggestions for improving execution on the H7-CM4, or notice any potential issues in our testing approach, please don't hesitate to contact Marco Accame at marco.accame@iit.it.



