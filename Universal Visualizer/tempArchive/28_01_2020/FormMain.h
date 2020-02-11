#pragma once

#include "Form1.h"
#include "OpenGL funcs.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace UniversalVisualizer {

	/// <summary>
	/// ������ ��� Form_Process
	///
	/// ��������! ��� ��������� ����� ����� ������ ���������� ����� ��������
	///          �������� ����� ����� �������� ("Resource File Name") ��� �������� ���������� ������������ �������,
	///          ���������� �� ����� ������� � ����������� .resx, �� ������� ������� ������ �����. � ��������� ������,
	///          ������������ �� ������ ��������� �������� � ���������������
	///          ���������, ��������������� ������ �����.
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/// <summary>
		/// ��������� ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ������������ ����� ��� ��������� ������������ - �� ���������
		/// ���������� ������� ������ ��� ������ ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(442, 245);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximizeBox = false;
			this->Name = L"FormMain";
			this->Text = L"������";
			this->Activated += gcnew System::EventHandler(this, &FormMain::FormMain_Activated);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FormMain_Activated(System::Object^  sender, System::EventArgs^  e) {
		UniversalVisualizer::Form1^ f = gcnew UniversalVisualizer::Form1(this);
		this->Hide();
		f->Show();
		int argc = 1;
		char** argv = new char*[1];
		argv[0] = new char[1];
		argv[0][0] = 0;
		init_OpenGL(argc, argv);
	}
	};
}

