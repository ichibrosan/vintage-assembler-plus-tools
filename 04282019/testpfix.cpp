// $Log: testpfix.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// testpfix.cpp 24-Feb-11   Running on Mac OS X 10.6.6
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

static char szTestpfixCpp[] = "$Id: testpfix.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#define POSTFIX

#include "asdefs.hpp"
#include "includes.hpp"
#include "cpostfix.hpp"

int main(int argc,char **argv)
{
	Version(argv[0]);
	printf("Ported from C Version by Luiz Roberto Meier 2010\n");

//	char szInBuff[128];
//	printf("Enter expression: ");
//	scanf("%s",szInBuff);

	CPostfix pfix(argc);
	for(int x=0;x<10;x++) {
		pfix.convert("A+C");
		printf("Result was %s\n",pfix.getresult());
	}
	return (EXIT_SUCCESS);
}

