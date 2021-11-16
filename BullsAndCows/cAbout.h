#pragma once

#include <wx/wx.h>

class cAbout : public wxFrame
{
public:
	cAbout();
	~cAbout();

	void OnOkButtonClicked(wxCommandEvent& evt);
};
