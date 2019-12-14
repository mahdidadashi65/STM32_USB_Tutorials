namespace PCSerialController
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btnOpen = new System.Windows.Forms.Button();
            this.txtPortName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.btnReadKeys = new System.Windows.Forms.Button();
            this.txtResponse = new System.Windows.Forms.TextBox();
            this.cBoxLED1 = new System.Windows.Forms.CheckBox();
            this.cBoxLED2 = new System.Windows.Forms.CheckBox();
            this.cBoxLED3 = new System.Windows.Forms.CheckBox();
            this.cBoxLED4 = new System.Windows.Forms.CheckBox();
            this.cBoxSW1 = new System.Windows.Forms.CheckBox();
            this.cBoxSW2 = new System.Windows.Forms.CheckBox();
            this.cBoxSW3 = new System.Windows.Forms.CheckBox();
            this.cBoxSW4 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(15, 60);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(101, 23);
            this.btnOpen.TabIndex = 0;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // txtPortName
            // 
            this.txtPortName.Location = new System.Drawing.Point(47, 23);
            this.txtPortName.Name = "txtPortName";
            this.txtPortName.Size = new System.Drawing.Size(69, 20);
            this.txtPortName.TabIndex = 1;
            this.txtPortName.Text = "COM16";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Port:";
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // btnReadKeys
            // 
            this.btnReadKeys.Location = new System.Drawing.Point(15, 101);
            this.btnReadKeys.Name = "btnReadKeys";
            this.btnReadKeys.Size = new System.Drawing.Size(101, 23);
            this.btnReadKeys.TabIndex = 3;
            this.btnReadKeys.Text = "Read Keys";
            this.btnReadKeys.UseVisualStyleBackColor = true;
            this.btnReadKeys.Click += new System.EventHandler(this.btnReadKeys_Click);
            // 
            // txtResponse
            // 
            this.txtResponse.Location = new System.Drawing.Point(167, 19);
            this.txtResponse.Multiline = true;
            this.txtResponse.Name = "txtResponse";
            this.txtResponse.Size = new System.Drawing.Size(276, 230);
            this.txtResponse.TabIndex = 4;
            this.txtResponse.DoubleClick += new System.EventHandler(this.txtResponse_DoubleClick);
            // 
            // cBoxLED1
            // 
            this.cBoxLED1.AutoSize = true;
            this.cBoxLED1.Location = new System.Drawing.Point(15, 150);
            this.cBoxLED1.Name = "cBoxLED1";
            this.cBoxLED1.Size = new System.Drawing.Size(53, 17);
            this.cBoxLED1.TabIndex = 5;
            this.cBoxLED1.Text = "LED1";
            this.cBoxLED1.UseVisualStyleBackColor = true;
            this.cBoxLED1.CheckedChanged += new System.EventHandler(this.cBoxLED1_CheckedChanged);
            // 
            // cBoxLED2
            // 
            this.cBoxLED2.AutoSize = true;
            this.cBoxLED2.Location = new System.Drawing.Point(15, 173);
            this.cBoxLED2.Name = "cBoxLED2";
            this.cBoxLED2.Size = new System.Drawing.Size(53, 17);
            this.cBoxLED2.TabIndex = 6;
            this.cBoxLED2.Text = "LED2";
            this.cBoxLED2.UseVisualStyleBackColor = true;
            this.cBoxLED2.CheckedChanged += new System.EventHandler(this.cBoxLED2_CheckedChanged);
            // 
            // cBoxLED3
            // 
            this.cBoxLED3.AutoSize = true;
            this.cBoxLED3.Location = new System.Drawing.Point(15, 196);
            this.cBoxLED3.Name = "cBoxLED3";
            this.cBoxLED3.Size = new System.Drawing.Size(53, 17);
            this.cBoxLED3.TabIndex = 7;
            this.cBoxLED3.Text = "LED3";
            this.cBoxLED3.UseVisualStyleBackColor = true;
            this.cBoxLED3.CheckedChanged += new System.EventHandler(this.cBoxLED3_CheckedChanged);
            // 
            // cBoxLED4
            // 
            this.cBoxLED4.AutoSize = true;
            this.cBoxLED4.Location = new System.Drawing.Point(15, 219);
            this.cBoxLED4.Name = "cBoxLED4";
            this.cBoxLED4.Size = new System.Drawing.Size(53, 17);
            this.cBoxLED4.TabIndex = 8;
            this.cBoxLED4.Text = "LED4";
            this.cBoxLED4.UseVisualStyleBackColor = true;
            this.cBoxLED4.CheckedChanged += new System.EventHandler(this.cBoxLED4_CheckedChanged);
            // 
            // cBoxSW1
            // 
            this.cBoxSW1.AutoSize = true;
            this.cBoxSW1.Location = new System.Drawing.Point(88, 150);
            this.cBoxSW1.Name = "cBoxSW1";
            this.cBoxSW1.Size = new System.Drawing.Size(50, 17);
            this.cBoxSW1.TabIndex = 9;
            this.cBoxSW1.Text = "SW1";
            this.cBoxSW1.UseVisualStyleBackColor = true;
            // 
            // cBoxSW2
            // 
            this.cBoxSW2.AutoSize = true;
            this.cBoxSW2.Location = new System.Drawing.Point(88, 173);
            this.cBoxSW2.Name = "cBoxSW2";
            this.cBoxSW2.Size = new System.Drawing.Size(50, 17);
            this.cBoxSW2.TabIndex = 10;
            this.cBoxSW2.Text = "SW2";
            this.cBoxSW2.UseVisualStyleBackColor = true;
            // 
            // cBoxSW3
            // 
            this.cBoxSW3.AutoSize = true;
            this.cBoxSW3.Location = new System.Drawing.Point(88, 196);
            this.cBoxSW3.Name = "cBoxSW3";
            this.cBoxSW3.Size = new System.Drawing.Size(50, 17);
            this.cBoxSW3.TabIndex = 11;
            this.cBoxSW3.Text = "SW2";
            this.cBoxSW3.UseVisualStyleBackColor = true;
            // 
            // cBoxSW4
            // 
            this.cBoxSW4.AutoSize = true;
            this.cBoxSW4.Location = new System.Drawing.Point(88, 219);
            this.cBoxSW4.Name = "cBoxSW4";
            this.cBoxSW4.Size = new System.Drawing.Size(50, 17);
            this.cBoxSW4.TabIndex = 12;
            this.cBoxSW4.Text = "SW4";
            this.cBoxSW4.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 261);
            this.Controls.Add(this.cBoxSW4);
            this.Controls.Add(this.cBoxSW3);
            this.Controls.Add(this.cBoxSW2);
            this.Controls.Add(this.cBoxSW1);
            this.Controls.Add(this.cBoxLED4);
            this.Controls.Add(this.cBoxLED3);
            this.Controls.Add(this.cBoxLED2);
            this.Controls.Add(this.cBoxLED1);
            this.Controls.Add(this.txtResponse);
            this.Controls.Add(this.btnReadKeys);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtPortName);
            this.Controls.Add(this.btnOpen);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.TextBox txtPortName;
        private System.Windows.Forms.Label label1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button btnReadKeys;
        private System.Windows.Forms.TextBox txtResponse;
        private System.Windows.Forms.CheckBox cBoxLED1;
        private System.Windows.Forms.CheckBox cBoxLED2;
        private System.Windows.Forms.CheckBox cBoxLED3;
        private System.Windows.Forms.CheckBox cBoxLED4;
        private System.Windows.Forms.CheckBox cBoxSW1;
        private System.Windows.Forms.CheckBox cBoxSW2;
        private System.Windows.Forms.CheckBox cBoxSW3;
        private System.Windows.Forms.CheckBox cBoxSW4;
    }
}

