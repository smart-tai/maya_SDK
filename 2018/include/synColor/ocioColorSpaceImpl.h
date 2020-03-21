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

#ifndef _SYNCOLOR_OCIO_COLOR_SPACE_IMPL_H
#define _SYNCOLOR_OCIO_COLOR_SPACE_IMPL_H

#include <synColor/synColorNamespace.h>

#include <synColor/colorSpace.h>

#include <string>


//--------------------------------------------------------------------------------------------------
//
namespace SynColorImpl
{
  //------------------------------------------------------------------------------------------------
  //
  class OCIOColorSpaceImpl : public SYNCOLOR::ColorSpace
  {
  public:
    //! \brief Constructor
    explicit OCIOColorSpaceImpl(const char* name);

    //! \brief Destructor
    ~OCIOColorSpaceImpl();

    //! \brief Initialize the instance
    SYNCOLOR::SynStatus init();

    //! \copydoc ColorSpace::getName
    const char* getName() const;

    //! \copydoc ColorSpace::getUserFacingName
    const char* getUserFacingName() const;

    //! \copydoc ColorSpace::getChromaticities
    SYNCOLOR::SynStatus getChromaticities(SYNCOLOR::Chromaticities& chromaticities) const;

  private:
    //! The color space name
    std::string _name;
  };
}

#endif //_SYNCOLOR_OCIO_COLOR_SPACE_IMPL_H
