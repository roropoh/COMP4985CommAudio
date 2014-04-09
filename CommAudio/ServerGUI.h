#include "Master.h"

using namespace std;

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
	private: System::Windows::Forms::Button^  start_button;

	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::ListBox^  songlist;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  fwd_button;
	private: System::Windows::Forms::Button^  stop_button;
	private: System::Windows::Forms::Button^  pause_button;
	private: System::Windows::Forms::Button^  rew_button;
	private: System::Windows::Forms::Button^  play_button;

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
			this->start_button = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->songlist = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->fwd_button = (gcnew System::Windows::Forms::Button());
			this->stop_button = (gcnew System::Windows::Forms::Button());
			this->pause_button = (gcnew System::Windows::Forms::Button());
			this->rew_button = (gcnew System::Windows::Forms::Button());
			this->play_button = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(522, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// start_button
			// 
			this->start_button->Location = System::Drawing::Point(427, 70);
			this->start_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->start_button->Name = L"start_button";
			this->start_button->Size = System::Drawing::Size(75, 23);
			this->start_button->TabIndex = 19;
			this->start_button->Text = L"start";
			this->start_button->UseVisualStyleBackColor = true;
			this->start_button->Click += gcnew System::EventHandler(this, &ServerGUI::start_button_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(21, 138);
			this->progressBar1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(399, 23);
			this->progressBar1->TabIndex = 18;
			// 
			// songlist
			// 
			this->songlist->FormattingEnabled = true;
			this->songlist->ItemHeight = 16;
			this->songlist->Location = System::Drawing::Point(21, 207);
			this->songlist->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->songlist->Name = L"songlist";
			this->songlist->Size = System::Drawing::Size(480, 180);
			this->songlist->TabIndex = 17;
			// 
			// groupBox1
			// 
			this->groupBox1->Location = System::Drawing::Point(21, 36);
			this->groupBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->groupBox1->Size = System::Drawing::Size(399, 92);
			this->groupBox1->TabIndex = 16;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Status";
			// 
			// fwd_button
			// 
			this->fwd_button->Location = System::Drawing::Point(345, 170);
			this->fwd_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->fwd_button->Name = L"fwd_button";
			this->fwd_button->Size = System::Drawing::Size(75, 23);
			this->fwd_button->TabIndex = 15;
			this->fwd_button->Text = L"fwd";
			this->fwd_button->UseVisualStyleBackColor = true;
			// 
			// stop_button
			// 
			this->stop_button->Location = System::Drawing::Point(264, 170);
			this->stop_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(75, 23);
			this->stop_button->TabIndex = 14;
			this->stop_button->Text = L"stop";
			this->stop_button->UseVisualStyleBackColor = true;
			// 
			// pause_button
			// 
			this->pause_button->Location = System::Drawing::Point(183, 170);
			this->pause_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pause_button->Name = L"pause_button";
			this->pause_button->Size = System::Drawing::Size(75, 23);
			this->pause_button->TabIndex = 13;
			this->pause_button->Text = L"pause";
			this->pause_button->UseVisualStyleBackColor = true;
			// 
			// rew_button
			// 
			this->rew_button->Location = System::Drawing::Point(21, 170);
			this->rew_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->rew_button->Name = L"rew_button";
			this->rew_button->Size = System::Drawing::Size(75, 23);
			this->rew_button->TabIndex = 12;
			this->rew_button->Text = L"rew";
			this->rew_button->UseVisualStyleBackColor = true;
			// 
			// play_button
			// 
			this->play_button->Location = System::Drawing::Point(101, 170);
			this->play_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->play_button->Name = L"play_button";
			this->play_button->Size = System::Drawing::Size(75, 23);
			this->play_button->TabIndex = 11;
			this->play_button->Text = L"play";
			this->play_button->UseVisualStyleBackColor = true;
			// 
			// ServerGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(522, 417);
			this->Controls->Add(this->start_button);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->songlist);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->fwd_button);
			this->Controls->Add(this->stop_button);
			this->Controls->Add(this->pause_button);
			this->Controls->Add(this->rew_button);
			this->Controls->Add(this->play_button);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"ServerGUI";
			this->Text = L"Comm Audio - Server";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void start_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 DWORD waitThreadId;
				 DWORD multicastThreadId;

				 world = (World*)calloc(1, sizeof(World));

				 world->clientOrServer = SERVER;
				 world->sockSessn.portNumber = DEFAULT_SERVERPORT;
				 
				 strcpy_s(world->sockMulti.ip, "235.255.24.55"); 

				 if (initWorld(world)) {
					 CreateThread(0, 0, waitForConnections, (LPVOID)world, 0, &waitThreadId);
					 CreateThread(0, 0, sendMulticast, (LPVOID)world, 0, &multicastThreadId);
				 }
	}
};
}
