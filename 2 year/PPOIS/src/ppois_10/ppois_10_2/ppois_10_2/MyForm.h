#pragma once

namespace ppois102 {

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
            InitializeComponent();
            //
            //TODO: �������� ��� ������������
            //

            // �������� � ��������� ��������� ����������
            label1 = gcnew System::Windows::Forms::Label();
            label1->Text = "������� ��������:";
            label1->Location = System::Drawing::Point(10, 10);

            textBox1 = gcnew System::Windows::Forms::TextBox();
            textBox1->Location = System::Drawing::Point(10, 30);


            label2 = gcnew System::Windows::Forms::Label();
            label2->Text = "������� ��������:";
            label2->Location = System::Drawing::Point(10, 60);

            textBox2 = gcnew System::Windows::Forms::TextBox();
            textBox2->Location = System::Drawing::Point(10, 90);

            button = gcnew System::Windows::Forms::Button();
            button->Text = "������";
            button->Location = System::Drawing::Point(150, 10);
            button->Click += gcnew System::EventHandler(this, &MyForm::Button_Click);

            // ���������� ��������� ���������� �� �����
            this->Controls->Add(label1);
            this->Controls->Add(label2);
            this->Controls->Add(textBox1);
            this->Controls->Add(textBox2);
            this->Controls->Add(button);
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
        System::ComponentModel::Container^ components;

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
            this->ClientSize = System::Drawing::Size(813, 539);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);

        }
#pragma endregion
    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::TextBox^ textBox1;
        System::Windows::Forms::TextBox^ textBox2;
        System::Windows::Forms::Button^ button;

        void Button_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // ��������� ���������� �������� �� ���������� ����
            String^ input1 = textBox1->Text;
            String^ input2 = textBox2->Text;

            // ���-����� ���������� ��������
            MessageBox::Show("�� �����: " + input1 + " " + input2, "���-�����");
        }
    };
}