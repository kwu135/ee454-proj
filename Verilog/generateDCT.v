module generateDCT(pixels_0, pixels_1, pixels_2, pixels_3, pixels_4,
	pixels_5, pixels_6, pixels_7, Clk, Reset, dct_0, dct_1, dct_2, dct_3,
	dct_4, dct_5, dct_6, dct_7, Done);
	input[63:0] pixels_0;
	input[63:0] pixels_1;
	input[63:0] pixels_2;
	input[63:0] pixels_3;
	input[63:0] pixels_4;
	input[63:0] pixels_5;
	input[63:0] pixels_6;
	input[63:0] pixels_7;

	input Clk;
	input Reset;
	output[255:0] dct_0;
	output[255:0] dct_1;
	output[255:0] dct_2;
	output[255:0] dct_3;
	output[255:0] dct_4;
	output[255:0] dct_5;
	output[255:0] dct_6;
	output[255:0] dct_7;

	output Done;
	
	reg[7:0] pixels[7:0][7:0];
	reg[31:0] dct_reg[7:0][7:0];
	
	reg[2:0] i;

	reg[31:0] s0[7:0];
	reg[31:0] s1[7:0]; 
	reg[31:0] s2[7:0]; 
	reg[31:0] s3[7:0]; 

	reg[31:0] d0[7:0]; 
	reg[31:0] d1[7:0]; 
	reg[31:0] d2[7:0]; 
	reg[31:0] d3[7:0];

	reg [6:0] state;

	localparam 
	ROWSD	=	5'b00001, 
	ROWCALC = 	5'b00010, 
	COLSD 	= 	5'b00100, 
	COLCALC = 	5'b01000, 
	DONE 	= 	5'b10000;

	assign Done = (state == DONE);

	assign dct_0[0*32+:32] = dct_reg[0][0];
	assign dct_0[1*32+:32] = dct_reg[0][1];
	assign dct_0[2*32+:32] = dct_reg[0][2];
	assign dct_0[3*32+:32] = dct_reg[0][3];
	assign dct_0[4*32+:32] = dct_reg[0][4];
	assign dct_0[5*32+:32] = dct_reg[0][5];
	assign dct_0[6*32+:32] = dct_reg[0][6];
	assign dct_0[7*32+:32] = dct_reg[0][7];

	assign dct_1[0*32+:32] = dct_reg[1][0];
	assign dct_1[1*32+:32] = dct_reg[1][1];
	assign dct_1[2*32+:32] = dct_reg[1][2];
	assign dct_1[3*32+:32] = dct_reg[1][3];
	assign dct_1[4*32+:32] = dct_reg[1][4];
	assign dct_1[5*32+:32] = dct_reg[1][5];
	assign dct_1[6*32+:32] = dct_reg[1][6];
	assign dct_1[7*32+:32] = dct_reg[1][7];

	assign dct_2[0*32+:32] = dct_reg[2][0];
	assign dct_2[1*32+:32] = dct_reg[2][1];
	assign dct_2[2*32+:32] = dct_reg[2][2];
	assign dct_2[3*32+:32] = dct_reg[2][3];
	assign dct_2[4*32+:32] = dct_reg[2][4];
	assign dct_2[5*32+:32] = dct_reg[2][5];
	assign dct_2[6*32+:32] = dct_reg[2][6];
	assign dct_2[7*32+:32] = dct_reg[2][7];

	assign dct_3[0*32+:32] = dct_reg[3][0];
	assign dct_3[1*32+:32] = dct_reg[3][1];
	assign dct_3[2*32+:32] = dct_reg[3][2];
	assign dct_3[3*32+:32] = dct_reg[3][3];
	assign dct_3[4*32+:32] = dct_reg[3][4];
	assign dct_3[5*32+:32] = dct_reg[3][5];
	assign dct_3[6*32+:32] = dct_reg[3][6];
	assign dct_3[7*32+:32] = dct_reg[3][7];

	assign dct_4[0*32+:32] = dct_reg[4][0];
	assign dct_4[1*32+:32] = dct_reg[4][1];
	assign dct_4[2*32+:32] = dct_reg[4][2];
	assign dct_4[3*32+:32] = dct_reg[4][3];
	assign dct_4[4*32+:32] = dct_reg[4][4];
	assign dct_4[5*32+:32] = dct_reg[4][5];
	assign dct_4[6*32+:32] = dct_reg[4][6];
	assign dct_4[7*32+:32] = dct_reg[4][7];

	assign dct_5[0*32+:32] = dct_reg[5][0];
	assign dct_5[1*32+:32] = dct_reg[5][1];
	assign dct_5[2*32+:32] = dct_reg[5][2];
	assign dct_5[3*32+:32] = dct_reg[5][3];
	assign dct_5[4*32+:32] = dct_reg[5][4];
	assign dct_5[5*32+:32] = dct_reg[5][5];
	assign dct_5[6*32+:32] = dct_reg[5][6];
	assign dct_5[7*32+:32] = dct_reg[5][7];

	assign dct_6[0*32+:32] = dct_reg[6][0];
	assign dct_6[1*32+:32] = dct_reg[6][1];
	assign dct_6[2*32+:32] = dct_reg[6][2];
	assign dct_6[3*32+:32] = dct_reg[6][3];
	assign dct_6[4*32+:32] = dct_reg[6][4];
	assign dct_6[5*32+:32] = dct_reg[6][5];
	assign dct_6[6*32+:32] = dct_reg[6][6];
	assign dct_6[7*32+:32] = dct_reg[6][7];

	assign dct_7[0*32+:32] = dct_reg[7][0];
	assign dct_7[1*32+:32] = dct_reg[7][1];
	assign dct_7[2*32+:32] = dct_reg[7][2];
	assign dct_7[3*32+:32] = dct_reg[7][3];
	assign dct_7[4*32+:32] = dct_reg[7][4];
	assign dct_7[5*32+:32] = dct_reg[7][5];
	assign dct_7[6*32+:32] = dct_reg[7][6];
	assign dct_7[7*32+:32] = dct_reg[7][7];

	localparam
	coeff0 = 31'b00000000000000000000000111110110, // 0.49039 * 1024 = 502
	coeff1 = 31'b00000000000000000000000111011001, // 0.46194 * 1024 = 473
	coeff2 = 31'b00000000000000000000000110101010, // 0.41573 * 1024 = 426
	coeff3 = 31'b00000000000000000000000101101010, // 0.35355 * 1024 = 362
	coeff4 = 31'b00000000000000000000000100011100, // 0.27779 * 1024 = 284
	coeff5 = 31'b00000000000000000000000011000100, // 0.19134 * 1024 = 196
	coeff6 = 31'b00000000000000000000000001100100; // 0.09755 * 1024 = 100

	// always (*)
	// begin
	// 	for (i=0; i<8; i=i+1)
	// 	begin
	// 		s0 = pixels[i][0] + pixels[i][7] - 256;
	// 		s1 = pixles[i][1] + pixels[i][6] - 256;
	// 		s2 = pixels[i][2] + pixels[i][5] - 256;
	// 		s3 = pixles[i][3] + pixles[i][4] - 256;

	// 		d0 = pixels[i][0] - pixels[i][7];
	// 		d1 = pixles[i][1] - pixels[i][6];
	// 		d2 = pixels[i][2] - pixels[i][5];
	// 		d3 = pixels[i][3] - pixels[i][4];

	// 		dct_reg[i][0] = (coeff3*(s0+s1+s2+s3)) >> 10;
	// 		dct_reg[i][1] = (coeff0*d0+coeff2*d1+coeff4*d2+coeff6*d3) >> 10;
	// 		dct_reg[i][2] = (coeff1*(s0-s3)+coeff5*(s1-s2)) >> 10;
	// 		dct_reg[i][3] = (coeff2*d0-coeff6*d1-coeff0*d2-coeff4*d3) >> 10;
	// 		dct_reg[i][4] = (coeff3*(s0-s1-s2+s3)) >> 10;
	// 		dct_reg[i][5] = (coeff4*d0-coeff0*d1+coeff6*d2+coeff2*d3) >> 10;
	// 		dct_reg[i][6] = (coeff5*(s0-s3)+coeff1*(s2-s1)) >> 10;
	// 		dct_reg[i][7] = (coeff6*d0-coeff4*d1+coeff2*d2-coeff0*d3) >> 10;
	// 	end
	// 	for (i=0; i<8; i=i+1)
	// 	begin
	// 		s0 = dct_reg[0][i] + dct_reg[7][i];
	// 		s1 = dct_reg[1][i] + dct_reg[6][i];
	// 		s2 = dct_reg[2][i] + dct_reg[5][i];
	// 		s3 = dct_reg[3][i] + dct_reg[4][i];

	// 		d0 = dct_reg[0][i] - dct_reg[7][i];
	// 		d1 = dct_reg[1][i] - dct_reg[6][i];
	// 		d2 = dct_reg[2][i] - dct_reg[5][i];
	// 		d3 = dct_reg[3][i] - dct_reg[4][i];

	// 		dct_reg[0][i] = (coeff3*(s0+s1+s2+s3)) >> 10;
	// 		dct_reg[1][i] = (coeff0*d0+coeff2*d1+coeff4*d2+coeff6*d3) >> 10;
	// 		dct_reg[2][i] = (coeff1*(s0-s3)+coeff5*(s1-s2)) >> 10;
	// 		dct_reg[3][i] = (coeff2*d0-coeff6*d1-coeff0*d2-coeff4*d3) >> 10;
	// 		dct_reg[4][i] = (coeff3*(s0-s1-s2+s3)) >> 10;
	// 		dct_reg[5][i] = (coeff4*d0-coeff0*d1+coeff6*d2+coeff2*d3) >> 10;
	// 		dct_reg[6][i] = (coeff5*(s0-s3)+coeff1*(s2-s1)) >> 10;
	// 		dct_reg[7][i] = (coeff6*d0-coeff4*d1+coeff2*d2-coeff0*d3) >> 10;
	// 	end
	// end

	always @(posedge Clk, posedge Reset)
	begin
		if (Reset)
		begin
			pixels[0][0] <= pixels_0[0*8+:8];
			pixels[0][1] <= pixels_0[1*8+:8];
			pixels[0][2] <= pixels_0[2*8+:8];
			pixels[0][3] <= pixels_0[3*8+:8];
			pixels[0][4] <= pixels_0[4*8+:8];
			pixels[0][5] <= pixels_0[5*8+:8];
			pixels[0][6] <= pixels_0[6*8+:8];
			pixels[0][7] <= pixels_0[7*8+:8];

			pixels[1][0] <= pixels_1[0*8+:8];
			pixels[1][1] <= pixels_1[1*8+:8];
			pixels[1][2] <= pixels_1[2*8+:8];
			pixels[1][3] <= pixels_1[3*8+:8];
			pixels[1][4] <= pixels_1[4*8+:8];
			pixels[1][5] <= pixels_1[5*8+:8];
			pixels[1][6] <= pixels_1[6*8+:8];
			pixels[1][7] <= pixels_1[7*8+:8];

			pixels[2][0] <= pixels_2[0*8+:8];
			pixels[2][1] <= pixels_2[1*8+:8];
			pixels[2][2] <= pixels_2[2*8+:8];
			pixels[2][3] <= pixels_2[3*8+:8];
			pixels[2][4] <= pixels_2[4*8+:8];
			pixels[2][5] <= pixels_2[5*8+:8];
			pixels[2][6] <= pixels_2[6*8+:8];
			pixels[2][7] <= pixels_2[7*8+:8];

			pixels[3][0] <= pixels_3[0*8+:8];
			pixels[3][1] <= pixels_3[1*8+:8];
			pixels[3][2] <= pixels_3[2*8+:8];
			pixels[3][3] <= pixels_3[3*8+:8];
			pixels[3][4] <= pixels_3[4*8+:8];
			pixels[3][5] <= pixels_3[5*8+:8];
			pixels[3][6] <= pixels_3[6*8+:8];
			pixels[3][7] <= pixels_3[7*8+:8];

			pixels[4][0] <= pixels_4[0*8+:8];
			pixels[4][1] <= pixels_4[1*8+:8];
			pixels[4][2] <= pixels_4[2*8+:8];
			pixels[4][3] <= pixels_4[3*8+:8];
			pixels[4][4] <= pixels_4[4*8+:8];
			pixels[4][5] <= pixels_4[5*8+:8];
			pixels[4][6] <= pixels_4[6*8+:8];
			pixels[4][7] <= pixels_4[7*8+:8];

			pixels[5][0] <= pixels_5[0*8+:8];
			pixels[5][1] <= pixels_5[1*8+:8];
			pixels[5][2] <= pixels_5[2*8+:8];
			pixels[5][3] <= pixels_5[3*8+:8];
			pixels[5][4] <= pixels_5[4*8+:8];
			pixels[5][5] <= pixels_5[5*8+:8];
			pixels[5][6] <= pixels_5[6*8+:8];
			pixels[5][7] <= pixels_5[7*8+:8];

			pixels[6][0] <= pixels_6[0*8+:8];
			pixels[6][1] <= pixels_6[1*8+:8];
			pixels[6][2] <= pixels_6[2*8+:8];
			pixels[6][3] <= pixels_6[3*8+:8];
			pixels[6][4] <= pixels_6[4*8+:8];
			pixels[6][5] <= pixels_6[5*8+:8];
			pixels[6][6] <= pixels_6[6*8+:8];
			pixels[6][7] <= pixels_6[7*8+:8];

			pixels[7][0] <= pixels_7[0*8+:8];
			pixels[7][1] <= pixels_7[1*8+:8];
			pixels[7][2] <= pixels_7[2*8+:8];
			pixels[7][3] <= pixels_7[3*8+:8];
			pixels[7][4] <= pixels_7[4*8+:8];
			pixels[7][5] <= pixels_7[5*8+:8];
			pixels[7][6] <= pixels_7[6*8+:8];
			pixels[7][7] <= pixels_7[7*8+:8];

			state <= ROWSD;
		end
		else
		begin
			case (state)
				ROWSD:
					begin
						for (i=0; i<8; i=i+1)
						begin
							s0[i] <= pixels[i][0] + pixels[i][7] - 256;
							s1[i] <= pixels[i][1] + pixels[i][6] - 256;
							s2[i] <= pixels[i][2] + pixels[i][5] - 256;
							s3[i] <= pixels[i][3] + pixels[i][4] - 256;

							d0[i] <= pixels[i][0] - pixels[i][7];
							d1[i] <= pixels[i][1] - pixels[i][6];
							d2[i] <= pixels[i][2] - pixels[i][5];
							d3[i] <= pixels[i][3] - pixels[i][4];
						end
						state <= ROWCALC;
					end
				ROWCALC:
					begin
						for (i=0; i<8; i=i+1)
						begin
							dct_reg[i][0] <= (coeff3*(s0[i]+s1[i]+s2[i]+s3[i])) >> 10;
							dct_reg[i][1] <= (coeff0*d0[i]+coeff2*d1[i]+coeff4*d2[i]+coeff6*d3[i]) >> 10;
							dct_reg[i][2] <= (coeff1*(s0[i]-s3[i])+coeff5*(s1[i]-s2[i])) >> 10;
							dct_reg[i][3] <= (coeff2*d0[i]-coeff6*d1[i]-coeff0*d2[i]-coeff4*d3[i]) >> 10;
							dct_reg[i][4] <= (coeff3*(s0[i]-s1[i]-s2[i]+s3[i])) >> 10;
							dct_reg[i][5] <= (coeff4*d0[i]-coeff0*d1[i]+coeff6*d2[i]+coeff2*d3[i]) >> 10;
							dct_reg[i][6] <= (coeff5*(s0[i]-s3[i])+coeff1*(s2[i]-s1[i])) >> 10;
							dct_reg[i][7] <= (coeff6*d0[i]-coeff4*d1[i]+coeff2*d2[i]-coeff0*d3[i]) >> 10;
						end
						state <= COLSD;
					end
				COLSD:
					begin
						for (i=0; i<8; i=i+1)
						begin
							s0[i] <= dct_reg[0][i] + dct_reg[7][i];
							s1[i] <= dct_reg[1][i] + dct_reg[6][i];
							s2[i] <= dct_reg[2][i] + dct_reg[5][i];
							s3[i] <= dct_reg[3][i] + dct_reg[4][i];

							d0[i] <= dct_reg[0][i] - dct_reg[7][i];
							d1[i] <= dct_reg[1][i] - dct_reg[6][i];
							d2[i] <= dct_reg[2][i] - dct_reg[5][i];
							d3[i] <= dct_reg[3][i] - dct_reg[4][i];
						end
						state <= COLCALC;
					end
				COLCALC:
					begin
						for (i=0; i<8; i=i+1)
						begin
							dct_reg[0][i] <= (coeff3*(s0[i]+s1[i]+s2[i]+s3[i])) >> 10;
							dct_reg[1][i] <= (coeff0*d0[i]+coeff2*d1[i]+coeff4*d2[i]+coeff6*d3[i]) >> 10;
							dct_reg[2][i] <= (coeff1*(s0[i]-s3[i])+coeff5*(s1[i]-s2[i])) >> 10;
							dct_reg[3][i] <= (coeff2*d0[i]-coeff6*d1[i]-coeff0*d2[i]-coeff4*d3[i]) >> 10;
							dct_reg[4][i] <= (coeff3*(s0[i]-s1[i]-s2[i]+s3[i])) >> 10;
							dct_reg[5][i] <= (coeff4*d0[i]-coeff0*d1[i]+coeff6*d2[i]+coeff2*d3[i]) >> 10;
							dct_reg[6][i] <= (coeff5*(s0[i]-s3[i])+coeff1*(s2[i]-s1[i])) >> 10;
							dct_reg[7][i] <= (coeff6*d0[i]-coeff4*d1[i]+coeff2*d2[i]-coeff0*d3[i]) >> 10;
						end
						state <= DONE;
					end
			endcase
		end
	end
endmodule