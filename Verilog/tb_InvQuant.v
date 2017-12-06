`timescale 1 ns / 100 ps
module tb_InvQuant;
 
reg [95:0] in0; 
reg [95:0] in1; 
reg [95:0] in2; 
reg [95:0] in3; 
reg [95:0] in4; 
reg [95:0] in5; 
reg [95:0] in6; 
reg [95:0] in7; 

reg Clk;

wire [95:0]out0;
wire [95:0]out1;
wire [95:0]out2;
wire [95:0]out3;
wire [95:0]out4;
wire [95:0]out5;
wire [95:0]out6;
wire [95:0]out7;

InvQuant uut(in0, in1, in2, in3, in4, in5, in6, in7, Clk, 
	out0, out1, out2, out3, out4, out5, out6, out7);

initial begin
	Clk=0;
	in0 = 
	(16 & 12'b111111111111 << 0) |
	(5 << 12 & 12'b111111111111 << 12) |
	(-1 << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in1 = 
	(0  & 12'b111111111111 << 0) |
	(-1 << 12 & 12'b111111111111 << 12) |
	(1  << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in2 = 
	(5  & 12'b111111111111 << 0) |
	(-4 << 12 & 12'b111111111111 << 12) |
	(1  << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in3 = 
	(0  & 12'b111111111111 << 0) |
	(1  << 12 & 12'b111111111111 << 12) |
	(-1 << 24 & 12'b111111111111 << 24) |
	(1 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in4 = 
	(-1 & 12'b111111111111 << 0) |
	(2  << 12 & 12'b111111111111 << 12) |
	(0 << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in5 = 
	(0  & 12'b111111111111 << 0) |
	(0  << 12 & 12'b111111111111 << 12) |
	(1  << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in6 = 
	(0  & 12'b111111111111 << 0) |
	(0  << 12 & 12'b111111111111 << 12) |
	(0  << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
	in7 = 
	(0  & 12'b111111111111 << 0) |
	(0  << 12 & 12'b111111111111 << 12) |
	(0  << 24 & 12'b111111111111 << 24) |
	(0 << 36 & 12'b111111111111 << 36) |
	(0 << 48 & 12'b111111111111 << 48) |
	(0 << 60 & 12'b111111111111 << 60) |
	(0 << 72 & 12'b111111111111 << 72) |
	(0 << 84 & 12'b111111111111 << 84);
end

always
		begin
		#10 Clk= ~Clk;
		end

endmodule