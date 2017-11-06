module HuffmanEncode(clk, data_in0, data_in1, data_in2, data_in3, data_in4,
	data_in5, data_in6, data_in7, reset, start, data_out, num_bits, done);
input clk, start, reset;
input [95:0] data_in0;
input [95:0] data_in1;
input [95:0] data_in2;
input [95:0] data_in3;
input [95:0] data_in4;
input [95:0] data_in5;
input [95:0] data_in6;
input [95:0] data_in7;
output reg [511:0] data_out = 512'b0;
output reg [8:0] num_bits = 9'b0;
output reg done = 1'b0;

reg [3:0] state = 4'b0001;

integer i, j;
reg [11:0] zigArray [63:0];

integer ampCount;
integer outputCount;
reg [3:0] amp;
reg [11:0] ampData;
reg [15:0] rleData;
reg [4:0] rleCount;

reg [7:0] huffData;
reg [7:0] huffCount;
reg [6:0] huffZero;



localparam
INI = 4'b0001,
ZIG = 4'b0010,
HUFF = 4'b0100,
DONE = 4'b1000;

always @(posedge clk or posedge reset) 
begin
	if(reset) begin
		data_out <= 512'b0;
		num_bits <= 9'b0;
		done <= 1'b0;
		for(i = 0; i<8; i = i + 1)
			zigArray[i] <= 10'b0;
		state <= INI;
	end else begin
		case(state)
			INI:
			begin
				data_out <= 512'b0;
				num_bits <= 9'b0;
				done <= 1'b0;
				if(start)
					state <= ZIG;
			end
			ZIG:
			begin
				/*
				zigArray[0] <= data_in[0][0];

				zigArray[1] <= data_in[0][1];
				zigArray[2] <= data_in[1][0];

				zigArray[3] <= data_in[2][0];
				zigArray[4] <= data_in[1][1];
				zigArray[5] <= data_in[0][2];

				zigArray[6] <= data_in[0][3];
				zigArray[7] <= data_in[1][2];
				zigArray[8] <= data_in[2][1];
				zigArray[9] <= data_in[3][0];

				zigArray[10] <= data_in[4][0];
				zigArray[11] <= data_in[3][1];
				zigArray[12] <= data_in[2][2];
				zigArray[13] <= data_in[1][3];
				zigArray[14] <= data_in[0][4];

				zigArray[15] <= data_in[0][5];
				zigArray[16] <= data_in[1][4];
				zigArray[17] <= data_in[2][3];
				zigArray[18] <= data_in[3][2];
				zigArray[19] <= data_in[4][1];
				zigArray[20] <= data_in[5][0];

				zigArray[21] <= data_in[6][0];
				zigArray[22] <= data_in[5][1];
				zigArray[23] <= data_in[4][2];
				zigArray[24] <= data_in[3][3];
				zigArray[25] <= data_in[2][4];
				zigArray[26] <= data_in[1][5];
				zigArray[27] <= data_in[0][6];

				zigArray[28] <= data_in[0][7];
				zigArray[29] <= data_in[1][6];
				zigArray[30] <= data_in[2][5];
				zigArray[31] <= data_in[3][4];
				zigArray[32] <= data_in[4][3];
				zigArray[33] <= data_in[5][2];
				zigArray[34] <= data_in[6][1];
				zigArray[35] <= data_in[7][0];

				zigArray[36] <= data_in[7][1];
				zigArray[37] <= data_in[6][2];
				zigArray[38] <= data_in[5][3];
				zigArray[39] <= data_in[4][4];
				zigArray[40] <= data_in[3][5];
				zigArray[41] <= data_in[2][6];
				zigArray[42] <= data_in[1][7];

				zigArray[43] <= data_in[2][7];
				zigArray[44] <= data_in[3][6];
				zigArray[45] <= data_in[4][5];
				zigArray[46] <= data_in[5][4];
				zigArray[47] <= data_in[6][3];
				zigArray[48] <= data_in[7][2];

				zigArray[49] <= data_in[7][3];
				zigArray[50] <= data_in[6][4];
				zigArray[51] <= data_in[5][5];
				zigArray[52] <= data_in[4][6];
				zigArray[53] <= data_in[3][7];

				zigArray[54] <= data_in[4][7];
				zigArray[55] <= data_in[5][6];
				zigArray[56] <= data_in[6][5];
				zigArray[57] <= data_in[7][4];

				zigArray[58] <= data_in[7][5];
				zigArray[59] <= data_in[6][6];
				zigArray[60] <= data_in[5][7];

				zigArray[61] <= data_in[6][7];
				zigArray[62] <= data_in[7][6];

				zigArray[63] <= data_in[7][7];
				*/
				zigArray[0] <= data_in0[0*12+:12];
				zigArray[1] <= data_in0[1*12+:12];
				zigArray[2] <= data_in1[0*12+:12];
				zigArray[3] <= data_in2[0*12+:12];
				zigArray[4] <= data_in1[1*12+:12];
				zigArray[5] <= data_in0[2*12+:12];
				zigArray[6] <= data_in0[3*12+:12];
				zigArray[7] <= data_in1[2*12+:12];
				zigArray[8] <= data_in2[1*12+:12];
				zigArray[9] <= data_in3[0*12+:12];
				zigArray[10] <= data_in4[0*12+:12];
				zigArray[11] <= data_in3[1*12+:12];
				zigArray[12] <= data_in2[2*12+:12];
				zigArray[13] <= data_in1[3*12+:12];
				zigArray[14] <= data_in0[4*12+:12];
				zigArray[15] <= data_in0[5*12+:12];
				zigArray[16] <= data_in1[4*12+:12];
				zigArray[17] <= data_in2[3*12+:12];
				zigArray[18] <= data_in3[2*12+:12];
				zigArray[19] <= data_in4[1*12+:12];
				zigArray[20] <= data_in5[0*12+:12];
				zigArray[21] <= data_in6[0*12+:12];
				zigArray[22] <= data_in5[1*12+:12];
				zigArray[23] <= data_in4[2*12+:12];
				zigArray[24] <= data_in3[3*12+:12];
				zigArray[25] <= data_in2[4*12+:12];
				zigArray[26] <= data_in1[5*12+:12];
				zigArray[27] <= data_in0[6*12+:12];
				zigArray[28] <= data_in0[7*12+:12];
				zigArray[29] <= data_in1[6*12+:12];
				zigArray[30] <= data_in2[5*12+:12];
				zigArray[31] <= data_in3[4*12+:12];
				zigArray[32] <= data_in4[3*12+:12];
				zigArray[33] <= data_in5[2*12+:12];
				zigArray[34] <= data_in6[1*12+:12];
				zigArray[35] <= data_in7[0*12+:12];
				zigArray[36] <= data_in7[1*12+:12];
				zigArray[37] <= data_in6[2*12+:12];
				zigArray[38] <= data_in5[3*12+:12];
				zigArray[39] <= data_in4[4*12+:12];
				zigArray[40] <= data_in3[5*12+:12];
				zigArray[41] <= data_in2[6*12+:12];
				zigArray[42] <= data_in1[7*12+:12];
				zigArray[43] <= data_in2[7*12+:12];
				zigArray[44] <= data_in3[6*12+:12];
				zigArray[45] <= data_in4[5*12+:12];
				zigArray[46] <= data_in5[4*12+:12];
				zigArray[47] <= data_in6[3*12+:12];
				zigArray[48] <= data_in7[2*12+:12];
				zigArray[49] <= data_in7[3*12+:12];
				zigArray[50] <= data_in6[4*12+:12];
				zigArray[51] <= data_in5[5*12+:12];
				zigArray[52] <= data_in4[6*12+:12];
				zigArray[53] <= data_in3[7*12+:12];
				zigArray[54] <= data_in4[7*12+:12];
				zigArray[55] <= data_in5[6*12+:12];
				zigArray[56] <= data_in6[5*12+:12];
				zigArray[57] <= data_in7[4*12+:12];
				zigArray[58] <= data_in7[5*12+:12];
				zigArray[59] <= data_in6[6*12+:12];
				zigArray[60] <= data_in5[7*12+:12];
				zigArray[61] <= data_in6[7*12+:12];
				zigArray[62] <= data_in7[6*12+:12];
				zigArray[63] <= data_in7[7*12+:12];

				state <= HUFF;
				huffZero <= 7'b0;
				huffCount <= 8'b0;
				num_bits <= 9'b0;
				rleData <= 16'b0;
				huffData <= 8'b0;
			end
			HUFF:
			begin
				//Done
				if(huffCount == 64)
				begin
					if(huffZero > 0)
					begin
						rleData = 16'b0000000000001010;
						rleCount = 4;
						//Output data
						for(outputCount = 1; outputCount <= rleCount; outputCount = outputCount + 1)
						begin
							data_out[num_bits + outputCount - 1] <= rleData[rleCount - outputCount];
						end
						huffZero <= 6'b0;
						num_bits <= num_bits + rleCount;
					end
					state <= DONE;

				end
				//DC Value
				if(!huffCount)
				begin
					rleCount = 0;
					if(!zigArray[huffCount])
						amp = 0;
					for(ampCount = 0; ampCount < 11; ampCount = ampCount + 1)
					begin
						if(zigArray[huffCount][ampCount] != zigArray[huffCount][11])
							amp = ampCount + 1;
					end
					/*
					//Negative
					if(zigArray[huffCount][11])
					begin
						ampData = (zigArray[huffCount] - 1) ^ (12'b111111111111 << amp);
						if(ampData[amp + 1])
							amp = amp + 1;
					end
					//Positive
					else
					begin
						ampData = zigArray[huffCount];
					end*/
					
					/*if(!zigArray[huffCount])
						amp = 0;
					else if(zigArray[huffCount][10] != zigArray[huffCount][11])
						amp = 11;
					else if(zigArray[huffCount][9] != zigArray[huffCount][11])
						amp = 10;
					else if(zigArray[huffCount][8] != zigArray[huffCount][11])
						amp = 9;
					else if(zigArray[huffCount][7] != zigArray[huffCount][11])
						amp = 8;
					else if(zigArray[huffCount][6] != zigArray[huffCount][11])
						amp = 7;
					else if(zigArray[huffCount][5] != zigArray[huffCount][11])
						amp = 6;
					else if(zigArray[huffCount][4] != zigArray[huffCount][11])
						amp = 5;
					else if(zigArray[huffCount][3] != zigArray[huffCount][11])
						amp = 4;
					else if(zigArray[huffCount][2] != zigArray[huffCount][11])
						amp = 3;
					else if(zigArray[huffCount][1] != zigArray[huffCount][11])
						amp = 2;
					else if(zigArray[huffCount][0] != zigArray[huffCount][11])
						amp = 1;
					else
						amp = 1;*/
					//Negative
					if(zigArray[huffCount][11])
					begin
						ampData = (zigArray[huffCount] - 1) ^ (12'b111111111111 << amp);
						if(ampData[amp])
						begin
							ampData[amp] = 0;
							amp = amp + 1;
						end
					end
					//Positive
					else
					begin
						ampData = zigArray[huffCount];
					end
					huffData = amp & 8'b00001111;
					case(huffData)
						8'h00:
						begin 
							rleData = 16'b0000000000000000;
							rleCount = 2;
						end
						8'h01:
						begin 
							rleData = 16'b0000000000000010;
							rleCount = 3;
						end
						8'h02:
						begin 
							rleData = 16'b0000000000000011;
							rleCount = 3;
						end
						8'h03:
						begin 
							rleData = 16'b0000000000000100;
							rleCount = 3;
						end
						8'h04:
						begin 
							rleData = 16'b0000000000000101;
							rleCount = 3;
						end
						8'h05:
						begin 
							rleData = 16'b0000000000000110;
							rleCount = 3;
						end
						8'h06:
						begin 
							rleData = 16'b0000000000001110;
							rleCount = 4;
						end
						8'h07:
						begin 
							rleData = 16'b0000000000011110;
							rleCount = 5;
						end
						8'h08:
						begin 
							rleData = 16'b0000000000111110;
							rleCount = 6;
						end
						8'h09:
						begin 
							rleData = 16'b0000000001111110;
							rleCount = 7;
						end
						8'h0A:
						begin 
							rleData = 16'b0000000011111110;
							rleCount = 8;
						end
						8'h0B:
						begin 
							rleData = 16'b0000000111111110;
							rleCount = 9;
						end
					endcase
					for(outputCount = 1; outputCount <= rleCount; outputCount = outputCount + 1)
					begin
						data_out[num_bits + outputCount - 1] <= rleData[rleCount - outputCount];
					end
					for(ampCount = 1; ampCount <= amp; ampCount = ampCount + 1)
					begin
						data_out[num_bits + rleCount + ampCount - 1] <= ampData[amp - ampCount];
					end
					huffCount = huffCount + 1;
					huffZero <= 6'b0;
					num_bits <= num_bits + rleCount + amp;
				end
				//AC Value
				else if(zigArray[huffCount])
				begin
					rleCount = 0;
					amp = 0;
					for(ampCount = 0; ampCount < 11; ampCount = ampCount + 1)
					begin
						if(zigArray[huffCount][ampCount] != zigArray[huffCount][11])
							amp = ampCount + 1;
					end
					//Negative
					if(zigArray[huffCount][11])
					begin
						ampData = (zigArray[huffCount] - 1) ^ (12'b111111111111 << amp);
						if(ampData[amp])
						begin
							ampData[amp] = 0;
							amp = amp + 1;
						end
					end
					//Positive
					else
					begin
						ampData = zigArray[huffCount];
					end

					if(huffZero >= 16)
					begin
						rleData = 16'b0000011111111001;
						rleCount = 11;
						//Output data
						for(outputCount = 1; outputCount <= rleCount; outputCount = outputCount + 1)
						begin
							data_out[num_bits + outputCount - 1] <= rleData[rleCount - outputCount];
						end
						huffZero <= huffZero - 16;
						num_bits <= num_bits + rleCount;
					end
					else
					begin
						huffData = ((huffZero ^ 6'b110000) << 4) | amp;
						case (huffData)
							8'h01:
							begin
								rleData = 16'b0000000000000000;
								rleCount = 2;
							end
							8'h02:
							begin
								rleData = 16'b0000000000000001;
								rleCount = 2;
							end
							8'h03:
							begin
								rleData = 16'b0000000000000100;
								rleCount = 3;
							end
							8'h00:
							begin
								rleData = 16'b0000000000001010;
								rleCount = 4;
							end
							8'h04:
							begin
								rleData = 16'b0000000000001011;
								rleCount = 4;
							end
							8'h11:
							begin
								rleData = 16'b0000000000001100;
								rleCount = 4;
							end
							8'h05:
							begin
								rleData = 16'b0000000000011010;
								rleCount = 5;
							end
							8'h12:
							begin
								rleData = 16'b0000000000011011;
								rleCount = 5;
							end
							8'h21:
							begin
								rleData = 16'b0000000000011100;
								rleCount = 5;
							end
							8'h31:
							begin
								rleData = 16'b0000000000111010;
								rleCount = 6;
							end
							8'h41:
							begin
								rleData = 16'b0000000000111011;
								rleCount = 6;
							end
							8'h06:
							begin
								rleData = 16'b0000000001111000;
								rleCount = 7;
							end
							8'h13:
							begin
								rleData = 16'b0000000001111001;
								rleCount = 7;
							end
							8'h51:
							begin
								rleData = 16'b0000000001111010;
								rleCount = 7;
							end
							8'h61:
							begin
								rleData = 16'b0000000001111011;
								rleCount = 7;
							end
							8'h07:
							begin
								rleData = 16'b0000000011111000;
								rleCount = 8;
							end
							8'h22:
							begin
								rleData = 16'b0000000011111001;
								rleCount = 8;
							end
							8'h71:
							begin
								rleData = 16'b0000000011111010;
								rleCount = 8;
							end
							8'h14:
							begin
								rleData = 16'b0000000111110110;
								rleCount = 9;
							end
							8'h32:
							begin
								rleData = 16'b0000000111110111;
								rleCount = 9;
							end
							8'h81:
							begin
								rleData = 16'b0000000111111000;
								rleCount = 9;
							end
							8'h91:
							begin
								rleData = 16'b0000000111111001;
								rleCount = 9;
							end
							8'hA1:
							begin
								rleData = 16'b0000000111111010;
								rleCount = 9;
							end
							8'h08:
							begin
								rleData = 16'b0000001111110110;
								rleCount = 10;
							end
							8'h23:
							begin
								rleData = 16'b0000001111110111;
								rleCount = 10;
							end
							8'h42:
							begin
								rleData = 16'b0000001111111000;
								rleCount = 10;
							end
							8'hB1:
							begin
								rleData = 16'b0000001111111001;
								rleCount = 10;
							end
							8'hC1:
							begin
								rleData = 16'b0000001111111010;
								rleCount = 10;
							end
							8'h15:
							begin
								rleData = 16'b0000011111110110;
								rleCount = 11;
							end
							8'h52:
							begin
								rleData = 16'b0000011111110111;
								rleCount = 11;
							end
							8'hD1:
							begin
								rleData = 16'b0000011111111000;
								rleCount = 11;
							end
							8'hF0:
							begin
								rleData = 16'b0000011111111001;
								rleCount = 11;
							end
							8'h24:
							begin
								rleData = 16'b0000111111110100;
								rleCount = 12;
							end
							8'h33:
							begin
								rleData = 16'b0000111111110101;
								rleCount = 12;
							end
							8'h62:
							begin
								rleData = 16'b0000111111110110;
								rleCount = 12;
							end
							8'h72:
							begin
								rleData = 16'b0000111111110111;
								rleCount = 12;
							end
							8'h82:
							begin
								rleData = 16'b0111111111000000;
								rleCount = 15;
							end
							8'h09:
							begin
								rleData = 16'b1111111110000010;
								rleCount = 16;
							end
							8'h0A:
							begin
								rleData = 16'b1111111110000011;
								rleCount = 16;
							end
							8'h16:
							begin
								rleData = 16'b1111111110000100;
								rleCount = 16;
							end
							8'h17:
							begin
								rleData = 16'b1111111110000101;
								rleCount = 16;
							end
							8'h18:
							begin
								rleData = 16'b1111111110000110;
								rleCount = 16;
							end
							8'h19:
							begin
								rleData = 16'b1111111110000111;
								rleCount = 16;
							end
							8'h1A:
							begin
								rleData = 16'b1111111110001000;
								rleCount = 16;
							end
							8'h25:
							begin
								rleData = 16'b1111111110001001;
								rleCount = 16;
							end
							8'h26:
							begin
								rleData = 16'b1111111110001010;
								rleCount = 16;
							end
							8'h27:
							begin
								rleData = 16'b1111111110001011;
								rleCount = 16;
							end
							8'h28:
							begin
								rleData = 16'b1111111110001100;
								rleCount = 16;
							end
							8'h29:
							begin
								rleData = 16'b1111111110001101;
								rleCount = 16;
							end
							8'h2A:
							begin
								rleData = 16'b1111111110001110;
								rleCount = 16;
							end
							8'h34:
							begin
								rleData = 16'b1111111110001111;
								rleCount = 16;
							end
							8'h35:
							begin
								rleData = 16'b1111111110010000;
								rleCount = 16;
							end
							8'h36:
							begin
								rleData = 16'b1111111110010001;
								rleCount = 16;
							end
							8'h37:
							begin
								rleData = 16'b1111111110010010;
								rleCount = 16;
							end
							8'h38:
							begin
								rleData = 16'b1111111110010011;
								rleCount = 16;
							end
							8'h39:
							begin
								rleData = 16'b1111111110010100;
								rleCount = 16;
							end
							8'h3A:
							begin
								rleData = 16'b1111111110010101;
								rleCount = 16;
							end
							8'h43:
							begin
								rleData = 16'b1111111110010110;
								rleCount = 16;
							end
							8'h44:
							begin
								rleData = 16'b1111111110010111;
								rleCount = 16;
							end
							8'h45:
							begin
								rleData = 16'b1111111110011000;
								rleCount = 16;
							end
							8'h46:
							begin
								rleData = 16'b1111111110011001;
								rleCount = 16;
							end
							8'h47:
							begin
								rleData = 16'b1111111110011010;
								rleCount = 16;
							end
							8'h48:
							begin
								rleData = 16'b1111111110011011;
								rleCount = 16;
							end
							8'h49:
							begin
								rleData = 16'b1111111110011100;
								rleCount = 16;
							end
							8'h4A:
							begin
								rleData = 16'b1111111110011101;
								rleCount = 16;
							end
							8'h53:
							begin
								rleData = 16'b1111111110011110;
								rleCount = 16;
							end
							8'h54:
							begin
								rleData = 16'b1111111110011111;
								rleCount = 16;
							end
							8'h55:
							begin
								rleData = 16'b1111111110100000;
								rleCount = 16;
							end
							8'h56:
							begin
								rleData = 16'b1111111110100001;
								rleCount = 16;
							end
							8'h57:
							begin
								rleData = 16'b1111111110100010;
								rleCount = 16;
							end
							8'h58:
							begin
								rleData = 16'b1111111110100011;
								rleCount = 16;
							end
							8'h59:
							begin
								rleData = 16'b1111111110100100;
								rleCount = 16;
							end
							8'h5A:
							begin
								rleData = 16'b1111111110100101;
								rleCount = 16;
							end
							8'h63:
							begin
								rleData = 16'b1111111110100110;
								rleCount = 16;
							end
							8'h64:
							begin
								rleData = 16'b1111111110100111;
								rleCount = 16;
							end
							8'h65:
							begin
								rleData = 16'b1111111110101000;
								rleCount = 16;
							end
							8'h66:
							begin
								rleData = 16'b1111111110101001;
								rleCount = 16;
							end
							8'h67:
							begin
								rleData = 16'b1111111110101010;
								rleCount = 16;
							end
							8'h68:
							begin
								rleData = 16'b1111111110101011;
								rleCount = 16;
							end
							8'h69:
							begin
								rleData = 16'b1111111110101100;
								rleCount = 16;
							end
							8'h6A:
							begin
								rleData = 16'b1111111110101101;
								rleCount = 16;
							end
							8'h73:
							begin
								rleData = 16'b1111111110101110;
								rleCount = 16;
							end
							8'h74:
							begin
								rleData = 16'b1111111110101111;
								rleCount = 16;
							end
							8'h75:
							begin
								rleData = 16'b1111111110110000;
								rleCount = 16;
							end
							8'h76:
							begin
								rleData = 16'b1111111110110001;
								rleCount = 16;
							end
							8'h77:
							begin
								rleData = 16'b1111111110110010;
								rleCount = 16;
							end
							8'h78:
							begin
								rleData = 16'b1111111110110011;
								rleCount = 16;
							end
							8'h79:
							begin
								rleData = 16'b1111111110110100;
								rleCount = 16;
							end
							8'h7A:
							begin
								rleData = 16'b1111111110110101;
								rleCount = 16;
							end
							8'h83:
							begin
								rleData = 16'b1111111110110110;
								rleCount = 16;
							end
							8'h84:
							begin
								rleData = 16'b1111111110110111;
								rleCount = 16;
							end
							8'h85:
							begin
								rleData = 16'b1111111110111000;
								rleCount = 16;
							end
							8'h86:
							begin
								rleData = 16'b1111111110111001;
								rleCount = 16;
							end
							8'h87:
							begin
								rleData = 16'b1111111110111010;
								rleCount = 16;
							end
							8'h88:
							begin
								rleData = 16'b1111111110111011;
								rleCount = 16;
							end
							8'h89:
							begin
								rleData = 16'b1111111110111100;
								rleCount = 16;
							end
							8'h8A:
							begin
								rleData = 16'b1111111110111101;
								rleCount = 16;
							end
							8'h92:
							begin
								rleData = 16'b1111111110111110;
								rleCount = 16;
							end
							8'h93:
							begin
								rleData = 16'b1111111110111111;
								rleCount = 16;
							end
							8'h94:
							begin
								rleData = 16'b1111111111000000;
								rleCount = 16;
							end
							8'h95:
							begin
								rleData = 16'b1111111111000001;
								rleCount = 16;
							end
							8'h96:
							begin
								rleData = 16'b1111111111000010;
								rleCount = 16;
							end
							8'h97:
							begin
								rleData = 16'b1111111111000011;
								rleCount = 16;
							end
							8'h98:
							begin
								rleData = 16'b1111111111000100;
								rleCount = 16;
							end
							8'h99:
							begin
								rleData = 16'b1111111111000101;
								rleCount = 16;
							end
							8'h9A:
							begin
								rleData = 16'b1111111111000110;
								rleCount = 16;
							end
							8'hA2:
							begin
								rleData = 16'b1111111111000111;
								rleCount = 16;
							end
							8'hA3:
							begin
								rleData = 16'b1111111111001000;
								rleCount = 16;
							end
							8'hA4:
							begin
								rleData = 16'b1111111111001001;
								rleCount = 16;
							end
							8'hA5:
							begin
								rleData = 16'b1111111111001010;
								rleCount = 16;
							end
							8'hA6:
							begin
								rleData = 16'b1111111111001011;
								rleCount = 16;
							end
							8'hA7:
							begin
								rleData = 16'b1111111111001100;
								rleCount = 16;
							end
							8'hA8:
							begin
								rleData = 16'b1111111111001101;
								rleCount = 16;
							end
							8'hA9:
							begin
								rleData = 16'b1111111111001110;
								rleCount = 16;
							end
							8'hAA:
							begin
								rleData = 16'b1111111111001111;
								rleCount = 16;
							end
							8'hB2:
							begin
								rleData = 16'b1111111111010000;
								rleCount = 16;
							end
							8'hB3:
							begin
								rleData = 16'b1111111111010001;
								rleCount = 16;
							end
							8'hB4:
							begin
								rleData = 16'b1111111111010010;
								rleCount = 16;
							end
							8'hB5:
							begin
								rleData = 16'b1111111111010011;
								rleCount = 16;
							end
							8'hB6:
							begin
								rleData = 16'b1111111111010100;
								rleCount = 16;
							end
							8'hB7:
							begin
								rleData = 16'b1111111111010101;
								rleCount = 16;
							end
							8'hB8:
							begin
								rleData = 16'b1111111111010110;
								rleCount = 16;
							end
							8'hB9:
							begin
								rleData = 16'b1111111111010111;
								rleCount = 16;
							end
							8'hBA:
							begin
								rleData = 16'b1111111111011000;
								rleCount = 16;
							end
							8'hC2:
							begin
								rleData = 16'b1111111111011001;
								rleCount = 16;
							end
							8'hC3:
							begin
								rleData = 16'b1111111111011010;
								rleCount = 16;
							end
							8'hC4:
							begin
								rleData = 16'b1111111111011011;
								rleCount = 16;
							end
							8'hC5:
							begin
								rleData = 16'b1111111111011100;
								rleCount = 16;
							end
							8'hC6:
							begin
								rleData = 16'b1111111111011101;
								rleCount = 16;
							end
							8'hC7:
							begin
								rleData = 16'b1111111111011110;
								rleCount = 16;
							end
							8'hC8:
							begin
								rleData = 16'b1111111111011111;
								rleCount = 16;
							end
							8'hC9:
							begin
								rleData = 16'b1111111111100000;
								rleCount = 16;
							end
							8'hCA:
							begin
								rleData = 16'b1111111111100001;
								rleCount = 16;
							end
							8'hD2:
							begin
								rleData = 16'b1111111111100010;
								rleCount = 16;
							end
							8'hD3:
							begin
								rleData = 16'b1111111111100011;
								rleCount = 16;
							end
							8'hD4:
							begin
								rleData = 16'b1111111111100100;
								rleCount = 16;
							end
							8'hD5:
							begin
								rleData = 16'b1111111111100101;
								rleCount = 16;
							end
							8'hD6:
							begin
								rleData = 16'b1111111111100110;
								rleCount = 16;
							end
							8'hD7:
							begin
								rleData = 16'b1111111111100111;
								rleCount = 16;
							end
							8'hD8:
							begin
								rleData = 16'b1111111111101000;
								rleCount = 16;
							end
							8'hD9:
							begin
								rleData = 16'b1111111111101001;
								rleCount = 16;
							end
							8'hDA:
							begin
								rleData = 16'b1111111111101010;
								rleCount = 16;
							end
							8'hE1:
							begin
								rleData = 16'b1111111111101011;
								rleCount = 16;
							end
							8'hE2:
							begin
								rleData = 16'b1111111111101100;
								rleCount = 16;
							end
							8'hE3:
							begin
								rleData = 16'b1111111111101101;
								rleCount = 16;
							end
							8'hE4:
							begin
								rleData = 16'b1111111111101110;
								rleCount = 16;
							end
							8'hE5:
							begin
								rleData = 16'b1111111111101111;
								rleCount = 16;
							end
							8'hE6:
							begin
								rleData = 16'b1111111111110000;
								rleCount = 16;
							end
							8'hE7:
							begin
								rleData = 16'b1111111111110001;
								rleCount = 16;
							end
							8'hE8:
							begin
								rleData = 16'b1111111111110010;
								rleCount = 16;
							end
							8'hE9:
							begin
								rleData = 16'b1111111111110011;
								rleCount = 16;
							end
							8'hEA:
							begin
								rleData = 16'b1111111111110100;
								rleCount = 16;
							end
							8'hF1:
							begin
								rleData = 16'b1111111111110101;
								rleCount = 16;
							end
							8'hF2:
							begin
								rleData = 16'b1111111111110110;
								rleCount = 16;
							end
							8'hF3:
							begin
								rleData = 16'b1111111111110111;
								rleCount = 16;
							end
							8'hF4:
							begin
								rleData = 16'b1111111111111000;
								rleCount = 16;
							end
							8'hF5:
							begin
								rleData = 16'b1111111111111001;
								rleCount = 16;
							end
							8'hF6:
							begin
								rleData = 16'b1111111111111010;
								rleCount = 16;
							end
							8'hF7:
							begin
								rleData = 16'b1111111111111011;
								rleCount = 16;
							end
							8'hF8:
							begin
								rleData = 16'b1111111111111100;
								rleCount = 16;
							end
							8'hF9:
							begin
								rleData = 16'b1111111111111101;
								rleCount = 16;
							end
							8'hFA:
							begin
								rleData = 16'b1111111111111110;
								rleCount = 16;
							end
							
						endcase
						for(outputCount = 1; outputCount <= rleCount; outputCount = outputCount + 1)
						begin
							data_out[num_bits + outputCount - 1] <= rleData[rleCount - outputCount];
						end
						for(ampCount = 1; ampCount <= amp; ampCount = ampCount + 1)
						begin
							data_out[num_bits + rleCount + ampCount - 1] <= ampData[amp - ampCount];
						end

						huffCount <= huffCount + 1;
						huffZero <= 6'b0;
						num_bits <= num_bits + rleCount + amp;
					end

				end
				else
				begin
					huffZero <= huffZero + 1;
					huffCount <= huffCount + 1;
				end

			end
			DONE:
			begin
				done <= 1'b1;
			end

		endcase // state
	end
end

endmodule // HuffmanEncode
