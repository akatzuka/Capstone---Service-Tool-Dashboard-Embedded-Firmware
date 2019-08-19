#pragma once
#include <map>
#include "startupWindow.h"
#include "main_client.h"

namespace servicetool {

#ifndef MODEL_INFO
#define MODEL_INFO

	typedef enum DATATYPE {
		DIN,
		DOUT,
		AIN
	};

	struct model_info {
		int din;
		int dout;
		int ain;
	};

	const std::map<char*, DATATYPE> datatypeMap = {
		{"din", DIN},
		{"dout", DOUT},
		{"ain", AIN}
	};

	/* List various models sizes needed for Manual screen */
	model_info NUCLEO = { NUCLEO_DIN, NUCLEO_DOUT, NUCLEO_AIN };

	/* Examples of others */
	model_info m13BX5 = { 13, 2, 5 };
	model_info m25BX25 = { 25, 2, 25 };
	model_info mXL45BX50 = { 45, 2, 50 };

	/* Later to be replaced with just the individual model structs or something */
	const std::map<char*, model_info*> modelMap = {
		{"Nucleo", &NUCLEO},
		{"XL45BX50", &mXL45BX50},
		{"13BX5", &m13BX5},
		{"25BX25", &m25BX25}
	};

	/* Pointer to be assigned by the chosen model */
	model_info *modelSizes;

	IOS_Data localNucleo;
	XL45BX50_Data localmXL45BX50;

	/* Out data to be assigned */
	O_DATA outData;

#endif

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for app_ui
	/// </summary>

	public ref class app_ui : public System::Windows::Forms::Form
	{
	public:
		app_ui(void)
		{
			InitializeComponent();

			startStartupWindow();
		}

	public:
		// ADD VARIABLES HERE //
		bool operational = true;
		Client *handler;
		char* model;
	private: System::Windows::Forms::Label^  modelLabel;
	public:

	private: System::Windows::Forms::Button^  firmwareUpdate;
	private: System::Windows::Forms::Label^  versionNumberLabel;
	private: System::Windows::Forms::Label^  versionNumber;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::OpenFileDialog^  uploadFile;
	private: System::Windows::Forms::Button^  button1;
	public:
	private: System::Windows::Forms::Panel^  manualPanel;

	public:
		// ADD FUNCTION DECLARATIONS HERE //
		Void startStartupWindow();
		Void setConnectionHostandPort(const char* host);
		bool connectToClient();
		Void updateStatusUpdateBox(System::String^ message); 
		void sendCommandClick();
		void getModelData(char* modelName);
		void createBtn(int decrement, DATATYPE type, int increment, IOS_Data data);
		std::string convertToStdString(System::String ^str);
		char* convertToCharPtr(System::String ^str);

		void closeHandler()
		{
			this->handler->closeSocket();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~app_ui()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::Button^  snapshotBtn;


	private: System::Windows::Forms::TabControl^  tabWindow;
	private: System::Windows::Forms::TabPage^  Home;
	private: System::Windows::Forms::TabPage^  Observation;
	private: System::Windows::Forms::RadioButton^  ethernetRadioBtn;

	private: System::Windows::Forms::Label^  hostLabel;

	private: System::Windows::Forms::PictureBox^  connectionStatus;
	private: System::Windows::Forms::Button^  disconnectBtn;
	private: System::Windows::Forms::ComboBox^  timeIntervalBox;
	private: System::Windows::Forms::PictureBox^  interphasicLogo;
	private: System::Windows::Forms::TextBox^  hostnameTextBox;
	private: System::Windows::Forms::Panel^  panel1; //Don't delete

	private: System::Windows::Forms::ColorDialog^  colorDialog1; //Don't delete
	private: System::ComponentModel::IContainer^  components;

	private: System::Windows::Forms::Label^  DILabel;
	private: System::Windows::Forms::Label^  AILabel;
	private: System::Windows::Forms::Label^  DOLabel;
	private: System::Windows::Forms::Label^  TempLabel;
	private: System::Windows::Forms::Label^  AOLabel;



	private: System::Windows::Forms::TabPage^  Manual;
	private: System::Windows::Forms::Button^  sendCmd;
	private: System::Windows::Forms::TextBox^  commandInput;
	private: System::Windows::Forms::TextBox^  TempStatus;
	private: System::Windows::Forms::TextBox^  AOStatus;
	private: System::Windows::Forms::TextBox^  AIStatus;
	private: System::Windows::Forms::TextBox^  DOStatus;
	private: System::Windows::Forms::TextBox^  DIStatus;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  statusBtn;
	private: System::Windows::Forms::Button^  stopBtn;
	private: System::Windows::Forms::Button^  startBtn;
	private: System::Windows::Forms::RichTextBox^  statusUpdateBox;
	private: System::Windows::Forms::Timer^  sys_tick;
	private: System::Windows::Forms::SaveFileDialog^  saveToFile;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(app_ui::typeid));
			this->tabWindow = (gcnew System::Windows::Forms::TabControl());
			this->Home = (gcnew System::Windows::Forms::TabPage());
			this->statusBtn = (gcnew System::Windows::Forms::Button());
			this->AOStatus = (gcnew System::Windows::Forms::TextBox());
			this->AIStatus = (gcnew System::Windows::Forms::TextBox());
			this->DOStatus = (gcnew System::Windows::Forms::TextBox());
			this->DIStatus = (gcnew System::Windows::Forms::TextBox());
			this->TempStatus = (gcnew System::Windows::Forms::TextBox());
			this->TempLabel = (gcnew System::Windows::Forms::Label());
			this->AOLabel = (gcnew System::Windows::Forms::Label());
			this->AILabel = (gcnew System::Windows::Forms::Label());
			this->DOLabel = (gcnew System::Windows::Forms::Label());
			this->DILabel = (gcnew System::Windows::Forms::Label());
			this->Observation = (gcnew System::Windows::Forms::TabPage());
			this->sendCmd = (gcnew System::Windows::Forms::Button());
			this->commandInput = (gcnew System::Windows::Forms::TextBox());
			this->stopBtn = (gcnew System::Windows::Forms::Button());
			this->startBtn = (gcnew System::Windows::Forms::Button());
			this->statusUpdateBox = (gcnew System::Windows::Forms::RichTextBox());
			this->timeIntervalBox = (gcnew System::Windows::Forms::ComboBox());
			this->snapshotBtn = (gcnew System::Windows::Forms::Button());
			this->Manual = (gcnew System::Windows::Forms::TabPage());
			this->manualPanel = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->ethernetRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->hostLabel = (gcnew System::Windows::Forms::Label());
			this->connectionStatus = (gcnew System::Windows::Forms::PictureBox());
			this->disconnectBtn = (gcnew System::Windows::Forms::Button());
			this->interphasicLogo = (gcnew System::Windows::Forms::PictureBox());
			this->hostnameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->sys_tick = (gcnew System::Windows::Forms::Timer(this->components));
			this->saveToFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->modelLabel = (gcnew System::Windows::Forms::Label());
			this->firmwareUpdate = (gcnew System::Windows::Forms::Button());
			this->versionNumberLabel = (gcnew System::Windows::Forms::Label());
			this->versionNumber = (gcnew System::Windows::Forms::Label());
			this->uploadFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabWindow->SuspendLayout();
			this->Home->SuspendLayout();
			this->Observation->SuspendLayout();
			this->Manual->SuspendLayout();
			this->manualPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->connectionStatus))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->interphasicLogo))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabWindow
			// 
			this->tabWindow->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabWindow->Controls->Add(this->Home);
			this->tabWindow->Controls->Add(this->Observation);
			this->tabWindow->Controls->Add(this->Manual);
			this->tabWindow->ItemSize = System::Drawing::Size(150, 20);
			this->tabWindow->Location = System::Drawing::Point(-3, 90);
			this->tabWindow->Name = L"tabWindow";
			this->tabWindow->SelectedIndex = 0;
			this->tabWindow->Size = System::Drawing::Size(711, 348);
			this->tabWindow->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabWindow->TabIndex = 6;
			// 
			// Home
			// 
			this->Home->Controls->Add(this->statusBtn);
			this->Home->Controls->Add(this->AOStatus);
			this->Home->Controls->Add(this->AIStatus);
			this->Home->Controls->Add(this->DOStatus);
			this->Home->Controls->Add(this->DIStatus);
			this->Home->Controls->Add(this->TempStatus);
			this->Home->Controls->Add(this->TempLabel);
			this->Home->Controls->Add(this->AOLabel);
			this->Home->Controls->Add(this->AILabel);
			this->Home->Controls->Add(this->DOLabel);
			this->Home->Controls->Add(this->DILabel);
			this->Home->Location = System::Drawing::Point(4, 24);
			this->Home->Name = L"Home";
			this->Home->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
			this->Home->Size = System::Drawing::Size(703, 320);
			this->Home->TabIndex = 0;
			this->Home->Text = L"Home";
			this->Home->UseVisualStyleBackColor = true;
			// 
			// statusBtn
			// 
			this->statusBtn->AllowDrop = true;
			this->statusBtn->Location = System::Drawing::Point(283, 37);
			this->statusBtn->Name = L"statusBtn";
			this->statusBtn->Size = System::Drawing::Size(161, 23);
			this->statusBtn->TabIndex = 17;
			this->statusBtn->Text = L"Status Change";
			this->statusBtn->UseVisualStyleBackColor = true;
			this->statusBtn->Click += gcnew System::EventHandler(this, &app_ui::statusBtn_Click);
			// 
			// AOStatus
			// 
			this->AOStatus->BackColor = System::Drawing::Color::Green;
			this->AOStatus->Cursor = System::Windows::Forms::Cursors::Default;
			this->AOStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AOStatus->ForeColor = System::Drawing::Color::White;
			this->AOStatus->Location = System::Drawing::Point(496, 226);
			this->AOStatus->Name = L"AOStatus";
			this->AOStatus->ReadOnly = true;
			this->AOStatus->Size = System::Drawing::Size(100, 26);
			this->AOStatus->TabIndex = 16;
			this->AOStatus->Text = L"Operational";
			this->AOStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// AIStatus
			// 
			this->AIStatus->BackColor = System::Drawing::Color::Green;
			this->AIStatus->Cursor = System::Windows::Forms::Cursors::Default;
			this->AIStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AIStatus->ForeColor = System::Drawing::Color::White;
			this->AIStatus->Location = System::Drawing::Point(150, 226);
			this->AIStatus->Name = L"AIStatus";
			this->AIStatus->ReadOnly = true;
			this->AIStatus->Size = System::Drawing::Size(100, 26);
			this->AIStatus->TabIndex = 15;
			this->AIStatus->Text = L"Operational";
			this->AIStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// DOStatus
			// 
			this->DOStatus->BackColor = System::Drawing::Color::Green;
			this->DOStatus->Cursor = System::Windows::Forms::Cursors::Default;
			this->DOStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DOStatus->ForeColor = System::Drawing::Color::White;
			this->DOStatus->Location = System::Drawing::Point(496, 135);
			this->DOStatus->Name = L"DOStatus";
			this->DOStatus->ReadOnly = true;
			this->DOStatus->Size = System::Drawing::Size(100, 26);
			this->DOStatus->TabIndex = 14;
			this->DOStatus->Text = L"Operational";
			this->DOStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// DIStatus
			// 
			this->DIStatus->BackColor = System::Drawing::Color::Green;
			this->DIStatus->Cursor = System::Windows::Forms::Cursors::Default;
			this->DIStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DIStatus->ForeColor = System::Drawing::Color::White;
			this->DIStatus->Location = System::Drawing::Point(150, 135);
			this->DIStatus->Name = L"DIStatus";
			this->DIStatus->ReadOnly = true;
			this->DIStatus->Size = System::Drawing::Size(100, 26);
			this->DIStatus->TabIndex = 11;
			this->DIStatus->Text = L"Operational";
			this->DIStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// TempStatus
			// 
			this->TempStatus->AcceptsReturn = true;
			this->TempStatus->BackColor = System::Drawing::Color::Green;
			this->TempStatus->Cursor = System::Windows::Forms::Cursors::Default;
			this->TempStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TempStatus->ForeColor = System::Drawing::Color::White;
			this->TempStatus->Location = System::Drawing::Point(317, 135);
			this->TempStatus->Name = L"TempStatus";
			this->TempStatus->ReadOnly = true;
			this->TempStatus->Size = System::Drawing::Size(96, 26);
			this->TempStatus->TabIndex = 10;
			this->TempStatus->Text = L"65 F";
			this->TempStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// TempLabel
			// 
			this->TempLabel->AutoSize = true;
			this->TempLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TempLabel->Location = System::Drawing::Point(298, 94);
			this->TempLabel->Name = L"TempLabel";
			this->TempLabel->Size = System::Drawing::Size(135, 26);
			this->TempLabel->TabIndex = 4;
			this->TempLabel->Text = L"Temperature";
			// 
			// AOLabel
			// 
			this->AOLabel->AutoSize = true;
			this->AOLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AOLabel->Location = System::Drawing::Point(472, 180);
			this->AOLabel->Name = L"AOLabel";
			this->AOLabel->Size = System::Drawing::Size(162, 26);
			this->AOLabel->TabIndex = 3;
			this->AOLabel->Text = L"Analog Outputs";
			// 
			// AILabel
			// 
			this->AILabel->AutoSize = true;
			this->AILabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AILabel->Location = System::Drawing::Point(133, 180);
			this->AILabel->Name = L"AILabel";
			this->AILabel->Size = System::Drawing::Size(145, 26);
			this->AILabel->TabIndex = 2;
			this->AILabel->Text = L"Analog Inputs";
			// 
			// DOLabel
			// 
			this->DOLabel->AutoSize = true;
			this->DOLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DOLabel->Location = System::Drawing::Point(472, 91);
			this->DOLabel->Name = L"DOLabel";
			this->DOLabel->Size = System::Drawing::Size(155, 26);
			this->DOLabel->TabIndex = 1;
			this->DOLabel->Text = L"Digital Outputs";
			// 
			// DILabel
			// 
			this->DILabel->AutoSize = true;
			this->DILabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DILabel->Location = System::Drawing::Point(133, 91);
			this->DILabel->Name = L"DILabel";
			this->DILabel->Size = System::Drawing::Size(138, 26);
			this->DILabel->TabIndex = 0;
			this->DILabel->Text = L"Digital Inputs";
			// 
			// Observation
			// 
			this->Observation->Controls->Add(this->sendCmd);
			this->Observation->Controls->Add(this->commandInput);
			this->Observation->Controls->Add(this->stopBtn);
			this->Observation->Controls->Add(this->startBtn);
			this->Observation->Controls->Add(this->statusUpdateBox);
			this->Observation->Controls->Add(this->timeIntervalBox);
			this->Observation->Controls->Add(this->snapshotBtn);
			this->Observation->Location = System::Drawing::Point(4, 24);
			this->Observation->Name = L"Observation";
			this->Observation->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
			this->Observation->Size = System::Drawing::Size(703, 320);
			this->Observation->TabIndex = 0;
			this->Observation->Text = L"Observation";
			this->Observation->UseVisualStyleBackColor = true;
			// 
			// sendCmd
			// 
			this->sendCmd->Location = System::Drawing::Point(628, 287);
			this->sendCmd->Name = L"sendCmd";
			this->sendCmd->Size = System::Drawing::Size(65, 20);
			this->sendCmd->TabIndex = 20;
			this->sendCmd->Text = L"Send";
			this->sendCmd->UseVisualStyleBackColor = true;
			this->sendCmd->Click += gcnew System::EventHandler(this, &app_ui::sendCmd_Click);
			// 
			// commandInput
			// 
			this->commandInput->Location = System::Drawing::Point(13, 289);
			this->commandInput->Name = L"commandInput";
			this->commandInput->Size = System::Drawing::Size(599, 20);
			this->commandInput->TabIndex = 19;
			// 
			// stopBtn
			// 
			this->stopBtn->BackColor = System::Drawing::Color::DarkRed;
			this->stopBtn->ForeColor = System::Drawing::Color::White;
			this->stopBtn->Location = System::Drawing::Point(57, 15);
			this->stopBtn->Name = L"stopBtn";
			this->stopBtn->Size = System::Drawing::Size(38, 23);
			this->stopBtn->TabIndex = 18;
			this->stopBtn->Text = L"Stop";
			this->stopBtn->UseVisualStyleBackColor = false;
			this->stopBtn->Click += gcnew System::EventHandler(this, &app_ui::stopBtn_Click);
			// 
			// startBtn
			// 
			this->startBtn->BackColor = System::Drawing::Color::DarkGreen;
			this->startBtn->ForeColor = System::Drawing::Color::White;
			this->startBtn->Location = System::Drawing::Point(13, 15);
			this->startBtn->Name = L"startBtn";
			this->startBtn->Size = System::Drawing::Size(38, 23);
			this->startBtn->TabIndex = 17;
			this->startBtn->Text = L"Start";
			this->startBtn->UseVisualStyleBackColor = false;
			this->startBtn->Click += gcnew System::EventHandler(this, &app_ui::startBtn_Click);
			// 
			// statusUpdateBox
			// 
			this->statusUpdateBox->Location = System::Drawing::Point(13, 49);
			this->statusUpdateBox->Name = L"statusUpdateBox";
			this->statusUpdateBox->ReadOnly = true;
			this->statusUpdateBox->Size = System::Drawing::Size(681, 234);
			this->statusUpdateBox->TabIndex = 16;
			this->statusUpdateBox->Text = L"";
			// 
			// timeIntervalBox
			// 
			this->timeIntervalBox->FormattingEnabled = true;
			this->timeIntervalBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1 second", L"2 seconds", L"3 seconds" });
			this->timeIntervalBox->Location = System::Drawing::Point(573, 18);
			this->timeIntervalBox->Name = L"timeIntervalBox";
			this->timeIntervalBox->Size = System::Drawing::Size(121, 21);
			this->timeIntervalBox->TabIndex = 15;
			this->timeIntervalBox->Text = L"Time Intervals";
			// 
			// snapshotBtn
			// 
			this->snapshotBtn->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->snapshotBtn->Location = System::Drawing::Point(101, 15);
			this->snapshotBtn->Name = L"snapshotBtn";
			this->snapshotBtn->Size = System::Drawing::Size(95, 23);
			this->snapshotBtn->TabIndex = 1;
			this->snapshotBtn->Text = L"Snapshot";
			this->snapshotBtn->UseVisualStyleBackColor = false;
			this->snapshotBtn->Click += gcnew System::EventHandler(this, &app_ui::snapshotBtn_Click);
			// 
			// Manual
			// 
			this->Manual->Controls->Add(this->manualPanel);
			this->Manual->Location = System::Drawing::Point(4, 24);
			this->Manual->Name = L"Manual";
			this->Manual->Size = System::Drawing::Size(703, 320);
			this->Manual->TabIndex = 2;
			this->Manual->Text = L"Manual";
			this->Manual->UseVisualStyleBackColor = true;
			// 
			// manualPanel
			// 
			this->manualPanel->AutoScroll = true;
			this->manualPanel->Controls->Add(this->button1);
			this->manualPanel->Controls->Add(this->button2);
			this->manualPanel->Location = System::Drawing::Point(11, 4);
			this->manualPanel->Name = L"manualPanel";
			this->manualPanel->Size = System::Drawing::Size(683, 322);
			this->manualPanel->TabIndex = 0;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(579, 9);
			this->button2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(65, 23);
			this->button2->TabIndex = 0;
			this->button2->Text = L"Send";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &app_ui::button2_Click);
			// 
			// ethernetRadioBtn
			// 
			this->ethernetRadioBtn->Checked = true;
			this->ethernetRadioBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ethernetRadioBtn->Location = System::Drawing::Point(550, 31);
			this->ethernetRadioBtn->Name = L"ethernetRadioBtn";
			this->ethernetRadioBtn->Size = System::Drawing::Size(65, 20);
			this->ethernetRadioBtn->TabIndex = 7;
			this->ethernetRadioBtn->TabStop = true;
			this->ethernetRadioBtn->Text = L"Ethernet";
			this->ethernetRadioBtn->UseVisualStyleBackColor = true;
			// 
			// hostLabel
			// 
			this->hostLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hostLabel->Location = System::Drawing::Point(401, 31);
			this->hostLabel->Name = L"hostLabel";
			this->hostLabel->Size = System::Drawing::Size(35, 23);
			this->hostLabel->TabIndex = 11;
			this->hostLabel->Text = L"Host";
			this->hostLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// connectionStatus
			// 
			this->connectionStatus->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->connectionStatus->Location = System::Drawing::Point(382, 15);
			this->connectionStatus->Name = L"connectionStatus";
			this->connectionStatus->Size = System::Drawing::Size(28, 22);
			this->connectionStatus->TabIndex = 13;
			this->connectionStatus->TabStop = false;
			// 
			// disconnectBtn
			// 
			this->disconnectBtn->Location = System::Drawing::Point(619, 31);
			this->disconnectBtn->Name = L"disconnectBtn";
			this->disconnectBtn->Size = System::Drawing::Size(75, 21);
			this->disconnectBtn->TabIndex = 14;
			this->disconnectBtn->Text = L"Disconnect";
			this->disconnectBtn->UseVisualStyleBackColor = true;
			this->disconnectBtn->Click += gcnew System::EventHandler(this, &app_ui::disconnectBtn_Click);
			// 
			// interphasicLogo
			// 
			this->interphasicLogo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"interphasicLogo.Image")));
			this->interphasicLogo->Location = System::Drawing::Point(11, 9);
			this->interphasicLogo->Name = L"interphasicLogo";
			this->interphasicLogo->Size = System::Drawing::Size(192, 65);
			this->interphasicLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->interphasicLogo->TabIndex = 16;
			this->interphasicLogo->TabStop = false;
			// 
			// hostnameTextBox
			// 
			this->hostnameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hostnameTextBox->Location = System::Drawing::Point(441, 32);
			this->hostnameTextBox->Name = L"hostnameTextBox";
			this->hostnameTextBox->Size = System::Drawing::Size(101, 21);
			this->hostnameTextBox->TabIndex = 9;
			this->hostnameTextBox->Text = L"127.0.0.1";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->connectionStatus);
			this->panel1->Location = System::Drawing::Point(304, 41);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(416, 52);
			this->panel1->TabIndex = 0;
			// 
			// sys_tick
			// 
			this->sys_tick->Tick += gcnew System::EventHandler(this, &app_ui::sys_tick_Tick);
			// 
			// modelLabel
			// 
			this->modelLabel->AutoSize = true;
			this->modelLabel->Font = (gcnew System::Drawing::Font(L"Arial", 16, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->modelLabel->Location = System::Drawing::Point(207, 32);
			this->modelLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->modelLabel->Name = L"modelLabel";
			this->modelLabel->Padding = System::Windows::Forms::Padding(0, 2, 0, 0);
			this->modelLabel->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->modelLabel->Size = System::Drawing::Size(91, 27);
			this->modelLabel->TabIndex = 17;
			this->modelLabel->Text = L"MODEL";
			// 
			// firmwareUpdate
			// 
			this->firmwareUpdate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->firmwareUpdate->Location = System::Drawing::Point(619, 60);
			this->firmwareUpdate->Name = L"firmwareUpdate";
			this->firmwareUpdate->Size = System::Drawing::Size(75, 21);
			this->firmwareUpdate->TabIndex = 23;
			this->firmwareUpdate->Text = L"Update";
			this->firmwareUpdate->UseVisualStyleBackColor = true;
			this->firmwareUpdate->Click += gcnew System::EventHandler(this, &app_ui::firmwareUpdate_Click);
			// 
			// versionNumberLabel
			// 
			this->versionNumberLabel->AutoSize = true;
			this->versionNumberLabel->Location = System::Drawing::Point(427, 64);
			this->versionNumberLabel->Name = L"versionNumberLabel";
			this->versionNumberLabel->Size = System::Drawing::Size(130, 13);
			this->versionNumberLabel->TabIndex = 21;
			this->versionNumberLabel->Text = L"Current Firmware Version: ";
			// 
			// versionNumber
			// 
			this->versionNumber->AutoSize = true;
			this->versionNumber->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->versionNumber->Location = System::Drawing::Point(563, 66);
			this->versionNumber->Name = L"versionNumber";
			this->versionNumber->Size = System::Drawing::Size(55, 14);
			this->versionNumber->TabIndex = 22;
			this->versionNumber->Text = L"v2018.1.1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(579, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(65, 24);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Stop";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &app_ui::button1_Click);
			// 
			// app_ui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(709, 435);
			this->Controls->Add(this->firmwareUpdate);
			this->Controls->Add(this->modelLabel);
			this->Controls->Add(this->versionNumberLabel);
			this->Controls->Add(this->tabWindow);
			this->Controls->Add(this->versionNumber);
			this->Controls->Add(this->interphasicLogo);
			this->Controls->Add(this->disconnectBtn);
			this->Controls->Add(this->hostLabel);
			this->Controls->Add(this->hostnameTextBox);
			this->Controls->Add(this->ethernetRadioBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"app_ui";
			this->Text = L"Service Tool";
			this->Load += gcnew System::EventHandler(this, &app_ui::app_ui_Load);
			this->tabWindow->ResumeLayout(false);
			this->Home->ResumeLayout(false);
			this->Home->PerformLayout();
			this->Observation->ResumeLayout(false);
			this->Observation->PerformLayout();
			this->Manual->ResumeLayout(false);
			this->manualPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->connectionStatus))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->interphasicLogo))->EndInit();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void observationBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->tabWindow->SelectTab(Observation);
	}

	private: System::Void homeBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->tabWindow->SelectTab(Home);
	}

	private: System::Void app_ui_Load(System::Object^  sender, System::EventArgs^  e) 
	{}

	private: System::Void disconnectBtn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (this->disconnectBtn->Text == "Disconnect")
		{
			this->hostnameTextBox->Text = L"";
			this->disconnectBtn->Text = L"Connect";
			// Disconnect from socket
			this->handler->closeSocket();
		}
		else
		{
			connectToClient();
		}
	}

	private: System::Void statusBtn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (operational)
		{
			this->DIStatus->BackColor = System::Drawing::Color::Red;
			this->DOStatus->BackColor = System::Drawing::Color::Red;
			this->AIStatus->BackColor = System::Drawing::Color::Red;
			this->AOStatus->BackColor = System::Drawing::Color::Red;
			this->TempStatus->BackColor = System::Drawing::Color::Red;

			this->DIStatus->Text = L"Error";
			this->DOStatus->Text = L"Error";
			this->AIStatus->Text = L"Error";
			this->AOStatus->Text = L"Error";
			this->TempStatus->Text = L"100 �F";
			
			operational = false;
		}
		else
		{
			this->DIStatus->BackColor = System::Drawing::Color::Green;
			this->DOStatus->BackColor = System::Drawing::Color::Green;
			this->AIStatus->BackColor = System::Drawing::Color::Green;
			this->AOStatus->BackColor = System::Drawing::Color::Green;
			this->TempStatus->BackColor = System::Drawing::Color::Green;

			this->DIStatus->Text = L"Operational";
			this->DOStatus->Text = L"Operational";
			this->AIStatus->Text = L"Operational";
			this->AOStatus->Text = L"Operational";
			this->TempStatus->Text = L"65 F";

			operational = true;
		}
	}
	private: System::Void snapshotBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		sys_tick->Stop();
		saveToFile->DefaultExt = "*.rtf";
		saveToFile->Filter = "Rich Text Format|*.rtf";
		saveToFile->Title = "Save a Text File";
		if (saveToFile->ShowDialog() == System::Windows::Forms::DialogResult::OK && saveToFile->FileName->Length > 0) {
			statusUpdateBox->SaveFile(saveToFile->FileName);
		}
	}
	private: System::Void sys_tick_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		if (timeIntervalBox->SelectedIndex == 0)
			sys_tick->Interval = 1000;
		else if (timeIntervalBox->SelectedIndex == 1)
			sys_tick->Interval = 2000;
		else if (timeIntervalBox->SelectedIndex == 2)
			sys_tick->Interval = 3000;

		updateStatusUpdateBox(this->handler->Observe() + "\r\n");

		statusUpdateBox->ScrollToCaret();
	}

	private: System::Void startBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		sys_tick->Start();
	}

	private: System::Void stopBtn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		sys_tick->Stop();
	}

	private: System::Void sendCmd_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		sendCommandClick();
	}

	private: System::Void ioButtons_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		// Will want to create a custom button or model base class so that it can have other 
		// modes other than 'on' and 'off'
		System::String ^name = safe_cast<Button ^>(sender)->Name;
		printf("Button clicked: %s\n", name);
		int intValue = 0;

		cli::array<String^> ^strArray = name->Split('_');
		DATATYPE type;
		char* typeString = convertToCharPtr(strArray[0]);

		for (auto x : datatypeMap)
		{
			if (strcmp(x.first, typeString) == 0)
			{
				printf("Found match to: %s\n", typeString);
				type = x.second;
			}
		}


		if (safe_cast<Button ^>(sender)->Text == "on")
		{
			safe_cast<Button ^>(sender)->Text = L"off";
			safe_cast<Button ^>(sender)->BackColor = System::Drawing::Color::Red;
			intValue = 0;
		}
		else if(safe_cast<Button ^>(sender)->Text == "off")
		{
			safe_cast<Button ^>(sender)->Text = L"on";
			safe_cast<Button ^>(sender)->BackColor = System::Drawing::Color::Green;
			intValue = 1;
		}

		switch (type)
		{
			case DATATYPE::DIN: {
				localNucleo.din[atol(convertToCharPtr(strArray[1]))] = intValue;
				printf("Button clicked din value: %d\n",localNucleo.din[atol(convertToCharPtr(strArray[1]))]);
				break;
			}
			case DATATYPE::DOUT: {
				localNucleo.dout[atol(convertToCharPtr(strArray[1]))] = intValue;
				outData.dout[atol(convertToCharPtr(strArray[1]))] = intValue;
				printf("Button clicked dout value: %d\n", localNucleo.dout[atol(convertToCharPtr(strArray[1]))]);
				break;
			}
		}
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->handler->Manual(outData);
	}

	private: System::Void firmwareUpdate_Click(System::Object^  sender, System::EventArgs^  e) {
	
		this->uploadFile->InitialDirectory = "c:\\";
		this->uploadFile->DefaultExt = "*.bin";
		this->uploadFile->Filter = "Binary files(*.bin) | *.bin";
		this->uploadFile->Title = "Upload Firmware Update";

		if (this->uploadFile->ShowDialog() == System::Windows::Forms::DialogResult::OK && uploadFile->FileName->Length > 0)
		{
			this->handler->Update(convertToStdString(uploadFile->FileName));
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->handler->Stop_Manual();
	}
};
}