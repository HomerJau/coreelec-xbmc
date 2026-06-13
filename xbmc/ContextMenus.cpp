/*
 *  Copyright (C) 2016-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ContextMenus.h"

#include "ServiceBroker.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "input/WindowTranslator.h"
#include "music/MusicFileItemClassify.h"
#include "resources/LocalizeStrings.h"
#include "resources/ResourcesComponent.h"
#include "storage/MediaManager.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "utils/Variant.h"

using namespace KODI;

namespace CONTEXTMENU
{

  bool CEjectDisk::IsVisible(const CFileItem& item) const
  {
#ifdef HAS_OPTICAL_DRIVE
    return item.IsRemovable() && (item.IsDVD() || MUSIC::IsCDDA(item));
#else
    return false;
#endif
  }

  bool CEjectDisk::Execute(const std::shared_ptr<CFileItem>& item) const
  {
#ifdef HAS_OPTICAL_DRIVE
    CServiceBroker::GetMediaManager().ToggleTray(
        CServiceBroker::GetMediaManager().TranslateDevicePath(item->GetPath())[0]);
#endif
    return true;
  }

  bool CEjectDrive::IsVisible(const CFileItem& item) const
  {
    // Must be HDD
    return item.IsRemovable() && !item.IsDVD() && !MUSIC::IsCDDA(item);
  }

  bool CEjectDrive::Execute(const std::shared_ptr<CFileItem>& item) const
  {
    return CServiceBroker::GetMediaManager().Eject(item->GetPath());
  }

} // namespace CONTEXTMENU
