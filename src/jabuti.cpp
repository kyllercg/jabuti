/**
 * \file		jabuti.cpp
 * \brief		The <b>Jabuti</b> application.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		June, 2004
 * \version		$Id$
 * 
 * ACMs application. This file contain the routines of the <b>jabuti</b>
 * apllication. The <b>jabuti</b> application is the program that performs the
 * synthesis of asyncrhronous communication mechanisms from a specification
 * based on a set of DFA models.
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

#include "config.h"

#include "StateGraph.h"
#include "Penknife.h"
#include "Simulator.h"

#include "SGParser.h"
#include "sg.h"

#include <iostream>

#include <getopt.h>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * FOR COMMAND LINE OPTIONS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** The command line option for displaying help massage of <b>jabuti</b>. */
#define _HELP							10

/** The command line option for displaying version number of <b>jabuti</b>. */
#define _VERSION						11

/** The command line option for synthesis of a <b>RRBB</b> AMC. */
#define _RRBB							_CHANNEL_RRBB

/** The command line option for synthesis of a <b>OWBB</b> AMC. */
#define _OWBB							_CHANNEL_OWBB

/** The command line option for synthesis of a <b>OWRRBB</b> AMC. */
#define _OWRRBB							_CHANNEL_OWRRBB

/** The <b>ACM</b> only generation command line option. */
#define _ACM							200

/** The <b>Petri net</b> generation command line option. */
#define _PETRI							201

/** The <b>simulation</b> command line option. */
#define _SIM							202


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CODE ERRORS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Error code: wrong syntax when calling the parser program. */
#define _JABUTI_ERROR_CODE_SYNTAX		10

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * MISC
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** The code for nothing. */
#define _NONE							-1

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Data structures
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** <code>struct</code> to store command line options. */
typedef struct parsed_options {
	/** Code for command to be executed. */
	int command; 
	
	/** The size of the channel to be generated */
	int size;
	
	/** The arguments that modifies the main command. */
	int args;
	
	/** The number of steps to be executed if simulation was required. */
	int steps;
} p_options;

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

/** Used to set the input file name for LeX & Yacc. */
extern FILE *yyin;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * FUNCTIONS PROTOTYPES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int callParser(char *);
p_options readCmdLine(int argc, char *argv[]);
void jabuti_help(void);
void jabuti_version(void);

/**
 * \brief	This is the main program of the <b>Jabuti</b> suite.
 * 
 * \fn		int main(int argc, char *argv[])
 * \param	argc: number of arguments.
 * \param	*argv: list of arguments.
 * \return	An integer containing:
 * 			- <code>_SGPARSER_ERROR_NOT_EXISTS</code> if the program executes
 * 			  correctly.
 * 			- <code>_SGPARSER_ERROR_EXISTS</code> if the file contains some
 * 			  parser error.
 * 			- <code>_SGPARSER_ERROR_CODE_FILE_OP</code> if it was not possible
 * 			  to open the input file.
 * 			- <code>_SGPARSER_ERROR_CODE_FILE_CL</code> if some error occurred
 * 			  when closing the input file.
 * 			- <code>_ACMS_ERROR_CODE_SYNTAX</code> if the parser program was not
 * 			  correctly called (command line syntax error).
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	12/01/2005
 */
int main(int argc, char *argv[])
{
	#ifdef _JABUTI_APPS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " main()" << endl;
	#endif
	
	p_options op = readCmdLine(argc, argv);
	
	if (op.command == _HELP) {
		
		jabuti_help();
		exit(_SGPARSER_ERROR_NOT_EXISTS);
	} else if (op.command == _VERSION) {
		
		jabuti_version();
		exit(_SGPARSER_ERROR_NOT_EXISTS);
	}
	
	StateGraph *acm = new StateGraph(op.command, op.size);
	
	acm->makeACM();
	acm->acm2petrify(argv);
	
	/*
	if (op.args == _ACM) {
		
		acm->acm2petrify(argv);
	} else if (op.args == _PETRI) {
		
		acm->acm2petrify(argv);	
	}
	*/
	
	//acm->pACM();
		
	acm->~StateGraph();
		
	#ifdef _JABUTI_APPS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /main()" << endl;
	#endif
	
	exit(_SGPARSER_ERROR_NOT_EXISTS);
}

/**
 * \brief	Parse the command line passed to <b>jabuti</b>.
 * 
 * \fn		p_options readCmdLine(int argc, char *argv[])
 * \param	argc: number of arguments.
 * \param	*argv: list of arguments.
 * \return	A vector of type <code>p_options</code> containing the values
 * 			passed by command line.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	12/01/2005
 */
p_options readCmdLine(int argc, char *argv[])
{
	#ifdef _JABUTI_APPS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " readCmdLine()" << endl;
	#endif
	
	bool command = false;
	bool args = false;
	
	p_options op;
	
	op.command = _NONE;
	op.size = _NONE;
	op.args = _NONE;
	op.steps = _NONE;
	
	int opt = 0;
	//int digit_optind = 0;
	
	int options_index = 0;
	static struct option options[] = {
		{"help", 	no_argument, 		NULL, 	_HELP},
		{"version", no_argument, 		NULL, 	_VERSION},
		{"rrbb", 	required_argument, 	NULL, 	_RRBB},
		{"owbb", 	required_argument, 	NULL, 	_OWBB},
		{"owrrbb", 	required_argument, 	NULL, 	_OWRRBB},
		// {"acm", 	no_argument, 		NULL, 	_ACM},
		// {"petri", 	no_argument, 		NULL, 	_PETRI},
		// {"sim", 	required_argument, 	NULL, 	_SIM},
		{0, 		0, 					0, 		0}
	};
		
	while (opt != -1) {
		
		opt = getopt_long_only(argc, argv, "", options, &options_index);
		
		switch (opt) {
			
			case _RRBB:
			case _OWBB:
			case _OWRRBB:
			case _HELP:
			case _VERSION:
				
				if (command) {
					
					jabuti_help();
					exit(_JABUTI_ERROR_CODE_SYNTAX);
				}
				
				command = true;
				op.command = opt;
				
				if (op.command != _VERSION && op.command != _HELP) {
					
					op.size = atoi(optarg);
				}
				
				break;
				
			/*
			case _ACM:
			case _PETRI:
			case _SIM:
				
				if (args) {
					
					jabuti_help();
					exit(_JABUTI_ERROR_CODE_SYNTAX);
				}
				
				args = true;
				op.args = opt;
				
				if (op.args == _SIM) {
					
					op.steps = atoi(optarg);
				}
				
				break;
			*/
			
			default:
				
				if (opt != -1) {
					
					jabuti_help();
					exit(_JABUTI_ERROR_CODE_SYNTAX);
				}

				break;
		}
	}
	
	if (command == false) {
		
		jabuti_help();
		exit(_JABUTI_ERROR_CODE_SYNTAX);
	} else if (op.command != _VERSION 
				&& op.command != _HELP
				&& op.size < 2) {
		
		jabuti_help();
		exit(_JABUTI_ERROR_CODE_SYNTAX);
	} /* else if (op.command != _VERSION 
				&& op.command != _HELP
				&& op.size >= 2
				&& op.args == false) {
		
		jabuti_help();
		exit(_JABUTI_ERROR_CODE_SYNTAX);
	} else if (op.command != _VERSION 
				&& op.command != _HELP
				&& op.size >= 2
				&& op.args == true
				&& op.steps < 1) {
		
		jabuti_help();
		exit(_JABUTI_ERROR_CODE_SYNTAX);
	} */
	
	#ifdef _JABUTI_APPS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /readCmdLine()" << endl;
	#endif
	
	return op;
}

/**
 * \brief	Calls <b>yacc</b> functions to parse input file.
 * 
 * \fn		int callParser(char *f)
 * \param	*f: the name of the file with the system description.
 * \return	An integer containing:
 * 			- <code>_SGPARSER_ERROR_NOT_EXISTS</code> if the input file contains
 * 			  no parser errors.
 * 			- <code>_SGPARSER_ERROR_EXISTS</code> if the file contains some
 * 			  paser error.
 * 			- <code>_SGPARSER_ERROR_CODE_FILE_OP</code> if it was not possible
 * 			  to open the input file.
 * 			- <code>_SGPARSER_ERROR_CODE_FILE_CL</code> if there was an error
 * 			  when closing the input file.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
int callParser(char *f)
{
	#ifdef _JABUTI_APPS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " callParser()" << endl;
	#endif
	
	FILE *srcfile;
	
	if ((srcfile = fopen(f, "rb")) == NULL) {
		
		return _SGPARSER_ERROR_CODE_FILE_OP;
	}
	
	yyin = srcfile;
	
	yyparse();
	
	if (fclose(srcfile) != 0) {
		
		return _SGPARSER_ERROR_CODE_FILE_CL;
	}
	
	if (sgparser.hasErrors() == true) {
		
		return _SGPARSER_ERROR_EXISTS;
	}
	
	#ifdef _JABUTI_APPS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /callParser()" << endl;
	#endif
	
	return _SGPARSER_ERROR_NOT_EXISTS;
}

/**
 * \brief	Prints the syntax of <b>jabuti</b>.
 * 
 * \fn		void jabuti_help(void)
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	12/01/2005
 */
void jabuti_help(void)
{
	cout << "usage: jabuti command argumments" << endl << endl;
	
	cout << "command" << endl;
	cout << "    --help        shows this message" << endl;
	cout << "    --version     shows version number" << endl;
	cout << "    --rrbb n      generates a RRBB ACM with n cells" << endl;
	cout << "    --owbb n      generates a OWBB ACM with n cells" << endl;
	cout << "    --owrrbb n    generates a OWRRBB ACM with n cells" << endl
		 << endl;
	
	/* cout << "argumments" << endl;
	cout << "    --acm         generates the state graph for the AMC" << endl;
	cout << "    --petri       generates the petri net for the ACM" << endl;
	cout << "    --sim n       generates the ACM and simulates it by n steps"
		 << endl << endl; */
}

/**
 * \brief	Prints the version of <b>jabuti</b>.
 * 
 * \fn		void jabuti_version(void)
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	12/01/2005
 */
void jabuti_version(void)
{
	cout << "jabuti " << _acms_version << " (compiled " << __DATE__ << " at "
		 << __TIME__ << ")" << endl;
}
