#pragma once

#include <wx/wx.h>

class cHelp : public wxFrame
{
public:
	cHelp();
	~cHelp() = default;

	void OnOkButtonClicked(wxCommandEvent& evt);
};
