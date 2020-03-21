/****************************************************************************** 
 *
 *                 (C) Copyright 1982-2015 by Autodesk, Inc.
 *
 * The information contained herein is confidential, proprietary to Autodesk,
 * Inc., and considered a trade secret as defined in section 499C of the
 * penal code of the State of California.  Use of this information by anyone
 * other than authorized employees of Autodesk, Inc. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 *        AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
 *        AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
 *        MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
 *        DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
 *        UNINTERRUPTED OR ERROR FREE.
 *
 ******************************************************************************/
/*
 *
 * Name:            ClmLicenseMgr.h
 *
 * Description:     Header file to represent the ClmLicenseMgr.
 *
 */
//////////////////////////////////////////////////////////////////////////
#ifndef CLMLICENSEMGR_H
#define CLMLICENSEMGR_H
//////////////////////////////////////////////////////////////////////////
#include "ClmLicenseMgrCore.h"
//////////////////////////////////////////////////////////////////////////
namespace CLM { namespace LicenseServices {
//////////////////////////////////////////////////////////////////////////
class ClmLicenseMgrImp;
//////////////////////////////////////////////////////////////////////////
class ClmLicenseMgr : public ClmLicenseMgrCore
{
public:

    // Returns the singleton instance of the ClmLicenseMgr class.
    // Can be called anywhere to retrieve the LicenseMgr pointer. 
    // *** Call this as early as you can in your startup to benefit from asynchronous initialization of webkit
    // Note: LicenseMgr is NOT guaranteed thread safe
    CLMINT_LINKAGE static ClmLicenseMgr* ClicGetInstance();
		// sets a custom derived ClmLicenseMgr instance
		CLMINT_LINKAGE static bool ClicSetInstance(ClmLicenseMgr *instance);
		// checks if ClmLicenseMgr has been instantiated
		CLMINT_LINKAGE static bool ClicHasInstance();
		// Cleans up the License manager. 
		// When product crash, calling this API and set bCrash = true to place mark in usage based report
		CLMINT_LINKAGE static ClmStatus ClicCleanUp(bool bCrash = false);

protected:

	CLMINT_LINKAGE ClmLicenseMgr();
	CLMINT_LINKAGE virtual ~ClmLicenseMgr();

private:

    static ClmLicenseMgr *mInstance;

    ClmLicenseMgrImp *mImp;
public:
		ClmLicenseMgrImp *GetImp(){return mImp;};
};

}}

#endif //CLMLICENSEMGR_H

