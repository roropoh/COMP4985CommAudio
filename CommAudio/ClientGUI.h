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

	private: World* world;

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
	private: System::Windows::Forms::GroupBox^  groupBox1;
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
			this->playToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->soundToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->songlist = (gcnew System::Windows::Forms::ListBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->shuffle_button = (gcnew System::Windows::Forms::Button());
			this->connect_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textbox_ip = (gcnew System::Windows::Forms::TextBox());
			this->textbox_portnumber = (gcnew System::Windows::Forms::TextBox());
			this->connectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// play_button
			// 
			this->play_button->Location = System::Drawing::Point(101, 240);
			this->play_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->play_button->Name = L"play_button";
			this->play_button->Size = System::Drawing::Size(75, 23);
			this->play_button->TabIndex = 1;
			this->play_button->Text = L"play";
			this->play_button->UseVisualStyleBackColor = true;
			// 
			// rew_button
			// 
			this->rew_button->Location = System::Drawing::Point(21, 240);
			this->rew_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->rew_button->Name = L"rew_button";
			this->rew_button->Size = System::Drawing::Size(75, 23);
			this->rew_button->TabIndex = 2;
			this->rew_button->Text = L"rew";
			this->rew_button->UseVisualStyleBackColor = true;
			// 
			// pause_button
			// 
			this->pause_button->Location = System::Drawing::Point(183, 240);
			this->pause_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pause_button->Name = L"pause_button";
			this->pause_button->Size = System::Drawing::Size(75, 23);
			this->pause_button->TabIndex = 3;
			this->pause_button->Text = L"pause";
			this->pause_button->UseVisualStyleBackColor = true;
			// 
			// stop_button
			// 
			this->stop_button->Location = System::Drawing::Point(264, 240);
			this->stop_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(75, 23);
			this->stop_button->TabIndex = 4;
			this->stop_button->Text = L"stop";
			this->stop_button->UseVisualStyleBackColor = true;
			// 
			// fwd_button
			// 
			this->fwd_button->Location = System::Drawing::Point(345, 240);
			this->fwd_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->fwd_button->Name = L"fwd_button";
			this->fwd_button->Size = System::Drawing::Size(75, 23);
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
			this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(522, 28);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// playToolStripMenuItem
			// 
			this->playToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->playToolStripMenuItem1 });
			this->playToolStripMenuItem->Name = L"playToolStripMenuItem";
			this->playToolStripMenuItem->Size = System::Drawing::Size(48, 24);
			this->playToolStripMenuItem->Text = L"Play";
			// 
			// playToolStripMenuItem1
			// 
			this->playToolStripMenuItem1->Name = L"playToolStripMenuItem1";
			this->playToolStripMenuItem1->Size = System::Drawing::Size(105, 24);
			this->playToolStripMenuItem1->Text = L"Play";
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->soundToolStripMenuItem });
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(67, 24);
			this->optionToolStripMenuItem->Text = L"Option";
			// 
			// soundToolStripMenuItem
			// 
			this->soundToolStripMenuItem->Name = L"soundToolStripMenuItem";
			this->soundToolStripMenuItem->Size = System::Drawing::Size(120, 24);
			this->soundToolStripMenuItem->Text = L"Sound";
			// 
			// groupBox1
			// 
			this->groupBox1->Location = System::Drawing::Point(21, 106);
			this->groupBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->groupBox1->Size = System::Drawing::Size(399, 92);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Status";
			// 
			// songlist
			// 
			this->songlist->FormattingEnabled = true;
			this->songlist->ItemHeight = 16;
			this->songlist->Location = System::Drawing::Point(21, 277);
			this->songlist->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->songlist->Name = L"songlist";
			this->songlist->Size = System::Drawing::Size(480, 180);
			this->songlist->TabIndex = 8;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(21, 208);
			this->progressBar1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(399, 23);
			this->progressBar1->TabIndex = 9;
			// 
			// shuffle_button
			// 
			this->shuffle_button->Location = System::Drawing::Point(427, 140);
			this->shuffle_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->shuffle_button->Name = L"shuffle_button";
			this->shuffle_button->Size = System::Drawing::Size(75, 23);
			this->shuffle_button->TabIndex = 10;
			this->shuffle_button->Text = L"shuffle";
			this->shuffle_button->UseVisualStyleBackColor = true;
			// 
			// connect_button
			// 
			this->connect_button->Location = System::Drawing::Point(264, 70);
			this->connect_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->connect_button->Name = L"connect_button";
			this->connect_button->Size = System::Drawing::Size(75, 23);
			this->connect_button->TabIndex = 0;
			this->connect_button->Text = L"connect";
			this->connect_button->UseVisualStyleBackColor = true;
			this->connect_button->Click += gcnew System::EventHandler(this, &ClientGUI::connect_button_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 17);
			this->label1->TabIndex = 11;
			this->label1->Text = L"IP Address";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 17);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Port number";
			// 
			// textbox_ip
			// 
			this->textbox_ip->Location = System::Drawing::Point(113, 38);
			this->textbox_ip->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textbox_ip->Name = L"textbox_ip";
			this->textbox_ip->Size = System::Drawing::Size(225, 22);
			this->textbox_ip->TabIndex = 13;
			this->textbox_ip->Text = L"127.0.0.1";
			// 
			// textbox_portnumber
			// 
			this->textbox_portnumber->Location = System::Drawing::Point(113, 69);
			this->textbox_portnumber->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textbox_portnumber->Name = L"textbox_portnumber";
			this->textbox_portnumber->Size = System::Drawing::Size(100, 22);
			this->textbox_portnumber->TabIndex = 14;
			this->textbox_portnumber->Text = L"5150";
			// 
			// connectToolStripMenuItem
			// 
			this->connectToolStripMenuItem->Name = L"connectToolStripMenuItem";
			this->connectToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->connectToolStripMenuItem->Text = L"Connect";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// ClientGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(522, 468);
			this->Controls->Add(this->textbox_portnumber);
			this->Controls->Add(this->textbox_ip);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->connect_button);
			this->Controls->Add(this->shuffle_button);
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
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"ClientGUI";
			this->Text = L"Comm Audio - Client";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//TCP
			// new thread:
			// ~struct: sendSockParams > socket, stats, buff

		//TCP
			// new thread:
			// ~struct: recvSockParams > socket, stats, buff
			// setRecvSockParams ( recvSockParams )
			// createAndBindSock ( recvSockPrams -> socket )	
			// listenForConnections ( (new) recvSockParams -> socket )
			// if established -> new thread:
				// tcpWithClient <> doTcpWithClientWork
				// end
			// back to listenForConnections

		// UDP
			// new thread
			// ~struct: recvSockParams > socket, stats, buff
			// setSendSockParams ( sendSockParams )
			// createAndBindSock ( sendSockPrams -> socket )
			// udpMulticast <> doUdpMulticastWork
			// close

private: System::Void initWSA() {
			 
			WORD wVersionRequested;
			WSADATA WSAData;

			wVersionRequested = MAKEWORD(2, 2);

			if (WSAStartup(wVersionRequested, &WSAData) != 0) {
				MessageBox::Show("WSAStartup failed with error (" + WSAGetLastError() + ")", "Error");
				WSACleanup();
				exit(1);
			}

		}

private: System::Void connect_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 char* textbox_ip_string;
			 char* textbox_portnumber_string;
			 INT textbox_portnumber_int;
		   	 DWORD connectThreadId;
				
			 world = (World*)calloc(1, sizeof(World));

			 world->clientOrServer = CLIENT;
			 world->sockTcp.protocol = SOCK_STREAM;

			 textbox_ip_string = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textbox_ip->Text);
			 textbox_portnumber_string = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textbox_portnumber->Text);
			 textbox_portnumber_int = atoi(textbox_portnumber_string);

			 strcpy(world->sockTcp.ip, textbox_ip_string);
			 world->sockTcp.portNumber = textbox_portnumber_int;

			 if(initWorld(world)) {
				 CreateThread(0, 0, retrieveSessionFromServer, (LPVOID)world, 0, &connectThreadId);
			 }
}

private: System::Void serverToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 DWORD waitThreadId;
			 DWORD multicastThreadId;

			 world = (World*)calloc(1, sizeof(World));

			 world->clientOrServer		 = SERVER;
			 world->sockTcp.protocol   = SOCK_STREAM;
			 world->sockTcp.portNumber = DEFAULT_SERVERPORT;

			 if(initWorld(world)) {
				 CreateThread(0, 0, waitForConnections, (LPVOID)world, 0, &waitThreadId);
				 CreateThread(0, 0, sendMulticast, (LPVOID)world, 0, &multicastThreadId);
			 }
}
};
}
