# ---------------------------------------------------
# ascii.mak    v19.04.28i for x86_64-apple-darwin18
# Serial No. 2019-0501-654321                        
# Copyright (C) 2019 Douglas Goodall,  United States.
# ---------------------------------------------------
# ascii.mak autogenerated by makemake.cpp 
# Sun Apr 28 08:17:38 PDT 2019

CC = g++
CCFLAGS = -w
INCLUDES = asdecz80.hpp globdata.hpp asdec65.hpp asdefs.hpp asdec68k.hpp asdecdir.hpp asymbols.hpp srcclass.hpp environ.hpp asmultip.hpp bcctrace.hpp asouthex.hpp portab.hpp asoutlst.hpp asomfgen.hpp inibind.hpp cpostfix.hpp dirclass.hpp asprint.hpp includes.hpp asoutwrn.hpp ascalc.hpp asdec20.hpp cbindefs.hpp strupr.hpp pcascii.hpp asdec85.hpp asresolv.hpp strlwr.hpp memory.hpp asparse.hpp defaults.hpp asparse2.hpp aseval.hpp dwgalloc.hpp asouterr.hpp asomfdef.hpp ashexout.hpp asdec80.hpp versbind.hpp 

ascii:	ascii.cpp $(INCLUDES) version.hpp 
	$(CC) $(CCFLAGS) ascii.cpp -o ascii

clean:
	rm -f ascii

# eof - ascii.mak