/**
 * \file		petri/PNmodel.cpp
 * \brief		The methods of the <b>PNmodel</b> class.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		January, 2005
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

#include "PNmodel.h"

#include <iostream>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CLASS CONSTRUCTORS / DESTRUCTOR
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Class constructor. Creates a new PNmodel object.
 * 
 * \fn		PNmodel::PNmodel()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
PNmodel::PNmodel()
{}

/**
 * \brief	Class destructor.
 * 
 * \fn		PNmodel::~PNmodel()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
PNmodel::~PNmodel()
{}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * PUBLIC METCHDS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Gets the label of the Petri net model.
 * 
 * \fn		string PNmodel::getLabel()
 * \return	The label of the Petri net model stored in the <code>label</code>
 * 			attribute.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
string PNmodel::getLabel()
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getLabel()" << endl;
	#endif
	
	return label;
}

/**
 * \brief	Gets the label of a place.
 * 
 * \fn		string PNmodel::getPlaceLabel(int t)
 * \param	t: the target of the place to find the label.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
string PNmodel::getPlaceLabel(int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getPlaceLabel()" << endl;
	#endif
	
	return P[t]->getLabel();
}

/**
 * \brief	Gets the label of a transition.
 * 
 * \fn		string PNmodel::getTransitionLabel(int t)
 * \param	t: the target of the transition to find the label.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
string PNmodel::getTransitionLabel(int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getTransitionLabel()" << endl;
	#endif
	
	return T[t]->getLabel();
}

/**
 * \brief	Gets all places of the system.
 * 
 * \fn		vector<int> PNmodel::getPlaces()
 * \return	a vector of all places of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> PNmodel::getPlaces()
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getPlaces()" << endl;
	#endif
	
	vector<int> vp;
	
	for (int c = 0; c < P.size(); c++) {
		
		vp.push_back(P[c]->getTarget());
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /getPlaces()" << endl;
	#endif
	
	return vp;
}

/**
 * \brief	Gets all transitions of the system.
 * 
 * \fn		vector<int> PNmodel::getTransitions()
 * \return	a vector of all transitions of the system.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> PNmodel::getTransitions()
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getTransitions()" << endl;
	#endif
	
	vector<int> vt;
	
	for (int c = 0; c < T.size(); c++) {
		
		vt.push_back(T[c]->getTarget());
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /getTransitions()" << endl;
	#endif
	
	return vt;
}

/**
 * \brief	Gets all transitions of a specific type.
 * 
 * \fn		vector<string> PNmodel::getTransitions(int t)
 * \param	t: the type of transitions to look for.
 * \return	a vector of all transitions of type specifyied by <code>t</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<string> PNmodel::getTransitions(int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getTransitions()" << endl;
	#endif
	
	vector<string> vt;
	
	for (int c = 0; c < T.size(); c++) {
		
		if (T[c]->getType() == t) {
			
			vt.push_back(T[c]->getLabel());
		}
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /getTransitions()" << endl;
	#endif
	
	return vt;
}

/**
 * \brief	Sets the label of the Petri net model.
 * 
 * \fn		void PNmodel::setLabel(string l)
 * \param	l: the new label of the state.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void PNmodel::setLabel(string l)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  setLabel()" << endl;
	#endif
	
	label = l;
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setLabel()" << endl;
	#endif
}

/**
 * \brief	Gets all all output transitions of a place.
 * 
 * \fn		vector<int> PNmodel::getOutPlaces(int t)
 * \param	t: the target of the place.
 * \return	a vector of all output transitions of place <code>t</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> PNmodel::getOutPlaces(int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getOutPlaces()" << endl;
	#endif
	
	return P[t]->getOut();
}

/**
 * \brief	Gets all all output places of a transition.
 * 
 * \fn		vector<int> PNmodel::getOutTransitions(int t)
 * \param	t: the target of the transition.
 * \return	a vector of all output places of transition <code>t</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> PNmodel::getOutTransitions(int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getOutTransitions()" << endl;
	#endif
	
	return T[t]->getOut();
}

/**
 * \brief	Gets the amount of tokens in a place
 * 
 * \fn		int PNmodel::getTokens(int t)
 * \param	t: the target of the place.
 * \return	the amount of tokens in a place <code>t</code>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int PNmodel::getTokens(int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  getTokens()" << endl;
	#endif
	
	return P[t]->getTokens();
}

/**
 * \brief	Sets the label of the Petri net model.
 * 
 * \fn		void PNmodel::setLabel(const char *l)
 * \param	*l: the new label of the state.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void PNmodel::setLabel(const char *l)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  setLabel()" << endl;
	#endif
	
	label = l;
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setLabel()" << endl;
	#endif
}

/**
 * \brief	Sets the number of tokens stored in a given place.
 * 
 * \fn		void PNmodel::setTokens(string l, int n)
 * \param	l: the label of the place.
 * \param	n: the amount of tokens to store on the place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void PNmodel::setTokens(string l, int n)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  setTokens()" << endl;
	#endif
	
	int p = existsPlace(l);
	
	P[p]->setTokens(n);
		
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setTokens()" << endl;
	#endif
}

/**
 * \brief	Sets the number of tokens stored in a given place.
 * 
 * \fn		void PNmodel::setTokens(int t, int n)
 * \param	t: the target of the place.
 * \param	n: the amount of tokens to store on the place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void PNmodel::setTokens(int t, int n)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  setTokens()" << endl;
	#endif
	
	P[t]->setTokens(n);
		
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setTokens()" << endl;
	#endif
}

/**
 * \brief	Insert an arc linking a place and a transition.
 * 
 * \fn		void PNmodel::insertArc(int src, int dest, int stype)
 * \param	src: target of the source node.
 * \param	dest: target of the destination node.
 * \param	stype: type of the source node.
 * 			- <b><code>_PN_P</code></b> if the node is a <b>place</b>.
 * 			- <b><code>_PN_T</code></b> if the node is a <b>transition</b>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void PNmodel::insertArc(int src, int dest, int stype)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  insertArc()" << endl;
	#endif
	
	switch (stype) {
		
		case _PN_P:
			
			P[src]->addOut(dest);
			T[dest]->addIn(src);
			break;
		
		case _PN_T:
			
			P[dest]->addIn(src);
			T[src]->addOut(dest);
			break;
		
		default:
			
			cerr << __FILE__ << ": " << __LINE__ << ". Type not allowed." 
				 << " Aborting execution." << endl;
			exit(-100);
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertArc()" << endl;
	#endif
}

/**
 * \brief	Inserts a new place in the Petri net.
 * 
 * \fn		int PNmodel::insertPlace(string l)
 * \param	l: the label of the new place.
 * \return	the target of the inserted place if insertion was ok.
 * 			<code>_PN_ERROR_CODE_NOT_INSERTED</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int PNmodel::insertPlace(string l)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  insertPlace()" << endl;
	#endif
	
	Place *paux = new Place(l, P.size());
	
	if (paux != NULL) {
		
		P.push_back(paux);
		
		#ifdef _JABUTI_CODE_DEBBUGING
			cerr << __FILE__ << ": " << __LINE__ << " /insertPlace()" << endl;
		#endif
		
		return(P.back()->getTarget());
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertPlace()" << endl;
	#endif
	
	return _PN_ERROR_CODE_NOT_INSERTED;
}

/**
 * \brief	Inserts a new transition in the Petri net.
 * 
 * \fn		int PNmodel::insertTransition(string l, int t)
 * \param	l: the label of the new transition.
 * \param	t: the type (internal, output, etc.) of the new transition.
 * \return	the target of the inserted transition if insertion was ok.
 * 			<code>_PN_ERROR_CODE_NOT_INSERTED</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int PNmodel::insertTransition(string l, int t)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  insertTransition()" << endl;
	#endif
	
	Transition *taux = new Transition(l, t, T.size());
	
	if (taux != NULL) {
		
		T.push_back(taux);
		
		#ifdef _JABUTI_CODE_DEBBUGING
			cerr << __FILE__ << ": " << __LINE__ << " /insertT()" << endl;
		#endif
		
		return(T.back()->getTarget());
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertT()" << endl;
	#endif
	
	return _PN_ERROR_CODE_NOT_INSERTED;
}

/**
 * \brief	Checks if a given place was already inserted.
 * 
 * \fn		int PNmodel::existsPlace(string l)
 * \param	l: the label of the place to be checked
 * \return	the target of the place if it was found. Or 
 * 			<code>_PN_ERROR_CODE_NOT_FOUND</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int PNmodel::existsPlace(string l)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  existsPlace()" << endl;
	#endif
	
	for (int i = 0; i < P.size(); i++) {
		
		if (P[i]->getLabel() == l) {
			
			#ifdef _JABUTI_CODE_DEBBUGING
				cerr << __FILE__ << ": " << __LINE__ << " /existsPlace()" << endl;
			#endif
			
			return i;
		}
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /existsPlace()" << endl;
	#endif
	
	return _PN_ERROR_CODE_NOT_FOUND;
}

/**
 * \brief	Checks if a given transition was already inserted.
 * 
 * \fn		int PNmodel::existsTransition(string l)
 * \param	l: the label of the transition to be checked
 * \return	the target of the transition if it was found. Or 
 * 			<code>_PN_ERROR_CODE_NOT_FOUND</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int PNmodel::existsTransition(string l)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  existsTransition()" << endl;
	#endif
	
	for (int i = 0; i < T.size(); i++) {
		
		if (T[i]->getLabel() == l) {
			
			#ifdef _JABUTI_CODE_DEBBUGING
				cerr << __FILE__ << ": " << __LINE__ << " /existsTransition()" << endl;
			#endif
			
			return i;
		}
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /existsTransition()" << endl;
	#endif
	
	return _PN_ERROR_CODE_NOT_FOUND;
}

/**
 * \brief	Checks the type (place or transition) of a given node.
 * 
 * \fn		int PNmodel::typeOf(string l)
 * \param	l: the label of the node to be checked
 * \return	<code>_PN_T</code> if the node is a transition. <code>_PN_P</code>
 * 			if it is a place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int PNmodel::typeOf(string l)
{
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << "  typeOf()" << endl;
	#endif
	
	for (int i = 0; i < T.size(); i++) {
		
		if (T[i]->getLabel() == l) {
			
			#ifdef _JABUTI_CODE_DEBBUGING
				cerr << __FILE__ << ": " << __LINE__ << " /typeOf()" << endl;
			#endif
			
			return _PN_T;
		}
	}
	
	for (int i = 0; i < P.size(); i++) {
		
		if (P[i]->getLabel() == l) {
			
			#ifdef _JABUTI_CODE_DEBBUGING
				cerr << __FILE__ << ": " << __LINE__ << " /typeOf()" << endl;
			#endif
			
			return _PN_P;
		}
	}
	
	#ifdef _JABUTI_CODE_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /typeOf()" << endl;
	#endif
	
	return _PN_ERROR_CODE_NOT_FOUND;
}
