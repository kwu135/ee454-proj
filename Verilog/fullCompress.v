module fullCompress(Clk, Reset, Done, pixels_0, pixels_1, pixels_2, pixels_3, pixels_4, pixels_5, pixels_6, pixels_7,
	inverseDct_0, inverseDct_1, inverseDct_2, inverseDct_3, inverseDct_4, inverseDct_5, inverseDct_6, inverseDct_7);

input Clk;
input Reset;
input Done;

input[63:0] pixels_0;
input[63:0] pixels_1;
input[63:0] pixels_2;
input[63:0] pixels_3;
input[63:0] pixels_4;
input[63:0] pixels_5;
input[63:0] pixels_6;
input[63:0] pixels_7;

reg ResetDCT;
wire DoneDCT;
wire[95:0] dct_0;
wire[95:0] dct_1;
wire[95:0] dct_2;
wire[95:0] dct_3;
wire[95:0] dct_4;
wire[95:0] dct_5;
wire[95:0] dct_6;
wire[95:0] dct_7;

reg[95:0] temp_0;
reg[95:0] temp_1;
reg[95:0] temp_2;
reg[95:0] temp_3;
reg[95:0] temp_4;
reg[95:0] temp_5;
reg[95:0] temp_6;
reg[95:0] temp_7;

wire[95:0] quant_0;
wire[95:0] quant_1;
wire[95:0] quant_2;
wire[95:0] quant_3;
wire[95:0] quant_4;
wire[95:0] quant_5;
wire[95:0] quant_6;
wire[95:0] quant_7;

wire[95:0] invQuant_0;
wire[95:0] invQuant_1;
wire[95:0] invQuant_2;
wire[95:0] invQuant_3;
wire[95:0] invQuant_4;
wire[95:0] invQuant_5;
wire[95:0] invQuant_6;
wire[95:0] invQuant_7;

reg ResetInvDCT;
wire DoneInvDCT;
output[63:0] inverseDct_0;
output[63:0] inverseDct_1;
output[63:0] inverseDct_2;
output[63:0] inverseDct_3;
output[63:0] inverseDct_4;
output[63:0] inverseDct_5;
output[63:0] inverseDct_6;
output[63:0] inverseDct_7;

reg [6:0] state;

generateDCT dct(pixels_0, pixels_1, pixels_2, pixels_3, pixels_4,
	pixels_5, pixels_6, pixels_7, Clk, ResetDCT, dct_0, dct_1, dct_2, dct_3,
	dct_4, dct_5, dct_6, dct_7, DoneDCT);
Quant quant(temp_0,temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7, Clk,
	quant_0, quant_1, quant_2, quant_3, quant_4, quant_5, quant_6, quant_7);
InvQuant invQuant(quant_0, quant_1, quant_2, quant_3, quant_4, quant_5, quant_6, quant_7, Clk, 
invQuant_0, invQuant_1, invQuant_2, invQuant_3, invQuant_4, invQuant_5, invQuant_6, invQuant_7);
inverseDCT invdct(Clk, ResetInvDCT, DoneInvDCT, 
	invQuant_0, invQuant_1, invQuant_2, invQuant_3, invQuant_4, invQuant_5, invQuant_6, invQuant_7, 
	inverseDct_0, inverseDct_1, inverseDct_2, inverseDct_3, inverseDct_4, inverseDct_5, inverseDct_6, inverseDct_7);

localparam 
DCT	=		5'b00001, 
QUANT = 	5'b00010, 
INVQUANT = 	5'b00100, 
INVDCT= 	5'b01000, 
DONE 	= 	5'b10000;

assign Done = (state == DONE);

always @(posedge Clk, posedge Reset)
begin
	if (Reset)
	begin
		state <= DCT;
		ResetDCT <= 1;
		ResetInvDCT <= 0;
	end
	else
	begin
		case(state)
			DCT:
			begin
				ResetDCT <= 0;
				if(DoneDCT)
				begin
					state <= QUANT;
					temp_0 <= dct_0;
					temp_1 <= dct_1;
					temp_2 <= dct_2;
					temp_3 <= dct_3;
					temp_4 <= dct_4;
					temp_5 <= dct_5;
					temp_6 <= dct_6;
					temp_7 <= dct_7;
				end
			end
			QUANT:
			begin
				state <= INVQUANT;
			end
			INVQUANT:
			begin
				state <= INVDCT;
				ResetInvDCT <= 1;
			end
			INVDCT:
			begin
				ResetInvDCT <= 0;
				if(DoneInvDCT)
				begin
					state <= DONE;
				end
			end
			DONE:
			begin

			end

		endcase // state
	end
end
endmodule