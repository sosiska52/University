#pragma once

namespace ppois1213 {

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
            //
            //TODO: �������� ��� ������������
            //
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
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

        // ���������� ������� Paint ��� ��������� ������
        void MyForm_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 12);
            SolidBrush^ brush = gcnew SolidBrush(Color::Black);

            int lineHeight = font->Height;
            int x = 0;
            int y = 0;

            for (int i = 1; i <= 5; i++)
            {
                String^ text = i.ToString() + " ������";
                g->DrawString(text, font, brush, x, y);
                x += (int)g->MeasureString(text, font).Width;
                y += lineHeight;
            }
        }

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
            this->ClientSize = System::Drawing::Size(668, 527);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);

        }
#pragma endregion
    };
}