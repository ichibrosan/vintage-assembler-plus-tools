// ---------------------------------------------------
// mktoday.cpp  21-Feb-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// ---------------------------------------------------
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// 2/20/2011 dwg - 
// Environmental aspects are now controlled by MACHTYPE
// and not the user name as before.

// since the addition of an include directory override
// in the makefile, we can use the general includes
// file and version handler, complete with environmental
// features.

#include "includes.hpp"

//           1         2
// 0123456789012345678901234567
// Sat Jan 29 14:43:54 PST 2011
char szBuffer[64];

char szUser[64];
char szOstype[64];

int main(int argc,char **argv)
{
	char szMkDirSpec[128];
	char szDirSpec[128];
	char szCommand[64];
	char szMonth[4];
	char szDay[4];
	char szYear[5];
	char szHour[3];
	int iMonth;

	strcpy(szUser,getenv("USER"));

	Version(argv[0]);

	system("date > date.tmp");
	FILE * fd = fopen("date.tmp","r");
	if(NULL == fd) {
		printf("Sorry, could not open date.tmp for input\n");
		exit(EXIT_FAILURE);
	}
	fgets(szBuffer,sizeof(szBuffer),fd);
	fclose(fd);
	system("rm -f date.tmp");

	memset(szMonth,0,sizeof(szMonth));
	memset(szDay,0,sizeof(szDay));
	memset(szYear,0,sizeof(szYear));
	memset(szHour,0,sizeof(szHour));

	strncpy(szMonth,&szBuffer[4],3);
	strncpy(szDay,&szBuffer[8],2);
	strncpy(szYear,&szBuffer[24],4);
	strncpy(szHour,&szBuffer[11],2);

	if(0 == strcmp("Jan",szMonth)) iMonth = 1;
	if(0 == strcmp("Feb",szMonth)) iMonth = 2;
	if(0 == strcmp("Mar",szMonth)) iMonth = 3;
	if(0 == strcmp("Apr",szMonth)) iMonth = 4;
	if(0 == strcmp("May",szMonth)) iMonth = 5;
	if(0 == strcmp("Jun",szMonth)) iMonth = 6;
	if(0 == strcmp("Jul",szMonth)) iMonth = 7;
	if(0 == strcmp("Aug",szMonth)) iMonth = 8;
	if(0 == strcmp("Sep",szMonth)) iMonth = 9;
	if(0 == strcmp("Oct",szMonth)) iMonth = 10;
	if(0 == strcmp("Nov",szMonth)) iMonth = 11;
	if(0 == strcmp("Dec",szMonth)) iMonth = 12;

	printf("Welcome %s\n",szUser);

        sprintf(szDirSpec,"%02d%02d%04d",
                iMonth,atoi(szDay),atoi(szYear));
	FILE * fdsh = fopen("today","w");
	fprintf(fdsh,"#!/bin/bash\n");
	fprintf(fdsh,"mkdir %s 2>> today.log\n",szDirSpec);
	fprintf(fdsh,"cd %s >> today.log\n",szDirSpec);

	if(0 == strcmp("x86_64-apple-darwin10.0",version.getmachtype())) {
                sprintf(szMkDirSpec,
                        "/Users/%s/framewk/%02d%02d%04d/Makefile",
                        version.getuser(),iMonth,atoi(szDay),atoi(szYear));
	}

        if(0 == strcmp("x86_64-redhat-linux-gnu",version.getmachtype())) {
                sprintf(szMkDirSpec,
                        "/home/%s/public_html/framewk/%02d%02d%04d/Makefile",
                        version.getuser(),iMonth,atoi(szDay),atoi(szYear));
        }

        FILE * fdmk = fopen(szMkDirSpec,"r");
	if(NULL == fdmk) {
        	if(0 == strcmp("x86_64-apple-darwin10.0",
				version.getmachtype())) {
                	fprintf(fdsh,"/Users/%s/framewk/bin/copylast\n",
                        	version.getuser());
        	}
        	if(0 == strcmp("x86_64-redhat-linux-gnu",
				version.getmachtype())) {
                	fprintf(fdsh,
				"/home/%s/public_html/framewk/bin/copylast\n",
                        	version.getuser());
        	}
	}
	if(NULL != fdmk) {
		fclose(fdmk);
	}
	fprintf(fdsh,"rm ../today\n");
	fclose(fdsh);

	system("chmod +x today");

	system("rm -r latest");

	char szLink[128];

        if(0 == strcmp("x86_64-apple-darwin10.0",version.getmachtype())) {
                sprintf(szLink,
		  "ln -s /Users/%s/framewk/%02d%02d%04d latest",
                  version.getuser(),iMonth,atoi(szDay),atoi(szYear));
        }
        
        if(0 == strcmp("x86_64-redhat-linux-gnu",version.getmachtype())) {
                sprintf(szLink,
		  "ln -s /home/%s/public_html/framewk/%02d%02d%04d latest",
                  version.getuser(),iMonth,atoi(szDay),atoi(szYear));
        }

	system(szLink);

	return EXIT_SUCCESS;
}

///////////////////////
// eof - mktoday.cpp //
///////////////////////

