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
 * Name:            ClmLicenseMgrCore      
 *
 * Description:     Header file to represent the ClmLicenseMgrCore.
 *
 */
//////////////////////////////////////////////////////////////////////////
#ifndef CLMLICENSEMGRCORE_H
#define CLMLICENSEMGRCORE_H
//////////////////////////////////////////////////////////////////////////
#include "clmdef.h"
//////////////////////////////////////////////////////////////////////////
namespace CLM { namespace LicenseServices {
//////////////////////////////////////////////////////////////////////////
class IClmLicenseEventListener;
class ClmLicenseMgrOptionsBuilder;
//////////////////////////////////////////////////////////////////////////
class ClmLicenseMgrCoreImp;
class ClmLicenseMgrCore
{
protected:
	CLMINT_LINKAGE ClmLicenseMgrCore();
	CLMINT_LINKAGE virtual ~ClmLicenseMgrCore();

public:
	// Returns the version of the Clic Component
	CLMINT_LINKAGE static ClmStatus ClicGetVersion(clmCHAR*& value);
	// Utility API to free memory which allocated in ClmLicenseMgrCore API, like GetFeatureInfo, ClicGetVersion etc
	// mem will be set to 0 after release
	CLMINT_LINKAGE static void ClicFreeMem(clmCHAR*& mem);

  // This optional (but recommended) function is called by callees before calling Initialize(), its job is to preload the clic base runtime asynchronously to improve startup performance. 
  // NOTES: Call this function about 2-3 seconds before instance->Initialize() and about 2-3 seconds after a initial call to GetInstance()
  CLMINT_LINKAGE virtual ClmStatus ClicPreInitialize(ClmLicenseMgrOptionsBuilder &startupOptions);

  // Initializes the License manager and the underlying Clic core Javascript runtime
  // *** To benefit from the improved startup performance, you must call ClmLicenseMgrCore* GetInstance() as soon as possible in your app startup code with ideally a call from PreInitialize()
  // then call this function as late as you can in your app startup
  // Integrating product must call this method before calling of any of the APIs.
  CLMINT_LINKAGE virtual ClmStatus ClicInitialize(ClmLicenseMgrOptionsBuilder &startupOptions);

  // Registers event listener for authorization information or IPM information refresh notification or traditional ADLM callback
  // Such Listener will be global and apply for all checked out license later
  CLMINT_LINKAGE virtual ClmStatus ClicRegisterLicenseEventHandler(IClmLicenseEventListener *pEventListener);

  // Unregisters the event listener for auth information or IPM information refresh notification or traditional ADLM callback
  CLMINT_LINKAGE virtual ClmStatus ClicUnregisterLicenseEventHandler(IClmLicenseEventListener *pEventListener);

  // - Call this function to notify Clic that the host application is ready to accept UI initialization
  // - You only need to call this one, on startup, after the ClicGetFeatureAuthorization
  // - If you call this function, expect UI to appear before this function returns
  // - For this function to operate, you must have already derived and registered an CClmLicenseEventUIListener through ClicRegisterLicenseEventHandler
  CLMINT_LINKAGE virtual ClmStatus ClicHostReadyForUI();

  // Set listen call back function data
  // use key == ClmFeatureKey::_PROCESS_EVENT_CB_DATA for process event callback
  // use key == ClmFeatureKey::_DIALOG_DISPLAY_CB_DATA for ADLM Dialog display callback
  CLMINT_LINKAGE virtual ClmStatus ClicSetLicenseEventHandlerData(const clmCHAR* const key, void* data);

  // Set feature information/configuration in license manager
  // Products can use this API to specify various configuration options, like Locale, error Log location etc.
  CLMINT_LINKAGE virtual ClmStatus ClicSetFeatureInfo(const clmCHAR* const key, const clmCHAR* const value);

  // Get feature information/configuration in license manager
  // Products can use this API to retrieve license information, like current check interval etc
  // If success, then value pointer reference will be changed to a pointer which point to allocated string buffer
  // Call ClicFreeMem to release the memory later 
  CLMINT_LINKAGE virtual ClmStatus ClicGetFeatureInfo(const clmCHAR* const key, clmCHAR*& value);

  // Authorizes the feature represented in the license manager
  // The License Mgr uses the appropriate method to check out license for the current feature
  CLMINT_LINKAGE virtual ClmStatus ClicGetFeatureAuthorization();

  // Check if the feature is authorized or not
  // This API will call ClicGetFeatureInfo(ClmFeatureKey::_AUTHORIZED, buff) internally and then convert to LicenseStatus enum 
  CLMINT_LINKAGE virtual LicenseStatus ClicGetFeatureStatus();

  // Release authorization of the feature in the license manager
  // This API will License Mgr use appropriate method to check in license for specified features.
  CLMINT_LINKAGE virtual ClmStatus ClicReleaseFeatureAuthorization();

  // Show UI Dialog / panel to display License information for current feature
  CLMINT_LINKAGE virtual ClmStatus ClicDisplayAuthorizationInfo();

  // Borrow a feature authorization from license server
  CLMINT_LINKAGE virtual ClmStatus ClicBorrowFeature();

  // Return feature authorization to license server
  CLMINT_LINKAGE virtual ClmStatus ClicReturnFeature(bool bCheckout = true);

  // Display borrow information, if it is borrowed
  CLMINT_LINKAGE virtual ClmStatus ClicDisplayBorrowInfo();

  // **LINUX PLATFORM ONLY** 
  // Periodically called in the main application thread when in manual timer mode
  CLMINT_LINKAGE virtual ClmStatus ClicManualClock();
  
	// internal use only
	ClmLicenseMgrCoreImp *GetCoreImp(){return mImp;};
private:
  ClmLicenseMgrCoreImp *mImp;
};

//////////////////////////////////////////////////////////////////////////
class CLMINT_LINKAGE IClmLicenseEventListener
{
public:
    IClmLicenseEventListener();
    virtual ~IClmLicenseEventListener();

    // Client application defined callback with the lost license identifier
    // to get notification when the license is lost (network licensing only)
    virtual void OnAPPQuitCB();

    // Client application defined callback to receive notification
	// that the product needs to close immediately
    virtual void OnAPPQuitNowCB();

    // Client application defined callback for processing a serial number that
    // has been updated by the user 
    // Note: Only Apply to ADLM Licensed Product
    virtual void OnSerialNumberUpdate(const clmCHAR* const /*serialNumber*/);

    // Client application defined callback to get notification when pending
    // events can be processed.
    // Note: Only Apply to ADLM Licensed Product
    virtual void OnProcessEvents(void* /*pData*/);

    // Client application defined callback to get notification when an AdLM
    // dialog is displayed and closed.  
    virtual void OnDialogDisplay(bool /*bDisplay*/, void* /*pData*/);

    // Client application defined callback to get notification when the user
    // activates, borrows or returns a license from the Authorization Info Dialog
    // Note:
    // updatedAction value:
    //   ACTIVATED   = 1,
    //   BORROWED    = 2,
    //   RETURNED    = 3
    virtual void OnAuthInfoDialogUpdate(int /*updatedAction*/);

    // Client application defined callback to get notification when
    // there is an authorization update.
    virtual void OnAuthorizationUpdate(const clmCHAR* jsonEventArgs) = 0;
};

//////////////////////////////////////////////////////////////////////////
// This class is used to provide convenient conversion from string typed Clic feature value to traditional ADLM compatible int
// It aids integrate CIP / CER component for ADLM License info
class ClmLicenseMgrADLMHelper
{
public:
    CLMINT_LINKAGE static int GetLicenseBehavior       (const clmCHAR* const value);
    CLMINT_LINKAGE static int GetLicenseUsage          (const clmCHAR* const value);
    CLMINT_LINKAGE static int GetLicenseExpirationState(const clmCHAR* const value);
};

//////////////////////////////////////////////////////////////////////////
class ClmLicenseMgrJSonHelperImp;
// this class gets and sets a one level deep Json with key value pairs. 
// It aids communication between C++ and JS, and back
class CLMINT_LINKAGE ClmLicenseMgrJSonHelper
{
public:
	ClmLicenseMgrJSonHelper();
	ClmLicenseMgrJSonHelper(const clmCHAR *json);
	virtual ~ClmLicenseMgrJSonHelper();

	// initializes from a pre-existing json structure, returns false if invalid json
	bool InitializeFrom(const clmCHAR *json);

	int GetInt(const clmCHAR *keyName, int defaultValue);
	long GetLong(const clmCHAR *keyName, long defaultValue);
	bool GetBool(const clmCHAR *keyName, bool defaultValue);
	const clmCHAR *GetStringConst(const clmCHAR *keyName, const clmCHAR *defaultValue);
	void *GetAddress(const char *keyName, void *defaultValue);

	// sets a key value pair to the base json object
	bool SetBool(const clmCHAR *keyName, bool keyValue);
	int  SetInt(const clmCHAR *keyName, int keyValue);
	long SetLong(const clmCHAR *keyName, long keyValue);
	const clmCHAR *SetString(const clmCHAR *keyName, const clmCHAR *keyValue);
	void *SetAddress(const char *keyName, void *keyValue);


	// returns a json string representation of the current setup
	const clmCHAR *Stringyfy();

private:
	ClmLicenseMgrJSonHelperImp *mImp;
};

//////////////////////////////////////////////////////////////////////////
// this class is used to set the startup options for ClmLicenseMgr
class ClmLicenseMgrOptionsBuilderImp;
class CLMINT_LINKAGE ClmLicenseMgrOptionsBuilder : public ClmLicenseMgrJSonHelper
{
public:
	ClmLicenseMgrOptionsBuilder(void *parentWnd=NULL, const clmCHAR *appPath=NULL);
	virtual ~ClmLicenseMgrOptionsBuilder();
private:
	ClmLicenseMgrOptionsBuilderImp *mImp;
};

//////////////////////////////////////////////////////////////////////////
class CLMINT_LINKAGE ClmLicenseMgrUIBuilder : public ClmLicenseMgrJSonHelper
{
public:

	ClmLicenseMgrUIBuilder();
	ClmLicenseMgrUIBuilder(const clmCHAR *json);
	virtual ~ClmLicenseMgrUIBuilder();

	// logical placement describers for windows that are placed relative to another
	enum WindowLocation
	{
		kDeadCenter		= 0,
		kTopCenter		= 1,
		kBottomCenter = 2,
		kLeftCenter		= 3,
		kRightCenter	= 4,
		kTopLeft			= 5,
		kBottomLeft		= 6,
		kTopRight			= 7,
		kBottomRight	= 8,
		// when a window is StuckToOwner=true, the following are additional logical placement describers for windows that are stuck to the edge of another window
		kTopRightCorner	= 9,
		kRightTop				= 10,
		kRightBottom		= 11,
		kRightBottomCorner= 12,
		kBottomLeftCorner = 13,
		kLeftBottom			= 14,
		kLeftTop				= 15, 
		kLeftTopCorner	= 16
	};

	// requests made for render frames that are embedded into other windows
	enum EmbeddedWindowRequest
	{
		kAppButton			= 0,	// request to be in the application button menu
		kCaptionBar			= 1,	// request to be in application caption bar
		kDocCaptionBar	= 2,	// request to be in application caption bar
		kInfoBar				= 3,	// request to be in application infocenter bar
		kHelpBar				= 4,	// request to be in application help area
		kRibbon					= 5,	// request to be in ribbon
		kQAT						= 6,	// request to be in Quick Access toolbar
		kToolbar				= 7,	// request to be in main application toolbar
		kMenu						= 8,	// request to be in main application menu
		kProperties			= 9,	// request to be in main properties window
		kStatusbar			= 10,	// request to be in the application status bar window
		kDialog					= 11,	// request to be in inside a dialog
		kOther					= 99	// something other than above
	};

	// modal/modeless window frame styles
	enum PopupWindowStyles {
		// use default window style
		kDefaultWindowStyle = 1,								
		// completely frameless window
		kFrameLessPopupWindow = 2,	
		// completely framed window without close
		kFramedPopupWindow = 4,	
		// framed window, with titlebar and close button
		kFullFramedPopupWindow = 8
	};
};

//////////////////////////////////////////////////////////////////////////
// use this class to hook into the Clic UI framework
class CClmLicenseEventUIListenerImp;
class ClmLicenseJSListenerMgrUI;
class CLMINT_LINKAGE CClmLicenseEventUIListener : public IClmLicenseEventListener
{
	friend class ClmLicenseJSListenerMgrUI;
public:
	CClmLicenseEventUIListener();
	virtual ~CClmLicenseEventUIListener();

	// called when an UI element needs to display, you will return your application frame window handle
	// for Windows this is AfxGetMainWnd()->GetSafeHwnd();
	// return HWND on Windows, id on Mac
	virtual void *RequestMainWindow() = 0;
	// asks the current windowing system to create an embedded window in which to render HTML into, returns null if none available, in which case any UI request will error out
	// return HWND on Windows, id on Mac
	virtual void *CreateHTMLRenderFrame(ClmLicenseMgrUIBuilder &uiDefinition) = 0;

	// Shows a popup window containing HTML/JS in a model state, pass a unique name of the control as the windowId
	// your implementation can use ShowClicModalHtmlPopupWindow(), if you do not require a host based dialog style
	virtual ClmStatus ShowModalHtmlPopupWindow(ClmLicenseMgrUIBuilder &uiDefinition) = 0;
	// Shows a popup window containing HTML/JS in a modeless state, pass a unique name of the control as the windowId
	// your implementation can use ShowClicModelessHtmlPopupWindow(), if you do not require a host based dialog style
	virtual ClmStatus ShowModelessHtmlPopupWindow(ClmLicenseMgrUIBuilder &uiDefinition) = 0;

	// platform specific UI functions - override these if you use non-standard OS UI frameworks like QT or WxWidget
	// performs a platform specific show/hide window - return true if the window handle was found and operated on successfully, otherwise return false
	virtual bool ShowWindow(void *hwnd, bool show);
	// performs a platform specific redraw window - return true if the window handle was found and operated on successfully, otherwise return false
	virtual bool RedrawWindow(void *hwnd);
	// performs a platform specific destroy window - return true if the window handle was found and operated on successfully, otherwise return false
	virtual bool DestroyWindow(void *hwnd);
	// performs a platform specific close window - return true if the window handle was found and operated on successfully, otherwise return false
	virtual bool CloseWindow(void *hwnd);
	// performs a platform specific move window, allows resizing also - return true if the window handle was found and operated on successfully, otherwise return false
	virtual bool MoveWindow(void *hwnd, int x, int y, int width, int height);
	// performs a platform specific move window, allows resizing also  - return true if the window handle was found and operated on successfully, otherwise return false
	virtual bool GetWindowRect(void *hwnd, int &x, int &y, int &width, int &height);

	// implementing ShowModalHtmlPopupWindow and/or ShowModelessHtmlPopupWindow requires
	// - call StartHTMLRenderFrame() in your dialog OnInitDialog() event handler
	// - call EndHTMLRenderFrame() in your dialog OnShowWindow() event handler
	ClmStatus StartHTMLRenderFrame(ClmLicenseMgrUIBuilder &uiDefinition);
	// call this function to finialize the HTML web page render
	ClmStatus EndHTMLRenderFrame(ClmLicenseMgrUIBuilder &uiDefinition);
	
	// this function is used to refresh the browser ui frames, in case of redraw problems (mainly used on Windows only)
	ClmStatus RedrawRenderFrames();

	// Shows a popup window containing HTML/JS in a model state, pass a unique name of the control as the windowId
	// this call utilizes the clic core for displaying a native dialog
	ClmStatus ShowClicModalHtmlPopupWindow(ClmLicenseMgrUIBuilder &uiDefinition);
	// Shows a popup window containing HTML/JS in a modeless state, pass a unique name of the control as the windowId
	// this call utilizes the clic core for displaying a native dialog
	ClmStatus ShowClicModelessHtmlPopupWindow(ClmLicenseMgrUIBuilder &uiDefinition);

private:
	CClmLicenseEventUIListenerImp *mImp;
};


}}

//////////////////////////////////////////////////////////////////////////
#ifdef CLM_LINUX
#define override
#define nullptr NULL
#endif
//////////////////////////////////////////////////////////////////////////

#endif // CLMLICENSEMGRCORE_H
