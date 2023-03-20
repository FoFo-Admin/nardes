#include "MyForm.h"
#include "gamelogic.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	srand(time(NULL));

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Nardes::MyForm form;
	Application::Run(% form);
}
