namespace AgoraClrDemo
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnJoinChannel = new System.Windows.Forms.Button();
            this.txtVendorkey = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtResult = new System.Windows.Forms.TextBox();
            this.lblResult = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtChannelName = new System.Windows.Forms.TextBox();
            this.localVideo = new System.Windows.Forms.PictureBox();
            this.btnStartPreview = new System.Windows.Forms.Button();
            this.remoteVideo = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.localVideo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.remoteVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // btnJoinChannel
            // 
            this.btnJoinChannel.Location = new System.Drawing.Point(93, 434);
            this.btnJoinChannel.Name = "btnJoinChannel";
            this.btnJoinChannel.Size = new System.Drawing.Size(75, 23);
            this.btnJoinChannel.TabIndex = 0;
            this.btnJoinChannel.Text = "加入频道";
            this.btnJoinChannel.UseVisualStyleBackColor = true;
            this.btnJoinChannel.Click += new System.EventHandler(this.btnJoinChannel_Click);
            // 
            // txtVendorkey
            // 
            this.txtVendorkey.Location = new System.Drawing.Point(106, 35);
            this.txtVendorkey.Name = "txtVendorkey";
            this.txtVendorkey.Size = new System.Drawing.Size(331, 21);
            this.txtVendorkey.TabIndex = 2;
            this.txtVendorkey.Text = "3d09433bedce4d68b50d444772728d0d";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "Vendor Key:";
            // 
            // txtResult
            // 
            this.txtResult.Location = new System.Drawing.Point(106, 96);
            this.txtResult.Multiline = true;
            this.txtResult.Name = "txtResult";
            this.txtResult.Size = new System.Drawing.Size(331, 93);
            this.txtResult.TabIndex = 5;
            this.txtResult.TextChanged += new System.EventHandler(this.txtResult_TextChanged);
            // 
            // lblResult
            // 
            this.lblResult.AutoSize = true;
            this.lblResult.Location = new System.Drawing.Point(10, 96);
            this.lblResult.Name = "lblResult";
            this.lblResult.Size = new System.Drawing.Size(53, 12);
            this.lblResult.TabIndex = 6;
            this.lblResult.Text = "调用结果";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "Channel Name :";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // txtChannelName
            // 
            this.txtChannelName.Location = new System.Drawing.Point(106, 62);
            this.txtChannelName.Name = "txtChannelName";
            this.txtChannelName.Size = new System.Drawing.Size(331, 21);
            this.txtChannelName.TabIndex = 7;
            this.txtChannelName.Text = "666";
            this.txtChannelName.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // localVideo
            // 
            this.localVideo.Location = new System.Drawing.Point(12, 230);
            this.localVideo.Name = "localVideo";
            this.localVideo.Size = new System.Drawing.Size(231, 168);
            this.localVideo.TabIndex = 9;
            this.localVideo.TabStop = false;
            // 
            // btnStartPreview
            // 
            this.btnStartPreview.Location = new System.Drawing.Point(12, 434);
            this.btnStartPreview.Name = "btnStartPreview";
            this.btnStartPreview.Size = new System.Drawing.Size(75, 23);
            this.btnStartPreview.TabIndex = 10;
            this.btnStartPreview.Text = "打开本地视频";
            this.btnStartPreview.UseVisualStyleBackColor = true;
            this.btnStartPreview.Click += new System.EventHandler(this.btnStartPreview_Click);
            // 
            // remoteVideo
            // 
            this.remoteVideo.Location = new System.Drawing.Point(258, 230);
            this.remoteVideo.Name = "remoteVideo";
            this.remoteVideo.Size = new System.Drawing.Size(231, 168);
            this.remoteVideo.TabIndex = 11;
            this.remoteVideo.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(520, 479);
            this.Controls.Add(this.remoteVideo);
            this.Controls.Add(this.btnStartPreview);
            this.Controls.Add(this.localVideo);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtChannelName);
            this.Controls.Add(this.lblResult);
            this.Controls.Add(this.txtResult);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtVendorkey);
            this.Controls.Add(this.btnJoinChannel);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.localVideo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.remoteVideo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnJoinChannel;
        private System.Windows.Forms.TextBox txtVendorkey;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtResult;
        private System.Windows.Forms.Label lblResult;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtChannelName;
        private System.Windows.Forms.PictureBox localVideo;
        private System.Windows.Forms.Button btnStartPreview;
        private System.Windows.Forms.PictureBox remoteVideo;
    }
}

