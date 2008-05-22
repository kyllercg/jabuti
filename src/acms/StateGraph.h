/**
 * \file		acms/StateGraph.h
 * \brief		The definition of the <b>StateGraph</b> class.
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
 */

using namespace std;

#include "config.h"

#include "Channel.h"
#include "Process.h"
#include "PNmodel.h"

//#include <iostream>
//#include <sstream>
#include <string>
#include <vector>
//
//#include "assert.h"

#ifndef STATEGRAPH_H
#define STATEGRAPH_H

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * DEFINES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** ACM process label. */
#define _ACMS_PROCESS_LABEL					"ACM"

/** Base label for tha states of a Signal process. */
#define _ACMS_STATE_LABEL					"s"

/** The target of the initial state of each process. Zero by default. */
#define _ACMS_INIT							0

/** In general means <b>false</b>, <b>no</b>, <b>not found</b> and so on. */
#define _ACMS_NONE							-10

/** The position of the <b>writer</b> counter in the vector of counters. */
#define _ACMS_WRITER_CELL					0

/** The position of the <b>reader</b> counter in the vector of counters. */
#define _ACMS_READER_CELL					1

/** The position of the <b>writer step</b> counter in the vector of counters. */
#define _ACMS_WRITER_STEP					2

/** The position of the <b>reader step</b> counter in the vector of counters. */
#define _ACMS_READER_STEP					3

/** The position of the <b>write slot</b> variable in the vector of counters. */
#define _ACMS_WRITER_SLOT					4

/** The position of the <b>read slot</b> variable in the vector of counters. */
#define _ACMS_READER_SLOT					5

/** The position of the <b>overwriting</b> bit in the vector of counters. */
#define _ACMS_OVER							6

/** Defines the number of the first part of an IO oparation. */
#define _ACMS_STEP_1						0

/** Defines the number of the second part of an IO oparation. */
#define _ACMS_STEP_2						1

/** Defines the number of the third part of an IO oparation. */
#define _ACMS_STEP_3						2

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * ERRORS MESSAGE
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Message error: policy not implemented. */
#define _ACMS_ERROR_POL_N_IMPLEMENTED		"policy not implemented"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CODE ERRORS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Error code: policy not implemented. */
#define _ACMS_ERROR_CODE_POL_N_IMPLEMENTED	30

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * STRINGS FOR PETRIFY MODEL
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** jabuti version text.*/
#define _acms_version						"0.4.2"

/**
 * \class	StateGraph StateGraph.h
 * \brief	The <b>StateGraph</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	June, 2004
 * 
 * The <b>StateGraph</b> class. This class defines the assyncronous
 * communications mechanisms availables for the composition of two (or more)
 * processes.
 */
class StateGraph {

	public:
		
		/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		 * Public methods prototypes.
		 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
		
		StateGraph(Channel *ch, vector<Process *> proc);
		StateGraph(int policy, int size);
		StateGraph();
		~StateGraph();
		
		Process getACM();
		Channel* getChannel();
		vector<Process *> getProcesses();
		
		void setChannel(Channel *ch);
		void setProcesses(vector<Process *> proc);
		
		void makeACM();
		
		void acm2petrify(char *cmd[]);
		PNmodel * acm2petrinet(void);
		PNmodel * acm2petrinetRR(void);
		PNmodel * acm2petrinetOW(void);
		vector<string> getEvents(int t);
		
		void reset();
		
	private:
		
		/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		 * Private attributes.
		 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
		
		/** To store the result of the synthesis algorithms. */
		Process *ACM;
		
		/** The communication channel of the system. */
		Channel *ACMChannel;
		
		/** To control the states (slots information) that have been generated.
		 * Depending on the policy, each element of <code>Counters</code> will
		 * a different information.
		 * 
		 * - <b>RRBB (message)</b>, <b>OWBB (signal)</b> and
		 *   <b>OWRRBB (pool)</b>:
		 * 	-#	<code>Counters[state][0]</code>: contains the cell
		 *		counter for the writer.
		 *	-#	<code>Counters[state][1]</code>: contains the cell
		 *		counter for the reader.
		 *	-#	<code>Counters[state][2]</code>: contains an
		 *		indication to the step performed in the write operation. Maybe 
		 * 		<code>_ACMS_STEP_1</code> or <code>_ACMS_STEP_2</code>.
		 *	-#	<code>Counters[state][3]</code>: contains an
		 *		indication to the step performed in the read operation. Maybe 
		 * 		<code>_ACMS_STEP_1</code> or <code>_ACMS_STEP_2</code>.
		 * - <b>OWBB</b> and <b>OWRRBB</b>:
		 * 	-#	<code>Counters[state][4]</code>: contains the slot
		 *		counter for the writer.
		 * 	-#	<code>Counters[state][5]</code>: contains the slot
		 *		counter for the reader.
		 *  -#  <code>Counters[state][6]</code>: indicates if writer is in an
		 * 		overwriting loop.
		 */
		vector<vector<int> > Counters;
		
		/** The vector with the pairs (cell,slot) that has not been read by
		 *  the reader */
		vector<vector<int> > LastCounters;
		
		/** This is an auxiliary vector to avoid using many memory. */
		vector<int> _counters;
		
		/** This is an auxiliary vector to avoid using many memory. */
		vector<int> _lastcounters;
		
		/** Vector with all processes of the system. */
		vector<Process *> Processes;
		
		/** To control the states that have not been processed (yet). */
		vector<int> New;
		
		/** To control the states that have been generated. */
		vector<vector<int> > All;
		
		/** To be used in the choose of the correct exists() method. */
		bool isRRBB;
				
		/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		 * Private methods prototypes.
		 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
		
		void createInitState();
		void generateStateSpace();
		void generateSuccessors(int state);
		void createNewState(int proc, int arc, int state, 
															vector<int> succ);
		void createNewStateOW(int proc, int arc, int state, 
															vector<int> succ);
		void createNewStateRR(int proc, int arc, int state, 
															vector<int> succ);
		void createNewArc(int proc, int arc, int state, int succ);
		void createNewArcOW(int proc, int arc, int state, int succ);
		void createNewArcRR(int proc, int arc, int state, int succ);
		int nextState(int state, int proc, int pcurr, int arc, int psucc);
		void nextCounters(int proc, int arc, int state);
		void nextCountersOW(int proc, int arc, int state);
		void nextCountersRR(int proc, int arc, int state);
		int exists(vector<int> succ);
		void insertArc(int proc, int src, int dest, string lab);
};
#endif /* STATEGRAPH_H */
