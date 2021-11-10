#include "cMain.h"

cMain::cMain()
	: wxFrame(nullptr, wxID_ANY, "Bulls and Cows", wxPoint(10, 10), wxSize(800, 600), 
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	// Declarations of menu bar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* gameMenu = new wxMenu();
	wxMenu* helpMenu = new wxMenu();

	// Create menu items
	wxMenuItem* newGame = new wxMenuItem(nullptr, wxID_ANY, wxT("&New Game\tCtrl+N"));
	// Escape might be too easy to press accidentally
	wxMenuItem* exit = new wxMenuItem(nullptr, wxID_ANY, wxT("&Exit\tEscape")); 
	wxMenuItem* about = new wxMenuItem(nullptr, wxID_ANY, wxT("&About")); 
	wxMenuItem* help = new wxMenuItem(nullptr, wxID_ANY, wxT("&How to Play\tCtrl+Shift+?")); 

	// Add menu items to menus
	// Game menu
	gameMenu->Append(newGame);
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
	Bind(wxEVT_MENU, &cMain::OnExitButtonClicked, this, exit->GetId());
	Bind(wxEVT_MENU, &cMain::OnAboutMenuClicked, this, about->GetId());
	Bind(wxEVT_MENU, &cMain::OnHowToPlayMenuClicked, this, help->GetId());

	// Create other widgets
	m_GuessButton = new wxButton(this, wxID_ANY, "Guess", wxPoint(10, 10), wxSize(60, 30));

	m_ExitButton = new wxButton(this, wxID_ANY, "Exit", wxPoint(10, 50), wxSize(60, 30));
	m_ExitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnExitButtonClicked, this);

	// Final setup for frame
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
