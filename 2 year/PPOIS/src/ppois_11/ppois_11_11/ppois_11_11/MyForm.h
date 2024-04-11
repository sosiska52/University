#pragma once

namespace ppois1111 {

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
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ workToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ enterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->workToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->workToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(282, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// workToolStripMenuItem
			// 
			this->workToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->enterToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->workToolStripMenuItem->Name = L"workToolStripMenuItem";
			this->workToolStripMenuItem->Size = System::Drawing::Size(55, 24);
			this->workToolStripMenuItem->Text = L"work";
			// 
			// enterToolStripMenuItem
			// 
			this->enterToolStripMenuItem->Name = L"enterToolStripMenuItem";
			this->enterToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->enterToolStripMenuItem->Text = L"enter";
			this->enterToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::enterToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->exitToolStripMenuItem->Text = L"exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(52, 24);
			this->helpToolStripMenuItem->Text = L"help";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
private: System::Void enterToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Form^ inputForm = gcnew Form();
	inputForm->Text = "Ввод числа";

	TextBox^ textBox = gcnew TextBox();
	textBox->Dock = DockStyle::Top;

	Button^ okButton = gcnew Button();
	okButton->Text = "ОК";
	okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
	okButton->Dock = DockStyle::Top;

	Button^ cancelButton = gcnew Button();
	cancelButton->Text = "Cancel";
	cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	cancelButton->Dock = DockStyle::Top;

	inputForm->Controls->Add(cancelButton);
	inputForm->Controls->Add(okButton);
	inputForm->Controls->Add(textBox);

	if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		double number;
		if (Double::TryParse(textBox->Text, number)) {
			double square = number * number;
			MessageBox::Show("Квадрат числа: " + square.ToString());
		}
		else {
			MessageBox::Show("Некорректный формат числа!");
		}
	}
}
};
}
