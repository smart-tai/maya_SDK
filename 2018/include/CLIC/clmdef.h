/* 
$Header: //depot/PLI/clic/current/client/global/inc/clmdef.h#16 $
$NoKeywords: $
*/
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
 * IDENTIFICATION:      clmdef.h
 *
 * AUTHOR:              
 *
 * DESCRIPTION:         Header file for the CLMSDK common definitions
 *
 */ 
#ifndef CLMDEF_H
#define CLMDEF_H

/*
 * DEFINES:
 */
#if defined(cplusplus) | defined (__cplusplus)
    #define CLMINT_EXTERNC              extern "C"
#else
    #define CLMINT_EXTERNC
#endif

#if defined(_WIN32)
    #define CLMINT_EXPORT_LINKAGE   __declspec(dllexport)
    #define CLMINT_IMPORT_LINKAGE   __declspec(dllimport)
#else
    #define CLMINT_EXPORT_LINKAGE   __attribute__ ((visibility("default")))
    #define CLMINT_IMPORT_LINKAGE   __attribute__ ((visibility("default")))
#endif

/* CLMINT_LINKAGE_C and CLMINT_LINKAGE */
#if defined(CLMINT_DECLARE_EXPORT)
    #define CLMINT_LINKAGE_C        CLMINT_EXTERNC CLMINT_EXPORT_LINKAGE
    #define CLMINT_LINKAGE          CLMINT_EXPORT_LINKAGE

#elif defined(CLMINT_DECLARE_STATIC)
    #define CLMINT_LINKAGE_C        
    #define CLMINT_LINKAGE         

#else
    #define CLMINT_LINKAGE_C        CLMINT_EXTERNC CLMINT_IMPORT_LINKAGE
    #define CLMINT_LINKAGE          CLMINT_IMPORT_LINKAGE

#endif

/* CLMINT_DECLARE() */
#if defined(_WIN32)
    #define CLMINT_DECLARE(type)    CLMINT_LINKAGE type
#else
    #define CLMINT_DECLARE(type)    type CLMINT_LINKAGE 
#endif
//////////////////////////////////////////////////////////////////////////
typedef char clmCHAR;

//////////////////////////////////////////////////////////////////////////
namespace CLM { namespace LicenseServices {

    typedef void * ClicFeature;

	//////////////////////////////////////////////////////////////////////////
	//  CLM API status return codes
	enum ClmStatus {
		// The API function is not currently implemented 
		kNotImplemented                       = -1,
		// Success 
		kStatusOk                             =  0,
		// Fail 
		kStatusFail                           =  1,
		// Internal program error 
		kStatusInternalError                  =  2,
		//  The system is out of memory 
		kStatusOutOfMemory                    =  3,
		//  The argument to a function is bad 
		kStatusBadArg                         =  4,
		//  Null pointer error 
		kStatusNullPointer                    =  5,
		//  Error initializing CLM 
		kStatusInitializationError            =  6,
		//  CLM has already been initialized 
		kStatusAlreadyInitialized             =  7,
		//  The feature was not found Ini
		kStatusFeatureNotFound                =  8,
		//  Authorization error 
		kStatusAuthorizeError                 =  9,
		//  Network error
		kStatusNetworkError                   =  10,
		// Marketing info not available
		kStatusIPMInfoError                   =  11,
		// Licensing error
		kStatusLicensingError                 =  12,
		// User Cancelled
		kStatusCancelled                      =  13,
		// a plugin has been initialized, but no ClmLicenceMgr instance exists to plug-into
		kStatusNoHostLicensing                =  14,
		// Unable to load CLM binaries.
		kStatusCLMLoadError                   =  15,
		// Unable to validate genuine CLM binaries.
		kStatusCLMValidationError             =  16,
		// Invalid folder path provided by user in the CLM API.
		kStatusCLMInvalidFolderPath           =  17,
		// CLM binaries are missing while loading CLM.
		kStatusCLMFilesMissingError           =  18,
		// CLM requires GUI mode error
		kStatusRequiresGUIModeError           =  19,
        // Required CLM binaries are missing or not loaded when required.
        kStatusLibraryMissingOrNotLoaded 	  =  20,
        // CLM is not initailzed 
        kStatusNotInitialized            	  =  21
	};

	// Status of License
	//
	enum LicenseStatus {
		//  Unknown License status 
		UnknownLicense			= -1,
		//  Authorized 
		Authorized				=  0,
		//  Not Authorized 
		NotAuthorized			=  1,
	};

	//////////////////////////////////////////////////////////////////////////
	#define DECLARE_FEATURE_KEY(k)   const clmCHAR* const k = #k
	namespace ClmFeatureKey {
		DECLARE_FEATURE_KEY(_PROD_NAME);
		DECLARE_FEATURE_KEY(_LSA);
		DECLARE_FEATURE_KEY(_METHOD);
		DECLARE_FEATURE_KEY(_STANDALONE);
		DECLARE_FEATURE_KEY(_NETWORK);
		DECLARE_FEATURE_KEY(_MSSA);
		DECLARE_FEATURE_KEY(_USER);
		DECLARE_FEATURE_KEY(_RESOURCE);
		DECLARE_FEATURE_KEY(_LOG);
		DECLARE_FEATURE_KEY(_LOCALE);
		DECLARE_FEATURE_KEY(_DEF_PROD_KEY);
		DECLARE_FEATURE_KEY(_DEF_PROD_VER);
		DECLARE_FEATURE_KEY(_SEL_PROD_KEY);
		DECLARE_FEATURE_KEY(_SEL_PROD_VER);
		DECLARE_FEATURE_KEY(_CASCADING);
		DECLARE_FEATURE_KEY(_ENT_FLEX);
		DECLARE_FEATURE_KEY(_SILENT);
		DECLARE_FEATURE_KEY(_LIC_PATH);
		DECLARE_FEATURE_KEY(_CHK_INTVL);
		DECLARE_FEATURE_KEY(_RETRY_INTVL);
		DECLARE_FEATURE_KEY(_RETRY_COUNT);
		DECLARE_FEATURE_KEY(_INFORM_BORROW);
		DECLARE_FEATURE_KEY(_AUTHORIZED);
		DECLARE_FEATURE_KEY(_LIC_SERVER_NUM);
		DECLARE_FEATURE_KEY(_LIC_SERVER_NAMES);
		DECLARE_FEATURE_KEY(_IS_TRIAL);
		DECLARE_FEATURE_KEY(_IS_BORROW);
		DECLARE_FEATURE_KEY(_SESSION_SPECIFIC);
		DECLARE_FEATURE_KEY(_USERNAME);
        DECLARE_FEATURE_KEY(_HOST_USERNAME);
		DECLARE_FEATURE_KEY(_HOSTNAME);
		DECLARE_FEATURE_KEY(_SN_DEF_KEY);
		DECLARE_FEATURE_KEY(_SN_SEL_KEY);
		DECLARE_FEATURE_KEY(_BEHAVIOR);
		DECLARE_FEATURE_KEY(_USAGE);
		DECLARE_FEATURE_KEY(_TYPE);
		DECLARE_FEATURE_KEY(_STATE);
		DECLARE_FEATURE_KEY(_FEATURE_NAME);
		DECLARE_FEATURE_KEY(_FEATURE_VERSION);
		DECLARE_FEATURE_KEY(_SN);
		DECLARE_FEATURE_KEY(_LIC_NUM_INUSE);
		DECLARE_FEATURE_KEY(_LIC_NUM_TOTAL);
		DECLARE_FEATURE_KEY(_LIC_NUM_FLOAT);
		DECLARE_FEATURE_KEY(_LIC_NUM_OVERDRAFT);
		DECLARE_FEATURE_KEY(_LIC_NUM_BORROWED);
		DECLARE_FEATURE_KEY(_TIMEOUT);
		DECLARE_FEATURE_KEY(_MODEL);
		DECLARE_FEATURE_KEY(_HEARTBEAT);
		DECLARE_FEATURE_KEY(_PROCESS_EVENT_CB_DATA);
		DECLARE_FEATURE_KEY(_DIALOG_DISPLAY_CB_DATA);
		DECLARE_FEATURE_KEY(_EXP_STATE);
		DECLARE_FEATURE_KEY(_EXP_DATE);
		DECLARE_FEATURE_KEY(_FEATUREID);
		DECLARE_FEATURE_KEY(_USERID);
		DECLARE_FEATURE_KEY(_ACCESSTOKEN);
		DECLARE_FEATURE_KEY(_CLIC_LIC_MSG);
		DECLARE_FEATURE_KEY(_CLIC_FEATURE_INFO);
		DECLARE_FEATURE_KEY(_CLIC_MARKET_INFO);
		DECLARE_FEATURE_KEY(_CLIC_OLD_ENT);
		DECLARE_FEATURE_KEY(_CLIC_RESP_model);
		DECLARE_FEATURE_KEY(_CLIC_RESP_status);
		DECLARE_FEATURE_KEY(_CLIC_RESP_startDate);
		DECLARE_FEATURE_KEY(_CLIC_RESP_endDate);
		DECLARE_FEATURE_KEY(_CLIC_RESP_featureType);
		DECLARE_FEATURE_KEY(_TYPEARGS);
		DECLARE_FEATURE_KEY(_INSTALLINFO);
        DECLARE_FEATURE_KEY(_LEGACY_STATUS_CODE);
        DECLARE_FEATURE_KEY(_LEGACY_PRODUCT_INFO_DLG);

        DECLARE_FEATURE_KEY(_BRANDING_BACKGROUND);
        DECLARE_FEATURE_KEY(_BRANDING_BACKGROUND_RESDLL);
		
		DECLARE_FEATURE_KEY(_BRANDING_CSS);
	}
}}

//////////////////////////////////////////////////////////////////////////
#define CLMINT_OBFUSCATE
#ifdef CLMINT_OBFUSCATE
#define ClicGetInstance                   qpcpmciqsdudufmnzzzwwcmiwdpqwpksskf
#define ClicSetInstance                   qpcpmsdadsassdmnssswwcmifentonksskf
#define ClicHasInstance                   qpcpmfentondsadawsdakpopplplplplpla
#define ClicGetVersion                    fdsfifuqncislsaowqpowpfkikcdkdmcjub
#define ClicPreInitialize                 ombnsdhnnfdekbfnuandjcmdifilwkidmdw
#define ClicInitialize                    fsdfr3refedrewfetretregfdgdsfdfds4k
#define ClicCleanUp                       jfmoidmdhdmpqmdmhvnudoaiuwpannhcnvl
#define ClicRegisterLicenseEventHandler   piykymcicwldiqwodjqqqmvncmapqokdoww
#define ClicUnregisterLicenseEventHandler ficowivmiqnqiudmbzjnrhqipanchcekdic
#define ClicSetLicenseEventHandlerData    ufdsjdhsfhdsfdrerefdsfndfdfndvnjhfj
#define ClicSetFeatureInfo                uuwumcnuwnfucmiqwldpwmcuqowudsfdsfd
#define ClicGetFeatureInfo                uwmcjgfowqajzcuwbiwpoppqqckwmcwjdia
#define ClicGetFeatureAuthorization       acefowkmcibwlduqjdigjazawpcndwoppqm
#define ClicReleaseFeatureAuthorization   wimcicdowpmcpwqsidwpqmdikdciwdsssdq
#define ClicDisplayAuthorizationInfo      ccmmmbziwwodoqpdiowncugawcmudughaqq
#define ClicHostReadyForUI                fdakjfskckunfentonnnaiunixanusunsid
#define ClicFreeMem                       uwmcodfasdfdsaftrewipoppqkaiqwwwcmw
#define ClicGetFeatureStatus              pfdfdsrefdsuwkmfdsfdsfdsfdtretryytg
#define ClicBorrowFeature                 dfjiosdjfjdtertrr0909fdsf4534rgdfgd
#define ClicReturnFeature                 df89gfgf8dff23dfsdf0909fsddfd7443f8
#define ClicDisplayBorrowInfo             pp9k4f8jkf7gji8dfiu0909fdiii239kd85
#define ClicManualClock                   dtmgwmodtpamtfwfzbsxbyfzby230909dtp
#define ClicGetLicenseMgrCoreImp          njjjdjnjnslllaskljijijoiwpopokpcmmk
#endif
//////////////////////////////////////////////////////////////////////////

#endif /* CLMDEF_H */
