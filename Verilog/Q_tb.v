module Q_tb_v;

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

Quant uut(in0, in1, in2, in3, in4, in5, in6, in7, Clk, 
	out0, out1, out2, out3, out4, out5, out6, out7);

initial begin
	Clk=0;
in0 = 
(254 << 0  & 12'b111111111111 << 0) |
(59 << 12 & 12'b111111111111 << 12) |
(-10 << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(-4 << 48 & 12'b111111111111 << 48) |
(4 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(5 << 84 & 12'b111111111111 << 84);
in1 = 
(4 << 0 & 12'b111111111111 << 0) |
(-6 << 12 & 12'b111111111111 << 12) |
(8  << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(-1 << 48 & 12'b111111111111 << 48) |
(6 << 60 & 12'b111111111111 << 60) |
(2 << 72 & 12'b111111111111 << 72) |
(-2 << 84 & 12'b111111111111 << 84);
in2 = 
(65 << 0 & 12'b111111111111 << 0) |
(-50 << 12 & 12'b111111111111 << 12) |
(13  << 24 & 12'b111111111111 << 24) |
(6 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(-8 << 60 & 12'b111111111111 << 60) |
(6 << 72 & 12'b111111111111 << 72) |
(1 << 84 & 12'b111111111111 << 84);
in3 = 
(5 << 0 & 12'b111111111111 << 0) |
(23  << 12 & 12'b111111111111 << 12) |
(-20 << 24 & 12'b111111111111 << 24) |
(19 << 36 & 12'b111111111111 << 36) |
(-7 << 48 & 12'b111111111111 << 48) |
(-2 << 60 & 12'b111111111111 << 60) |
(-2 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
in4 = 
(-20 << 0 & 12'b111111111111 << 0) |
(41  << 12 & 12'b111111111111 << 12) |
(-14 << 24 & 12'b111111111111 << 24) |
(2 << 36 & 12'b111111111111 << 36) |
(4 << 48 & 12'b111111111111 << 48) |
(-6 << 60 & 12'b111111111111 << 60) |
(-5 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
in5 = 
(4  << 0 & 12'b111111111111 << 0) |
(-4  << 12 & 12'b111111111111 << 12) |
(31  << 24 & 12'b111111111111 << 24) |
(-15 << 36 & 12'b111111111111 << 36) |
(11 << 48 & 12'b111111111111 << 48) |
(-21 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
in6 = 
(20  << 0 & 12'b111111111111 << 0) |
(-2  << 12 & 12'b111111111111 << 12) |
(-2  << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(1 << 48 & 12'b111111111111 << 48) |
(-4 << 60 & 12'b111111111111 << 60) |
(-2 << 72 & 12'b111111111111 << 72) |
(4 << 84 & 12'b111111111111 << 84);
in7 = 
(-10 << 0 & 12'b111111111111 << 0) |
(19  << 12 & 12'b111111111111 << 12) |
(-19  << 24 & 12'b111111111111 << 24) |
(27 << 36 & 12'b111111111111 << 36) |
(-21 << 48 & 12'b111111111111 << 48) |
(6 << 60 & 12'b111111111111 << 60) |
(-6 << 72 & 12'b111111111111 << 72) |
(-1 << 84 & 12'b111111111111 << 84);
end

always
		begin
		#10 Clk= ~Clk;
		end

endmodule
