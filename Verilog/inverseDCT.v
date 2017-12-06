module inverseDCT(Clk, Reset, Done,
	dct_0, dct_1, dct_2, dct_3, dct_4, dct_5, dct_6, dct_7, 
	inverseDct_0, inverseDct_1, inverseDct_2, inverseDct_3, inverseDct_4, inverseDct_5, inverseDct_6, inverseDct_7);

input Clk;
input Reset;
input Done;

reg[3:0] x;
reg[3:0] y;
reg[3:0] i;
reg[3:0] j;

input [95:0] dct_0;
input [95:0] dct_1;
input [95:0] dct_2;
input [95:0] dct_3;
input [95:0] dct_4;
input [95:0] dct_5;
input [95:0] dct_6;
input [95:0] dct_7;

output[63:0] inverseDct_0;
output[63:0] inverseDct_1;
output[63:0] inverseDct_2;
output[63:0] inverseDct_3;
output[63:0] inverseDct_4;
output[63:0] inverseDct_5;
output[63:0] inverseDct_6;
output[63:0] inverseDct_7;

reg signed [11:0] dct_reg[7:0][7:0];
reg [7:0] invdct_reg[7:0][7:0];

reg signed [63:0] cosine[7:0][7:0];
reg signed [63:0] coeff[7:0][7:0];

reg signed [63:0] temp[7:0][7:0];

reg [6:0] state;

localparam 
START	=	5'b00001, 
ROWCALC = 	5'b00010, 
COLSD 	= 	5'b00100, 
COLCALC = 	5'b01000, 
DONE 	= 	5'b10000;

	assign Done = (state == DONE);

assign inverseDct_0[0*8+:8] = invdct_reg[0][0];
assign inverseDct_0[1*8+:8] = invdct_reg[0][1];
assign inverseDct_0[2*8+:8] = invdct_reg[0][2];
assign inverseDct_0[3*8+:8] = invdct_reg[0][3];
assign inverseDct_0[4*8+:8] = invdct_reg[0][4];
assign inverseDct_0[5*8+:8] = invdct_reg[0][5];
assign inverseDct_0[6*8+:8] = invdct_reg[0][6];
assign inverseDct_0[7*8+:8] = invdct_reg[0][7];
assign inverseDct_1[0*8+:8] = invdct_reg[1][0];
assign inverseDct_1[1*8+:8] = invdct_reg[1][1];
assign inverseDct_1[2*8+:8] = invdct_reg[1][2];
assign inverseDct_1[3*8+:8] = invdct_reg[1][3];
assign inverseDct_1[4*8+:8] = invdct_reg[1][4];
assign inverseDct_1[5*8+:8] = invdct_reg[1][5];
assign inverseDct_1[6*8+:8] = invdct_reg[1][6];
assign inverseDct_1[7*8+:8] = invdct_reg[1][7];
assign inverseDct_2[0*8+:8] = invdct_reg[2][0];
assign inverseDct_2[1*8+:8] = invdct_reg[2][1];
assign inverseDct_2[2*8+:8] = invdct_reg[2][2];
assign inverseDct_2[3*8+:8] = invdct_reg[2][3];
assign inverseDct_2[4*8+:8] = invdct_reg[2][4];
assign inverseDct_2[5*8+:8] = invdct_reg[2][5];
assign inverseDct_2[6*8+:8] = invdct_reg[2][6];
assign inverseDct_2[7*8+:8] = invdct_reg[2][7];
assign inverseDct_3[0*8+:8] = invdct_reg[3][0];
assign inverseDct_3[1*8+:8] = invdct_reg[3][1];
assign inverseDct_3[2*8+:8] = invdct_reg[3][2];
assign inverseDct_3[3*8+:8] = invdct_reg[3][3];
assign inverseDct_3[4*8+:8] = invdct_reg[3][4];
assign inverseDct_3[5*8+:8] = invdct_reg[3][5];
assign inverseDct_3[6*8+:8] = invdct_reg[3][6];
assign inverseDct_3[7*8+:8] = invdct_reg[3][7];
assign inverseDct_4[0*8+:8] = invdct_reg[4][0];
assign inverseDct_4[1*8+:8] = invdct_reg[4][1];
assign inverseDct_4[2*8+:8] = invdct_reg[4][2];
assign inverseDct_4[3*8+:8] = invdct_reg[4][3];
assign inverseDct_4[4*8+:8] = invdct_reg[4][4];
assign inverseDct_4[5*8+:8] = invdct_reg[4][5];
assign inverseDct_4[6*8+:8] = invdct_reg[4][6];
assign inverseDct_4[7*8+:8] = invdct_reg[4][7];
assign inverseDct_5[0*8+:8] = invdct_reg[5][0];
assign inverseDct_5[1*8+:8] = invdct_reg[5][1];
assign inverseDct_5[2*8+:8] = invdct_reg[5][2];
assign inverseDct_5[3*8+:8] = invdct_reg[5][3];
assign inverseDct_5[4*8+:8] = invdct_reg[5][4];
assign inverseDct_5[5*8+:8] = invdct_reg[5][5];
assign inverseDct_5[6*8+:8] = invdct_reg[5][6];
assign inverseDct_5[7*8+:8] = invdct_reg[5][7];
assign inverseDct_6[0*8+:8] = invdct_reg[6][0];
assign inverseDct_6[1*8+:8] = invdct_reg[6][1];
assign inverseDct_6[2*8+:8] = invdct_reg[6][2];
assign inverseDct_6[3*8+:8] = invdct_reg[6][3];
assign inverseDct_6[4*8+:8] = invdct_reg[6][4];
assign inverseDct_6[5*8+:8] = invdct_reg[6][5];
assign inverseDct_6[6*8+:8] = invdct_reg[6][6];
assign inverseDct_6[7*8+:8] = invdct_reg[6][7];
assign inverseDct_7[0*8+:8] = invdct_reg[7][0];
assign inverseDct_7[1*8+:8] = invdct_reg[7][1];
assign inverseDct_7[2*8+:8] = invdct_reg[7][2];
assign inverseDct_7[3*8+:8] = invdct_reg[7][3];
assign inverseDct_7[4*8+:8] = invdct_reg[7][4];
assign inverseDct_7[5*8+:8] = invdct_reg[7][5];
assign inverseDct_7[6*8+:8] = invdct_reg[7][6];
assign inverseDct_7[7*8+:8] = invdct_reg[7][7];


initial
begin
	cosine[0][0] = 1024;
	cosine[0][1] = 1004;
	cosine[0][2] = 946;
	cosine[0][3] = 851;
	cosine[0][4] = 724;
	cosine[0][5] = 568;
	cosine[0][6] = 391;
	cosine[0][7] = 199;
	cosine[1][0] = 1024;
	cosine[1][1] = 851;
	cosine[1][2] = 391;
	cosine[1][3] = -199;
	cosine[1][4] = -724;
	cosine[1][5] = -1004;
	cosine[1][6] = -946;
	cosine[1][7] = -568;
	cosine[2][0] = 1024;
	cosine[2][1] = 568;
	cosine[2][2] = -391;
	cosine[2][3] = -1004;
	cosine[2][4] = -724;
	cosine[2][5] = 199;
	cosine[2][6] = 946;
	cosine[2][7] = 851;
	cosine[3][0] = 1024;
	cosine[3][1] = 199;
	cosine[3][2] = -946;
	cosine[3][3] = -568;
	cosine[3][4] = 724;
	cosine[3][5] = 851;
	cosine[3][6] = -391;
	cosine[3][7] = -1004;
	cosine[4][0] = 1024;
	cosine[4][1] = -199;
	cosine[4][2] = -946;
	cosine[4][3] = 568;
	cosine[4][4] = 724;
	cosine[4][5] = -851;
	cosine[4][6] = -391;
	cosine[4][7] = 1004;
	cosine[5][0] = 1024;
	cosine[5][1] = -568;
	cosine[5][2] = -391;
	cosine[5][3] = 1004;
	cosine[5][4] = -724;
	cosine[5][5] = -199;
	cosine[5][6] = 946;
	cosine[5][7] = -851;
	cosine[6][0] = 1024;
	cosine[6][1] = -851;
	cosine[6][2] = 391;
	cosine[6][3] = 199;
	cosine[6][4] = -724;
	cosine[6][5] = 1004;
	cosine[6][6] = -946;
	cosine[6][7] = 568;
	cosine[7][0] = 1024;
	cosine[7][1] = -1004;
	cosine[7][2] = 946;
	cosine[7][3] = -851;
	cosine[7][4] = 724;
	cosine[7][5] = -568;
	cosine[7][6] = 391;
	cosine[7][7] = -199;

	coeff[0][0] = 511;
coeff[0][1] = 724;
coeff[0][2] = 724;
coeff[0][3] = 724;
coeff[0][4] = 724;
coeff[0][5] = 724;
coeff[0][6] = 724;
coeff[0][7] = 724;
coeff[1][0] = 724;
coeff[1][1] = 1024;
coeff[1][2] = 1024;
coeff[1][3] = 1024;
coeff[1][4] = 1024;
coeff[1][5] = 1024;
coeff[1][6] = 1024;
coeff[1][7] = 1024;
coeff[2][0] = 724;
coeff[2][1] = 1024;
coeff[2][2] = 1024;
coeff[2][3] = 1024;
coeff[2][4] = 1024;
coeff[2][5] = 1024;
coeff[2][6] = 1024;
coeff[2][7] = 1024;
coeff[3][0] = 724;
coeff[3][1] = 1024;
coeff[3][2] = 1024;
coeff[3][3] = 1024;
coeff[3][4] = 1024;
coeff[3][5] = 1024;
coeff[3][6] = 1024;
coeff[3][7] = 1024;
coeff[4][0] = 724;
coeff[4][1] = 1024;
coeff[4][2] = 1024;
coeff[4][3] = 1024;
coeff[4][4] = 1024;
coeff[4][5] = 1024;
coeff[4][6] = 1024;
coeff[4][7] = 1024;
coeff[5][0] = 724;
coeff[5][1] = 1024;
coeff[5][2] = 1024;
coeff[5][3] = 1024;
coeff[5][4] = 1024;
coeff[5][5] = 1024;
coeff[5][6] = 1024;
coeff[5][7] = 1024;
coeff[6][0] = 724;
coeff[6][1] = 1024;
coeff[6][2] = 1024;
coeff[6][3] = 1024;
coeff[6][4] = 1024;
coeff[6][5] = 1024;
coeff[6][6] = 1024;
coeff[6][7] = 1024;
coeff[7][0] = 724;
coeff[7][1] = 1024;
coeff[7][2] = 1024;
coeff[7][3] = 1024;
coeff[7][4] = 1024;
coeff[7][5] = 1024;
coeff[7][6] = 1024;
coeff[7][7] = 1024;
end

always @(posedge Clk, posedge Reset)
begin
	if (Reset)
	begin
		dct_reg[0][0] <= dct_0[0*12+:12];
		dct_reg[0][1] <= dct_0[1*12+:12];
		dct_reg[0][2] <= dct_0[2*12+:12];
		dct_reg[0][3] <= dct_0[3*12+:12];
		dct_reg[0][4] <= dct_0[4*12+:12];
		dct_reg[0][5] <= dct_0[5*12+:12];
		dct_reg[0][6] <= dct_0[6*12+:12];
		dct_reg[0][7] <= dct_0[7*12+:12];
		dct_reg[1][0] <= dct_1[0*12+:12];
		dct_reg[1][1] <= dct_1[1*12+:12];
		dct_reg[1][2] <= dct_1[2*12+:12];
		dct_reg[1][3] <= dct_1[3*12+:12];
		dct_reg[1][4] <= dct_1[4*12+:12];
		dct_reg[1][5] <= dct_1[5*12+:12];
		dct_reg[1][6] <= dct_1[6*12+:12];
		dct_reg[1][7] <= dct_1[7*12+:12];
		dct_reg[2][0] <= dct_2[0*12+:12];
		dct_reg[2][1] <= dct_2[1*12+:12];
		dct_reg[2][2] <= dct_2[2*12+:12];
		dct_reg[2][3] <= dct_2[3*12+:12];
		dct_reg[2][4] <= dct_2[4*12+:12];
		dct_reg[2][5] <= dct_2[5*12+:12];
		dct_reg[2][6] <= dct_2[6*12+:12];
		dct_reg[2][7] <= dct_2[7*12+:12];
		dct_reg[3][0] <= dct_3[0*12+:12];
		dct_reg[3][1] <= dct_3[1*12+:12];
		dct_reg[3][2] <= dct_3[2*12+:12];
		dct_reg[3][3] <= dct_3[3*12+:12];
		dct_reg[3][4] <= dct_3[4*12+:12];
		dct_reg[3][5] <= dct_3[5*12+:12];
		dct_reg[3][6] <= dct_3[6*12+:12];
		dct_reg[3][7] <= dct_3[7*12+:12];
		dct_reg[4][0] <= dct_4[0*12+:12];
		dct_reg[4][1] <= dct_4[1*12+:12];
		dct_reg[4][2] <= dct_4[2*12+:12];
		dct_reg[4][3] <= dct_4[3*12+:12];
		dct_reg[4][4] <= dct_4[4*12+:12];
		dct_reg[4][5] <= dct_4[5*12+:12];
		dct_reg[4][6] <= dct_4[6*12+:12];
		dct_reg[4][7] <= dct_4[7*12+:12];
		dct_reg[5][0] <= dct_5[0*12+:12];
		dct_reg[5][1] <= dct_5[1*12+:12];
		dct_reg[5][2] <= dct_5[2*12+:12];
		dct_reg[5][3] <= dct_5[3*12+:12];
		dct_reg[5][4] <= dct_5[4*12+:12];
		dct_reg[5][5] <= dct_5[5*12+:12];
		dct_reg[5][6] <= dct_5[6*12+:12];
		dct_reg[5][7] <= dct_5[7*12+:12];
		dct_reg[6][0] <= dct_6[0*12+:12];
		dct_reg[6][1] <= dct_6[1*12+:12];
		dct_reg[6][2] <= dct_6[2*12+:12];
		dct_reg[6][3] <= dct_6[3*12+:12];
		dct_reg[6][4] <= dct_6[4*12+:12];
		dct_reg[6][5] <= dct_6[5*12+:12];
		dct_reg[6][6] <= dct_6[6*12+:12];
		dct_reg[6][7] <= dct_6[7*12+:12];
		dct_reg[7][0] <= dct_7[0*12+:12];
		dct_reg[7][1] <= dct_7[1*12+:12];
		dct_reg[7][2] <= dct_7[2*12+:12];
		dct_reg[7][3] <= dct_7[3*12+:12];
		dct_reg[7][4] <= dct_7[4*12+:12];
		dct_reg[7][5] <= dct_7[5*12+:12];
		dct_reg[7][6] <= dct_7[6*12+:12];
		dct_reg[7][7] <= dct_7[7*12+:12];
		state <= START;
		x <= 0;
		y <= 0;
		i <= 0;
		j <= 0;
		for (i = 0; i < 8; i = i + 1)
		begin
			for (j = 0; j < 8; j = j + 1)
			begin
				temp[i][j] <= 0;
			end
		end
	end
	else
	begin
		case(state)
			START:
			begin
				/*if(x < 8)
				begin
					if(y < 8)
					begin
						if(i < 8)
						begin
							if(j < 8)
							begin
								j <= j + 1;
								temp[x][y] <= temp[x][y] + cosine[x][i] * cosine[y][j] * dct_reg[i][j] * coeff[i][j];	
							end
							else
							begin
								j <= 0;
								i <= i + 1;
							end
						end
						else
						begin
							i <= 0;
							y <= y + 1;
							invdct_reg[x][y] <= (temp[x][y] >> 32) + 128;
						end
					end
					else
					begin
						y <= 0;
						x <= x + 1;
					end
				end
				else
				begin
					state <= DONE;
				end*/

				for (x = 0; x < 8; x = x + 1)
				begin
					for (y = 0; y < 8; y = y + 1) 
					begin
						temp[x][y] = 0;
						for (i = 0; i < 8; i = i + 1)
						begin
							for (j = 0; j < 8; j = j + 1)
							begin
								temp[x][y] = temp[x][y] + cosine[x][i] * cosine[y][j] * dct_reg[i][j] * coeff[i][j];
							end
						end
						invdct_reg[x][y] <= (temp[x][y] >> 32) + 128;
					end
				end
				state <= DONE;

			end

		endcase // state
	end
end
endmodule // inverseDCT