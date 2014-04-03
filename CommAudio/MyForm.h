#include "Master.h"
#include "ClientGUI.h"

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
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: World* world;

	private: System::Windows::Forms::Button^  main_client_button;
	private: System::Windows::Forms::Button^  main_server_button;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  modeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clientToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  serverToolStripMenuItem;
	protected:

	protected:

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
			this->main_client_button = (gcnew System::Windows::Forms::Button());
			this->main_server_button = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clientToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->serverToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// main_client_button
			// 
			this->main_client_button->Location = System::Drawing::Point(98, 70);
			this->main_client_button->Name = L"main_client_button";
			this->main_client_button->Size = System::Drawing::Size(75, 23);
			this->main_client_button->TabIndex = 0;
			this->main_client_button->Text = L"Client";
			this->main_client_button->UseVisualStyleBackColor = true;
			this->main_client_button->Click += gcnew System::EventHandler(this, &MyForm::main_client_button_Click);
			// 
			// main_server_button
			// 
			this->main_server_button->Location = System::Drawing::Point(98, 131);
			this->main_server_button->Name = L"main_server_button";
			this->main_server_button->Size = System::Drawing::Size(75, 23);
			this->main_server_button->TabIndex = 1;
			this->main_server_button->Text = L"Server";
			this->main_server_button->UseVisualStyleBackColor = true;
			this->main_server_button->Click += gcnew System::EventHandler(this, &MyForm::main_server_button_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->modeToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(282, 28);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// modeToolStripMenuItem
			// 
			this->modeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->clientToolStripMenuItem,
					this->serverToolStripMenuItem
			});
			this->modeToolStripMenuItem->Name = L"modeToolStripMenuItem";
			this->modeToolStripMenuItem->Size = System::Drawing::Size(60, 24);
			this->modeToolStripMenuItem->Text = L"Mode";
			// 
			// clientToolStripMenuItem
			// 
			this->clientToolStripMenuItem->Name = L"clientToolStripMenuItem";
			this->clientToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->clientToolStripMenuItem->Text = L"Client";
			// 
			// serverToolStripMenuItem
			// 
			this->serverToolStripMenuItem->Name = L"serverToolStripMenuItem";
			this->serverToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->serverToolStripMenuItem->Text = L"Server";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->main_server_button);
			this->Controls->Add(this->main_client_button);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Comm Audio";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void main_client_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 ClientGUI ^ clientForm = gcnew ClientGUI();

				 world = (World*)calloc(1, sizeof(World));
				 
				 world->clientOrServer = CLIENT;
				 this->Hide();
				 clientForm->Show();
	}
	private: System::Void main_server_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 world = (World*)calloc(1, sizeof(World));

				 world->clientOrServer = SERVER;
				 this->Hide();
	}
	};
}
