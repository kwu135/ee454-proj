`timescale 1 ns / 100 ps

module tb_inverseDCT();

reg[95:0] pixels_0;
reg[95:0] pixels_1;
reg[95:0] pixels_2;
reg[95:0] pixels_3;
reg[95:0] pixels_4;
reg[95:0] pixels_5;
reg[95:0] pixels_6;
reg[95:0] pixels_7;

reg Clk;
reg Reset;
wire[63:0] dct_0;
wire[63:0] dct_1;
wire[63:0] dct_2;
wire[63:0] dct_3;
wire[63:0] dct_4;
wire[63:0] dct_5;
wire[63:0] dct_6;
wire[63:0] dct_7;

wire Done;
parameter CLK_PERIOD=2;
always 	#(CLK_PERIOD/2) Clk=~Clk;

initial 
begin
Clk=0;
Reset =0;

pixels_0 = 
(255 & 12'b111111111111 << 0) |
(60 << 12 & 12'b111111111111 << 12) |
(-7 << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(0 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_1 = 
(5  & 12'b111111111111 << 0) |
(-7 << 12 & 12'b111111111111 << 12) |
(9  << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(0 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_2 = 
(63  & 12'b111111111111 << 0) |
(-54 << 12 & 12'b111111111111 << 12) |
(11  << 24 & 12'b111111111111 << 24) |
(13 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(-17 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_3 = 
(9  & 12'b111111111111 << 0) |
(22  << 12 & 12'b111111111111 << 12) |
(-26 << 24 & 12'b111111111111 << 24) |
(15 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(0 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_4 = 
(-22 & 12'b111111111111 << 0) |
(39  << 12 & 12'b111111111111 << 12) |
(-15 << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(0 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_5 = 
(0  & 12'b111111111111 << 0) |
(0  << 12 & 12'b111111111111 << 12) |
(34  << 24 & 12'b111111111111 << 24) |
(-19 << 36 & 12'b111111111111 << 36) |
(21 << 48 & 12'b111111111111 << 48) |
(-23 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_6 = 
(15  & 12'b111111111111 << 0) |
(0  << 12 & 12'b111111111111 << 12) |
(0  << 24 & 12'b111111111111 << 24) |
(0 << 36 & 12'b111111111111 << 36) |
(0 << 48 & 12'b111111111111 << 48) |
(0 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);
pixels_7 = 
(-17  & 12'b111111111111 << 0) |
(19  << 12 & 12'b111111111111 << 12) |
(-21  << 24 & 12'b111111111111 << 24) |
(23 << 36 & 12'b111111111111 << 36) |
(-25 << 48 & 12'b111111111111 << 48) |
(0 << 60 & 12'b111111111111 << 60) |
(0 << 72 & 12'b111111111111 << 72) |
(0 << 84 & 12'b111111111111 << 84);

#(CLK_PERIOD)
Reset = 1;
#(CLK_PERIOD)
Reset = 0;
#(CLK_PERIOD * 8*8*8*8*2+100)
$stop;
end

inverseDCT dct(Clk, Reset, Done, pixels_0, pixels_1, pixels_2, pixels_3, pixels_4,
	pixels_5, pixels_6, pixels_7, dct_0, dct_1, dct_2, dct_3,
	dct_4, dct_5, dct_6, dct_7);
endmodule