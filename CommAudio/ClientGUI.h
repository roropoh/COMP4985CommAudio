#include "Master.h"

#pragma once

namespace CommAudio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ClientGUI
	/// </summary>
	public ref class ClientGUI : public System::Windows::Forms::Form
	{
	public:
		ClientGUI(void)
		{
			InitializeComponent();

			initWSA();

			//
			//TODO: Add the constructor code here
			//
		}
		void UpdateClientStatus(String ^);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ClientGUI()
		{
			WSACleanup();
			if (components)
			{
				delete components;
			}
		}

	private: SocketInformation *si;

	private: System::Windows::Forms::Button^  play_button;
	protected:

	private: System::Windows::Forms::Button^  rew_button;
	private: System::Windows::Forms::Button^  pause_button;
	private: System::Windows::Forms::Button^  stop_button;
	private: System::Windows::Forms::Button^  fwd_button;
	protected:




	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  playToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  playToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  soundToolStripMenuItem;

	private: System::Windows::Forms::ListBox^  songlist;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Button^  shuffle_button;
	private: System::Windows::Forms::Button^  connect_button;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textbox_ip;
	private: System::Windows::Forms::TextBox^  textbox_portnumber;
	private: System::Windows::Forms::ToolStripMenuItem^  connectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  client_status_box;
	private: System::Windows::Forms::Label^  label3;










	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->play_button = (gcnew System::Windows::Forms::Button());
			this->rew_button = (gcnew System::Windows::Forms::Button());
			this->pause_button = (gcnew System::Windows::Forms::Button());
			this->stop_button = (gcnew System::Windows::Forms::Button());
			this->fwd_button = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->connectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->soundToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->songlist = (gcnew System::Windows::Forms::ListBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->shuffle_button = (gcnew System::Windows::Forms::Button());
			this->connect_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textbox_ip = (gcnew System::Windows::Forms::TextBox());
			this->textbox_portnumber = (gcnew System::Windows::Forms::TextBox());
			this->client_status_box = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// play_button
			// 
			this->play_button->Location = System::Drawing::Point(76, 212);
			this->play_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->play_button->Name = L"play_button";
			this->play_button->Size = System::Drawing::Size(56, 19);
			this->play_button->TabIndex = 1;
			this->play_button->Text = L"play";
			this->play_button->UseVisualStyleBackColor = true;
			this->play_button->Click += gcnew System::EventHandler(this, &ClientGUI::play_button_Click);
			// 
			// rew_button
			// 
			this->rew_button->Location = System::Drawing::Point(16, 212);
			this->rew_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->rew_button->Name = L"rew_button";
			this->rew_button->Size = System::Drawing::Size(56, 19);
			this->rew_button->TabIndex = 2;
			this->rew_button->Text = L"rew";
			this->rew_button->UseVisualStyleBackColor = true;
			// 
			// pause_button
			// 
			this->pause_button->Location = System::Drawing::Point(137, 212);
			this->pause_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pause_button->Name = L"pause_button";
			this->pause_button->Size = System::Drawing::Size(56, 19);
			this->pause_button->TabIndex = 3;
			this->pause_button->Text = L"pause";
			this->pause_button->UseVisualStyleBackColor = true;
			// 
			// stop_button
			// 
			this->stop_button->Location = System::Drawing::Point(198, 212);
			this->stop_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(56, 19);
			this->stop_button->TabIndex = 4;
			this->stop_button->Text = L"stop";
			this->stop_button->UseVisualStyleBackColor = true;
			// 
			// fwd_button
			// 
			this->fwd_button->Location = System::Drawing::Point(259, 212);
			this->fwd_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->fwd_button->Name = L"fwd_button";
			this->fwd_button->Size = System::Drawing::Size(56, 19);
			this->fwd_button->TabIndex = 5;
			this->fwd_button->Text = L"fwd";
			this->fwd_button->UseVisualStyleBackColor = true;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->playToolStripMenuItem, this->optionToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(392, 24);
			this->menuStrip1->TabIndex = 6;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->connectToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// connectToolStripMenuItem
			// 
			this->connectToolStripMenuItem->Name = L"connectToolStripMenuItem";
			this->connectToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->connectToolStripMenuItem->Text = L"Connect";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// playToolStripMenuItem
			// 
			this->playToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->playToolStripMenuItem1 });
			this->playToolStripMenuItem->Name = L"playToolStripMenuItem";
			this->playToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->playToolStripMenuItem->Text = L"Play";
			// 
			// playToolStripMenuItem1
			// 
			this->playToolStripMenuItem1->Name = L"playToolStripMenuItem1";
			this->playToolStripMenuItem1->Size = System::Drawing::Size(96, 22);
			this->playToolStripMenuItem1->Text = L"Play";
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->soundToolStripMenuItem });
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->optionToolStripMenuItem->Text = L"Option";
			// 
			// soundToolStripMenuItem
			// 
			this->soundToolStripMenuItem->Name = L"soundToolStripMenuItem";
			this->soundToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->soundToolStripMenuItem->Text = L"Sound";
			// 
			// songlist
			// 
			this->songlist->FormattingEnabled = true;
			this->songlist->Location = System::Drawing::Point(16, 242);
			this->songlist->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->songlist->Name = L"songlist";
			this->songlist->Size = System::Drawing::Size(361, 147);
			this->songlist->TabIndex = 8;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(16, 186);
			this->progressBar1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(299, 19);
			this->progressBar1->TabIndex = 9;
			// 
			// shuffle_button
			// 
			this->shuffle_button->Location = System::Drawing::Point(320, 142);
			this->shuffle_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->shuffle_button->Name = L"shuffle_button";
			this->shuffle_button->Size = System::Drawing::Size(56, 19);
			this->shuffle_button->TabIndex = 10;
			this->shuffle_button->Text = L"shuffle";
			this->shuffle_button->UseVisualStyleBackColor = true;
			// 
			// connect_button
			// 
			this->connect_button->Location = System::Drawing::Point(198, 57);
			this->connect_button->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->connect_button->Name = L"connect_button";
			this->connect_button->Size = System::Drawing::Size(56, 19);
			this->connect_button->TabIndex = 0;
			this->connect_button->Text = L"connect";
			this->connect_button->UseVisualStyleBackColor = true;
			this->connect_button->Click += gcnew System::EventHandler(this, &ClientGUI::connect_button_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 31);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 11;
			this->label1->Text = L"IP Address";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 57);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Port number";
			// 
			// textbox_ip
			// 
			this->textbox_ip->Location = System::Drawing::Point(85, 31);
			this->textbox_ip->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textbox_ip->Name = L"textbox_ip";
			this->textbox_ip->Size = System::Drawing::Size(170, 20);
			this->textbox_ip->TabIndex = 13;
			this->textbox_ip->Text = L"192.168.1.72";
			// 
			// textbox_portnumber
			// 
			this->textbox_portnumber->Location = System::Drawing::Point(85, 56);
			this->textbox_portnumber->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textbox_portnumber->Name = L"textbox_portnumber";
			this->textbox_portnumber->Size = System::Drawing::Size(76, 20);
			this->textbox_portnumber->TabIndex = 14;
			this->textbox_portnumber->Text = L"7000";
			// 
			// client_status_box
			// 
			this->client_status_box->Enabled = false;
			this->client_status_box->Location = System::Drawing::Point(16, 98);
			this->client_status_box->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->client_status_box->Multiline = true;
			this->client_status_box->Name = L"client_status_box";
			this->client_status_box->Size = System::Drawing::Size(300, 76);
			this->client_status_box->TabIndex = 15;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 82);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(37, 13);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Status";
			// 
			// ClientGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(392, 396);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->client_status_box);
			this->Controls->Add(this->textbox_portnumber);
			this->Controls->Add(this->textbox_ip);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->connect_button);
			this->Controls->Add(this->shuffle_button);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->songlist);
			this->Controls->Add(this->fwd_button);
			this->Controls->Add(this->stop_button);
			this->Controls->Add(this->pause_button);
			this->Controls->Add(this->rew_button);
			this->Controls->Add(this->play_button);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"ClientGUI";
			this->Text = L"Comm Audio - Client";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ClientGUI::ClientGUI_FormClosing);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void connect_button_Click(System::Object^  sender, System::EventArgs^  e) {

				 PCHAR textbox_ip_string;
				 PCHAR textbox_portnumber_string;
				 INT   textbox_portnumber_int;

				 DWORD connectThreadId;

				 textbox_ip_string = (PCHAR)(PVOID)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textbox_ip->Text);
				 textbox_portnumber_string = (PCHAR)(PVOID)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textbox_portnumber->Text);
				 textbox_portnumber_int = atoi(textbox_portnumber_string);

				 si = (SocketInformation*)calloc(1, sizeof(SocketInformation));
				 si->world = (World*)calloc(1, sizeof(World));

				 strcpy_s(si->world->sockSessn.ip, MAXBUFLEN, textbox_ip_string);
				 si->world->sockSessn.portNumber = textbox_portnumber_int;
				 si->world->clientOrServer = CLIENT;

				 if (initWorld(si->world)) {
					 CreateThread(0, 0, retrieveSessionFromServer, (LPVOID)si, 0, &connectThreadId);
				 }
	}
	private: System::Void ClientGUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 Application::Exit();
	}
	private: System::Void play_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 HSTREAM streamHandle; // Handle for open stream

				 // Initialize BASS with default sound device and 44100Hz Sample rate
				 BASS_Init(-1, 44100, 0, 0, NULL);

				 // Load your soundfile and play it
				 streamHandle = BASS_StreamCreateFile(FALSE, "ladygaga.wav", 0, 0, 0);
				 BASS_ChannelPlay(streamHandle, FALSE);
	}
	};
}
