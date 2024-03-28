#pragma once

namespace ppois10 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ColorDialog^ colorDialog1;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(620, 22);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"9.1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(726, 22);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"9.2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(620, 70);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"str array";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm1::button3_Click);
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1051, 529);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm1";
			this->Text = L"MyForm1";
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			this->Shown += gcnew System::EventHandler(this, &MyForm1::MyForm1_Shown);
			this->Click += gcnew System::EventHandler(this, &MyForm1::MyForm1_Click);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm1::MyForm1_MouseClick);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: int clickCount = 0;
				bool flag9 = false;
	private: System::Void MyForm1_Click(System::Object^ sender, System::EventArgs^ e) {

		clickCount++;
		if (!flag9) {
			Graphics^ graphics = this->CreateGraphics();

			int width = this->ClientSize.Width;
			int height = this->ClientSize.Height;

			SolidBrush^ brush = gcnew SolidBrush(Color::White);

			graphics->FillRectangle(brush, 0, 0, width, height);

			for each (Control ^ control in this->Controls)
			{
				if (dynamic_cast<Label^>(control) != nullptr)
				{
					this->Controls->Remove(control);
				}
			}

			delete brush;

			String^ text = clickCount.ToString();

			Label^ label = gcnew Label();
			label->Text = text;
			label->Location = System::Drawing::Point(50, 50);
			label->AutoSize = true;

			this->Controls->Add(label);
		}
		
	}
	private: System::Void MyForm1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			int mouseX = e->X;
			int mouseY = e->Y;

			String^ text = mouseX.ToString() + "-" + mouseY.ToString();

			Label^ label = gcnew Label();
			label->Text = text;
			label->Location = System::Drawing::Point(50, 75);
			label->AutoSize = true;

			this->Controls->Add(label);

			String^ text1 = clickCount.ToString();

			Label^ label1 = gcnew Label();
			label1->Text = text1;
			label1->Location = System::Drawing::Point(50, 50);
			label1->AutoSize = true;

			this->Controls->Add(label1);
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		flag9 = true;
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		flag9 = false;
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	array<String^>^ strings = gcnew array<String^> {
			"Use",
			"function prototype",
			"GetTextExtentPoint( )"
	};

	Graphics^ graphics = this->CreateGraphics();
	int x = 100; // начальная координата X
	int y = 50; // начальная координата Y
	int lineHeight = 20; // высота строки

	for each (String ^ str in strings) {
		graphics->DrawString(str, this->Font, Brushes::Black, x, y);
		y += lineHeight; // переход на следующую строку
	}

	delete graphics; // освобождаем ресурсы
}
private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
}
private:
	System::Windows::Forms::Button^ okButton;
	System::Windows::Forms::Button^ cancelButton;
	System::Windows::Forms::Form^ dialogForm;

	void OkButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Действия при нажатии кнопки "OK"
		dialogForm->Close();
	}

	void CancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Действия при нажатии кнопки "Cancel"
		dialogForm->Close();
	}

	System::Void MyForm1_Shown(System::Object^ sender, System::EventArgs^ e) {
		// Создание и настройка немодального диалогового окна
		dialogForm = gcnew Form();
		dialogForm->Text = "Диалоговое окно";

		// Создание кнопок "OK" и "Cancel"
		okButton = gcnew System::Windows::Forms::Button();
		okButton->Text = "OK";
		okButton->Click += gcnew System::EventHandler(this, &MyForm1::OkButton_Click);

		cancelButton = gcnew System::Windows::Forms::Button();
		cancelButton->Text = "Cancel";
		cancelButton->Click += gcnew System::EventHandler(this, &MyForm1::CancelButton_Click);

		// Расположение кнопок на диалоговой форме
		okButton->Location = System::Drawing::Point(20, 20);
		cancelButton->Location = System::Drawing::Point(100, 20);
		dialogForm->Controls->Add(okButton);
		dialogForm->Controls->Add(cancelButton);

		// Отображение диалоговой формы
		dialogForm->Show();

		// Остальной код, который вы хотите выполнить после отображения диалоговой формы
	}
};
}
