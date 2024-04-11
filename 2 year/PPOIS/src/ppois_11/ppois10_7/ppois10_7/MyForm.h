#pragma once

namespace ppois107 {

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
    private: System::Windows::Forms::ListBox^ listBox1;
    protected:
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Label^ label1;

    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {

            fioList = gcnew System::Collections::Generic::List<System::String^>();

            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // listBox1
            // 
            this->listBox1->FormattingEnabled = true;
            this->listBox1->ItemHeight = 16;
            this->listBox1->Location = System::Drawing::Point(12, 12);
            this->listBox1->Name = L"listBox1";
            this->listBox1->Size = System::Drawing::Size(123, 420);
            this->listBox1->TabIndex = 0;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(164, 113);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(98, 23);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Добавить";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(166, 169);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(96, 23);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Удалить";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(166, 198);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(96, 23);
            this->button3->TabIndex = 3;
            this->button3->Text = L"Изменить";
            this->button3->UseVisualStyleBackColor = true;
            //this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
            // 
            // button4
            // 
            this->button4->Location = System::Drawing::Point(164, 409);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(108, 23);
            this->button4->TabIndex = 4;
            this->button4->Text = L"Выход";
            this->button4->UseVisualStyleBackColor = true;
            this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(164, 78);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(100, 22);
            this->textBox1->TabIndex = 5;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(161, 41);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(103, 17);
            this->label1->TabIndex = 6;
            this->label1->Text = L"Введите ФИО";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(284, 450);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->listBox1);
            this->Name = L"MyForm";
            this->Text = L"Form1";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        System::Collections::Generic::List<System::String^>^ fioList;

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        System::String^ fio = textBox1->Text;

        listBox1->Items->Add(fio);
        fioList->Add(fio);

        textBox1->Text = ""; // Очистка поля ввода
    }
    private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
        Application::Exit();
    }

           private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
               // Проверка, выбран ли элемент в ListBox
               if (listBox1->SelectedItem != nullptr) {
                   // Получение выбранного элемента
                   System::String^ selectedFio = listBox1->SelectedItem->ToString();

                   // Удаление элемента из ListBox
                   listBox1->Items->Remove(selectedFio);

                   // Удаление элемента из вектора
                   fioList->Remove(selectedFio);
               }
           }

           private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
                      // Проверка, выбран ли элемент в ListBox
                      if (listBox1->SelectedItem != nullptr) {
                          // Получение выбранного элемента
                          System::String^ selectedFio = listBox1->SelectedItem->ToString();

                          // Отображение выбранного элемента в TextBox
                          textBox1->Text = selectedFio;

                          // Удаление элемента из ListBox
                          listBox1->Items->Remove(selectedFio);

                          // Удаление элемента из вектора
                          fioList->Remove(selectedFio);
                      }
                  }

        private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e)
        {
            fioList->Add("Макаревич");
            fioList->Add("Цыбульский");
            fioList->Add("Ерш");
            // Заполняем ListBox элементами из fioList
            for each (System::String ^ fio in fioList)
            {
                listBox1->Items->Add(fio);
            }
        }
    };
}