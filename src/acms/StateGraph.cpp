/**
 * \file		acms/StateGraph.cpp
 * \brief		The methods of the StateGraph class.
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

#include "StateGraph.h"
#include "Penknife.h"

#include <iostream>
#include <sstream>

#include "assert.h"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CLASS CONSTRUCTORS / DESTRUCTOR
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Class constructor. Creates a new StateGraph element.
 * 
 * \fn		StateGraph::StateGraph(Channel *ch, vector<Process *> proc)
 * \param	ch: the channel of the system.
 * \param	proc: vector containg all the processes of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
StateGraph::StateGraph(Channel *ch, vector<Process *> proc)
{
	Process *aux = new Process(_ACMS_PROCESS_LABEL);
	ACM = aux;
	
	ACMChannel = ch;
	Processes = proc;
	
	isRRBB = false;
}


/**
 * \brief	Class constructor. Creates a new StateGraph element.
 * 
 * \fn		StateGraph::StateGraph(int policy, int size)
 * \param	policy: the policy for the new ACM.
 * \param	size: the number of cells of the new channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	12/01/2005
 */
StateGraph::StateGraph(int policy, int size)
{
	Process *aux = new Process(_ACMS_PROCESS_LABEL);
	ACM = aux;
	
	Channel *ch = new Channel("CH");
	ch->setType(policy);
	ch->setCells(size);
	
	if (policy == _CHANNEL_RRBB) {
		
		ch->setSlots(1);
	} else {
		
		ch->setSlots(2);
	}
	
	ACMChannel = ch;
	
	Process *p1 = new Process("writer");
	p1->insertState("s0");
	p1->insertArc(p1->States.back()->getTarget(), "wrCH", 
		p1->States.back()->getTarget(), _ARC_WRITE, ch->getTarget());
	
	Process *p2 = new Process("reader");
	p2->insertState("s0");
	p2->insertArc(0, "rdCH", 0, _ARC_READ, ch->getTarget());
	
	Processes.insert(Processes.end(), p1);
	Processes.insert(Processes.end(), p2);
	
	isRRBB = false;
}

/**
 * \brief	Class constructor. Creates a new StateGraph element.
 * 
 * \fn		StateGraph::StateGraph()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
StateGraph::StateGraph()
{
	Process *aux = new Process(_ACMS_PROCESS_LABEL);
	ACM = aux;
	
	isRRBB = false;
}

/**
 * \brief	Class destructor.
 * 
 * \fn		StateGraph::~StateGraph()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	09/09/2004
 */
StateGraph::~StateGraph()
{
	reset();
}


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * PUBLIC METHODS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Gets the synthesized process (ACM).
 * 
 * \fn		Process StateGraph::getACM()
 * \return	The synthesized ACM.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	17/06/2004
 */
Process StateGraph::getACM()
{
	return *ACM;
}

/**
 * \brief	Gets the vector of channels.
 * 
 * \fn		Channel* StateGraph::getChannel()
 * \return	The channel of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
Channel* StateGraph::getChannel()
{
	return ACMChannel;
}

/**
 * \brief	Gets the vector of processes.
 * 
 * \fn		vector<Process *> StateGraph::getProcesses()
 * \return	A vector containg all the processes of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
vector<Process *> StateGraph::getProcesses()
{
	return Processes;
}

/**
 * \brief	Sets the channel of the system.
 * 
 * \fn		void StateGraph::setChannel(Channel *ch)
 * \param	ch: the channel of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
void StateGraph::setChannel(Channel *ch)
{
	ACMChannel = ch;
}

/**
 * \brief	Sets the vector of processes.
 * 
 * \fn		void StateGraph::setProcesses(vector<Process *> proc)
 * \param	proc: vector containg all the processes of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
void StateGraph::setProcesses(vector<Process *> proc)
{
	Processes = proc;
}

/**
 * \brief	This is the public method to generate the ACM process.
 * 
 * \fn		void StateGraph::makeACM()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
void StateGraph::makeACM()
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " makeACM()" << endl;
	#endif
	
	reset();
	generateStateSpace();
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /makeACM()" << endl;
	#endif
}

/**
 * \brief	Resets all control information about the slots of the channels.
 * 
 * \fn		void StateGraph::reset()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	18/10/2004
 */
void StateGraph::reset()
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " reset()" << endl;
	#endif
	
	int cont, size;
	vector<int> aux;
	
	New.clear();
	All.clear();
	Counters.clear();
	LastCounters.clear();
	_counters.clear();
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /reset()" << endl;
	#endif
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * PRIVATE METHODS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Generates the state space of the <code>ACM</code> process.
 * 
 * \fn		void StateGraph::generateStateSpace()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	17/06/2004
 */
void StateGraph::generateStateSpace()
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " generateStateSpace()" << endl;
	#endif
	
	createInitState();
	
	while (New.size() != 0) {
		
		generateSuccessors(New.back());
		New.pop_back();
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /generateStateSpace()" << endl;
	#endif
}

/**
 * \brief	Creates the initial state of the <code>ACM</code> process.
 * 
 * \fn		void StateGraph::createInitState()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/01/2006
 */
void StateGraph::createInitState()
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createInitState()" << endl;
	#endif
	
	vector<int> state;
	vector<int> aux_c, aux_l;
	
	ostringstream saux;
	string label;
	
	saux << ACM->States.size() << flush;
	label = saux.str();
	
	int size = Processes.size();
	for (int cont = 0; cont < size; cont++) {
		
		state.insert(state.end(), _ACMS_INIT);
	}
	
	aux_c.clear();
	aux_l.clear();
	
	int n = ACMChannel->getCells();
	switch (ACMChannel->getType()) {
		
		case _CHANNEL_RRBB: // message ==> rr-bb
			
			aux_c.insert(aux_c.end(), n - 1); // w = n - 1
			aux_c.insert(aux_c.end(), 0); // r = 0
			aux_c.insert(aux_c.end(), _ACMS_STEP_1); // write in step 0
			aux_c.insert(aux_c.end(), _ACMS_STEP_1); // read in step 0
			
			break;
			
		case _CHANNEL_OWBB:   // signal ==> ow-bb
		case _CHANNEL_OWRRBB: // pool ==> ow-rr-bb
			
			aux_c.insert(aux_c.end(), 0); // w = 0
			aux_c.insert(aux_c.end(), n - 1); // r = 1
			aux_c.insert(aux_c.end(), _ACMS_STEP_1); // write in step 0
			aux_c.insert(aux_c.end(), _ACMS_STEP_1); // read in step 0
			aux_c.insert(aux_c.end(), 1); // slot de w = 1
			aux_c.insert(aux_c.end(), 1); // slot de r = 1
			aux_c.insert(aux_c.end(), 0); // overwrite = no
			
			break;
			
		default:
			
			Penknife::pkerrors(_ACMS_ERROR_POL_N_IMPLEMENTED, "UNKNOWN");
			exit(_ACMS_ERROR_CODE_POL_N_IMPLEMENTED);
	}
	
	All.insert(All.begin(), state);
	New.insert(New.begin(), _ACMS_INIT);
	Counters.insert(Counters.begin(), aux_c);
	LastCounters.insert(LastCounters.begin(), aux_l);
	
	ACM->insertState(label.c_str());
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createInitState()" << endl;
	#endif
}

/**
 * \brief	Generates all successors of a given state.
 * 
 * \fn		void StateGraph::generateSuccessors(int state)
 * \param	state: the state to generate the successors.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::generateSuccessors(int state)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " generateSuccessors()" << endl;
	#endif
	
	int pcont, psize, scont, ssize, acont, ssucc;
	vector<int> succ, proc_succ;
	
	psize = Processes.size();
	
	for (pcont = 0; pcont < psize; pcont++) {
		
		assert(All.size() == Counters.size());
		
		proc_succ = Processes[pcont]->getSuccessors(All[state][pcont]);
		ssize = proc_succ.size();
		
		for (int scont = 0; scont < ssize; scont++) {
			
			acont = Processes[pcont]->getTarget(All[state][pcont], \
				proc_succ[scont]);
			
			succ = All[state];
			succ[pcont] = nextState(state, pcont, scont, acont, \
				proc_succ[scont]);
			
			nextCounters(pcont, acont, state);
			ssucc = exists(succ);
			
			if (ssucc == _ACMS_NONE) {
				
				createNewState(pcont, acont, state, succ);
			} else if (ssucc != state) { // exists(...) != _ACMS_NONE != state
				
				createNewArc(pcont, acont, state, ssucc);
			}
		}
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /generateSuccessors()" << endl;
	#endif
}

/**
 * \brief	Creates a new state and adds it to the state space.
 * 
 * \fn		void StateGraph::createNewState(int proc, int arc, int state,
															vector<int> succ)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc (step) of <i>proc</i> that will be
 * 			executed.
 * \param	state: the target of the current state.
 * \param	succ: the state that is reached when running the process
 * 			<i>proc</i> one step.
 * 
 * Creates a new state and adds it to the state space. This method calls the 
 * proper method to create a state (depending on the type of the channel) or
 * simple creates the state if the event is internal do the process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::createNewState(int proc, int arc, int state, vector<int> succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createNewState()" << endl;
	#endif
	
	if (Processes[proc]->Arcs[arc]->isIO()) {
		
		switch (ACMChannel->getType()) {
			
			case _CHANNEL_RRBB:
				
				createNewStateRR(proc, arc, state, succ);
				break;
			
			case _CHANNEL_OWBB:
			case _CHANNEL_OWRRBB:
				
				createNewStateOW(proc, arc, state, succ);
				break;
			
			default:
				
				Penknife::pkerrors(_ACMS_ERROR_POL_N_IMPLEMENTED, "UNKNOWN");
				exit(_ACMS_ERROR_CODE_POL_N_IMPLEMENTED);
		}
	} else {
		
		ostringstream saux;
		string label;
		
		saux << ACM->States.size() << flush;
		label = saux.str();
		
		ACM->insertState(label.c_str());
		All.insert(All.end(), succ);
		New.insert(New.begin(), ACM->getTarget(label.c_str()));
		
		insertArc(proc, state, ACM->getTarget(label.c_str()), \
			Processes[proc]->Arcs[arc]->getLabel());
		
		Counters.insert(Counters.end(), _counters);
		LastCounters.insert(LastCounters.end(), _lastcounters);
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createNewState()" << endl;
	#endif
}

/**
 * \brief	Creates a new state and adds it to the state space.
 * 
 * \fn		void StateGraph::createNewStateOW(int proc, int arc, int state, 
															vector<int> succ)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc (step) of <i>proc</i> that will be
 * 			executed.
 * \param	state: the target of the current state.
 * \param	succ: the state that is reached when running the process
 * 			<i>proc</i> one step.
 * 
 * Creates a new state and adds it to the state space. This method is used only
 * in the case that the channel is of type <code>_CHANNEL_OWBB</code> or 
 * <code>_CHANNEL_OWRRBB</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	20/09/2004
 */
void StateGraph::createNewStateOW(int proc, int arc, int state, vector<int> succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createNewStateOW()"
			 << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	
	ostringstream saux;
	string label;
	
	saux << ACM->States.size() << flush;
	label = saux.str();
	
	if (type == _ARC_WRITE) {
		
		ACM->insertState(label.c_str());
		All.insert(All.end(), succ);
		New.insert(New.begin(), ACM->getTarget(label.c_str()));
		
		Counters.insert(Counters.end(), _counters);
		LastCounters.insert(LastCounters.end(), _lastcounters);
		
		if (Counters[state][_ACMS_WRITER_STEP] == _ACMS_STEP_1) {
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << Counters[state][_ACMS_WRITER_CELL] << flush;
			saa << Counters[state][_ACMS_WRITER_SLOT] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(Counters[state][_ACMS_WRITER_CELL]);
			ACM->Arcs.back()->setOnSlot(Counters[state][_ACMS_WRITER_SLOT]);
		} else {
			
			string laux = "l";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_WRITER_CELL] << flush;
			saa << Counters[state][_ACMS_WRITER_SLOT] << flush;
			saa << _counters[_ACMS_WRITER_CELL] << flush;
			saa << _counters[_ACMS_WRITER_SLOT] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);

			ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
		}
	} else if (type == _ARC_READ) {
		
		if (Counters[state][_ACMS_READER_STEP] == _ACMS_STEP_2) {
			
			string laux = "m";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			saa << Counters[state][_ACMS_READER_SLOT] << flush;
			saa << _counters[_ACMS_READER_CELL] << flush;
			saa << _counters[_ACMS_READER_SLOT] << flush;
			laux.append(saa.str());
			
			if (ACMChannel->getType() == _CHANNEL_OWRRBB
				|| Counters[state][_ACMS_READER_CELL] != \
				   _counters[_ACMS_READER_CELL]
				|| Counters[state][_ACMS_READER_SLOT] != \
				   _counters[_ACMS_READER_SLOT]) {
				
				ACM->insertState(label.c_str());
				All.insert(All.end(), succ);
				New.insert(New.begin(), ACM->getTarget(label.c_str()));
				
				Counters.insert(Counters.end(), _counters);
				LastCounters.insert(LastCounters.end(), _lastcounters);
				
				insertArc(proc, state, ACM->getTarget(label.c_str()), laux);

				ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
			}
		} else {
			
			ACM->insertState(label.c_str());
			All.insert(All.end(), succ);
			New.insert(New.begin(), ACM->getTarget(label.c_str()));
			
			Counters.insert(Counters.end(), _counters);
			LastCounters.insert(LastCounters.end(), _lastcounters);
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			saa << Counters[state][_ACMS_READER_SLOT] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(Counters[state][_ACMS_READER_CELL]);
			ACM->Arcs.back()->setOnSlot(Counters[state][_ACMS_READER_SLOT]);
		}
	}
				
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createNewStateOW()" 
			 << endl;
	#endif
}

/**
 * \brief	Creates a new state and adds it to the state space.
 * 
 * \fn		void StateGraph::createNewStateRR(int proc, int arc, int state, 
															vector<int> succ)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc (step) of <i>proc</i> that will be
 * 			executed.
 * \param	state: the target of the current state.
 * \param	succ: the state that is reached when running the process
 * 			<i>proc</i> one step.
 * 
 * Creates a new state and adds it to the state space. This method is used only
 * in the case that the channel is of type <code>_CHANNEL_RRBB</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::createNewStateRR(int proc, int arc, int state, vector<int> succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createNewStateRR()"
			 << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	int cells = ACMChannel->getCells();
	
	ostringstream saux;
	string label;
	
	saux << ACM->States.size() << flush;
	label = saux.str();
	
	if (type == _ARC_WRITE) {
		
		ACM->insertState(label.c_str());
		
		All.insert(All.end(), succ);
		New.insert(New.begin(), ACM->getTarget(label.c_str()));
		Counters.insert(Counters.end(), _counters);
		
		if (Counters[state][_ACMS_WRITER_STEP] == _ACMS_STEP_1) {
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << _counters[_ACMS_WRITER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(_counters[_ACMS_WRITER_CELL]);
		} else { // Counters[state][channel][_ACMS_WRITER_STEP] == _ACMS_STEP_2
			
			string laux = "l";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_WRITER_CELL] << flush;
			saa << _counters[_ACMS_WRITER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);

			ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
		}
	} else if (type == _ARC_READ) {
		
		ACM->insertState(label.c_str());
		All.insert(All.end(), succ);
		New.insert(New.begin(), ACM->getTarget(label.c_str()));
		
		Counters.insert(Counters.end(), _counters);
		
		if (Counters[state][_ACMS_READER_STEP] == _ACMS_STEP_1) {
			
			string laux = "m";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			saa << _counters[_ACMS_READER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);

			ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
		} else { // Counters[state][channel][_ACMS_READER_STEP] == _ACMS_STEP_2
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, ACM->getTarget(label.c_str()), laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(Counters[state][_ACMS_READER_CELL]);
		}
	}
				
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createNewStateRR()" 
			 << endl;
	#endif
}

/**
 * \brief	Creates a new arc and adds it to the state space.
 * 
 * \fn		void StateGraph::createNewArc(int proc, int arc, int state,
  																	int succ)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc being executed in<i>proc</i>.
 * \param	state: the current state of the system.
 * \param	succ: the successor state of <i>state</i>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::createNewArc(int proc, int arc, int state, int succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createNewArc()" << endl;
	#endif
	
	if (Processes[proc]->Arcs[arc]->isIO()) {
		
		int channel = Processes[proc]->Arcs[arc]->getChannel();
		
		switch (ACMChannel->getType()) {
			
			case _CHANNEL_OWBB:
				
				createNewArcOW(proc, arc, state, succ);
				break;
			
			case _CHANNEL_RRBB:
				
				createNewArcRR(proc, arc, state, succ);
				break;
			
			case _CHANNEL_OWRRBB:
				
				createNewArcOW(proc, arc, state, succ);
				break;
			
			default:
				
				Penknife::pkerrors(_ACMS_ERROR_POL_N_IMPLEMENTED, "UNKOWN");
				exit(_ACMS_ERROR_CODE_POL_N_IMPLEMENTED);
		}
	} else {
		
		insertArc(proc, state, succ, Processes[proc]->Arcs[arc]->getLabel());
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createNewArc()" << endl;
	#endif
}

/**
 * \brief	Creates a new arc and adds it to the state space.
 * 
 * \fn		void StateGraph::createNewArcOW(int proc, int arc, int state,
  																	int succ)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc being executed in<i>proc</i>.
 * \param	state: the current state of the system.
 * \param	succ: the successor state of <i>state</i>.
 * 
 * Creates a new arc and adds it to the state space. This method is used only
 * in the case that the channel is of type <code>_CHANNEL_OWBB</code> or 
 * <code>_CHANNEL_OWRRBB</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::createNewArcOW(int proc, int arc, int state, int succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createNewArcOW()" << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	
	if (type == _ARC_WRITE) {
		
		if (Counters[state][_ACMS_WRITER_STEP] == _ACMS_STEP_1) {
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << Counters[state][_ACMS_WRITER_CELL] << flush;
			saa << Counters[state][_ACMS_WRITER_SLOT] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, succ, laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(Counters[state][_ACMS_WRITER_CELL]);
			ACM->Arcs.back()->setOnSlot(Counters[state][_ACMS_WRITER_SLOT]);
		} else {
			
			string aa = "l";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_WRITER_CELL] << flush;
			saa << Counters[state][_ACMS_WRITER_SLOT] << flush;
			saa << _counters[_ACMS_WRITER_CELL] << flush;
			saa << _counters[_ACMS_WRITER_SLOT] << flush;
			aa.append(saa.str());
			
			insertArc(proc, state, succ, aa);

			ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
		}
	} else if (type == _ARC_READ) {
		
		if (Counters[state][_ACMS_READER_STEP] == _ACMS_STEP_2) {
			
			string laux = "m";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			saa << Counters[state][_ACMS_READER_SLOT] << flush;
			saa << _counters[_ACMS_READER_CELL] << flush;
			saa << _counters[_ACMS_READER_SLOT] << flush;
			laux.append(saa.str());
			
			if (ACMChannel->getType() == _CHANNEL_OWRRBB
				|| Counters[state][_ACMS_READER_CELL] != \
				   _counters[_ACMS_READER_CELL]
				|| Counters[state][_ACMS_READER_SLOT] != \
				   _counters[_ACMS_READER_SLOT]) {
				
				insertArc(proc, state, succ, laux);

				ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
			}
		} else {
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << _counters[_ACMS_READER_CELL] << flush;
			saa << _counters[_ACMS_READER_SLOT] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, succ, laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(_counters[_ACMS_READER_CELL]);
			ACM->Arcs.back()->setOnSlot(_counters[_ACMS_READER_SLOT]);
		}
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createNewArcOW()" << endl;
	#endif
}

/**
 * \brief	Creates a new arc and adds it to the state space.
 * 
 * \fn		void StateGraph::createNewArcRR(int proc, int arc, int state, int succ)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc being executed in<i>proc</i>.
 * \param	state: the current state of the system.
 * \param	succ: the successor state of <i>state</i>.
 * 
 * Creates a new arc and adds it to the state space. This method is used only
 * in the case that the channel is of type <code>_CHANNEL_RRBB</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::createNewArcRR(int proc, int arc, int state, int succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " createNewArcRR()" << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	int cells = ACMChannel->getCells();
	
	ostringstream saux;
	string label;
	
	saux << ACM->States.size() << flush;
	label = saux.str();
	
	if (type == _ARC_WRITE) {
		
		if (Counters[state][_ACMS_WRITER_STEP] == _ACMS_STEP_1) {
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << _counters[_ACMS_WRITER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, succ, laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(_counters[_ACMS_WRITER_CELL]);
		} else if (Counters[state][_ACMS_WRITER_STEP] == _ACMS_STEP_2) {
			
			string laux = "l";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_WRITER_CELL] << flush;
			saa << _counters[_ACMS_WRITER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, succ, laux);

			ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
		}
	} else if (type == _ARC_READ) {
		
		if (Counters[state][_ACMS_READER_STEP] == _ACMS_STEP_1) {
			
			string laux = "m";
			ostringstream saa;
			
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			saa << _counters[_ACMS_READER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, succ, laux);

			ACM->Arcs.back()->setIO(_ARC_CONTROL, channel);
		} else if (Counters[state][_ACMS_READER_STEP] == _ACMS_STEP_2) {
			
			string laux = Processes[proc]->Arcs[arc]->getLabel();
			ostringstream saa;
			
			saa << "_" << flush;
			saa << Counters[state][_ACMS_READER_CELL] << flush;
			laux.append(saa.str());
			
			insertArc(proc, state, succ, laux);
			
			ACM->Arcs.back()->setIO(type, channel);
			ACM->Arcs.back()->setOnCell(Counters[state][_ACMS_READER_CELL]);
		}
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /createNewArcRR()" << endl;
	#endif
}

/**
 * \brief	Checks if there is a changing in the state vector.
 * 
 * \fn		int StateGraph::nextState(int state, int proc, int pcurr, int arc, 
																	int psucc)
 * \param	state: the target of the current state of the <code>ACM</code>.
 * \param	proc: the target of the process that will run.
 * \param	pcurr: the target of the current state of <i>proc</i>.
 * \param	arc: the target of the arc in <i>proc</i> that will execute.
 * \param	psucc: the possible successor of <i>state</i> in <i>proc</i>.
 * \return	The target of the next state. If <i>arc</i> is not an IO operation
 * 			or if there is some pending in the IO, it returns <i>succ</i>.
 * 			Otherwise, it returns <i>state</i>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	07/09/2004
 */
int StateGraph::nextState(int state, int proc, int pcurr, int arc, int psucc)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " nextState()" << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	
	if (type == _ARC_WRITE 
		&& Counters[state][_ACMS_WRITER_STEP] == _ACMS_STEP_2) {
		
		return psucc;
	} else if (type == _ARC_READ
		&& Counters[state][_ACMS_READER_STEP] == _ACMS_STEP_2) {
			
		return psucc;
	} else if (type == _ARC_NONE) {
		
		return psucc;
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /nextState()" << endl;
	#endif
	
	return pcurr;
}

/**
 * \brief	Generates the state vector of the next state to be reached.
 * 
 * \fn		void StateGraph::nextCounters(int proc, int arc, int state)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc (step) of <i>proc</i> that will be
 * 			executed.
 * \param	state: the target of the current state.
 * 
 * Generates the state vector of the next state to be reached and stores the
 * result in the class attribute <code>_counters</code>. In fact this method is 
 * just a layer to call the correct method.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::nextCounters(int proc, int arc, int state)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " nextCounters()" << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	
	if (Processes[proc]->Arcs[arc]->isIO()) {
		
		switch(ACMChannel->getType()) {
			
			case _CHANNEL_OWBB:
				
				nextCountersOW(proc, arc, state);
				break;
			
			case _CHANNEL_RRBB:
				
				nextCountersRR(proc, arc, state);
				break;
			
			case _CHANNEL_OWRRBB:
				
				nextCountersOW(proc, arc, state);
				break;
			
			default :
				
				Penknife::pkerrors(_ACMS_ERROR_POL_N_IMPLEMENTED, "UNKOWN");
				exit(_ACMS_ERROR_CODE_POL_N_IMPLEMENTED);
		}
	} else {
		
		_counters = Counters[state];
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /nextCounters()" << endl;
	#endif
}

/**
 * \brief	Generates the state vector of the next state to be reached.
 * 
 * \fn		void StateGraph::nextCountersOW(int proc, int arc, int state)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc (step) of <i>proc</i> that will be
 * 			executed.
 * \param	state: the target of the current state.
 * 
 * Generates the state vector of the next state to be reached and stores the
 * result in the class attribute <code>_counters</code>. This method is used
 * only in the case that the channel is of type <code>_CHANNEL_OWRRBB</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/01/2006
 */
void StateGraph::nextCountersOW(int proc, int arc, int state)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " nextCountersOW()" << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	int cells = ACMChannel->getCells();
	int slots = ACMChannel->getSlots();
	
	_counters = Counters[state];
	_lastcounters = LastCounters[state];
	
	isRRBB =  false;
	
	int lastsize = _lastcounters.size();
	
	if (type == _ARC_WRITE) {
		
		int acell = _counters[_ACMS_WRITER_CELL];
		
		if (_counters[_ACMS_WRITER_STEP] == _ACMS_STEP_1) {
			
			_counters[_ACMS_WRITER_STEP] = \
				(_counters[_ACMS_WRITER_STEP] + 1) % 2;
			
		} else if (_counters[_ACMS_WRITER_STEP] == _ACMS_STEP_2) {
			
			int nextcell = (acell + 1) % cells;
			int nextslot = 1;
			
			if (nextcell == _counters[_ACMS_READER_CELL] 
				&& nextslot == _counters[_ACMS_READER_SLOT]) {
				
				nextslot = (nextslot + 1) % slots;
			}
			
			if (lastsize < ((cells - 1) * slots)) {
				
				_lastcounters.insert(_lastcounters.begin(), \
					_counters[_ACMS_WRITER_SLOT]);
				_lastcounters.insert(_lastcounters.begin(), \
					_counters[_ACMS_WRITER_CELL]);
			} else {
				
				_lastcounters.pop_back();
				_lastcounters.pop_back();
				_lastcounters.insert(_lastcounters.begin(), \
					_counters[_ACMS_WRITER_SLOT]);
				_lastcounters.insert(_lastcounters.begin(), \
					_counters[_ACMS_WRITER_CELL]);
			}
			
			_counters[_ACMS_OVER] = 0 ? nextslot == 1 : 1;
				
			_counters[_ACMS_WRITER_CELL] = nextcell;
			_counters[_ACMS_WRITER_SLOT] = nextslot;
			
			_counters[_ACMS_WRITER_STEP] = \
				(_counters[_ACMS_WRITER_STEP] + 1) % 2;
		}
	} else if (type == _ARC_READ) {
		
		int acell = _counters[_ACMS_READER_CELL];
		
		if (_counters[_ACMS_READER_STEP] == _ACMS_STEP_1) {
			
			_counters[_ACMS_READER_STEP] = \
				(_counters[_ACMS_READER_STEP] + 1) % 2;
		} else if (_counters[_ACMS_READER_STEP] == _ACMS_STEP_2) {
			
			if (_lastcounters.size() >= 2) {
				
				_counters[_ACMS_READER_SLOT] = _lastcounters[lastsize - 1];
				_counters[_ACMS_READER_CELL] = _lastcounters[lastsize - 2];
				_counters[_ACMS_OVER] = 0;
				
				_lastcounters.pop_back();
				_lastcounters.pop_back();
			}
				
			_counters[_ACMS_READER_STEP] = \
				(_counters[_ACMS_READER_STEP] + 1) % 2;
		}
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /nextCountersOW()" << endl;
	#endif
}

/**
 * \brief	Generates the state vector of the next state to be reached.
 * 
 * \fn		void StateGraph::nextCountersRR(int proc, int arc, int state)
 * \param	proc: the target of the running process.
 * \param	arc: the target of the arc (step) of <i>proc</i> that will be
 * 			executed.
 * \param	state: the target of the current state.
 * 
 * Generates the state vector of the next state to be reached and stores the
 * result in the class attribute <code>_counters</code>. This method is used 
 * only in the case that the channel is of type <code>_CHANNEL_RRBB</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
void StateGraph::nextCountersRR(int proc, int arc, int state)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " nextCountersRR()" << endl;
	#endif
	
	int channel = Processes[proc]->Arcs[arc]->getChannel();
	int type = Processes[proc]->Arcs[arc]->getIOType();
	int cells = ACMChannel->getCells();
	
	_counters = Counters[state];
	
	isRRBB =  true;
	
	if (cells == _CHANNEL_MIN_CELLS) {
		
		if (type == _ARC_WRITE) {
			
			int next = (_counters[_ACMS_WRITER_CELL] + 1) % cells;
			
			if (_counters[_ACMS_WRITER_STEP] == _ACMS_STEP_1
				&& _counters[_ACMS_READER_CELL] != \
				   _counters[_ACMS_WRITER_CELL]) {
				
				_counters[_ACMS_WRITER_STEP] = _ACMS_STEP_2;
			} else if (_counters[_ACMS_WRITER_STEP] == _ACMS_STEP_2) {
				
				_counters[_ACMS_WRITER_CELL] = next;
				_counters[_ACMS_WRITER_STEP] = _ACMS_STEP_1;
			}
		} else if (type == _ARC_READ) {
			
			if (_counters[_ACMS_READER_STEP] == _ACMS_STEP_1) {
				
				_counters[_ACMS_READER_CELL] = \
					(_counters[_ACMS_WRITER_CELL] + 1) % cells;
			}
			
			_counters[_ACMS_READER_STEP] = \
				(_counters[_ACMS_READER_STEP] + 1) % 2;
		}
	} else if (cells > _CHANNEL_MIN_CELLS) {
		
		if (type == _ARC_WRITE) {
			
			int next = (_counters[_ACMS_WRITER_CELL] + 1) % cells;
			
			if (_counters[_ACMS_WRITER_STEP] == _ACMS_STEP_1) {
				
				_counters[_ACMS_WRITER_STEP] = _ACMS_STEP_2;
			} else if (_counters[_ACMS_WRITER_STEP] == _ACMS_STEP_2
				&& _counters[_ACMS_READER_CELL] != next) {
				
				_counters[_ACMS_WRITER_CELL] = next;
				_counters[_ACMS_WRITER_STEP] = _ACMS_STEP_1;
			}
		} else if (type == _ARC_READ) {
			
			int next = (_counters[_ACMS_READER_CELL] + 1) % cells;
			
			if (_counters[_ACMS_READER_STEP] == _ACMS_STEP_1
				&& next != _counters[_ACMS_WRITER_CELL]) {
				
				_counters[_ACMS_READER_CELL] = next;
			}
			
			_counters[_ACMS_READER_STEP] = \
				(_counters[_ACMS_READER_STEP] + 1) % 2;
		}
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /nextCountersRR()"
			 << endl;
	#endif
}

/**
 * \brief	Checks if a vector state was previously generated.
 * 
 * \fn		int StateGraph::exists(vector<int> succ)
 * \param	succ: the state that is reached when running the process
 * 			<i>proc</i> one step.
 * \return	The position af the state <i>state</i> if it is present in the
 * 			vector <code>All</code> of all generated states.
 * 			<code>_ACMS_NONE</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	21/09/2004
 */
int StateGraph::exists(vector<int> succ)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " exists()" << endl;
	#endif
	
	int cont, size;
	
	size = All.size();
	for (cont = 0; cont < size; cont++) {
		
		if (isRRBB == true 
			&& succ == All[cont] 
			&& _counters == Counters[cont]) {
			
			return cont;
		} else if (isRRBB == false
					&& succ == All[cont]
					&& _counters == Counters[cont] 
					&& _lastcounters == LastCounters[cont]) {
			
			return cont;
		}
	}
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /exists()" << endl;
	#endif
	
	return _ACMS_NONE;
}

/**
 * \brief	Inserts a new <b>Arc</b> in the process <b>ACM</b>.
 * 
 * \fn		void StateGraph::insertArc(int proc, int src, int dest, string lab)
 * \param	proc: target of the process.
 * \param	src: target of the source state in process <i>proc</i>.
 * \param	dest: target of the destination state in process <i>proc</i>.
 * \param	lab: the label of the arc to be created.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	20/07/2004
 */
void StateGraph::insertArc(int proc, int src, int dest, string lab)
{
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " insertArc()" << endl;
	#endif
	
	string label;
	
	label = Processes[proc]->getLabel();
	label.append(".");
	label.append(lab);
					
	ACM->insertArc(src, label.c_str(), dest);
	
	#ifdef _JABUTI_ACMS_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertArc()" << endl;
	#endif
}

/**
 * \brief	Converts an <code>ACM</code> into a <code>PNmodel</code>.
 * 
 * \fn		PNmodel * StateGraph::acm2petrinet(void)
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/01/2005
 */
PNmodel * StateGraph::acm2petrinet(void)
{
	switch (ACMChannel->getType()) {
		
		case _CHANNEL_RRBB:
			
			return acm2petrinetRR();
			break;
		
		case _CHANNEL_OWBB:
		case _CHANNEL_OWRRBB:
			
			return acm2petrinetOW();
			break;
	}
}

/**
 * \brief	Converts an <code>ACM</code> into a <code>PNmodel</code>.
 * 
 * \fn		PNmodel * StateGraph::acm2petrinetRR(void)
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/01/2005
 */
PNmodel * StateGraph::acm2petrinetRR(void)
{
	PNmodel *pn = new PNmodel();
	
	int cont, cells, states;
	string prefix;
	
	cells = ACMChannel->getCells();
	states = Counters.size();
	
	for (cont = 0; cont < cells; cont++) {
		
		ostringstream saux;
		saux << cont << flush;
		
		prefix = "w!=";
		prefix.append(saux.str());
		
		pn->insertPlace(prefix);
		
		if (cont != cells - 1) {
			
			pn->setTokens(cont * 2, 1);
		}
		
		prefix = "r!=";
		prefix.append(saux.str());
		
		pn->insertPlace(prefix);
		
		if (cont != 0) {
			
			pn->setTokens(cont * 2 + 1, 1);
		}
	}
	
	for (cont = 0; cont < states; cont++) {
		
		
	}
	
	return pn;
}

/**
 * \brief	Converts an <code>ACM</code> into a <code>PNmodel</code>.
 * 
 * \fn		PNmodel * StateGraph::acm2petrinetOW(void)
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/01/2005
 */
PNmodel * StateGraph::acm2petrinetOW(void)
{
	return NULL;
}

/**
 * \brief	Converts an <code>ACM</code> to the Petrify format.
 * 
 * \fn		void StateGraph::acm2petrify(char *cmd[])
 * \param	*cmd[]: the command line.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/01/2005
 */
void StateGraph::acm2petrify(char *cmd[])
{
	vector<string> internal = getEvents(_ARC_WRITE);
	vector<string> outputs = getEvents(_ARC_CONTROL);
	vector<string> dummy = getEvents(_ARC_NONE);

	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	// Prints header of the model
	cout << "# Generated by jabuti " << _acms_version << " (compiled "
		 << __DATE__ << " at " << __TIME__ << ")" << endl;
	cout << "#";
	
	int i = 0;
	while (cmd[i] != NULL) cout << " " << cmd[i++];
	
	cout << endl;
	cout << "# " << asctime(timeinfo);
	cout << "# ";
	cout << ACM->States.size() << " states -- ";
	cout << ACM->Arcs.size() << " arcs" << endl;
	
	// Prints information about the model
	cout << ".model " << ACM->getLabel() << endl;
	
	// Prints list of INTERNAL events
	if (internal.size() > 0) {
		
		cout << ".internal";
		
		for (int cont = 0; cont < internal.size(); cont++) {
			
			cout << " " << internal[cont];
		}
		
		cout << endl;
	}

	// Prints list of OUTPUTS events
	if (outputs.size() > 0) {
		
		cout << ".outputs";
		
		for (int cont = 0; cont < outputs.size(); cont++) {
			
			cout << " " << outputs[cont];
		}
		
		cout << endl;
	}
	
	// Prints other events
	if (dummy.size() > 0) {
		
		cout << ".dummy";
		
		for (int cont = 0; cont < dummy.size(); cont++) {
			
			cout << " " << dummy[cont];
		}
		
		cout << endl;
	}
	
	// Prints process info
	for (int cont = 0; cont < Processes.size(); cont++) {
		
		string prefix = Processes[cont]->getLabel();
		vector<string> arcs;

		prefix.append(".");
		
		cout << ".process " << cont;

		for (int c2 = 0; c2 < ACM->Arcs.size(); c2++) {
			
			int c3;

			if (ACM->Arcs[c2]->getLabel().find(prefix.c_str(), 0) == 0) {
				
				for (c3 = 0; c3 < arcs.size(); c3++) {
					
					if (arcs[c3] == ACM->Arcs[c2]->getLabel())
						break;
				}
				
				if (c3 == arcs.size()) {
					
					arcs.insert(arcs.end(), ACM->Arcs[c2]->getLabel());
					cout << " " << ACM->Arcs[c2]->getLabel();	
				}
			}
		}

		cout << endl;
	}
	
	// Prints State Graph
	cout << ".state graph" << " # begin state graph" << endl;
	
	for (int cont = 0; cont < ACM->Arcs.size(); cont++) {
		
		cout << "s" << ACM->States[ACM->Arcs[cont]->getSrc()]->getLabel() << " ";
		cout << ACM->Arcs[cont]->getLabel() << " ";
		cout << "s" << ACM->States[ACM->Arcs[cont]->getDest()]->getLabel() << endl;
	}
		
	cout << ".marking{s" << ACM->States[0]->getLabel() << "}" << endl;
	cout << ".end" << " # end state graph" << endl;
}

/**
 * \brief	Looks for all arcs of a specific type.
 * 
 * \fn		vector<string> StateGraph::getEvents(int t)
 * \param	t: the type of the arc to look for. May be:
 *				- <code>_ARC_CONTROL</code> if we are looking for all
 *				  arcs that does some control action, or
 *				- <code>_ARC_NONE</code> for the arcs of others types.
 * \return	A vector with the set of arcs of the desired type.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/01/2005
 */
vector<string> StateGraph::getEvents(int t)
{
	vector<string> arcs;
	int i;
	int size = ACM->Arcs.size();

	for (int cont = 0; cont < size; cont++) {
		
		if (ACM->Arcs[cont]->getIOType() == _ARC_CONTROL && t == _ARC_CONTROL) {
			
			for (i = 0; i < arcs.size(); i++) {
				
				if (arcs[i] == ACM->Arcs[cont]->getLabel())
					break;
			}
			
			if (i == arcs.size()) {
				
				arcs.insert(arcs.end(), ACM->Arcs[cont]->getLabel());
			}
		} else if ((ACM->Arcs[cont]->getIOType() == _ARC_WRITE
				||  ACM->Arcs[cont]->getIOType() == _ARC_READ)
			&& (t == _ARC_WRITE || t == _ARC_READ)) {
			
			for (i = 0; i < arcs.size(); i++) {
				
				if (arcs[i] == ACM->Arcs[cont]->getLabel())
					break;
			}
			
			if (i == arcs.size()) {
				
				arcs.insert(arcs.end(), ACM->Arcs[cont]->getLabel());
			}
		} else if (ACM->Arcs[cont]->getIOType() == _ARC_NONE 
			&& t == _ARC_NONE) {
			
			for (i = 0; i < arcs.size(); i++) {
				
				if (arcs[i] == ACM->Arcs[cont]->getLabel())
					break;
			}
			
			if (i == arcs.size()) {
				
				arcs.insert(arcs.end(), ACM->Arcs[cont]->getLabel());
			}
		}
	}
	
	return arcs;
}
