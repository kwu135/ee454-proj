`timescale 1 ns / 100 ps

module tb_fullCompress();

reg[63:0] pixels_0;
reg[63:0] pixels_1;
reg[63:0] pixels_2;
reg[63:0] pixels_3;
reg[63:0] pixels_4;
reg[63:0] pixels_5;
reg[63:0] pixels_6;
reg[63:0] pixels_7;

reg Clk;
reg Reset;
wire[63:0] inverseDct_0;
wire[63:0] inverseDct_1;
wire[63:0] inverseDct_2;
wire[63:0] inverseDct_3;
wire[63:0] inverseDct_4;
wire[63:0] inverseDct_5;
wire[63:0] inverseDct_6;
wire[63:0] inverseDct_7;

wire Done;
parameter CLK_PERIOD=2;
always 	#(CLK_PERIOD/2) Clk=~Clk;

initial 
begin
Clk=0;
Reset =0;

pixels_0 = 
8'b10110101 |
8'b10110111 << 8 |
8'b10101100 << 16 |
8'b10100101 << 24 |
8'b10110000 << 32 |
8'b10101100 << 40 |
8'b10100001 << 48 |
8'b10011111 << 56;
pixels_1 = 
8'b10100100 |
8'b10010110 << 8 |
8'b10101000 << 16 |
8'b10100111 << 24 |
8'b10011011 << 32 |
8'b10101001 << 40 |
8'b10101110 << 48 |
8'b10100110 << 56;
pixels_2 = 
8'b10100101 |
8'b10100011 << 8 |
8'b10100110 << 16 |
8'b10011110 << 24 |
8'b10011000 << 32 |
8'b10011011 << 40 |
8'b10100100 << 48 |
8'b10011001 << 56;
pixels_3 = 
8'b10100111 |
8'b10100111 << 8 |
8'b10100011 << 16 |
8'b10011011 << 24 |
8'b10001010 << 32 |
8'b01110010 << 40 |
8'b01111010 << 48 |
8'b10011001 << 56;
pixels_4 = 
8'b10100111 |
8'b10101000 << 8 |
8'b10100101 << 16 |
8'b10100110 << 24 |
8'b10010111 << 32 |
8'b10001110 << 40 |
8'b01111010 << 48 |
8'b00111111 << 56;
pixels_5 = 
8'b10101001 |
8'b10101000 << 8 |
8'b10101101 << 16 |
8'b10101001 << 24 |
8'b10101000 << 32 |
8'b10011011 << 40 |
8'b10011001 << 48 |
8'b10010110 << 56;
pixels_6 = 
8'b10101000 |
8'b10101011 << 8 |
8'b10100011 << 16 |
8'b10011001 << 24 |
8'b10100000 << 32 |
8'b10100011 << 40 |
8'b10100000 << 48 |
8'b10100100 << 56;
pixels_7 = 
8'b10101000 |
8'b10100111 << 8 |
8'b10101100 << 16 |
8'b10101001 << 24 |
8'b10101101 << 32 |
8'b10100100 << 40 |
8'b10100011 << 48 |
8'b10100101 << 56;

#(CLK_PERIOD)
Reset = 1;
#(CLK_PERIOD)
Reset = 0;
#(CLK_PERIOD * 400)
$stop;
end

fullCompress fullcompress(Clk, Reset, Done, pixels_0, pixels_1, pixels_2, pixels_3, pixels_4, pixels_5, pixels_6, pixels_7,
	inverseDct_0, inverseDct_1, inverseDct_2, inverseDct_3, inverseDct_4, inverseDct_5, inverseDct_6, inverseDct_7);

endmodule