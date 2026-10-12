#pragma once

#define WINVER 0x0400
#define _WIN32_WINNT 0x0400
#define _ATL_STATIC_REGISTRY

#define WLIST_ALLOC(size) malloc(size)
#define WLIST_FREE(ptr) free(ptr)

#include <winsock2.h>
#include <windows.h>
#include "../Wangreal/include/wtypes.h"
#include <atlbase.h>
#include <atlapp.h>
extern WTL::CAppModule _Module;
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlw.h>
#include <atlctrlx.h>
#include "z_ilfill.h"
ILFILLX1
#include <atlmisc.h>
#include <atldlgs.h>
ILFILLX1B

#include <math.h>
#include <stdexcept>
ILFILLX2
#include "wmath.h"
#include "gamath.h"
#include "wutil.h"
#include "wminmax.h"
#include "wlist.h"
#include "wmemblock.h"
#include "wlock.h"
#include "wmempak.h"
#include "rectmng.h"
#include "wscene.h"
#include "wvideo.h"
#include "wmesh.h"
#include "wresrcmng.h"
#include "wdevmng.h"
#include "wxtnlbuffer.h"
#include "xzip.h"
#include "cfile.h"
#include "wreg.h"
#include "bitmap.h"
#include "wavi.h"
#include "wpuppet.h"
#include "wview.h"
#include "wflag.h"
#include "wangrealapp.h"
#include "westpak.h"
#include "wblockmodel.h"
#include "wboneset.h"
#include "wpetfile.h"
#include "soundmanager.h"
#include "z_ilfill.h"
ILFILL0
#include "objectfactory.h"
#include "background.h"
#include "w3danispr.h"
#include "woverlay.h"
#include "singleton.h"

#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

#include "basicdebug.h"
#include "commonutil.h"

#include "tinyxml.h"

#include "../../shared/exceptionreport.h"
#include "lock.hpp"
#include "packet.h"
#include "titles_client.h"
#include "clientsocket.h"
#include "chatmsg.h"
// HACK: originally in chatmsg.h, but shifts the frwndmanager unit too much
inline void CChatMsg::Toggle(bool toggle)
{
	m_bToggle = toggle;
}
#include "frwndinl.h"
#include "frbutton.h"
#include "frlistbox.h"
#include "frstatic.h"
#include "frgraphicinterface.h"
#include "frarea.h"
#include "wfont.h"
#include "ucclibrary.h"
#include "hackingmanager.h"
#include "frframe.h"
#include "frscrollbar.h"
#include "frcombobox.h"
#include "frwndmanager.h"
#include "inputmanager.h"
#include "ccrc32.h"
// HACK
template unsigned int std::vector<CRC_MT::sCRC_CHKTASK*>::size() const;
#include "tooltip.h"
#include "frform.h"
#include "frgaugebar.h"
#include "z_ilfill.h"
ILFILL1
#include "fremoticon.h"
#include "frviewer.h"
#include "fredit.h"
#include "fresh.h"
#include "mainframe.h"
// HACK: should be inline with class definition, but symbol ordering is tricky
inline FrDesktop* Fresh::GetDesktop() const
{
	return manager->GetDesktop();
}
#include "tweaker.h"
#include "networksystem.h"
#include "networkmonitor.h"
#include "projectg.h"
#include "gdtextbox.h"
#include "gdbitmapbox.h"
#include "gdvoiceitem.h"
#include "../../shared/globalgamedefine.h"
#include "../../shared/globalnetworkdefine.h"
#include "taskmanager.h"
#include "actor.h"
#include "taskmain.h"
#include "nodecontainer.h"
#include "scenemanager.h"
#include "courseorder.h"

// HACK: workaround for unsolved symbol ordering problems
template void std::vector<WVector>::reserve(unsigned int);
template float Min<float>(float, float);
#include "shareddoc.h"
#include "uccmanager.h"
#include "frtext.h"
#include "wtemplate.h"

// HACK: the PCH seems to instantiate these somewhere - it hasn't been recovered yet
template std::string::iterator std::string::iterator::operator+(int) const;
