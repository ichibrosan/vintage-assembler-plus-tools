# ---------------------------------------------------
# mkfiles/testlrad.mak  Ver 11.03.25l  
# Serial No. 2011-1042-654321    All Rights Reserved.
# Copyright (C) 2011 Douglas Goodall,  United States.
# ---------------------------------------------------
# mkfiles/testlrad.mak autogenerated by asmall.cpp 
# Fri Mar 25 11:27:59 PDT 2011
# Copyright (c)2011 Douglas Goodall. Rights Reserved.

AS = ../assemble

INCFILES  = assemble.inc banner.inc cpm80.inc gplstuff.inc incl1.inc incl2.inc incl3.inc 

testlrad.hex:	testlrad.asm $(INCFILES) $(AS) 
	$(AS) testlrad 

clean:
	rm -f *.bin  *.lst *.log *.hex

# eof - mkfiles/testlrad.mak
