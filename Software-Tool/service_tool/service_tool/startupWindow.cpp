#include "startupWindow.h"
#include <msclr/marshal.h>

using namespace servicetool;
using namespace System::Runtime::InteropServices;

char* startupWindow::getModelName() 
{
	return (char*)(void*)Marshal::StringToHGlobalAnsi(this->modelSelectionBox->GetItemText(this->modelSelectionBox->SelectedItem));
}

const char* startupWindow::getHost()
{
	return this->host;
}

void startupWindow::connectBtnClick()
{
	const char* setHost = static_cast<const char*>(Marshal::StringToHGlobalAnsi(this->hostInputBox->Text).ToPointer());

	this->host = setHost;

	this->Close();
}
