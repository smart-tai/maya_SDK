//
// ==================================================================
// Copyright 2017 Autodesk, Inc.  All rights reserved.
//
// This computer source code  and related  instructions and comments are
// the unpublished confidential and proprietary information of Autodesk,
// Inc. and are  protected  under applicable  copyright and trade secret
// law. They may not  be disclosed to, copied or used by any third party
// without the prior written consent of Autodesk, Inc.
// ==================================================================
//
//
//! \file synColor/nativeColorSpaceImpl.h
//!
//! \brief Class to get information about color space.
//!

#ifndef _SYNCOLOR_NATIVE_COLOR_SPACE_IMPL_H
#define _SYNCOLOR_NATIVE_COLOR_SPACE_IMPL_H

#include <synColor/synColorNamespace.h>

#include <synColor/colorSpace.h>
#include <synColor/colorSpaceUtils.h>

#include <synColor/sharedPtr.h>

#include <string>


//--------------------------------------------------------------------------------------------------
//
namespace SynColorImpl
{
  //------------------------------------------------------------------------------------------------
  //
  class NativeColorSpaceImpl : public SYNCOLOR::ColorSpace
  {
  public:
    //! \brief Constructor
    explicit NativeColorSpaceImpl(const char* name);

    //! \brief Destructor
    ~NativeColorSpaceImpl();

    //! \brief Initialize the instance
    SYNCOLOR::SynStatus init();

    //! \copydoc ColorSpace::acquireProgram
    const char* getName() const;

    //! \copydoc ColorSpace::getUserFacingName
    const char* getUserFacingName() const;

    //! \copydoc ColorSpace::getChromaticities
    SYNCOLOR::SynStatus getChromaticities(SYNCOLOR::Chromaticities& chromaticities) const;

  protected:
    //! \brief Get the chromaticity coordinates from the attributes
    //! \param key is the chromaticity key
    //! \return the coordinate
    float _getChromaticity(SYNCOLOR::ColorSpaceAttributeKey key) const;

  private:
    //! The information about the color space
    SYNCOLOR::ColorSpacesAttributesPtr _attrs;
    //! The color space name
    std::string _name;
  };
}

#endif //_SYNCOLOR_NATIVE_COLOR_SPACE_IMPL_H
