# study-cm4-performances
This repository hosts a study that compares the performance of the CM4 cores of STM32G474 and STM32H745 that we use for the motor control in our robots.

## Details

We started this study because the same FOC motor control code that we run on the board `amcblcd` that hosts a  STM32G474 clocked @ 168 MHz performed poorly when moved to the `amc` board on the CM4 core of its STM32H745 clocked @ 200 MHz (the CM7 is clocked @ 400 MHz).

The code is generated from a MATLAB model and contains some floating point operations at single precision (sine, cosine, multiplications, ...) and is executed inside an IRQ handler of end of DMA transfer.

We were surprised by the poor performance of the CM4 core of the STM32G474 and we did a lot of comparative tests.

The tests obviously were run on our own boards with their own HW peripheral and so with a complex software embedded environment that could give support to HW and also host a complex multithreaded RTOS application.

The test were initially done to measure execution time of the original FOC motor control code that we generated from MATLAB model but soon we moved to more general single precision math code.

We later moved the more general tests to run on ST development boards with the same MPUs we have on our `amcbldc` and `amc` boards for the sake of sharing the information we have found out and ask suggestions to the community.

So, we have these sections:

- folder `docs` contains the [results](./docs/performances.md) we have measured on the two boards;
- folder code contains [instructions](./code/how-to-run-tests.md) about how to add our code inside official ST code available on Github for those MPUs. 



If anybody has information about the supposed worse performance of the H7 Vs the G4 or has suggestions about how to improve execution performance of the H7 or also if anybody can spot something wrong in our tests:

- please contact myself: marco.accame@iit.it

