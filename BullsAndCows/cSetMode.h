#pragma once

#include <wx/wx.h>
#include "cMain.h"

class cSetMode : public wxFrame
{
public:
	cSetMode(cMain* main);
	~cSetMode();

	void OnSetModeButtonClicked(wxCommandEvent& evt);
	GameMode GetGameModeFromIndex(int index);

	wxButton* m_SetButton;
	wxComboBox* m_ModeComboBox;

private:
	cMain* m_Main;
};
