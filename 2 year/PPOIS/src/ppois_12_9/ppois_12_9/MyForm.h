#pragma once

#include <vector> // ��������� ������������ ���� ��� ������������� std::vector

namespace ppois129 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			points = gcnew System::Collections::Generic::List<Point>(); // �������������� ������ �����
			mouseClicked = false; // ���� ��� �����������, ���� �� ������ ����� ������� ����
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void OnMouseDown(MouseEventArgs^ e) override
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				Point clickPoint(e->X, e->Y);
				points->Add(clickPoint); // ��������� ���������� ����� � ������
				mouseClicked = true; // ������������� ����, ��� ����� ������� ���� ���� ������
			}
			else if (e->Button == System::Windows::Forms::MouseButtons::Right)
			{
				if (mouseClicked)
				{
					Graphics^ g = this->CreateGraphics();
					Pen^ pen = gcnew Pen(Color::Black);
					for (int i = 0; i < points->Count - 1; i++)
					{
						g->DrawLine(pen, points[i], points[i + 1]); // ��������� �������� ����� ������� �������
					}
					mouseClicked = false; // ���������� ���� ����� ��������� �����������
				}
			}
		}

	private:
		System::ComponentModel::Container^ components;
		System::Collections::Generic::List<Point>^ points; // ������ ��� �������� ��������� �����
		bool mouseClicked; // ���� ��� �����������, ���� �� ������ ����� ������� ����

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300, 300);
			this->Text = L"MyForm";
			this->Padding = System::Windows::Forms::Padding(0); this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
		}
#pragma endregion
	private:
		void MyForm::MyForm_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			// ��� ��� ��� ��������� ������� MouseDown
		}
	};
}