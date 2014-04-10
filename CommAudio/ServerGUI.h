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
	/// Summary for ServerGUI
	/// </summary>
	public ref class ServerGUI : public System::Windows::Forms::Form
	{
	public:
		char* file_name;

		ServerGUI(void)
		{
			InitializeComponent();

			initWSA();

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ServerGUI()
		{
			WSACleanup();
			if (components)
			{
				delete components;
			}
		}

	private: World* world;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::Button^  shuffle_button;


	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::ListBox^  songlist;

	private: System::Windows::Forms::Button^  fwd_button;
	private: System::Windows::Forms::Button^  stop_button;
	private: System::Windows::Forms::Button^  pause_button;
	private: System::Windows::Forms::Button^  rew_button;
	private: System::Windows::Forms::Button^  play_button;
	private: System::Windows::Forms::TextBox^  server_status_box;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  start_button;
	private: System::Windows::Forms::Button^  openfile_button;



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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shuffle_button = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->songlist = (gcnew System::Windows::Forms::ListBox());
			this->fwd_button = (gcnew System::Windows::Forms::Button());
			this->stop_button = (gcnew System::Windows::Forms::Button());
			this->pause_button = (gcnew System::Windows::Forms::Button());
			this->rew_button = (gcnew System::Windows::Forms::Button());
			this->play_button = (gcnew System::Windows::Forms::Button());
			this->server_status_box = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->start_button = (gcnew System::Windows::Forms::Button());
			this->openfile_button = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(392, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(92, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// shuffle_button
			// 
			this->shuffle_button->Location = System::Drawing::Point(320, 84);
			this->shuffle_button->Margin = System::Windows::Forms::Padding(2);
			this->shuffle_button->Name = L"shuffle_button";
			this->shuffle_button->Size = System::Drawing::Size(56, 19);
			this->shuffle_button->TabIndex = 19;
			this->shuffle_button->Text = L"shuffle";
			this->shuffle_button->UseVisualStyleBackColor = true;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(16, 140);
			this->progressBar1->Margin = System::Windows::Forms::Padding(2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(299, 19);
			this->progressBar1->TabIndex = 18;
			// 
			// songlist
			// 
			this->songlist->FormattingEnabled = true;
			this->songlist->Location = System::Drawing::Point(16, 196);
			this->songlist->Margin = System::Windows::Forms::Padding(2);
			this->songlist->Name = L"songlist";
			this->songlist->Size = System::Drawing::Size(361, 147);
			this->songlist->TabIndex = 17;
			// 
			// fwd_button
			// 
			this->fwd_button->Location = System::Drawing::Point(259, 166);
			this->fwd_button->Margin = System::Windows::Forms::Padding(2);
			this->fwd_button->Name = L"fwd_button";
			this->fwd_button->Size = System::Drawing::Size(56, 19);
			this->fwd_button->TabIndex = 15;
			this->fwd_button->Text = L"fwd";
			this->fwd_button->UseVisualStyleBackColor = true;
			// 
			// stop_button
			// 
			this->stop_button->Location = System::Drawing::Point(198, 166);
			this->stop_button->Margin = System::Windows::Forms::Padding(2);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(56, 19);
			this->stop_button->TabIndex = 14;
			this->stop_button->Text = L"stop";
			this->stop_button->UseVisualStyleBackColor = true;
			// 
			// pause_button
			// 
			this->pause_button->Location = System::Drawing::Point(137, 166);
			this->pause_button->Margin = System::Windows::Forms::Padding(2);
			this->pause_button->Name = L"pause_button";
			this->pause_button->Size = System::Drawing::Size(56, 19);
			this->pause_button->TabIndex = 13;
			this->pause_button->Text = L"pause";
			this->pause_button->UseVisualStyleBackColor = true;
			// 
			// rew_button
			// 
			this->rew_button->Location = System::Drawing::Point(16, 166);
			this->rew_button->Margin = System::Windows::Forms::Padding(2);
			this->rew_button->Name = L"rew_button";
			this->rew_button->Size = System::Drawing::Size(56, 19);
			this->rew_button->TabIndex = 12;
			this->rew_button->Text = L"rew";
			this->rew_button->UseVisualStyleBackColor = true;
			// 
			// play_button
			// 
			this->play_button->Location = System::Drawing::Point(76, 166);
			this->play_button->Margin = System::Windows::Forms::Padding(2);
			this->play_button->Name = L"play_button";
			this->play_button->Size = System::Drawing::Size(56, 19);
			this->play_button->TabIndex = 11;
			this->play_button->Text = L"play";
			this->play_button->UseVisualStyleBackColor = true;
			this->play_button->Click += gcnew System::EventHandler(this, &ServerGUI::play_button_Click);
			// 
			// server_status_box
			// 
			this->server_status_box->Enabled = false;
			this->server_status_box->Location = System::Drawing::Point(16, 53);
			this->server_status_box->Margin = System::Windows::Forms::Padding(2);
			this->server_status_box->Multiline = true;
			this->server_status_box->Name = L"server_status_box";
			this->server_status_box->Size = System::Drawing::Size(300, 76);
			this->server_status_box->TabIndex = 20;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(14, 31);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(37, 13);
			this->label3->TabIndex = 21;
			this->label3->Text = L"Status";
			// 
			// start_button
			// 
			this->start_button->Location = System::Drawing::Point(320, 31);
			this->start_button->Margin = System::Windows::Forms::Padding(2);
			this->start_button->Name = L"start_button";
			this->start_button->Size = System::Drawing::Size(56, 19);
			this->start_button->TabIndex = 22;
			this->start_button->Text = L"start";
			this->start_button->UseVisualStyleBackColor = true;
			this->start_button->Click += gcnew System::EventHandler(this, &ServerGUI::start_button_Click_1);
			// 
			// openfile_button
			// 
			this->openfile_button->Location = System::Drawing::Point(320, 63);
			this->openfile_button->Margin = System::Windows::Forms::Padding(2);
			this->openfile_button->Name = L"openfile_button";
			this->openfile_button->Size = System::Drawing::Size(56, 19);
			this->openfile_button->TabIndex = 23;
			this->openfile_button->Text = L"open file";
			this->openfile_button->UseVisualStyleBackColor = true;
			this->openfile_button->Click += gcnew System::EventHandler(this, &ServerGUI::openfile_button_Click);
			// 
			// ServerGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(392, 354);
			this->Controls->Add(this->openfile_button);
			this->Controls->Add(this->start_button);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->server_status_box);
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
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"ServerGUI";
			this->Text = L"Comm Audio - Server";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ServerGUI::ServerGUI_FormClosing);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void play_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 HSTREAM streamHandle; // Handle for open stream
				 MediaComponent media;
				 // Initialize BASS with default sound device and 44100Hz Sample rate
				 BASS_Init(-1, 44100, 0, 0, NULL);

				 // Load your soundfile and play it
				 streamHandle = BASS_StreamCreateFile(FALSE, file_name, 0, 0, 0);
				 BASS_ChannelGetData(streamHandle, media.buffer, PACKETSIZE);
				 //BASS_ChannelPlay(streamHandle, FALSE);
				 //BASS_StreamPutData(streamHandle, media.buffer, PACKETSIZE);
	}
	private: System::Void openfile_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
				 openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
				 openFileDialog1->FilterIndex = 2;
				 openFileDialog1->RestoreDirectory = true;

				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
					 file_name = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);

					 //file_name_string = gcnew System::String(file_name);
					 songlist->Items->Add(openFileDialog1->SafeFileName);
				 }
	}
	private: System::Void ServerGUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 Application::Exit();
	}
	private: System::Void start_button_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 DWORD waitThreadId;
				 DWORD multicastThreadId;

				 world = (World*)calloc(1, sizeof(World));

				 world->clientOrServer = SERVER;
				 world->sockSessn.portNumber = DEFAULT_SERVERPORT;

				 strcpy_s(world->sockMulti.ip, "235.100.24.55");

				 if (initWorld(world)) {
					 CreateThread(0, 0, waitForConnections, (LPVOID)world, 0, &waitThreadId);
					 CreateThread(0, 0, sendMulticast, (LPVOID)world, 0, &multicastThreadId);
				 }
	}
	};
}
