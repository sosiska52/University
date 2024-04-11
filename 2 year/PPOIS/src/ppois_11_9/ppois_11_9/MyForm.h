#pragma once

namespace ppois119 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: äîáàâüòå êîä êîíñòğóêòîğà
			//
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ğåñóğñû.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ âÂÎÄToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ âÛÂÎÄToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåğåìåííàÿ êîíñòğóêòîğà.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òğåáóåìûé ìåòîä äëÿ ïîääåğæêè êîíñòğóêòîğà — íå èçìåíÿéòå 
		/// ñîäåğæèìîå ıòîãî ìåòîäà ñ ïîìîùüş ğåäàêòîğà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			listBox1 = gcnew System::Windows::Forms::ListBox();
			listBox1->Dock = System::Windows::Forms::DockStyle::Fill;

			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->âÂÎÄToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âÛÂÎÄToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->âÂÎÄToolStripMenuItem,
					this->âÛÂÎÄToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(282, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MyForm::menuStrip1_ItemClicked);
			// 
			// âÂÎÄToolStripMenuItem
			// 
			this->âÂÎÄToolStripMenuItem->Name = L"âÂÎÄToolStripMenuItem";
			this->âÂÎÄToolStripMenuItem->Size = System::Drawing::Size(62, 24);
			this->âÂÎÄToolStripMenuItem->Text = L"ÂÂÎÄ";
			this->âÂÎÄToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::âÂÎÄToolStripMenuItem_Click);
			// 
			// âÛÂÎÄToolStripMenuItem
			// 
			this->âÛÂÎÄToolStripMenuItem->Name = L"âÛÂÎÄToolStripMenuItem";
			this->âÛÂÎÄToolStripMenuItem->Size = System::Drawing::Size(74, 24);
			this->âÛÂÎÄToolStripMenuItem->Text = L"ÂÛÂÎÄ";
			this->âÛÂÎÄToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::âÛÂÎÄToolStripMenuItem_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::contextMenuStrip1_Opening);
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
	private: System::Void contextMenuStrip1_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
private: System::Void âÂÎÄToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Form^ inputForm = gcnew Form();
	inputForm->Text = "Ââîä ñòğîêè";

	TextBox^ textBox = gcnew TextBox();
	textBox->Dock = DockStyle::Top;

	Button^ addButton = gcnew Button();
	addButton->Text = "ÄÎÁÀÂÈÒÜ";
	addButton->Dock = DockStyle::Top;
	addButton->Click += gcnew System::EventHandler(this, &MyForm::AddButton_Click);

	inputForm->Controls->Add(addButton);
	inputForm->Controls->Add(textBox);

	inputForm->ShowDialog();
}

private:
	System::Windows::Forms::ListBox^ listBox1;
private: System::Void AddButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Button^ addButton = dynamic_cast<Button^>(sender);
	if (addButton != nullptr) {
		Form^ parentForm = dynamic_cast<Form^>(addButton->Parent);
		if (parentForm != nullptr) {
			TextBox^ textBox = dynamic_cast<TextBox^>(parentForm->Controls[1]);
			if (textBox != nullptr) {
				String^ inputText = textBox->Text;
				listBox1->Items->Add(inputText);
				parentForm->Close();
			}
		}
	}
}
private: System::Void âÛÂÎÄToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Form^ listBoxForm = gcnew Form();
	listBoxForm->Text = "ListBox Form";

	ListBox^ listBox = gcnew ListBox();
	listBox->Dock = DockStyle::Fill;

	// Êîïèğîâàíèå ıëåìåíòîâ èç listBox1 â listBox
	for each (Object ^ item in listBox1->Items)
	{
		listBox->Items->Add(item);
	}

	listBoxForm->Controls->Add(listBox);

	listBoxForm->ShowDialog();
}
};
}
