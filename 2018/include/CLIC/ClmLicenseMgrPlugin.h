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
 * Name:            ClmLicenseMgrPlugin
 *
 * Description:     Header file to represent the ClmLicenseMgrPlugin for a plugin DLL.
 *
 */
//////////////////////////////////////////////////////////////////////////
#ifndef CLMLICENSEMGR_PLUGIN_H
#define CLMLICENSEMGR_PLUGIN_H
//////////////////////////////////////////////////////////////////////////
#include "ClmLicenseMgrCore.h"
//////////////////////////////////////////////////////////////////////////
namespace CLM { namespace LicenseServices {
//////////////////////////////////////////////////////////////////////////
class ClmLicenseMgrPluginImp;
//////////////////////////////////////////////////////////////////////////
class ClmLicenseMgrPlugin : public ClmLicenseMgrCore
{
public:
    CLMINT_LINKAGE ClmLicenseMgrPlugin();
    CLMINT_LINKAGE ~ClmLicenseMgrPlugin();

		// This optional (but recommended) function is called by callees before calling Initialize(), its job is to preload the clic base runtime asynchronously to improve startup performance. 
		// NOTES: Call this function about 2-3 seconds before instance->Initialize() and about 2-3 seconds after a initial call to GetInstance()
		CLMINT_LINKAGE virtual ClmStatus ClicPreInitialize(ClmLicenseMgrOptionsBuilder &startupOptions) override;

		// Initializes the License manager and the underlying Clic core Javascript runtime
		// *** To benefit from the improved startup performance, you must call ClmLicenseMgrCore* GetInstance() as soon as possible in your app startup code with ideally a call from PreInitialize()
		// then call this function as late as you can in your app startup
		// Integrating product must call this method before calling of any of the APIs.
		CLMINT_LINKAGE virtual ClmStatus ClicInitialize(ClmLicenseMgrOptionsBuilder &startupOptions) override;

		CLMINT_LINKAGE const clmCHAR *GetProductName();
		CLMINT_LINKAGE void SetProductName(const clmCHAR *friendlyProductName);

private:

	ClmLicenseMgrPluginImp *mImp;
public:
	ClmLicenseMgrPluginImp *GetImp(){return mImp;};
};
}}

#endif //CLMLICENSEMGR_PLUGIN_H
