/**
 * \file		apps/codep_test.cpp
 * \brief		<b>codep_test</b> executable program.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		June, 2004
 * \version		$Id$
 * 
 * Copyright (C) 2004, 2008 - Kyller Costa Gorgônio
 * Copyright (C) 2004, 2008 - Universitat Politècnica de Catalunya
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
 * $Id$
 */

using namespace std;

#include "PNParser.h"

#include <iostream>
#include <string>
#include <vector>

/** To be used inside <i>yyparser()</i>. It SHOULD exists. */
PNParser pnparser;

/**
 * \brief	Just to print information about a system.
 * 
 * \fn		static void printSystem(PNParser pp)
 * \param	pp: the parser.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	26/10/2004
 */
static void printSystem(PNParser pp)
{
	vector<string> v;
	int i, c;
	
	vector<int> t = pp.getTransitions();
	vector<int> p = pp.getPlaces();
	vector<int> s;
	
	
	cout << ".model " << pp.getPNLabel() << endl;
	
	v.clear();
	v = pp.getTransitions(_PN_T_OUTPUTS);
	
	if (!v.empty()) {
		
		cout << ".outputs";
		for (i = 0; i < v.size(); i++) {
			
			cout << " " << v[i];
		}
		cout << endl;
	}
	
	v.clear();
	v = pp.getTransitions(_PN_T_INTERNAL);
	
	if (!v.empty()) {
		
		cout << ".internal";
		for (i = 0; i < v.size(); i++) {
			
			cout << " " << v[i];
		}
		cout << endl;
	}
	
	v.clear();
	v = pp.getTransitions(_PN_T_DUMMY);
	
	if (!v.empty()) {
		
		cout << ".dummy";
		for (i = 0; i < v.size(); i++) {
			
			cout << " " << v[i];
		}
		cout << endl;
	}
	
	cout << ".graph" << endl;
	
	if (!t.empty()) {
		
		for (i = 0; i < t.size(); i++) {
			
			cout << pnparser.getLabelT(t[i]);
			
			s = pnparser.getOutT(t[i]);
			
			for (c = 0; c < s.size(); c++) {
				
				cout << " " << pnparser.getLabelP(s[c]);
			}
			
			cout << endl;
		}
	}
	
	if (!p.empty()) {
		
		for (i = 0; i < p.size(); i++) {
			
			cout << pnparser.getLabelP(p[i]);
			
			s = pnparser.getOutP(p[i]);
			
			for (c = 0; c < s.size(); c++) {
				
				cout << " " << pnparser.getLabelT(s[c]);
			}
			
			cout << endl;
		}
	}
	
	cout << ".marking {";
	
	if (!p.empty()) {
		
		for (i = 0; i < p.size(); i++) {
			
			int n = pnparser.getTokens(p[i]);
			
			if (n > 0) {
				
				cout << " " << pnparser.getLabelP(p[i]);
			}
		}
	}
	
	cout << " }" << endl;
	
	cout << ".end" << endl;
}

/**
 * \brief	A program that just parse a file with a system description.
 * 
 * \fn		int main(int argc, char *argv[])
 * \param	argc: number of arguments.
 * \param	*argv: list of arguments.
 * \return	An integer.
 * 
 * \return	An integer value with the error code. Zero is return if there is no
 * 			errors.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	26/10/2004
 */
int main(int argc, char *argv[])
{
	int r = _PNPARSER_ERROR_NOT_EXISTS;
	
	if (argc != 2) {
		
		pnparser.pperrors(_PNPARSER_ERROR_USAGE);
		exit(_PNPARSER_ERROR_CODE_SYNTAX);
	}

	r = pnparser.callPNParser(argv[1]);
	
	switch (r) {
		
		case _PNPARSER_ERROR_EXISTS:
		
			cerr << _PNPARSER_ERROR_MSG << endl;
			break;
			
		case _PNPARSER_ERROR_CODE_FILE_OP:
		
			cerr << _PNPARSER_ERROR_FILE_OP << argv[1] << endl;
			break;
	
		case _PNPARSER_ERROR_CODE_FILE_CL:
		
			cerr << _PNPARSER_ERROR_FILE_CL << argv[1] << endl;
			break;
			
		default:
			
			printSystem(pnparser);
			break;
	}
	
	pnparser.~PNParser();
		
	exit(r);
}
