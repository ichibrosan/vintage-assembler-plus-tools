// $Log: makemake.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// makemake.cpp 24-Feb-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// ---------------------------------------------------
// This file is part of Vintage Modern Assembler Plus Tools.
//
// VMAPT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// VMAPT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with VMAPT.  If not, see <http://www.gnu.org/licenses/>.

static char szMakemakeCpp[] = "$Id: makemake.cpp,v 1.3 2011/04/14 15:13:09 doug Exp doug $";

//
// 2/8/2011 dwg - best version ever. All .hpp files 
// are considered dependencies except for version.hpp
// which is not a dependency for makevers.cpp
// Individual Makefile are generated as a safety measure


//#define __TRACE

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define DIRCLASS
#include "includes.hpp"

//#define SHOW_NAMLEN
//#define SHOW_TYPE

/*
 * The dirent structure defines the format of directory entries.
 *
 * A directory entry has a struct dirent at the front of it, containing its
 * inode number, the length of the entry, and the length of the name
 * contained in the entry.  These are followed by the name padded to a 4
 * byte boundary with null g_ucBytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN when 32-bit
 * ino_t is in effect; (MAXPATHLEN - 1) when 64-bit ino_t is in effect.
 */

//#define __DARWIN_MAXPATHLEN	1024

//#define __DARWIN_STRUCT_DIRENTRY { \
//	__uint64_t  d_ino;      /* file number of entry */ \
//	__uint64_t  d_seekoff;  /* seek offset (optional, used by servers) */ \
//	__uint16_t  d_reclen;   /* length of this record */ \
//	__uint16_t  d_namlen;   /* length of string in d_name */ \
//	__uint8_t   d_type;     /* file type, see below */ \
//	char      d_name[__DARWIN_MAXPATHLEN]; 
//} dirent;

//#define	MAXNAMLEN	__DARWIN_MAXNAMLEN

//*
//* File types
//*
//#define	DT_UNKNOWN	 0
//#define	DT_FIFO		 1
//#define	DT_CHR		 2
//#define	DT_DIR		 4
//#define	DT_BLK		 6
//#define	DT_REG		 8
//#define	DT_LNK		10
//#define	DT_SOCK		12
//#define	DT_WHT		14

char szInsBuffer[8192];
char szBinBuffer[1024];
char szHppBuffer[1023];
char szCppBuffer[1024];
char szCommon[4096];
char sz8080[4096];
char sz8085[4096];
char sz6502[4096];
char sz68000[4096];
char szZ80[4096];
char sz1620[4096];

int getdate(char * szTimeDate)
{
	char szLocal[64];
	system("date > date.tmp");
	FILE * fd = fopen("date.tmp","r");
	if(NULL == fd) {
		printf("Sorry, could not open date.tmp for input\n");
		exit(EXIT_FAILURE);
	}
	fgets(szLocal,sizeof(szLocal),fd);
	fclose(fd);
	system("rm -f date.tmp");
	strcpy(szTimeDate,szLocal);
	return EXIT_SUCCESS;
}

int makemak(char *szFilename,FILE *mfp,char *uid,char *machtype)
{
  char szMkFileName[128];
  char szSrcFileName[128];
  char szTgtFileName[128];
  char szTimeDate[128];
  char g_szBuffer2[128];

  strcpy(szMkFileName,szFilename);
  szMkFileName[strlen(szMkFileName)-4] = 0;
  strcat(szMkFileName,".mak");

  strcpy(szSrcFileName,szFilename);
  szSrcFileName[strlen(szSrcFileName)-4] = 0;
  strcat(szSrcFileName,".cpp");

  strcpy(szTgtFileName,szFilename);
  szTgtFileName[strlen(szTgtFileName)-4] = 0;

  FILE * fp = fopen(szMkFileName,"w");
  if(NULL == fp) {
    printf("Error: cannot open %s for output\n",szMkFileName);
    return(EXIT_FAILURE);
  }

  getdate(szTimeDate);
  char szProg[128];
  strcpy(szProg,szMkFileName);
  while(12 > strlen(szProg)) {
    strcat(szProg," ");
  }

  fprintf(fp,"# ---------------------------------------------------\n");
  fprintf(fp,"# %s v%2d.%02d.%02d%c for %s\n",
	  szProg,RMJ,RMN,RUP,'a'+RTP,machtype);
  fprintf(fp,"# Serial No. 20%2d-%04d-654321                        \n",
	RMJ,atoi(uid));
  fprintf(fp,"# Copyright (C) 20%d Douglas Goodall,  United States.\n",
	RMJ);
  fprintf(fp,"# ---------------------------------------------------\n");

  fprintf(fp,"# %s autogenerated by makemake.cpp \n# %s\n",
	  szMkFileName,szTimeDate);
  fprintf(fp,"CC = g++\n");
  fprintf(fp,"CCFLAGS = -w");

  // 04/28/2019 dwg - 
  fprintf(fp,"INSTBIN = ~/src/framewk/bin");

#ifdef __TRACE
  fprintf(fp," -D__TRACE ");
#endif
#ifdef __WARN
  fprintf(fp," -D__WARN ");
#endif
  fprintf(fp,"\n");
  fprintf(fp,"INCLUDES = %s\n",szHppBuffer);
  fprintf(fp,"\n");
  fprintf(fp,"%s:\t%s $(INCLUDES) ",szTgtFileName,szSrcFileName);
  if(0 != strcmp("makevers.cpp",szSrcFileName)) {
    fprintf(fp,"version.hpp ");
  }
  fprintf(fp,"\n");
  fprintf(fp,"\t$(CC) $(CCFLAGS) %s -o %s\n",szSrcFileName,szTgtFileName);
  if(0 == strcmp("asmall.cpp",szSrcFileName)) {
    fprintf(fp,"\t$(QUIET)cp asmall astests\n");
    fprintf(fp,"\t$(QUIET)cp asmall aserrors\n");
  }
  if(0 == strcmp("editall.cpp",szSrcFileName)) {
    fprintf(fp,"\t$(QUIET)cp editall astests\n");
    fprintf(fp,"\t$(QUIET)cp editall ascommon\n");
    fprintf(fp,"\t$(QUIET)cp editall as8085\n");
    fprintf(fp,"\t$(QUIET)cp editall as68000\n");
    fprintf(fp,"\t$(QUIET)cp editall as8080\n");
    fprintf(fp,"\t$(QUIET)cp editall as6502\n");
    fprintf(fp,"\t$(QUIET)cp editall asz80\n");
    fprintf(fp,"\t$(QUIET)cp editall as1620\n");
    fprintf(fp,"\t$(QUIET)cp editall doc\n");
  }
  
  fprintf(fp,"\n");
  fprintf(fp,"clean:\n");
  fprintf(fp,"\trm -f %s\n",szTgtFileName);
  fprintf(fp,"\n");
  fprintf(fp,"# eof - %s\n",szMkFileName);
  fclose(fp);

  return(EXIT_SUCCESS);
}



int main(int argc,char **argv)
{
  Version(argv[0]);

  char szMkFileName[128];
  char szSrcFileName[128];
  char szTgtFileName[128];
  char szTimeDate[128];

  TRACE("clearing buffers");
  memset(szInsBuffer,0,sizeof(szInsBuffer));  
  memset(szBinBuffer,0,sizeof(szBinBuffer));
  memset(szHppBuffer,0,sizeof(szHppBuffer));
  memset(szCppBuffer,0,sizeof(szCppBuffer));
  memset(sz8085,0,sizeof(sz8085));
  memset(sz6502,0,sizeof(sz6502));
  memset(sz68000,0,sizeof(sz68000));
  memset(sz8080,0,sizeof(sz8080));
  memset(szZ80,0,sizeof(szZ80));
  memset(sz1620,0,sizeof(sz1620));

// This works on Msc OS X
//char g_szBuffer2[__DARWIN_MAXPATHLEN];

  // This works anywhere
  char g_szBuffer2[4096];

  TRACE("starting dir1 - ./*.cpp");
  CDir *  dir1 = new CDir(".");
  if(NULL == dir1) {
    printf("Sorry, cannot instanciate dir1\n");
    exit(EXIT_FAILURE);
  }
  int rc1 = dir1->read();
  while(EXIT_SUCCESS == rc1) {
    dir1->getname(g_szBuffer2);
    if(DT_REG == dir1->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
	if(0 == strcmp(".cpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {

	  // trim off the file extension to create binary name
	  strcpy(szTgtFileName,g_szBuffer2);
	  szTgtFileName[strlen(szTgtFileName)-4] = 0;

	  // collect the names of the target binaries
	  strcat(szBinBuffer,szTgtFileName);
	  strcat(szBinBuffer," ");

	  // collect the names of the installed binaries
	  strcat(szInsBuffer,"~/bin/");
	  strcat(szInsBuffer,szTgtFileName);
	  strcat(szInsBuffer," ");

	  // collect the names of the source files
	  strcat(szCppBuffer,g_szBuffer2);
	  strcat(szCppBuffer," ");
	}
      }
    }
    rc1 = dir1->read();
  }
  delete dir1;

  TRACE("starting dir2 - ./*.hpp");
  CDir *  dir2 = new CDir(".");
  if(NULL == dir2) {
    printf("Sorry, cannot instanciate dir2\n");
    exit(EXIT_FAILURE);
  }
  int rc2 = dir2->read();
  while(EXIT_SUCCESS == rc2) {
    dir2->getname(g_szBuffer2);
    if(DT_REG == dir2->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
	  if(0 != strcmp("version.hpp",g_szBuffer2)) {
            strcat(szHppBuffer,g_szBuffer2);
            strcat(szHppBuffer," ");
	  }
        }
      }
    }
    rc2 = dir2->read();
  }
  delete dir2;


  TRACE("starting dir3 - ascommon/*.hpp");
  CDir *  dir3 = new CDir("ascommon");
  if(NULL == dir3) {
    printf("Sorry, cannot instanciate dir3\n");
    exit(EXIT_FAILURE);
  }
  int rc3 = dir3->read();
  while(EXIT_SUCCESS == rc3) {
    dir3->getname(g_szBuffer2);
    if(DT_REG == dir3->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(szCommon,"ascommon/");
	  strcat(szCommon,g_szBuffer2);
          strcat(szCommon," ");
        }
      }
    }
    rc3 = dir3->read();
  }
  delete dir3;

  TRACE("starting dir4 - as8080/*.hpp");
  CDir *  dir4 = new CDir("as8085");
  if(NULL == dir4) {
    printf("Sorry, cannot instanciate dir4\n");
    exit(EXIT_FAILURE);
  }
  int rc4 = dir4->read();
  while(EXIT_SUCCESS == rc4) {
    dir4->getname(g_szBuffer2);
    if(DT_REG == dir4->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(sz8085,"as8085/");
	  strcat(sz8085,g_szBuffer2);
          strcat(sz8085," ");
        }
      }
    }
    rc4 = dir4->read();
  }
  delete dir4;

  TRACE("starting dir5 - as6502/*.hpp");
  CDir *  dir5 = new CDir("as6502");
  if(NULL == dir5) {
    printf("Sorry, cannot instanciate dir5\n");
    exit(EXIT_FAILURE);
  }
  int rc5 = dir5->read();
  while(EXIT_SUCCESS == rc5) {
    dir5->getname(g_szBuffer2);
    if(DT_REG == dir5->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(sz6502,"as6502/");
          strcat(sz6502,g_szBuffer2);
          strcat(sz6502," ");
        }
      }
    }
    rc5 = dir5->read();
  }
  delete dir5;

  TRACE("starting dir7 - as68000/*.hpp");
  CDir *  dir7 = new CDir("as68000");
  if(NULL == dir7) {
    printf("Sorry, cannot instanciate dir7\n");
    exit(EXIT_FAILURE);
  }
  int rc7 = dir7->read();
  while(EXIT_SUCCESS == rc7) {
    dir7->getname(g_szBuffer2);
    if(DT_REG == dir7->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(sz68000,"as68000/");
          strcat(sz68000,g_szBuffer2);
          strcat(sz68000," ");
        }
      }
    }
    rc7 = dir7->read();
  }

  delete dir7;

  TRACE("starting dir8 - as8080/*.hpp");
  CDir *  dir8 = new CDir("as8080");
  if(NULL == dir8) {
    printf("Sorry, cannot instanciate dir8\n");
    exit(EXIT_FAILURE);
  }
  TRACE("doing dir8 initial read");
  int rc8 = dir8->read();
  TRACE("back from initial read");
  while(EXIT_SUCCESS == rc8) {
    dir8->getname(g_szBuffer2);
    TRACE("dir8 data is:");
    TRACE(g_szBuffer2);
    if(DT_REG == dir8->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(sz8080,"as8080/");
          strcat(sz8080,g_szBuffer2);
          strcat(sz8080," ");
        }
      }
    }
    rc8 = dir8->read();
  }
  delete dir8;
  TRACE("done with dir8");

  CDir *  dir9 = new CDir("asz80");
  if(NULL == dir9) {
    printf("Sorry, cannot instanciate dir9\n");
    exit(EXIT_FAILURE);
  }
  int rc9 = dir9->read();
  while(EXIT_SUCCESS == rc9) {
    dir9->getname(g_szBuffer2);
    if(DT_REG == dir9->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(szZ80,"asz80/");
          strcat(szZ80,g_szBuffer2);
          strcat(szZ80," ");
        }
      }
    }
    rc9 = dir9->read();
  }
  delete dir9;


  CDir *  dirx = new CDir("as1620");
  if(NULL == dirx) {
    printf("Sorry, cannot instanciate dirx\n");
    exit(EXIT_FAILURE);
  }
  int rcx = dirx->read();
  while(EXIT_SUCCESS == rcx) {
    dirx->getname(g_szBuffer2);
    if(DT_REG == dirx->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
          strcat(szZ80,"as1620/");
          strcat(szZ80,g_szBuffer2);
          strcat(szZ80," ");
        }
      }
    }
    rcx = dirx->read();
  }
  delete dirx;




  TRACE("opening Makefile");
  FILE * mfp = fopen("Makefile","w");
  if(NULL == mfp) {
    printf("Sorry, cannot open 'Makefile' for writing\n");
    exit(EXIT_FAILURE);
  }

  TRACE("writing banner");
  fprintf(mfp,"# ---------------------------------------------------\n");
  fprintf(mfp,"# Makefile  v%2d.%02d.%02d%c   for  %s\n",
          RMJ,RMN,RUP,'a'+RTP,version.getmachtype());
  fprintf(mfp,"# Serial No. 20%2d-%04d-654321 Licensed under GNU GPL.\n",
        RMJ,atoi(version.getuid()));
  fprintf(mfp,"# Copyright (C) 2011 Douglas Goodall,  United States.\n");
  fprintf(mfp,"# ---------------------------------------------------\n");

  fprintf(mfp,"# %s autogenerated by makemake.cpp \n# %s\n",
          szMkFileName,szTimeDate);

  TRACE("writing macros");
  fprintf(mfp,"QUIET    = @\n");
  fprintf(mfp,"MACHTYPE = %s\n",version.getmachtype());
  fprintf(mfp,"PWD      = %s\n",version.getpwd());
  fprintf(mfp,"OSTYPE   = %s\n",version.getostype());
  fprintf(mfp,"UID      = %s\n",version.getuid());
  fprintf(mfp,"USER     = %s\n",version.getuser());

  fprintf(mfp,"CC       = g++\n");
  fprintf(mfp,"CCFLAGS  = ");
  fprintf(mfp,"-w ");
  fprintf(mfp,"\n\n");
  fprintf(mfp,"SOURCES  = %s\n\n",szCppBuffer);
  fprintf(mfp,"INCLUDES = %s\n\n",szHppBuffer);
  fprintf(mfp,"BINARIES = %s\n\n",szBinBuffer);
  fprintf(mfp,"INSTBINS = %s\n\n",szInsBuffer);
  fprintf(mfp,"COMMON   = %s\n\n",szCommon);
  fprintf(mfp,"I8085    = %s\n\n",sz8085);
  fprintf(mfp,"R6502    = %s\n\n",sz6502);
  fprintf(mfp,"M68000   = %s\n\n",sz68000);
  fprintf(mfp,"I8080    = %s\n\n",sz8080);
  fprintf(mfp,"Z80      = %s\n\n",szZ80);
  fprintf(mfp,"I1620    = %s\n\n",sz1620);
  fprintf(mfp,"DEPENDS  = "
	      	"$(SOURCES) $(COMMON) "
		"$(I8085) $(I8080) $(M68000) $(R6502) $(Z80) $(I1620)\n\n");
  fprintf(mfp,"DECLS    = "
              "ascommon/decoincl.hpp "
              "as8080/decoincl.hpp "
              "as8085/decoincl.hpp "
              "as6502/decoincl.hpp "
              "asz80/decoincl.hpp "
	      "as1620/decoincl.hpp "
              "as68000/decoincl.hpp\n\n");

  TRACE("writing rules");
  fprintf(mfp,"all:\t$(BINARIES) GPATH ");
  fprintf(mfp,"\n\n");

  fprintf(mfp,"version.hpp:\tmakevers\n");
  fprintf(mfp,	"\t$(QUIET)./makevers\n\n");

  fprintf(mfp,"GPATH:\t$(DEPENDS)\n");
  fprintf(mfp,	"\t$(QUIET)gtags >gtags.log 2>gtags.log\n"
	      	"\t$(QUIET)htags >htags.log 2>htags.log\n\n");

  TRACE("starting dir6 - ./*.cpp");
  CDir *  dir6 = new CDir(".");
  if(NULL == dir6) {
    printf("Sorry, cannot instanciate dir6\n");
    exit(EXIT_FAILURE);
  }
  int rc6 = dir6->read();
  while(EXIT_SUCCESS == rc6) {
    dir6->getname(g_szBuffer2);
    if(DT_REG == dir6->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
	if(0 == strcmp(".cpp",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
	  TRACE("calling makemake()");
	  int rc6 = makemak(g_szBuffer2,mfp,
			version.getuid(),
			version.getmachtype());
	  if(EXIT_FAILURE == rc6) {
	    printf("Sorry, could not create .mak file for %s\n",g_szBuffer2);
	    printf("The 'Makefile' is not affected\n");
	  }

	  // directory scan yields source filenames
	  strcpy(szSrcFileName,g_szBuffer2);

	  TRACE("create root and target");
	  // chop off file extension to create root and target
          strcpy(szTgtFileName,g_szBuffer2);
          szTgtFileName[strlen(szTgtFileName)-4] = 0;
		
          TRACE("create backup makefile name");
	  // create backup makefile name
	  strcpy(szMkFileName,szTgtFileName);
	  strcat(szMkFileName,".mak");
	 
 	  TRACE("create build rule");
	  // create rule to build program and specify
	  // all hpp files in the directory as dependencies
  	  fprintf(mfp,"%s:\t%s $(INCLUDES) ",szTgtFileName,szSrcFileName);

	  // all targets except makevers.cpp get version.hpp
	  if(0 != strcmp("makevers.cpp",szSrcFileName)) {
	    fprintf(mfp,"version.hpp ");
	  }

	  TRACE("add makefile dependencies");
	  // add Makefile as dependency for all targets
	  fprintf(mfp,"Makefile ");

	  if(0 == strcmp("assemble.cpp",szSrcFileName)) {
	    fprintf(mfp,"$(DEPENDS) $(DECLS)\n");
	  } else {
	    fprintf(mfp,"\n");
	  }
	  // add clause to build the target  		
	  fprintf(mfp,"\t$(CC) $(CCFLAGS) %s ",szSrcFileName);
	  fprintf(mfp,"-o %s\n",szTgtFileName);
	  if(0 == strcmp("assemble.cpp",szSrcFileName)) {
	    fprintf(mfp,"\t$(QUIET)rm -f $(DECLS)\n");
	  } 
	  // if building asmall, copy binary to astests directory
	  if(0 == strcmp("asmall.cpp",szSrcFileName)) {
	    fprintf(mfp,"\t$(QUIET)cp asmall astests\n");
	  }
	  fprintf(mfp,"\n");
	}
      }
    }
    rc6 = dir6->read();
  }
  delete dir6;

  fprintf(mfp,"as8085/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  as8085/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C as8085\n\n");

  fprintf(mfp,"as8080/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  as8080/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C as8080\n\n");

  fprintf(mfp,"as6502/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  as6502/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C as6502\n\n");

  fprintf(mfp,"asz80/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  asz80/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C asz80\n\n");

  fprintf(mfp,"as68000/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  as68000/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C as68000\n\n");

  fprintf(mfp,"as1620/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  as1620/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C as1620\n\n");

  fprintf(mfp,"ascommon/decoincl.hpp:\tMakefile\n");
  fprintf(mfp,"\t$(QUIET)cp makedeco.mk  ascommon/Makefile\n");
  fprintf(mfp,"\t$(QUIET)make -B -C ascommon\n");

  fprintf(mfp,"\n\n");
  fprintf(mfp,	"clean:\n");
  fprintf(mfp,		"\t$(QUIET)rm -f editthem version.hpp "
			"*.mak *.lst *hex *.map *.log \n");
  fprintf(mfp,		"\t$(QUIET)rm -f "
"ascommon/editall ascommon/decoincl.hpp ascommon/makedeco ascommon/Makefile "
"ascommon/makedeco.cpp ascommon/decoincl.sav "
"ascommon/editall.ini ascommon/editthem "
  "as8085/editall   as8085/decoincl.hpp   as8085/makedeco   as8085/Makefile "
  "as8085/makedeco.cpp as8085/decoincl.sav "
  "as8085/editall.ini as8085/editthem "
   "asz80/editall    asz80/decoincl.hpp    asz80/makedeco    asz80/Makefile "
   "asz80/makedeco.cpp asz80/decoincl.sav "
   "asz80/editall.ini asz80/editthem "
  "as8080/editall   as8080/decoincl.hpp   as8080/makedeco   as8080/Makefile "
  "as8080/makedeco.cpp as8080/decoincl.sav "
  "as8080/editall.ini as8080/editthem "
 "as68000/editall  as68000/decoincl.hpp  as68000/makedeco  as68000/Makefile "
 "as68000/makedeco.cpp as68000/decoincl.sav "
 "as68000/editall.ini as68000/editthem "

 "as1620/editall  as1620/decoincl.hpp  as1620/makedeco  as1620/Makefile "
 "as1620/makedeco.cpp as1620/decoincl.sav "
 "as1620/editall.ini as1620/editthem "

  "as6502/editall   as6502/decoincl.hpp   as6502/makedeco   as6502/Makefile "
  "as6502/makedeco.cpp as6502/decoincl.sav "
  "as6502/editall.ini as6502/editthem doc/editall\n");
  fprintf(mfp,"\t$(QUIET)rm -f astests/asmall astests/editall\n");
  fprintf(mfp,"\t$(QUIET)rm -f %s\n",szBinBuffer);
  fprintf(mfp,"\t$(QUIET)rm -f -r *.sym astests/*.sym\n");
  fprintf(mfp,"\t$(QUIET)rm -f astests/*.lst astests/*.log \n");
  fprintf(mfp,"\t$(QUIET)rm -f astests/*.hex astests/*.bin \n");
  fprintf(mfp,"\t$(QUIET)rm -f astests/*.obj \n");

  fprintf(mfp,"\t$(QUIET)rm -f -r G* HTML\n\n");

  fprintf(mfp,"installbins:\n");
  fprintf(mfp,"\tcp $(BINARIES) ~/src/framewk/bin\n\n");

  fprintf(mfp,"uninstall:\n");
  fprintf(mfp,"\trm -f $(INSTBINS)\n\n");

  fprintf(mfp,"# eof - Makefile\n");
  fclose(mfp);
  system("cp Makefile Makefile.mk");
  system("cp makevers.mak makevers.mk");
  system("cp makemake.mak makemake.mk");
  return EXIT_SUCCESS;
}

