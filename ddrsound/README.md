# DDRSound

This demo takes the wav parser and player and has it store and read the wav data from ddr memory.  We are using an 8bit interface, but it might make sense to use a 16bit interface. 

The DDR code requires that you present an address to the controller, and then wait for it to return a signal saying that the byte is available.  This makes the state machine in the wav player a little more complicated.  Also, writing data is a bit more complicated, because we need to use the ioctl_wait to tell the HPS to wait until the ddr system has written the data.

The wav_wr (we) line doesn't want to stay high. It needs to be high to start, and then can't go high until wav_data_ready. Basically,
it needs to be high for one clock, then low while we wait for the ddr system to tell us the ram is ready to take another write.


