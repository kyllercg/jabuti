/**
 * \file		acms/Penknife.h
 * \brief		The definition of the <b>Penknife</b> class.
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

//#include <iostream>

#ifndef PENKNIFE_H
#define PENKNIFE_H

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * ERRORS MESSAGE
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
/** Message error: error when opening file. */
#define _PK_ERROR_OPEN_FILE				"error opening input file"

/**
 * \class	Penknife Penknife.h
 * \brief	The <b>Penknife</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	June, 2004
 * 
 * The <b>Penknife</b> class. As the name sugests, this class implements some
 * (maybe many) methods that may be usefull in many different places.
 */
class Penknife {

	public:

		Penknife();								/* class constructor */
		~Penknife();							/* class destructor */
		static void pkerrors(char *m);			/* prints error message */
		static void pkerrors(char *m, char *f);	/* prints error message */	
};
#endif /* PENKNIFE_H */
