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
 * Name:            ClmLoader.h
 *
 * Description:     Header file for CLM Loader class (Windows platform only).
 *
 */

#ifndef CLMLOADER_H
#define CLMLOADER_H

// This header file is meant for Windows platform only.
// Mac and Linux platforms doesn't need to include this header file at all.

#include "clmdef.h"

// Clic namespace
namespace CLM { namespace LicenseServices {

// Enable obfuscate for clmloader exposed API's
#define CLMLOADER_OBFUSCATE

#ifdef CLMLOADER_OBFUSCATE
#define ClicLoadBinaries        kthipcoamdhtoaodnfhisfdfkdpspskwpwi
#define ClicUnloadBinaries      bopwudwepwwlemqekdwedjweweeueuiedc
#endif

/**
 * ClicLoadBinaries
 *
 * Description:
 * API to load CLM binaries from CLM common shared location for Windows platform only.
 * All Product teams supporting CLM common shared location must integrate with
 * clmloader.dll and call this API to load CLM binaries. For products like Fusion
 * which carry its own copy of CLM binaries, integration of clmloader is optional.
 * All other CLM licensing API's needs to be called after loading CLM binaries.
 * NOTE: This exposed function is not thread safe.
 *
 * Arguments:
 *  binDirFullPath [in, optional]   Custom directory full path containing CLM binaries.
 *                                  This argument provides flexibility to load CLM
 *                                  binaries from custom location for any specific needs.
 *                                  Use this parameter when you want to load CLM from custom
 *                                  location, otherwise pass NULL always.
 *
 * Return:                          kStatusOk if success, ClmStatus error otherwise.
 *
 */
CLMINT_LINKAGE_C ClmStatus ClicLoadBinaries(const clmCHAR* const binDirFullPath = NULL);

/**
 * ClicUnloadBinaries
 *
 * Description:
 * API to unload CLM binaries from product process space for Windows platform only.
 * This API needs to be called after ClicLoadBinaries() API return kStatusOk response.
 * Call this API at the end just before closing down the application.
 * NOTE: This exposed function is not thread safe.
 *
 * Return:                          kStatusOk if success, ClmStatus error otherwise.
 *
 */
CLMINT_LINKAGE_C ClmStatus ClicUnloadBinaries();

}} // namespace ends

#endif //CLMLOADER_H
