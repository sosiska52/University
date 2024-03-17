#pragma once

namespace ppois9 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	protected:
	private: System::ComponentModel::IContainer^ components;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(744, 70);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Clean";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(744, 41);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Draw";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(744, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Numbers";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(831, 497);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Click += gcnew System::EventHandler(this, &MyForm::MyForm_Click);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		int windowHeight = this->ClientSize.Height; // Высота клиентской области окна
		int numberCount = 10; // Количество чисел для вывода

		int step = windowHeight / numberCount; // Шаг между числами
		int y = 0; // Текущая позиция по вертикали

		for (int i = 1; i <= numberCount; i++)
		{
			int number = i;
			int square = number * number;

			String^ text = number.ToString() + " - " + square.ToString();

			Label^ label = gcnew Label();
			label->Text = text;
			label->Location = System::Drawing::Point(10, y);
			label->AutoSize = true;

			this->Controls->Add(label);

			y += step;
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		// Создаем объект Graphics для рисования на форме
		Graphics^ graphics = this->CreateGraphics();

		// Устанавливаем красный цвет пера и заливку
		Pen^ pen = gcnew Pen(Color::Red);
		SolidBrush^ brush = gcnew SolidBrush(Color::Red);

		// Получаем размеры клиентской области формы
		int width = this->ClientSize.Width;
		int height = this->ClientSize.Height;

		// Вычисляем размеры и положение круга
		int circleSize = Math::Min(width, height) / 4; // Размер круга равен четверти минимальной стороны формы
		int circleX = (width - circleSize) / 2; // Горизонтальная позиция круга
		int circleY = (height - circleSize) / 2; // Вертикальная позиция круга

		// Рисуем и заполняем круг на форме
		graphics->DrawEllipse(pen, circleX, circleY, circleSize, circleSize);
		graphics->FillEllipse(brush, circleX, circleY, circleSize, circleSize);

		// Освобождаем ресурсы
		delete pen;
		delete brush;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		// Создаем объект Graphics для рисования на форме
		Graphics^ graphics = this->CreateGraphics();

		// Получаем размеры клиентской области формы
		int width = this->ClientSize.Width;
		int height = this->ClientSize.Height;

		// Создаем белую заливку
		SolidBrush^ brush = gcnew SolidBrush(Color::White);

		// Заполняем всю клиентскую область формы белым цветом
		graphics->FillRectangle(brush, 0, 0, width, height);

		// Удаляем все Label на форме
		for each (Control ^ control in this->Controls)
		{
			if (dynamic_cast<Label^>(control) != nullptr)
			{
				this->Controls->Remove(control);
			}
		}

		// Освобождаем ресурсы
		delete brush;
	}

		   private:
			   int clickCount = 0;

	private: System::Void MyForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			// Увеличиваем счетчик нажатий
			//clickCount++;

			// Получаем координаты мыши
			int mouseX = e->X;
			int mouseY = e->Y;

			// Формируем сообщение с координатами мыши и количеством нажатий
			String^ message = "Координаты мыши: X = " + mouseX + ", Y = " + mouseY + "\n"
				+ "Количество нажатий: " + clickCount;

			String^ text = mouseX.ToString() + "-" + mouseY.ToString();

			Label^ label = gcnew Label();
			label->Text = text;
			label->Location = System::Drawing::Point(100, 100);
			label->AutoSize = true;

			this->Controls->Add(label);

			// Выводим сообщение
			MessageBox::Show(message);

			String^ text1 = clickCount.ToString();

			Label^ label1 = gcnew Label();
			label1->Text = text1;
			label1->Location = System::Drawing::Point(50, 50);
			label1->AutoSize = true;

			this->Controls->Add(label1);
		}
	}

private: System::Void MyForm_Click(System::Object^ sender, System::EventArgs^ e) {
	// Создаем объект Graphics для рисования на форме
	Graphics^ graphics = this->CreateGraphics();

	// Получаем размеры клиентской области формы
	int width = this->ClientSize.Width;
	int height = this->ClientSize.Height;

	// Создаем белую заливку
	SolidBrush^ brush = gcnew SolidBrush(Color::White);

	// Заполняем всю клиентскую область формы белым цветом
	graphics->FillRectangle(brush, 0, 0, width, height);

	// Удаляем все Label на форме
	for each (Control ^ control in this->Controls)
	{
		if (dynamic_cast<Label^>(control) != nullptr)
		{
			this->Controls->Remove(control);
		}
	}

	// Освобождаем ресурсы
	delete brush;

	clickCount++;

	String^ text = clickCount.ToString();

	Label^ label = gcnew Label();
	label->Text = text;
	label->Location = System::Drawing::Point(50, 50);
	label->AutoSize = true;

	this->Controls->Add(label);
}
};
}
