#ifndef _MCallbackIdArray
#define _MCallbackIdArray
//-
// ===========================================================================
// Copyright 2017 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//+
//
// CLASS:    MCallbackIdArray
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MTypes.h>
#include <maya/MStatus.h>
#include <maya/MMessage.h>



OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MCallbackIdArray)

//! \ingroup OpenMaya
//! \brief Array of MCallbackId data type. 
/*!
This class implements an array of MCallbackId.  Common convenience functions
are available, and the implementation is compatible with the internal
Maya implementation so that it can be passed efficiently between plugins
and internal maya data structures.
*/
class OPENMAYA_EXPORT MCallbackIdArray
{

public:
					MCallbackIdArray();
					MCallbackIdArray( const MCallbackIdArray& other );
					MCallbackIdArray( unsigned int initialSize,
							   MCallbackId initialValue = 0 );
					~MCallbackIdArray();
 	MCallbackId		operator[]( unsigned int index ) const;
 	MCallbackIdArray& operator=( const MCallbackIdArray & other );
	MStatus			set( MCallbackId element, unsigned int index );
	MStatus			setLength( unsigned int length );
 	unsigned int        length() const;
 	MStatus			remove( unsigned int index );
 	MStatus			insert( MCallbackId element, unsigned int index );
 	MStatus			append( MCallbackId element );
 	MStatus         copy( const MCallbackIdArray& source );
 	MStatus		 	clear();
	void			setSizeIncrement ( unsigned int newIncrement );
	unsigned int		sizeIncrement () const;

BEGIN_NO_SCRIPT_SUPPORT:

 	//!	NO SCRIPT SUPPORT
	MCallbackIdArray( const MCallbackId src[], unsigned int count );

	//!	NO SCRIPT SUPPORT
	MStatus			get( MCallbackId[] ) const;

	//!	NO SCRIPT SUPPORT
 	MCallbackId&	 operator[]( unsigned int index );

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT std::ostream &operator<<(std::ostream &os,
											   const MCallbackIdArray &array);

END_NO_SCRIPT_SUPPORT:

	static const char* className();

protected:
// No protected members

private:
	MCallbackIdArray( void* );
 	void* fArray;
	bool   own;
};

OPENMAYA_NAMESPACE_CLOSE

#endif /* __cplusplus */
#endif /* _MCallbackIdArray */
