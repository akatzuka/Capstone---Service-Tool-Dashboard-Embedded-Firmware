#pragma once
#include <iostream>
#include <stdio.h>

using namespace std;

namespace servicetool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for startupWindow
	/// </summary>
	public ref class startupWindow : public System::Windows::Forms::Form
	{
	public:
		startupWindow(void)
		{
			InitializeComponent();
			this->modelSelectionBox->SelectedIndex = 1;
			this->connectionSelection->SelectedIndex = 1;
		}

		explicit startupWindow(char* model)
		{
			InitializeComponent();
			this->model = model;
		}

	public:
	public:
		const char* host;

		const char* getHost();
		void connectBtnClick();
		char* model;

		char* getModelName();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~startupWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ComboBox^  modelSelectionBox;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  connectionSelection;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  connectBtn;



	private: System::Windows::Forms::TextBox^  hostInputBox;

	private: System::Windows::Forms::Label^  label3;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(startupWindow::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->modelSelectionBox = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->connectionSelection = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->connectBtn = (gcnew System::Windows::Forms::Button());
			this->hostInputBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(220, 78);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(492, 182);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 17;
			this->pictureBox1->TabStop = false;
			// 
			// modelSelectionBox
			// 
			this->modelSelectionBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->modelSelectionBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Select a Model", L"Nucleo", L"XL45BX50", L"25BX25",
					L"13BX5"
			});
			this->modelSelectionBox->Location = System::Drawing::Point(333, 286);
			this->modelSelectionBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->modelSelectionBox->Name = L"modelSelectionBox";
			this->modelSelectionBox->Size = System::Drawing::Size(378, 28);
			this->modelSelectionBox->TabIndex = 18;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(216, 291);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(105, 20);
			this->label1->TabIndex = 19;
			this->label1->Text = L"Select Model:";
			// 
			// connectionSelection
			// 
			this->connectionSelection->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->connectionSelection->FormattingEnabled = true;
			this->connectionSelection->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Select a Connection", L"Ethernet",
					L"USB", L"CAN BUS", L"Bluetooth"
			});
			this->connectionSelection->Location = System::Drawing::Point(333, 328);
			this->connectionSelection->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->connectionSelection->Name = L"connectionSelection";
			this->connectionSelection->Size = System::Drawing::Size(378, 28);
			this->connectionSelection->TabIndex = 20;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(216, 332);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 20);
			this->label2->TabIndex = 21;
			this->label2->Text = L"Connection";
			// 
			// connectBtn
			// 
			this->connectBtn->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->connectBtn->Location = System::Drawing::Point(600, 367);
			this->connectBtn->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->connectBtn->Name = L"connectBtn";
			this->connectBtn->Size = System::Drawing::Size(112, 35);
			this->connectBtn->TabIndex = 22;
			this->connectBtn->Text = L"Connect";
			this->connectBtn->UseVisualStyleBackColor = true;
			this->connectBtn->Click += gcnew System::EventHandler(this, &startupWindow::button1_Click);
			// 
			// hostInputBox
			// 
			this->hostInputBox->Location = System::Drawing::Point(333, 371);
			this->hostInputBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->hostInputBox->MinimumSize = System::Drawing::Size(4, 35);
			this->hostInputBox->Name = L"hostInputBox";
			this->hostInputBox->Size = System::Drawing::Size(244, 26);
			this->hostInputBox->TabIndex = 9;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(216, 371);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(87, 20);
			this->label3->TabIndex = 11;
			this->label3->Text = L"IP Address";
			this->label3->Click += gcnew System::EventHandler(this, &startupWindow::label3_Click);
			// 
			// startupWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ClientSize = System::Drawing::Size(940, 517);
			this->Controls->Add(this->hostInputBox);
			this->Controls->Add(this->connectBtn);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->connectionSelection);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->modelSelectionBox);
			this->Controls->Add(this->pictureBox1);
			this->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"startupWindow";
			this->Text = L"Service Tool";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	connectBtnClick();
}

private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void portInputBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
