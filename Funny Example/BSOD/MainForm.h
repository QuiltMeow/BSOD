#pragma once

#include "BSOD.h"

namespace BSOD {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm() {
			InitializeComponent();
			click = false;
		}
	protected:
		bool click;

		~MainForm() {
			if (components) {
				delete components;
			}
		}
	private:
		System::Windows::Forms::Button^ btnTrigger;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent()
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->btnTrigger = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			//
			// btnTrigger
			//
			this->btnTrigger->Location = System::Drawing::Point(15, 20);
			this->btnTrigger->Name = L"btnTrigger";
			this->btnTrigger->Size = System::Drawing::Size(150, 23);
			this->btnTrigger->TabIndex = 0;
			this->btnTrigger->Text = L"喵 點我點我 :3 ~";
			this->btnTrigger->UseVisualStyleBackColor = true;
			this->btnTrigger->Click += gcnew System::EventHandler(this, &MainForm::btnTrigger_Click);
			//
			// MainForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(184, 61);
			this->Controls->Add(this->btnTrigger);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"喵嗚";
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void btnTrigger_Click(System::Object^ sender, System::EventArgs^ e) {
			if (click) {
				return;
			}
			click = true;
			btnTrigger->Text = "祝您好運 ><";
			Application::DoEvents();
			triggerBSOD();
		}
	};
}