// ---------------------------------------------------
// dq.hpp       23-Feb-11   Running on Mac OS X 10.6.6
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
//

if(0 == strcmp(strupr(g_szOpcode),"DQ")) {
	fprintf(g_flog,"Processing Z80 DQ  g_szOpcode\n");
        g_iLineType = TYPE_Z80;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {

		unsigned long long llTemp = resolvep64(g_szParms);

		unsigned long       lTempl = llTemp&0x00000000ffffffffLL;
		unsigned long       lTemph = llTemp>>32;
		unsigned long lTemp = lTempl;
		unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
		unsigned int  uiTemph = (unsigned int)lTemp >> 16;
                g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;

                lTemp = lTemph;
                uiTempl = (unsigned int)lTemp & 0x0000ffffL;
                uiTemph = (unsigned int)lTemp >> 16;
                g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
                g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;

	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

