#pragma once

namespace ppois127 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			labelKey = nullptr;
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Click += gcnew System::EventHandler(this, &MyForm::MyForm_Click);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void MyForm_Click(System::Object^ sender, System::EventArgs^ e) {
		MouseEventArgs^ mouseEvent = dynamic_cast<MouseEventArgs^>(e);
		if (mouseEvent != nullptr && mouseEvent->Button == System::Windows::Forms::MouseButtons::Left) {
			int mouseX = mouseEvent->X;
			int mouseY = mouseEvent->Y;

			// �������������� ���������� ���� � ������
			String^ coordinates = String::Format("X: {0}, Y: {1}", mouseX, mouseY);

			// ����������� ��������� �� �����
			Label^ coordinatesLabel = gcnew Label();
			coordinatesLabel->Text = coordinates;
			coordinatesLabel->Location = Point(mouseX, mouseY);
			this->Controls->Add(coordinatesLabel);
		}
	}

	private:
		System::Windows::Forms::Label^ labelKey;
	private: System::Void MyForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		// ��������� ������� �������
		char keyPressed = static_cast<char>(e->KeyChar);

		// �������� ��� ���������� Label ��� ����������� ������� �������
		if (labelKey == nullptr) {
			labelKey = gcnew Label();
			labelKey->Location = Point(10, 10); // ������� �������� ���������� Label � ����� ������� ���� ����
			this->Controls->Add(labelKey);
		}
		labelKey->Text = "Pressed Key: " + System::Char::ToString(keyPressed);
	}
	};
}
