#include "cMain.h"
#include "cSetMode.h"

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
	wxMenuItem* exit = new wxMenuItem(nullptr, wxID_ANY, wxT("&Exit\tEscape")); 
	wxMenuItem* about = new wxMenuItem(nullptr, wxID_ANY, wxT("&About")); 
	wxMenuItem* help = new wxMenuItem(nullptr, wxID_ANY, wxT("&How to Play\tCtrl+Shift+?")); 

	// Add menu items to menus
	// Game menu
	gameMenu->Append(newGame);
	gameMenu->Append(setMode);
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

	// Create sizers
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* guessInputSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create other widgets
	m_ExitButton = new wxButton(this, wxID_ANY, "Exit", wxPoint(0, 0), wxSize(60, 30));
	m_ExitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnExitButtonClicked, this);

	m_GuessButton = new wxButton(this, wxID_ANY, "Guess", wxPoint(0, 0), wxSize(60, 21));
	m_GuessInput = new wxTextCtrl(this, wxID_ANY, "Test", wxDefaultPosition, wxSize(175, 20));
	guessInputSizer->Add(new wxStaticText(this, wxID_ANY, "Guess Input: ", wxDefaultPosition, wxDefaultSize), 
		wxSizerFlags(0).CenterVertical());
	guessInputSizer->Add(m_GuessInput);
	guessInputSizer->AddSpacer(5);
	guessInputSizer->Add(m_GuessButton);

	m_ResultsBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(310, 150));

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Bulls and Cows", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);
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
}

cMain::~cMain()
{
}

void cMain::OnExitButtonClicked(wxCommandEvent& evt)
{
	this->Close();
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
}

void cMain::OnAboutMenuClicked(wxCommandEvent& evt)
{
	wxMessageBox("About");
	evt.Skip();
}

void cMain::OnHowToPlayMenuClicked(wxCommandEvent& evt)
{
	wxMessageBox("idk");
	evt.Skip();
}

void cMain::NewGame()
{
	wxMessageBox("New game clicked");
}
