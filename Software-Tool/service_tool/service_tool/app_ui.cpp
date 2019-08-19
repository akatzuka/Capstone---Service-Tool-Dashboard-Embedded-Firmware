#include "startupWindow.h"
#include "app_ui.h"
#include <msclr/marshal_cppstd.h>

using namespace servicetool;
using namespace System::Runtime::InteropServices;

using namespace servicetool;
using namespace System::Globalization;

[STAThread]


void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	servicetool::app_ui form;
	Application::Run(%form);
	form.closeHandler();
}

Void app_ui::startStartupWindow() {
	//this->handler = new tcpHandler();
	this->handler = new Client();

	startupWindow form;
	form.ShowDialog();

	setConnectionHostandPort(form.getHost());
	getModelData(form.getModelName());
	connectToClient();
}

Void app_ui::setConnectionHostandPort(const char* host)
{
	System::String^ setHost = gcnew String(host);

	this->hostnameTextBox->Text = setHost;
	this->disconnectBtn->Text = L"Disconnect";
}

bool app_ui::connectToClient()
{
	printf("inside works");
	this->handler = new Client();
	const char* host = static_cast<const char*>(Marshal::StringToHGlobalAnsi(this->hostnameTextBox->Text).ToPointer());

	if (this->handler->connectToClient(host)) {
		this->disconnectBtn->Text = L"Disconnect";
		printf("still works");
		return true;
	}
	else
		return false;
}

Void app_ui::updateStatusUpdateBox(System::String^ message)
{
	statusUpdateBox->AppendText(message);
	statusUpdateBox->ScrollToCaret();
}

void app_ui::sendCommandClick()
{
	char* userInput = static_cast<char*>(Marshal::StringToHGlobalAnsi(this->commandInput->Text).ToPointer());
	//this->handler->sendData(userInput);

	updateStatusUpdateBox("Sent: " + this->commandInput->Text + "\r\n");

	//char* dataReceived = this->handler->getReturnedData();
	//updateStatusUpdateBox("Received: " + gcnew String(dataReceived) + "\r\n");
}

/* Hard coded just for the Nucleo Board. 
	Since the sizes are different. */
void app_ui::getModelData(char* modelName)
{

	for (auto x : modelMap)
	{
		if (strcmp(x.first, modelName) == 0)
		{
			printf("Found match to: %s\n", modelName);
			modelSizes = x.second;
		}
	}

	this->modelLabel->Text = gcnew String(modelName);

	Dummy::createStaticFakeData(localNucleo);

	for (int i = 0; i < NUCLEO.din; i++)
	{
		printf("Model DIN from fake struct data: %d\n", localNucleo.din[i]);
	}

	for (int i = 0; i < NUCLEO.dout; i++)
	{
		printf("Model DOUT from fake struct data: %d\n", localNucleo.dout[i]);
	}

	for (int i = 0; i < NUCLEO.ain; i++)
	{
		printf("Model AIN from fake struct data: %d\n", localNucleo.ain[i]);
	}

	printf("Model DOUT from fake struct data: %d\n", modelSizes->dout);
	printf("Model DIN from fake struct data: %d\n", modelSizes->din);
	printf("Model AIN from fake struct data: %d\n", modelSizes->ain);
	createBtn(modelSizes->din, DATATYPE::DIN, 0, localNucleo);
	createBtn(modelSizes->dout, DATATYPE::DOUT, 0, localNucleo);
	createBtn(modelSizes->ain, DATATYPE::AIN, 0, localNucleo);
}

/* Recursive function */
void app_ui::createBtn(int decrement, DATATYPE type, int increment, IOS_Data data)
{
	bool intValue = true;
	int innerValue;
	float ainInnerValue;

	if (decrement == 0)
	{
		return;
	}

	System::String ^typeLabel, ^typeButtonName, ^itemNumber;
	itemNumber = System::Convert::ToString(increment);
	int leftShift;
	int ySpacing = (20 * (increment * 2));

	switch (type)
	{
	case DATATYPE::AIN:
		typeLabel = L"Analog Input ";
		typeButtonName = L"ain";
		intValue = false;
		leftShift = 17;
		ainInnerValue = data.ain[increment];
		break;
	case DATATYPE::DIN:
		typeLabel = L"Digital Input ";
		typeButtonName = L"din";
		leftShift = 175;
		innerValue = data.din[increment];
		break;
	case DATATYPE::DOUT:
		typeLabel = L"Digital Output ";
		typeButtonName = L"dout";
		leftShift = 335;
		innerValue = data.dout[increment];
		outData.dout[increment] = innerValue;
		break;
	}

	typeLabel += itemNumber;
	typeButtonName += "_"+itemNumber;

	System::Windows::Forms::Button^  ioButtons = (gcnew System::Windows::Forms::Button());
	System::Windows::Forms::Label^  ioLabels = (gcnew System::Windows::Forms::Label());

	//
	// Label
	// 
	ioLabels->AutoSize = true;
	ioLabels->Location = System::Drawing::Point(leftShift, ySpacing + 5);
	ioLabels->Name = typeLabel->Replace(" ", "");
	ioLabels->TabIndex = 0;
	ioLabels->Text = typeLabel;
	ioLabels->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));

	// 
	// Button
	// 
	ioButtons->Location = System::Drawing::Point(leftShift + (ioLabels->Width * .85), ySpacing);
	ioButtons->Name = typeButtonName;
	ioButtons->Size = System::Drawing::Size(50, 23);
	ioButtons->TabIndex = 1;
	ioButtons->UseVisualStyleBackColor = true;

	if (type == DATATYPE::DIN || type == DATATYPE::DOUT) {
		ioButtons->Text = (innerValue ? L"on" : L"off");
		ioButtons->BackColor = (innerValue ? System::Drawing::Color::Green : System::Drawing::Color::Red);
		ioButtons->ForeColor = System::Drawing::Color::White;
		ioButtons->Click += gcnew System::EventHandler(this, &app_ui::ioButtons_Click);
	}
	else
	{
		ioButtons->Text = ainInnerValue.ToString(CultureInfo::InvariantCulture);
	}

	this->manualPanel->Controls->Add(ioButtons);
	this->manualPanel->Controls->Add(ioLabels);

	createBtn(--decrement, type, ++increment, data);
}

std::string app_ui::convertToStdString(System::String ^str)
{
	msclr::interop::marshal_context context;
	std::string converted = context.marshal_as<std::string>(str);
	return converted;
	//return "";
}

char* app_ui::convertToCharPtr(System::String ^str)
{
	char* converted = static_cast<char*>(Marshal::StringToHGlobalAnsi(str).ToPointer());
	return converted;
}

