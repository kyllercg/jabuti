/**
 * \file		apps/sg_test.cpp
 * \brief		The file with the main function for the <b>sg-test</b> program.
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
 * e.
 */

using namespace std;

#include "sg.h"

#include "SGParser.h"

#include <iostream>
#include <vector>

#include <stdio.h>

//extern "C" {
// #include "../parser/SGParser.h"
//}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * INITIALIZING CLASS VARIABLES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int Process::nextTarget = 0;
int Channel::nextTarget = 0;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * LOCAL FUNCTIONS PROTOTYPES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
static void printstate(Process *p, char *s);
static void makeTest();
static void errors(char *m);

/**
 * \brief	This is a test program for the <b>sg</b> module of <b>Jabuti/b>.
 * 
 * \fn		int main(int argc, char *argv[])
 * \param	argc: number of arguments.
 * \param	*argv[]: list of arguments.
 * \return	An integer value with the error code. Zero is return if there is 
 * 			no errors.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	02/06/2004
 */
int main(int argc, char *argv[])
{
	if (argc != 1) {
		
		errors(_SG_ERROR_USAGE);
		exit(_SG_ERROR_CODE_SYNTAX);
	}
	
	makeTest();
	
	exit(0);
}

/**
 * \brief	Prints an error message.
 * 
 * \fn		static void errors(char *m)
 * \param	*m: error message.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
static void errors(char *m)
{
	cerr << m << endl;
}

/**
 * \brief	Runs a test.
 * 
 * \fn		static void makeTest()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
static void makeTest()
{
	Process *p = new Process("proc_1");
	
	vector<int> succ;
	vector<int> pred;
	
	int cont;
	
	if (p == NULL) {
		
		cerr << "nao funcionou!" << endl;
		exit(1);
	}
	
	p->insertState("s1");
	p->insertState("s2");
	p->insertState("s3");
	p->insertState("s4");
	
	p->insertArc(p->getTarget("s1"), "a1", p->getTarget("s2"));
	p->insertArc(p->getTarget("s1"), "a2", p->getTarget("s3"));
	p->insertArc(p->getTarget("s1"), "a3", p->getTarget("s4"));
	p->insertArc(p->getTarget("s2"), "a4", p->getTarget("s3"));
	p->insertArc(p->getTarget("s3"), "a5", p->getTarget("s4"));
	p->insertArc(p->getTarget("s4"), "a6", p->getTarget("s1"));
	
	cout << "process: " << p->getLabel() << " (" << p->getTarget() << ")" 
		 << endl;
		 
	printstate(p, "s1");
	printstate(p, "s2");
	printstate(p, "s3");
	printstate(p, "s4");
}

/**
 * \brief	Just to print information about a state.
 * 
 * \fn		void printstate(Process *p, char *s)
 * \param	*p: the process.
 * \param	*s: the state label.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	02/06/2004
 */
static void printstate(Process *p, char *s)
{
	vector<int> succ;
	vector<int> pred;
	
	int cont;
	
	cout << "    state: " << p->getLabel(p->getTarget(s))
		 << " (" << p->getTarget(s) << ")" << endl;
	cout << "        successors:  ";
	succ = p->getSuccessors(p->getTarget(s));
	for (cont = 0; cont < succ.size(); cont++) {
		
		cout << " " << succ[cont] 
		     << " (" << p->getTarget(p->getTarget(s), succ[cont]) << ", "
		     << p->getLabel(p->getTarget(s), succ[cont]) << ")";
	}
	cout << endl;
	
	cout << "        predecessors:";
	pred = p->getPredecessors(p->getTarget(s));
	for (cont = 0; cont < pred.size(); cont++) {
		
		cout << " " <<  pred[cont] 
		     << " (" << p->getTarget(pred[cont], p->getTarget(s)) << ", "
		     << p->getLabel(pred[cont], p->getTarget(s)) << ")";
	}
	cout  << endl;
}
