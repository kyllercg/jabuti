/**
 * \file		petri/Place.cpp
 * \brief		The methods of the <b>Place</b> class.
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

#include "Place.h"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CLASS CONSTRUCTORS / DESTRUCTOR
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Class constructor. Creates a new Place object.
 * 
 * \fn		Place::Place()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
Place::Place()
{
	tokens = 0;
}

/**
 * \brief	Class constructor. Creates a new Place object.
 * 
 * \fn		Place::Place(string l, int t)
 * \param	l: the label of the new place.
 * \param	t: the target of the new place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
Place::Place(string l, int t)
{
	label = l;
	target = t;
	tokens = 0;
	
	in.clear();
	out.clear();
}

/**
 * \brief	Class destructor.
 * 
 * \fn		Place::~Place()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
Place::~Place()
{
	in.clear();
	out.clear();
}

/**
 * \brief	Gets the label of the place.
 * 
 * \fn		string Place::getLabel()
 * \return	the label of the place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
string Place::getLabel()
{
	return label;
}

/**
 * \brief	Gets the target of the place.
 * 
 * \fn		int Place::getTarget()
 * \return	the target of the place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int Place::getTarget()
{
	return target;
}

/**
 * \brief	Gets the number of tokens stored in the place.
 * 
 * \fn		int Place::getTokens()
 * \return	the number of tokens stored in the place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int Place::getTokens()
{
	return tokens;
}

/**
 * \brief	Gets the targets of all input transitions of the place.
 * 
 * \fn		vector<int> Place::getIn()
 * \return	a vector with the targets of all input transitions.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> Place::getIn()
{
	return in;
}

/**
 * \brief	Gets the targets of all output transitions of the place.
 * 
 * \fn		vector<int> Place::getOut()
 * \return	a vector with the targets of all output transitions.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> Place::getOut()
{
	return out;
}

/**
 * \brief	Sets the number of tokens stored in the place.
 * 
 * \fn		void Place::setTokens(int n)
 * \param	n: the number of tokens to be stored in the place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void Place::setTokens(int n)
{
	tokens = n;
}

/**
 * \brief	Checks if a given input transition target is already inserted.
 * 
 * \fn		bool Place::existsIn(int n)
 * \param	n: the target of the transition to be checked.
 * \return	<b><code>true</code></b> if the target is present in the 
 * 			<code>in</code> vector. <b><code>false</code></b> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
bool Place::existsIn(int n)
{
	vector<int>::iterator i = in.begin();
	
	while (i != in.end()) {
		
		if (*i == n) {
			
			return true;
		}
	}
	
	return false;
}

/**
 * \brief	Checks if a given output transition target is already inserted.
 * 
 * \fn		bool Place::existsOut(int n)
 * \param	n: the target of the transition to be checked.
 * \return	<b><code>true</code></b> if the target is present in the 
 * 			<code>out</code> vector. <b><code>false</code></b> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
bool Place::existsOut(int n)
{
	vector<int>::iterator i = out.begin();
	
	while (i != in.end()) {
		
		if (*i == n) {
			
			return true;
		}
	}
	
	return false;
}

/**
 * \brief	Adds a new input transition to the place.
 * 
 * \fn		void Place::addIn(int n)
 * \param	n: the target of the input transition.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void Place::addIn(int n)
{
	in.push_back(n);
}

/**
 * \brief	Adds a new output transition to the place.
 * 
 * \fn		void Place::addOut(int n)
 * \param	n: the target of the output transition.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void Place::addOut(int n)
{
	out.push_back(n);
}
