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
	void OnGuessButtonClicked(wxCommandEvent& evt);
	void OnNewGameMenuClicked(wxCommandEvent& evt);
	void OnSetModeMenuClicked(wxCommandEvent& evt);
	void OnAboutMenuClicked(wxCommandEvent& evt);
	void OnHowToPlayMenuClicked(wxCommandEvent& evt);
	void OnShowCurrentValueMenuClicked(wxCommandEvent& evt);
	void OnRegenerateValueMenuClicked(wxCommandEvent& evt);
	void OnCustomWordsFileMenuClicked(wxCommandEvent& evt);
	void OnGuessInputSubmitted(wxCommandEvent& evt);
	void NewGame();
	void CheckGuess();
	void AddResult(int bulls, int cows);
	void GameWon();

	const char* GameModeToCStr(const GameMode& gameMode);

	wxStaticText* m_TitleText = nullptr;
	wxButton* m_GuessButton = nullptr;
	wxTextCtrl* m_GuessInput = nullptr;
	wxListBox* m_ResultsBox = nullptr;
	wxButton* m_ExitButton = nullptr;

private:
	void LoadWords(std::string filename = "words.txt");
	void SelectNumber();
	void SelectWord();

	std::vector<std::string> m_WordPool;
	std::string m_CurrentValue = "";
	GameMode m_CurrentMode = GameMode::GAMEMODE_NUMBER;
};
