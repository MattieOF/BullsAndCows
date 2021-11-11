#pragma once

#include <wx/wx.h>

enum class GameMode
{
	GAMEMODE_WORD,
	GAMEMODE_NUMBER
};

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	void SetGameMode(GameMode gameMode);

	void OnExitButtonClicked(wxCommandEvent& evt);
	void OnNewGameMenuClicked(wxCommandEvent& evt);
	void OnSetModeMenuClicked(wxCommandEvent& evt);
	void OnAboutMenuClicked(wxCommandEvent& evt);
	void OnHowToPlayMenuClicked(wxCommandEvent& evt);
	void NewGame();

	const char* GameModeToCStr(const GameMode& gameMode);

	wxButton* m_GuessButton = nullptr;
	wxTextCtrl* m_GuessInput = nullptr;
	wxListBox* m_ResultsBox = nullptr;
	wxButton* m_ExitButton = nullptr;

private:
	GameMode m_CurrentMode = GameMode::GAMEMODE_NUMBER;
};
