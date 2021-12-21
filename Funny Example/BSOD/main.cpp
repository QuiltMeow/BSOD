#include "MainForm.h"
#include "BSOD.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace BSOD;

using namespace System::Diagnostics;
using namespace System::IO;
using namespace System::Text;

public ref class Util {
private:
protected:
	static String^ tempPath;
public:
	static const int COUNT_DOWN = 5;
	static const int WAIT_EXIT_TIME = 5000;

	static Util() {
		char buffer[MAX_PATH];
		GetTempPathA(MAX_PATH, buffer);
		tempPath = gcnew String(buffer);
	}

	static void VBSMessageBox(String^ name, String^ icon, String^ title, String^ message) {
		Process^ vbs = gcnew Process();
		String^ fileName = Path::Combine(tempPath, name + ".vbs");
		String^ Message = "MsgBox \"" + message + "\", " + icon + ", \"" + title + "\"";

		StreamWriter^ sw;
		try {
			sw = gcnew StreamWriter(fileName, false, Encoding::GetEncoding(950));
			sw->Write(Message);

			vbs->StartInfo->FileName = fileName;
			vbs->Start();
		}
		catch (...) {
		}
		finally {
			if (sw != nullptr) {
				try {
					sw->Close();
				}
				catch (...) {
				}
			}
		}
	}

	static void killTask(String^ processName) {
		Process^ kill = gcnew Process();
		kill->StartInfo = gcnew ProcessStartInfo();
		kill->StartInfo->FileName = "taskkill";
		kill->StartInfo->CreateNoWindow = true;
		kill->StartInfo->WindowStyle = ProcessWindowStyle::Hidden;
		kill->StartInfo->Arguments = "/F /IM \"" + processName + "\"";

		try {
			kill->Start();
			kill->WaitForExit(WAIT_EXIT_TIME);
		}
		catch (...) {
		}
	}
};

[STAThreadAttribute]
void Main(array<String^>^ args) {
	if (args->Length > 0) {
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		MainForm form;
		Application::Run(% form);
	}
	else {
		String^ warningIcon = "48";
		for (int count = Util::COUNT_DOWN; count > 0; --count) {
			Util::killTask("wscript.exe");
			String^ now = count.ToString();
			Util::VBSMessageBox(now, warningIcon, "­Ë¼Æ", now);
			Sleep(1000);
		}
		triggerBSOD();
	}
}