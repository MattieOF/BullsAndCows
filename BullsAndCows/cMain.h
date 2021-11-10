#pragma once

#include <wx/wx.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	void OnExitButtonClicked(wxCommandEvent& evt);
	void OnNewGameMenuClicked(wxCommandEvent& evt);
	void OnAboutMenuClicked(wxCommandEvent& evt);
	void OnHowToPlayMenuClicked(wxCommandEvent& evt);
	void NewGame();

	wxButton* m_GuessButton = nullptr;
	wxTextCtrl* m_GuessInput = nullptr;
	wxListBox* m_ResultsBox = nullptr;
	wxButton* m_ExitButton = nullptr;
};
