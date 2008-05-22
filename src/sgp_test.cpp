/**
 * \file		apps/sgparser_test.cpp
 * \brief		<b>sgparser_test</b> executable program.
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
 * .
 */

using namespace std;

#include "SGParser.h"

#include <iostream>
#include <string>
#include <vector>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * INITIALIZING CLASS VARIABLES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int Process::nextTarget = 0;
int Channel::nextTarget = 0;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * GLOBAL VARIABLES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */ 

/** To be used inside <i>yyparser()</i>. It SHOULD exists. */
SGParser sgparser;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * FUNCTIONS PROTOTYPES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
//int callParser(char *);
//static void printSystem(SGParser);

/**
 * \brief	Just to print information about a system.
 * 
 * \fn		static void printSystem(SGParser pp)
 * \param	pp: the parser.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
static void printSystem(SGParser pp)
{
	vector<int> succ;
	vector<int> pred;
	
	int cont, cont2, cont3;
	
	for (cont = 0; cont < pp.Channels.size(); cont++) {
		
		cout << "channel --> " << pp.Channels[cont]->getLabel() << " "
			 << pp.Channels[cont]->getSlots() << " (" 
			 << pp.Channels[cont]->getTarget() << ") ";
	
		if (pp.Channels[cont]->getType() == _CHANNEL_OWBB) {
			
			cout << "SIGNAL" << endl;
		} else if (pp.Channels[cont]->getType() == _CHANNEL_RRBB) {
			
			cout << "MESSAGE" << endl;
		} else {
			
			cout << "-" << endl;
		}
	}
	cout << endl;
	
	for (cont = 0; cont < pp.Processes.size(); cont++) {
		
		cout << "process --> " << pp.Processes[cont]->getLabel() << " ("
			 << pp.Processes[cont]->getTarget() << ")" << endl;
		
		for (cont2 = 0; cont2 < pp.Processes[cont]->States.size(); cont2++) {

			string label = pp.Processes[cont]->States[cont2]->getLabel();
			int target = pp.Processes[cont]->States[cont2]->getTarget();
		  	cout << "    state --> " << label << " (" << target << ")" << endl;
			cout << "        successors --> ";
			
			succ = pp.Processes[cont]->getSuccessors(target);
			for (cont3 = 0; cont3 < succ.size(); cont3++) {
		
				cout << " " << pp.Processes[cont]->getLabel(succ[cont3]) << " by "
					 << pp.Processes[cont]->getLabel(cont2, succ[cont3]) << " ("
				     << succ[cont3] << ")";
			}
			cout << endl;

			cout << "        predecessors --> ";
			pred = pp.Processes[cont]->getPredecessors(target);
			for (cont3 = 0; cont3 < pred.size(); cont3++) {
				
				cout << " " << pp.Processes[cont]->getLabel(pred[cont3]) << " by "
					 << pp.Processes[cont]->getLabel(pred[cont3], cont2) << " ("
				     << pred[cont3] << ")";
			}
			cout << endl;
		}
		cout  << endl;
	}
}

/**
 * \brief	A program that just parse a file with a system description.
 * 
 * \fn		int main(int argc, char *argv[])
 * \param	argc: number of arguments.
 * \param	*argv: list of arguments.
 * \return	An integer containing:
 * 			- <code>_SGPARSER_ERROR_NOT_EXISTS</code> if the input file contains
 * 			  no parser errors.
 * 			- <code>_SGPARSER_ERROR_EXISTS</code> if the input file contains
 * 			  some parser error.
 * 			- <code>_SGPARSER_ERROR_CODE_FILE_OP</code> if it was not possible
 * 			  to open the input file.
 * 			- <code>_SGPARSER_ERROR_CODE_FILE_CL</codeb> if some error occurred
 * 			  when closing the input file.
 * 			- <code>_SGPARSER_ERROR_CODE_SYNTAX</code> if the parser program was
 * 			  not correctly called (command line syntax error).
 * 
 * \return	An integer value with the error code. Zero is return if there is no
 * 			errors.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
int main(int argc, char *argv[])
{
	int r = _SGPARSER_ERROR_NOT_EXISTS;
	
	if (argc != 2) {
		
		sgparser.pperrors(_SGPARSER_ERROR_USAGE);
		exit(_SGPARSER_ERROR_CODE_SYNTAX);
	}

	r = sgparser.callSGParser(argv[1]);
	
	switch (r) {
		
		case _SGPARSER_ERROR_EXISTS:
		
			cerr << _SGPARSER_ERROR_MSG << endl;
			break;
			
		case _SGPARSER_ERROR_CODE_FILE_OP:
		
			cerr << _SGPARSER_ERROR_FILE_OP << argv[1] << endl;
			break;
	
		case _SGPARSER_ERROR_CODE_FILE_CL:
		
			cerr << _SGPARSER_ERROR_FILE_CL << argv[1] << endl;
			break;
		default:
			
			printSystem(sgparser);
			break;
	}
	
	sgparser.~SGParser();
		
	exit(r);
}
