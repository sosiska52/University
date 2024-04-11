#pragma once

namespace ppois11 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm2
	/// </summary>
	public ref class MyForm2 : public System::Windows::Forms::Form
	{
	public:
		MyForm2(void)
		{
			InitializeComponent();
			this->Text = L"Диалоговое окно"; // Изменяем текст заголовка окна на "Диалоговое окно"
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:

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
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(94, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm2::button1_Click);
			// 
			// MyForm2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(272, 77);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm2";
			this->Text = L"MyForm2";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		// Создание и настройка нового окна
		System::Windows::Forms::Form^ newForm = gcnew System::Windows::Forms::Form();
		newForm->Text = L"Окно с клиентской областью";
		newForm->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

		// Подписка на событие клика левой кнопки мыши
		newForm->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm2::NewForm_MouseClick);

		// Показ нового окна
		newForm->Show();
	}

	System::Void NewForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		   {
			   // Проверка, что была нажата левая кнопка мыши
			   if (e->Button == System::Windows::Forms::MouseButtons::Left)
			   {
				   // Вывод информационного сообщения о событии
				   MessageBox::Show("Нажата левая кнопка мыши!");

				   // Закрытие приложения
				   Application::Exit();
			   }
		   }
	};
}
