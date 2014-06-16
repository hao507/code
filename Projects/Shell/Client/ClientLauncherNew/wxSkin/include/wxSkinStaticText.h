/////////////////////////////////////////////////////////////////////////////////////////
// Name:		wxSkin
// Author:      Ren?Kraus aka upCASE <himself@upcase.de>
// Copyright:   Ren?Kraus (c)
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
//				with the addendum that you notify the author about projects using wxSkin
///////////////////////////////////////////////////////////////////////////////////////// 
#ifndef __WXSKINSTATICTEXT_H
#define __WXSKINSTATICTEXT_H

#ifdef __GNUG__
	#pragma interface "wxSkinStaticText.h"
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <wx/image.h>
#include "wxSkinWindow.h"
///wxSkinStaticText is a transparent text controls with an optional image label.
/**The text controls will be transparent as it is shaped to exactly fit the text displayed.
*/

#ifdef __WXMSW__
class wxSkinStaticText : public wxSkinWindow
{
public:
	
	wxSkinStaticText();
	
	wxSkinStaticText(wxWindow* parent,
 				int id,
				const wxString& label = "",
  				const wxPoint& pos = wxDefaultPosition,
         		const wxSize& size = wxDefaultSize,
           		long style = wxNO_BORDER,
				const wxString& name = "wxSkinStaticText");
	
 	~wxSkinStaticText();

	///Set the text label
	void SetLabel(const wxString& label);
		
	virtual void DrawCustom(wxDC& dc);

	inline void SetFontColor(wxColor color){m_fontColor = color; }
protected:
	void CreateLabel();

	virtual wxSize DoGetBestSize() const;

private:
	wxColor m_fontColor;
		
	DECLARE_DYNAMIC_CLASS(wxSkinStaticText);
};
#else
//#warning wxSkinStaticText only needed on MSW. In other ports it defaults to wxStaticText.
class wxSkinStaticText : public wxStaticText
{
public:
	wxSkinStaticText(){}
	
	wxSkinStaticText(wxWindow* parent,
 				int id,
				const wxString& label = wxEmptyString,
  				const wxPoint& pos = wxDefaultPosition,
         		const wxSize& size = wxDefaultSize,
           		long style = wxNO_BORDER,
				const wxString& name = wxT("wxSkinStaticText"))
			:wxStaticText(parent,id,label,pos,size,style,name)
	{}
	
	~wxSkinStaticText(){}
private:
	DECLARE_DYNAMIC_CLASS(wxSkinStaticText);
};
#endif

#endif

