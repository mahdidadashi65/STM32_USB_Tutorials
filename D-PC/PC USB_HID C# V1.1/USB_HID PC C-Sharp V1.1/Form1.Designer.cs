namespace USB_HID_PC_C_Sharp_V1._1
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
            this.btnOpen = new System.Windows.Forms.Button();
            this.txtResp = new System.Windows.Forms.TextBox();
            this.ckReceiveData = new System.Windows.Forms.CheckBox();
            this.ckLED1 = new System.Windows.Forms.CheckBox();
            this.ckLED2 = new System.Windows.Forms.CheckBox();
            this.ckLED3 = new System.Windows.Forms.CheckBox();
            this.ckSW1 = new System.Windows.Forms.CheckBox();
            this.ckSW2 = new System.Windows.Forms.CheckBox();
            this.ckSW3 = new System.Windows.Forms.CheckBox();
            this.ckSW4 = new System.Windows.Forms.CheckBox();
            this.tBarServo = new System.Windows.Forms.TrackBar();
            this.txtU8Val = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtU16Val = new System.Windows.Forms.TextBox();
            this.txtU32Val = new System.Windows.Forms.TextBox();
            this.txtfloatVal = new System.Windows.Forms.TextBox();
            this.txtfloatValOut = new System.Windows.Forms.TextBox();
            this.txtU32ValOut = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.tBarServo)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOpen
            // 
            this.btnOpen.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.btnOpen.Location = new System.Drawing.Point(12, 12);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(260, 47);
            this.btnOpen.TabIndex = 0;
            this.btnOpen.Text = "Open Connection";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // txtResp
            // 
            this.txtResp.Location = new System.Drawing.Point(12, 158);
            this.txtResp.Multiline = true;
            this.txtResp.Name = "txtResp";
            this.txtResp.Size = new System.Drawing.Size(260, 91);
            this.txtResp.TabIndex = 1;
            // 
            // ckReceiveData
            // 
            this.ckReceiveData.AutoSize = true;
            this.ckReceiveData.Location = new System.Drawing.Point(12, 135);
            this.ckReceiveData.Name = "ckReceiveData";
            this.ckReceiveData.Size = new System.Drawing.Size(89, 17);
            this.ckReceiveData.TabIndex = 4;
            this.ckReceiveData.Text = "ReceiveData";
            this.ckReceiveData.UseVisualStyleBackColor = true;
            this.ckReceiveData.CheckedChanged += new System.EventHandler(this.ckReceiveData_CheckedChanged);
            // 
            // ckLED1
            // 
            this.ckLED1.AutoSize = true;
            this.ckLED1.Location = new System.Drawing.Point(283, 18);
            this.ckLED1.Name = "ckLED1";
            this.ckLED1.Size = new System.Drawing.Size(53, 17);
            this.ckLED1.TabIndex = 5;
            this.ckLED1.Text = "LED1";
            this.ckLED1.UseVisualStyleBackColor = true;
            this.ckLED1.CheckedChanged += new System.EventHandler(this.ckLED1_CheckedChanged);
            // 
            // ckLED2
            // 
            this.ckLED2.AutoSize = true;
            this.ckLED2.Location = new System.Drawing.Point(355, 18);
            this.ckLED2.Name = "ckLED2";
            this.ckLED2.Size = new System.Drawing.Size(53, 17);
            this.ckLED2.TabIndex = 6;
            this.ckLED2.Text = "LED2";
            this.ckLED2.UseVisualStyleBackColor = true;
            this.ckLED2.CheckedChanged += new System.EventHandler(this.ckLED2_CheckedChanged);
            // 
            // ckLED3
            // 
            this.ckLED3.AutoSize = true;
            this.ckLED3.Location = new System.Drawing.Point(431, 18);
            this.ckLED3.Name = "ckLED3";
            this.ckLED3.Size = new System.Drawing.Size(53, 17);
            this.ckLED3.TabIndex = 7;
            this.ckLED3.Text = "LED3";
            this.ckLED3.UseVisualStyleBackColor = true;
            this.ckLED3.CheckedChanged += new System.EventHandler(this.ckLED3_CheckedChanged);
            // 
            // ckSW1
            // 
            this.ckSW1.AutoSize = true;
            this.ckSW1.Location = new System.Drawing.Point(534, 18);
            this.ckSW1.Name = "ckSW1";
            this.ckSW1.Size = new System.Drawing.Size(50, 17);
            this.ckSW1.TabIndex = 8;
            this.ckSW1.Text = "SW1";
            this.ckSW1.UseVisualStyleBackColor = true;
            // 
            // ckSW2
            // 
            this.ckSW2.AutoSize = true;
            this.ckSW2.Location = new System.Drawing.Point(590, 18);
            this.ckSW2.Name = "ckSW2";
            this.ckSW2.Size = new System.Drawing.Size(50, 17);
            this.ckSW2.TabIndex = 9;
            this.ckSW2.Text = "SW2";
            this.ckSW2.UseVisualStyleBackColor = true;
            // 
            // ckSW3
            // 
            this.ckSW3.AutoSize = true;
            this.ckSW3.Location = new System.Drawing.Point(646, 18);
            this.ckSW3.Name = "ckSW3";
            this.ckSW3.Size = new System.Drawing.Size(50, 17);
            this.ckSW3.TabIndex = 10;
            this.ckSW3.Text = "SW3";
            this.ckSW3.UseVisualStyleBackColor = true;
            // 
            // ckSW4
            // 
            this.ckSW4.AutoSize = true;
            this.ckSW4.Location = new System.Drawing.Point(702, 18);
            this.ckSW4.Name = "ckSW4";
            this.ckSW4.Size = new System.Drawing.Size(50, 17);
            this.ckSW4.TabIndex = 11;
            this.ckSW4.Text = "SW4";
            this.ckSW4.UseVisualStyleBackColor = true;
            // 
            // tBarServo
            // 
            this.tBarServo.Location = new System.Drawing.Point(283, 55);
            this.tBarServo.Maximum = 255;
            this.tBarServo.Name = "tBarServo";
            this.tBarServo.Size = new System.Drawing.Size(201, 45);
            this.tBarServo.TabIndex = 12;
            this.tBarServo.Scroll += new System.EventHandler(this.tBarServo_Scroll);
            // 
            // txtU8Val
            // 
            this.txtU8Val.Location = new System.Drawing.Point(628, 55);
            this.txtU8Val.Name = "txtU8Val";
            this.txtU8Val.Size = new System.Drawing.Size(100, 20);
            this.txtU8Val.TabIndex = 13;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label1.Location = new System.Drawing.Point(531, 58);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 16);
            this.label1.TabIndex = 14;
            this.label1.Text = "uint8_t Val:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label2.Location = new System.Drawing.Point(531, 85);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 16);
            this.label2.TabIndex = 15;
            this.label2.Text = "uint16_t Val:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label3.Location = new System.Drawing.Point(531, 112);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 16);
            this.label3.TabIndex = 16;
            this.label3.Text = "uint32_t Val:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label4.Location = new System.Drawing.Point(531, 139);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 16);
            this.label4.TabIndex = 17;
            this.label4.Text = "float Val:";
            // 
            // txtU16Val
            // 
            this.txtU16Val.Location = new System.Drawing.Point(628, 83);
            this.txtU16Val.Name = "txtU16Val";
            this.txtU16Val.Size = new System.Drawing.Size(100, 20);
            this.txtU16Val.TabIndex = 18;
            // 
            // txtU32Val
            // 
            this.txtU32Val.Location = new System.Drawing.Point(628, 111);
            this.txtU32Val.Name = "txtU32Val";
            this.txtU32Val.Size = new System.Drawing.Size(100, 20);
            this.txtU32Val.TabIndex = 19;
            // 
            // txtfloatVal
            // 
            this.txtfloatVal.Location = new System.Drawing.Point(628, 139);
            this.txtfloatVal.Name = "txtfloatVal";
            this.txtfloatVal.Size = new System.Drawing.Size(100, 20);
            this.txtfloatVal.TabIndex = 20;
            // 
            // txtfloatValOut
            // 
            this.txtfloatValOut.Location = new System.Drawing.Point(392, 134);
            this.txtfloatValOut.Name = "txtfloatValOut";
            this.txtfloatValOut.Size = new System.Drawing.Size(100, 20);
            this.txtfloatValOut.TabIndex = 24;
            // 
            // txtU32ValOut
            // 
            this.txtU32ValOut.Location = new System.Drawing.Point(392, 106);
            this.txtU32ValOut.Name = "txtU32ValOut";
            this.txtU32ValOut.Size = new System.Drawing.Size(100, 20);
            this.txtU32ValOut.TabIndex = 23;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label5.Location = new System.Drawing.Point(295, 134);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(69, 16);
            this.label5.TabIndex = 22;
            this.label5.Text = "float Val:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label6.Location = new System.Drawing.Point(295, 107);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(55, 16);
            this.label6.TabIndex = 21;
            this.label6.Text = "int Val:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(298, 172);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(194, 33);
            this.button1.TabIndex = 25;
            this.button1.Text = "Send Data";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(787, 261);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtfloatValOut);
            this.Controls.Add(this.txtU32ValOut);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtfloatVal);
            this.Controls.Add(this.txtU32Val);
            this.Controls.Add(this.txtU16Val);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtU8Val);
            this.Controls.Add(this.tBarServo);
            this.Controls.Add(this.ckSW4);
            this.Controls.Add(this.ckSW3);
            this.Controls.Add(this.ckSW2);
            this.Controls.Add(this.ckSW1);
            this.Controls.Add(this.ckLED3);
            this.Controls.Add(this.ckLED2);
            this.Controls.Add(this.ckLED1);
            this.Controls.Add(this.ckReceiveData);
            this.Controls.Add(this.txtResp);
            this.Controls.Add(this.btnOpen);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.tBarServo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.TextBox txtResp;
        private System.Windows.Forms.CheckBox ckReceiveData;
        private System.Windows.Forms.CheckBox ckLED1;
        private System.Windows.Forms.CheckBox ckLED2;
        private System.Windows.Forms.CheckBox ckLED3;
        private System.Windows.Forms.CheckBox ckSW1;
        private System.Windows.Forms.CheckBox ckSW2;
        private System.Windows.Forms.CheckBox ckSW3;
        private System.Windows.Forms.CheckBox ckSW4;
        private System.Windows.Forms.TrackBar tBarServo;
        private System.Windows.Forms.TextBox txtU8Val;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtU16Val;
        private System.Windows.Forms.TextBox txtU32Val;
        private System.Windows.Forms.TextBox txtfloatVal;
        private System.Windows.Forms.TextBox txtfloatValOut;
        private System.Windows.Forms.TextBox txtU32ValOut;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button1;
    }
}

