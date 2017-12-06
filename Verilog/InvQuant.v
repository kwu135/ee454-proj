module InvQuant(in0, in1, in2, in3, in4, in5, in6, in7, Clk, 
	out0, out1, out2, out3, out4, out5, out6, out7);

	input [95:0] in0; 
	input [95:0] in1; 
	input [95:0] in2; 
	input [95:0] in3; 
	input [95:0] in4; 
	input [95:0] in5; 
	input [95:0] in6; 
	input [95:0] in7; 
	input Clk;
	output [95:0] out0; reg [95:0]out0;
	output [95:0] out1; reg [95:0]out1;
	output [95:0] out2; reg [95:0]out2;
	output [95:0] out3; reg [95:0]out3;
	output [95:0] out4; reg [95:0]out4;
	output [95:0] out5; reg [95:0]out5;
	output [95:0] out6; reg [95:0]out6;
	output [95:0] out7; reg [95:0]out7;
	
	reg j[3:0];
	reg [7:0] Quant [7:0][7:0];
	

	initial begin
	Quant[0][0]<= 16;
	Quant[0][1]<= 11;
	Quant[0][2]<= 10;
	Quant[0][3]<= 16;
	Quant[0][4]<= 24;
	Quant[0][5]<= 40;
	Quant[0][6]<= 51;
	Quant[0][7]<= 61;
	Quant[1][0]<= 12;
	Quant[1][1]<= 12;
	Quant[1][2]<= 14;
	Quant[1][3]<= 19;
	Quant[1][4]<= 26;
	Quant[1][5]<= 58;
	Quant[1][6]<= 60;
	Quant[1][7]<= 55;
	Quant[2][0]<= 14;
	Quant[2][1]<= 13;
	Quant[2][2]<= 16;
	Quant[2][3]<= 24;
	Quant[2][4]<= 40;
	Quant[2][5]<= 57;
	Quant[2][6]<= 69;
	Quant[2][7]<= 56;
	Quant[3][0]<= 14;
	Quant[3][1]<= 17;
	Quant[3][2]<= 22;
	Quant[3][3]<= 29;
	Quant[3][4]<= 51;
	Quant[3][5]<= 87;
	Quant[3][6]<= 80;
	Quant[3][7]<= 62;
	Quant[4][0]<= 18;
	Quant[4][1]<= 22;
	Quant[4][2]<= 37;
	Quant[4][3]<= 56;
	Quant[4][4]<= 68;
	Quant[4][5]<= 109;
	Quant[4][6]<= 103;
	Quant[4][7]<= 77;
	Quant[5][0]<= 24;
	Quant[5][1]<= 35;
	Quant[5][2]<= 55;
	Quant[5][3]<= 64;
	Quant[5][4]<= 81;
	Quant[5][5]<= 104;
	Quant[5][6]<= 113;
	Quant[5][7]<= 92;
	Quant[6][0]<= 49;
	Quant[6][1]<= 64;
	Quant[6][2]<= 78;
	Quant[6][3]<= 87;
	Quant[6][4]<= 103;
	Quant[6][5]<= 121;
	Quant[6][6]<= 120;
	Quant[6][7]<= 101;
	Quant[7][0]<= 72;
	Quant[7][1]<= 92;
	Quant[7][2]<= 95;
	Quant[7][3]<= 98;
	Quant[7][4]<= 112;
	Quant[7][5]<= 100;
	Quant[7][6]<= 103;
	Quant[7][7]<= 99;
	end
	
	
	always @(posedge Clk)
	begin
	out0[95:84] = in0[95:84] * Quant[0][7];
	out0[83:72] = in0[83:72] * Quant[0][6];
	out0[71:60] = in0[71:60] * Quant[0][5];
	out0[59:48] = in0[59:48] * Quant[0][4];
	out0[47:36] = in0[47:36] * Quant[0][3];
	out0[35:24] = in0[35:24] * Quant[0][2];
	out0[23:12] = in0[23:12] * Quant[0][1];
	out0[11:0]  = in0[11:0]  * Quant[0][0];
	
	out1[95:84] = in1[95:84] * Quant[1][7];
	out1[83:72] = in1[83:72] * Quant[1][6];
	out1[71:60] = in1[71:60] * Quant[1][5];
	out1[59:48] = in1[59:48] * Quant[1][4];
	out1[47:36] = in1[47:36] * Quant[1][3];
	out1[35:24] = in1[35:24] * Quant[1][2];
	out1[23:12] = in1[23:12] * Quant[1][1];
	out1[11:0]  = in1[11:0]  * Quant[1][0];

	out2[95:84] = in2[95:84] * Quant[2][7];
	out2[83:72] = in2[83:72] * Quant[2][6];
	out2[71:60] = in2[71:60] * Quant[2][5];
	out2[59:48] = in2[59:48] * Quant[2][4];
	out2[47:36] = in2[47:36] * Quant[2][3];
	out2[35:24] = in2[35:24] * Quant[2][2];
	out2[23:12] = in2[23:12] * Quant[2][1];
	out2[11:0]  = in2[11:0]  * Quant[2][0];

	out3[95:84] = in3[95:84] * Quant[3][7];
	out3[83:72] = in3[83:72] * Quant[3][6];
	out3[71:60] = in3[71:60] * Quant[3][5];
	out3[59:48] = in3[59:48] * Quant[3][4];
	out3[47:36] = in3[47:36] * Quant[3][3];
	out3[35:24] = in3[35:24] * Quant[3][2];
	out3[23:12] = in3[23:12] * Quant[3][1];
	out3[11:0]  = in3[11:0]  * Quant[3][0];
	
	out4[95:84] = in4[95:84] * Quant[4][7];
	out4[83:72] = in4[83:72] * Quant[4][6];
	out4[71:60] = in4[71:60] * Quant[4][5];
	out4[59:48] = in4[59:48] * Quant[4][4];
	out4[47:36] = in4[47:36] * Quant[4][3];
	out4[35:24] = in4[35:24] * Quant[4][2];
	out4[23:12] = in4[23:12] * Quant[4][1];
	out4[11:0]  = in4[11:0]  * Quant[4][0];
	
	out5[95:84] = in5[95:84] * Quant[5][7];
	out5[83:72] = in5[83:72] * Quant[5][6];
	out5[71:60] = in5[71:60] * Quant[5][5];
	out5[59:48] = in5[59:48] * Quant[5][4];
	out5[47:36] = in5[47:36] * Quant[5][3];
	out5[35:24] = in5[35:24] * Quant[5][2];
	out5[23:12] = in5[23:12] * Quant[5][1];
	out5[11:0]  = in5[11:0]  * Quant[5][0];
	
	out6[95:84] = in6[95:84] * Quant[6][7];
	out6[83:72] = in6[83:72] * Quant[6][6];
	out6[71:60] = in6[71:60] * Quant[6][5];
	out6[59:48] = in6[59:48] * Quant[6][4];
	out6[47:36] = in6[47:36] * Quant[6][3];
	out6[35:24] = in6[35:24] * Quant[6][2];
	out6[23:12] = in6[23:12] * Quant[6][1];
	out6[11:0]  = in6[11:0]  * Quant[6][0];
	
	out7[95:84] = in7[95:84] * Quant[7][7];
	out7[83:72] = in7[83:72] * Quant[7][6];
	out7[71:60] = in7[71:60] * Quant[7][5];
	out7[59:48] = in7[59:48] * Quant[7][4];
	out7[47:36] = in7[47:36] * Quant[7][3];
	out7[35:24] = in7[35:24] * Quant[7][2];
	out7[23:12] = in7[23:12] * Quant[7][1];
	out7[11:0]  = in7[11:0]  * Quant[7][0];
	end
	
endmodule