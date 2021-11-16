#include "cMain.h"
#include "cSetMode.h"
#include "cAbout.h"
#include "cHelp.h"
#include <random>
#include <sstream>
#include <fstream>

cMain::cMain()
	: wxFrame(nullptr, wxID_ANY, "Bulls and Cows", wxPoint(10, 10), wxSize(300, 400), 
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	// Declarations of menu bar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* gameMenu = new wxMenu();
	wxMenu* helpMenu = new wxMenu();

	// Create menu items
	wxMenuItem* newGame = new wxMenuItem(nullptr, wxID_ANY, wxT("&New Game\tCtrl+N"));
	wxMenuItem* setMode = new wxMenuItem(nullptr, wxID_ANY, wxT("&Set Mode\tCtrl+M"));
	// Escape might be too easy to press accidentally
	wxMenuItem* about = new wxMenuItem(nullptr, wxID_ANY, wxT("&About")); 
	wxMenuItem* help = new wxMenuItem(nullptr, wxID_ANY, wxT("&How to Play\tCtrl+Shift+?")); 
	wxMenuItem* showValue = new wxMenuItem(nullptr, wxID_ANY, wxT("&Show Current Value")); 
	wxMenuItem* regenValue = new wxMenuItem(nullptr, wxID_ANY, wxT("&Regenerate Value")); 
	wxMenuItem* customWordsFile = new wxMenuItem(nullptr, wxID_ANY, wxT("&Custom Words File"));
	wxMenuItem* exit = new wxMenuItem(nullptr, wxID_ANY, wxT("&Exit\tEscape"));

	// Add menu items to menus
	// Game menu
	gameMenu->Append(newGame);
	gameMenu->Append(setMode);
	gameMenu->AppendSeparator();
	gameMenu->Append(showValue);
	gameMenu->Append(regenValue);
	gameMenu->Append(customWordsFile);
	gameMenu->AppendSeparator();
	gameMenu->Append(exit);
	// Help menu
	helpMenu->Append(about);
	helpMenu->Append(help);

	// Add menus to menubar
	menuBar->Append(gameMenu, wxT("&Game"));
	menuBar->Append(helpMenu, wxT("&Help"));
	SetMenuBar(menuBar);

	// Bind functions to menu items
	Bind(wxEVT_MENU, &cMain::OnNewGameMenuClicked, this, newGame->GetId());
	Bind(wxEVT_MENU, &cMain::OnSetModeMenuClicked, this, setMode->GetId());
	Bind(wxEVT_MENU, &cMain::OnExitButtonClicked, this, exit->GetId());
	Bind(wxEVT_MENU, &cMain::OnAboutMenuClicked, this, about->GetId());
	Bind(wxEVT_MENU, &cMain::OnHowToPlayMenuClicked, this, help->GetId());
	Bind(wxEVT_MENU, &cMain::OnShowCurrentValueMenuClicked, this, showValue->GetId());
	Bind(wxEVT_MENU, &cMain::OnRegenerateValueMenuClicked, this, regenValue->GetId());
	Bind(wxEVT_MENU, &cMain::OnCustomWordsFileMenuClicked, this, customWordsFile->GetId());

	// Create sizers
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* guessInputSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create other widgets
	m_ExitButton = new wxButton(this, wxID_ANY, "Exit", wxPoint(0, 0), wxSize(60, 30));
	m_ExitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnExitButtonClicked, this);

	m_GuessButton = new wxButton(this, wxID_ANY, "Guess", wxPoint(0, 0), wxSize(60, 21));
	m_GuessButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnGuessButtonClicked, this);
	m_GuessInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(175, 20), wxTE_PROCESS_ENTER | wxTE_NOHIDESEL | wxTE_LEFT);
	m_GuessInput->SetMaxLength(4);
	m_GuessInput->Bind(wxEVT_TEXT_ENTER, &cMain::OnGuessInputSubmitted, this);
	guessInputSizer->Add(new wxStaticText(this, wxID_ANY, "Guess Input: ", wxDefaultPosition, wxDefaultSize), 
		wxSizerFlags(0).CenterVertical());
	guessInputSizer->Add(m_GuessInput);
	guessInputSizer->AddSpacer(5);
	guessInputSizer->Add(m_GuessButton);

	m_ResultsBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(310, 150));

	mainSizer->AddSpacer(5);
	m_TitleText = new wxStaticText(this, wxID_ANY, "Bulls and Cows", wxDefaultPosition, wxDefaultSize);
	mainSizer->Add(m_TitleText, 0, wxLEFT, 10);
	mainSizer->Add(guessInputSizer, 0, wxALL, 10);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Results:", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);
	mainSizer->Add(m_ResultsBox, 0, wxLEFT, 10);
	mainSizer->AddSpacer(5);
	mainSizer->Add(m_ExitButton, 0, wxLEFT, 10);
	mainSizer->AddSpacer(5);

	// Final setup for frame
	SetSizerAndFit(mainSizer);
	SetAutoLayout(true);
	Layout();
	SetBackgroundColour(wxColour("lightgrey"));
	CenterOnScreen();

	LoadWords();
	SetGameMode(GameMode::GAMEMODE_NUMBER);
}

cMain::~cMain()
{
}

void cMain::SetGameMode(GameMode gameMode)
{
	m_CurrentMode = gameMode;
	m_GuessInput->Clear();
	m_ResultsBox->Clear();

	static wxTextValidator numValidator(wxFILTER_INCLUDE_CHAR_LIST);
	numValidator.SetCharIncludes("0123456789");
	switch (m_CurrentMode)
	{
	case GameMode::GAMEMODE_NUMBER:
		m_TitleText->SetLabelText("Bulls and Cows: Number Mode");
		m_GuessInput->SetValidator(numValidator);
		SelectNumber();
		break;
	case GameMode::GAMEMODE_WORD:
		if (m_WordPool.empty())
		{
			wxMessageBox("Word list is empty. Cannot use word mode.", "Error Loading", wxICON_ERROR);
			return;
		}
		m_TitleText->SetLabelText("Bulls and Cows: Word Mode");
		m_GuessInput->SetValidator(wxTextValidator(wxFILTER_ALPHA));
		SelectWord();
		break;
	}
}

void cMain::OnExitButtonClicked(wxCommandEvent& evt)
{
	this->Close();
	evt.Skip();
}

void cMain::OnGuessButtonClicked(wxCommandEvent& evt)
{
	CheckGuess();
	evt.Skip();
}

void cMain::OnNewGameMenuClicked(wxCommandEvent& evt)
{
	NewGame();
	evt.Skip();
}

void cMain::OnSetModeMenuClicked(wxCommandEvent& evt)
{
	cSetMode* setMode = new cSetMode(this);
	setMode->Show();
	evt.Skip();
}

void cMain::OnAboutMenuClicked(wxCommandEvent& evt)
{
	cAbout* about = new cAbout();
	about->Show();
	evt.Skip();
}

void cMain::OnHowToPlayMenuClicked(wxCommandEvent& evt)
{
	wxMessageBox("How to Play\n\
\n\
In number mode, you guess a 4 digit number with no duplicate digits.\n\
In word mode, you guess a 4 letter word. It can have duplicate characters.\n\
\n\
A bull is a character/digit in the correct place.\n\
A cow is a character/digit in the number/word, but in the wrong place.", "How to Play");
	// Originally I made an entire seperate window for this, but the message box is 10x easier and 10x prettier.
	// cHelp* help = new cHelp();
	// help->Show();
	evt.Skip();
}

void cMain::OnShowCurrentValueMenuClicked(wxCommandEvent& evt)
{
	wxMessageBox(m_CurrentValue, "Current Value");
}

void cMain::OnRegenerateValueMenuClicked(wxCommandEvent& evt)
{
	SetGameMode(m_CurrentMode);
}

void cMain::OnCustomWordsFileMenuClicked(wxCommandEvent& evt)
{
	wxString filename = wxFileSelector("Select Custom Words File", wxEmptyString, wxEmptyString, ".txt", 
		"Text Files (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (!filename.empty())
		LoadWords(filename.ToStdString());
}

void cMain::OnGuessInputSubmitted(wxCommandEvent& evt)
{
	CheckGuess();
}

void cMain::NewGame()
{
	wxMessageBox("New game clicked");
}

void cMain::CheckGuess()
{
	if (m_GuessInput->GetLineText(0).Length() != 4)
	{
		// Guess isn't long enough
		wxMessageBox("Guess should be 4 characters long!", "Error with guess", wxICON_ERROR);
		return;
	}

	if (m_CurrentMode == GameMode::GAMEMODE_NUMBER)
	{
		std::vector<char> seenChars;
		for (char c : m_GuessInput->GetLineText(0))
		{
			if (std::count(seenChars.begin(), seenChars.end(), c))
			{
				// Char has been seen before
				wxMessageBox("There should be no duplicate digits!", "Error with guess", wxICON_ERROR);
				return;
			}
			seenChars.push_back(c);
		}
	}

	wxString currentGuess = m_GuessInput->GetLineText(0);
	int bulls = 0, cows = 0;

	for (int i = 0; i < currentGuess.Length(); i++)
	{
		if (currentGuess[i] == m_CurrentValue[i])
			bulls++;
	}

	for (int i = 0; i < currentGuess.Length(); i++)
	{
		if (currentGuess.Contains(m_CurrentValue[i])) 
			cows++;
	}

	AddResult(bulls, cows);

	if (bulls == m_CurrentValue.length())
		GameWon();
}

void cMain::AddResult(int bulls, int cows)
{
	std::stringstream ss;
	ss << m_GuessInput->GetLineText(0);
	ss << ": ";
	ss << bulls << " bulls, ";
	ss << cows << " cows";
	m_ResultsBox->Append(ss.str());
	m_ResultsBox->EnsureVisible(m_ResultsBox->GetCount() - 1);
}

void cMain::GameWon()
{
	int result = wxMessageBox("Game won! Export guesses?", "Game Won", wxICON_INFORMATION | wxYES_NO);
	if (result == wxYES)
	{
		wxString saveFile = wxFileSelector("Export Results", wxEmptyString,
			"Guesses", ".txt", "Text Files (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (!saveFile.empty())
		{
			std::fstream file;
			file.open(saveFile.ToStdString(), std::fstream::out);
			file << "Guessed " << m_CurrentValue << " in " << m_ResultsBox->GetCount() << " guesses\n";
			for (unsigned int i = 0; i < m_ResultsBox->GetCount(); i++)
				file << m_ResultsBox->GetString(i) << "\n";
			file.close();
			wxMessageBox("Exported to " + saveFile);
		}
	}
	SetGameMode(m_CurrentMode);
}

const char* cMain::GameModeToCStr(const GameMode& gameMode)
{
	switch (gameMode)
	{
	case GameMode::GAMEMODE_NUMBER:
		return "Number";
	case GameMode::GAMEMODE_WORD:
		return "Word";
	default:
		return "Invalid";
	}
}

void cMain::LoadWords(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		wxMessageBox("Failed to load words file!", "Error Loading", wxICON_ERROR);
		return;
	}

	m_WordPool.clear();
	std::string line;

	while (std::getline(file, line))
	{
		line.erase(std::remove_if(line.begin(), line.end(), [](char c) {
			return std::isspace(static_cast<unsigned char>(c));
			}), line.end());

		if (line.length() == 4)
			m_WordPool.push_back(line);
		else
			wxMessageBox("Line not the right size!", "Error Loading", wxICON_ERROR);
	}

	if (m_WordPool.empty())
		wxMessageBox("Word list is empty. Cannot use word mode.", "Error Loading", wxICON_ERROR);
}

void cMain::SelectNumber()
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::stringstream ss;
	std::vector<char> digits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	for (int i = 0; i < 4; i++)
	{
		std::uniform_int_distribution<> distribution(0, digits.size() - 1);
		int index = distribution(engine);
		ss << digits.at(index);
		digits.erase(digits.begin() + index);
	}

	m_CurrentValue = ss.str();
}

void cMain::SelectWord()
{
	if (m_WordPool.empty())
	{
		wxMessageBox("Word list is empty. Cannot use word mode.", "Error Loading", wxICON_ERROR);
		return;
	}

	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<> distribution(0, m_WordPool.size() - 1);
	m_CurrentValue = m_WordPool.at(distribution(engine));
}
