# ---------------------------------------------------
# mkfiles/am9511.mak  Ver 11.03.13d  
# Serial No. 2011-1042-654321    All Rights Reserved.
# Copyright (C) 2011 Douglas Goodall,  United States.
# ---------------------------------------------------
# mkfiles/am9511.mak autogenerated by asmall.cpp 
# Sun Mar 13 03:45:54 PDT 2011
# Copyright (c)2011 Douglas Goodall. Rights Reserved.

AS = ../assemble

INCFILES  = assemble.inc banner.inc cpm80.inc incl1.inc incl2.inc incl3.inc 

am9511.hex:	am9511.asm $(INCFILES) $(AS) 
	$(AS) am9511 

clean:
	rm -f *.bin  *.lst *.log *.hex

# eof - mkfiles/am9511.mak
