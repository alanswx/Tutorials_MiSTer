
module detect2600
(
	input clk,
	input reset,
	input [15:0] addr,
	input enable,
	input [31:0] cart_size,
	input [7:0] data,
	output reg [3:0] force_bs,
	output reg sc
);

/*
	if (ext == ".F8") force_bs <= 1;
		if (ext == ".F6") force_bs <= 2;
		if (ext == ".FE") force_bs <= 3;
		if (ext == ".E0") force_bs <= 4;
		if (ext == ".3F") force_bs <= 5;
		if (ext == ".F4") force_bs <= 6;
		if (ext == ".P2") force_bs <= 7; // Pitfall II
		if (ext == ".FA") force_bs <= 8;
		if (ext == ".CV") force_bs <= 9;
		if (ext == ".UA") force_bs <= 11;
		if (ext == ".E7") force_bs <= 12;
		if (ext == ".F0") force_bs <= 13;
		if (ext == ".32") force_bs <= 14;
*/

wire hasMatch3F;

`include "cart_constants.vh"

always @(posedge clk) begin
sc<=0;
if (hasMatchFE) force_bs<=BANKFE;
else if (hasMatchE0 && cart_size=='d8192) force_bs<=BANKE0;
else if (hasMatch3F && cart_size>'d4096) force_bs<=BANK3F;
else if (hasMatchCV) force_bs<=BANKCV;
else if (hasMatchE7) force_bs<=BANKE7;
else if (cart_size == 'h2000 && hasMatchUA ) force_bs<=BANKUA; //  8k and less
else if (cart_size == 'h1800) force_bs<=BANKAR; //  multiple of 8448 is cassette  AR 
else if (cart_size == 'h2100) force_bs<=BANKAR; //  multiple of 8448 is cassette  AR 
else if (cart_size == 'h4200) force_bs<=BANKAR; //  multiple of 8448 is cassette  AR 
else if (cart_size == 'h6300) force_bs<=BANKAR; //  multiple of 8448 is cassette  AR 
else if (cart_size == 'h8400) force_bs<=BANKAR; //  multiple of 8448 is cassette  AR 
else if (cart_size <= 'h0800) force_bs<=BANK2K; //  2k and less
else if (cart_size <= 'h1000) force_bs<=BANK00; //  4k and less
else if (cart_size <= 'h2000) begin 
	force_bs<=BANKF8; //  8k and less
        sc <= has_sc;
end
else if (cart_size >= 'h2800 && cart_size <= 'h2900) force_bs<=BANKP2; // 10k+256 and less, should be > 10k < 10k+256?
else if (cart_size <= 'h3000) force_bs<=BANKFA; // 12k and less
else if (cart_size <= 'h4000) begin
	force_bs<=BANKF6; // 16k and less
        sc <= has_sc;
end
else if (cart_size <= 'h8000) begin
	force_bs<=BANKF4; // 32k and less
        sc <= has_sc;
end
else if (cart_size < 'h10000) force_bs<=BANK32; // 64k and less
else if (cart_size == 'h10000) force_bs<=BANKF0; // 64k  - there are a few checks here
else force_bs<=0;


//wire hasMatchFE = (~hasMatchF8) && (hasMatchFE_0 | hasMatchFE_1 | hasMatchFE_2 | hasMatchFE_3 );
//$display(" hasMatchF8 %x hasMatchFE_0 %x hasMatchFE_1 %x hasMatcHFE_2 %x hasMatchFE_3 %x",hasMatchF8,hasMatchFE_0,hasMatchFE_1,hasMatchFE_2,hasMatchFE_3);
//$display(" hasMatchFE %x ",hasMatchFE);
end

//----------------------------
//  3F detector
//----------------------------

match_bytes #(
	.num_bytes(8'd2),
	.pattern({ 8'h85, 8'h3F }),
	.needmatches(8'd2)
	) match_bytes_3F(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatch3F)
);

//------------------------------
// E7 detector
//-------------------------------

/*
bool CartDetector::isProbablyE7(const ByteBuffer& image, size_t size)
{
  // E7 cart bankswitching is triggered by accessing addresses
  // $FE0 to $FE6 using absolute non-indexed addressing
  // To eliminate false positives (and speed up processing), we
  // search for only certain known signatures
  // Thanks to "stella@casperkitty.com" for this advice
  // These signatures are attributed to the MESS project
  uInt8 signature[7][3] = {
	{ 0xAD, 0xE2, 0xFF },  // LDA $FFE2
	{ 0xAD, 0xE5, 0xFF },  // LDA $FFE5
	{ 0xAD, 0xE5, 0x1F },  // LDA $1FE5
	{ 0xAD, 0xE7, 0x1F },  // LDA $1FE7
	{ 0x0C, 0xE7, 0x1F },  // NOP $1FE7
	{ 0x8D, 0xE7, 0xFF },  // STA $FFE7
	{ 0x8D, 0xE7, 0x1F }   // STA $1FE7
  };
  for(uInt32 i = 0; i < 7; ++i)
	if(searchForBytes(image, size, signature[i], 3))
	  return true;

  return false;
}
*/
wire hasMatchE7_0 , hasMatchE7_1 , hasMatchE7_2 , hasMatchE7_3 , hasMatchE7_4 , hasMatchE7_5 , hasMatchE7_6;
wire hasMatchE7 = hasMatchE7_0 | hasMatchE7_1 | hasMatchE7_2 | hasMatchE7_3 | hasMatchE7_4 | hasMatchE7_5 | hasMatchE7_6;
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE2 , 8'hFF }),
	.needmatches(8'd1)
	) match_bytes_E7_0(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_0)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE5 , 8'hFF }),
	.needmatches(8'd1)
	) match_bytes_E7_1(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_1)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE5 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E7_2(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_2)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE7 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E7_3(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_3)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h0C, 8'hE7 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E7_4(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_4)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hE7 , 8'hFF }),
	.needmatches(8'd1)
	) match_bytes_E7_5(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_5)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE7 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E7_6(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE7_6)
);

//------------------------------
// E0 detector
//-------------------------------
/*
bool CartDetector::isProbablyE0(const ByteBuffer& image, size_t size)
{
  // E0 cart bankswitching is triggered by accessing addresses
  // $FE0 to $FF9 using absolute non-indexed addressing
  // To eliminate false positives (and speed up processing), we
  // search for only certain known signatures
  // Thanks to "stella@casperkitty.com" for this advice
  // These signatures are attributed to the MESS project
  uInt8 signature[8][3] = {
	{ 0x8D, 0xE0, 0x1F },  // STA $1FE0
	{ 0x8D, 0xE0, 0x5F },  // STA $5FE0
	{ 0x8D, 0xE9, 0xFF },  // STA $FFE9
	{ 0x0C, 0xE0, 0x1F },  // NOP $1FE0
	{ 0xAD, 0xE0, 0x1F },  // LDA $1FE0
	{ 0xAD, 0xE9, 0xFF },  // LDA $FFE9
	{ 0xAD, 0xED, 0xFF },  // LDA $FFED
	{ 0xAD, 0xF3, 0xBF }   // LDA $BFF3
  };
  for(uInt32 i = 0; i < 8; ++i)
	if(searchForBytes(image, size, signature[i], 3))
	  return true;

  return false;
}
*/
wire  hasMatchE0_0 , hasMatchE0_1 , hasMatchE0_2 , hasMatchE0_3 , hasMatchE0_4 , hasMatchE0_5 , hasMatchE0_6 , hasMatchE0_7;
wire hasMatchE0 = hasMatchE0_0 | hasMatchE0_1 | hasMatchE0_2 | hasMatchE0_3 | hasMatchE0_4 | hasMatchE0_5 | hasMatchE0_6 | hasMatchE0_7;
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hE0 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E0_0(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_0)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hE0 , 8'h5F }),
	.needmatches(8'd1)
	) match_bytes_E0_1(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_1)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hE9 , 8'hFF }),
	.needmatches(8'd1)
	) match_bytes_E0_2(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_2)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h0C, 8'hE0 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E0_3(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_3)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE0 , 8'h1F }),
	.needmatches(8'd1)
	) match_bytes_E0_4(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_4)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hE9 , 8'hFF }),
	.needmatches(8'd1)
	) match_bytes_E0_5(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_5)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hED , 8'hFF }),
	.needmatches(8'd1)
	) match_bytes_E0_6(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_6)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hF3 , 8'hBF }),
	.needmatches(8'd1)
	) match_bytes_E0_7(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchE0_7)
);

//------------------------------
// FE detector
//-------------------------------
// we need to check is FE and not F8

wire hasMatchF8_0 , hasMatchF8_1;
wire hasMatchF8 = hasMatchF8_0 | hasMatchF8_1;
wire hasMatchFE_0 , hasMatchFE_1 , hasMatchFE_2 , hasMatchFE_3;
wire hasMatchFE = (~hasMatchF8) && (hasMatchFE_0 | hasMatchFE_1 | hasMatchFE_2 | hasMatchFE_3 );


match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hF9 , 8'h1F }),
	.needmatches(8'd2)
	) match_bytes_F8_0(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchF8_0)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hF9 , 8'hFF }),
	.needmatches(8'd2)
	) match_bytes_F8_1(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchF8_1)
);


match_bytes #(
	.num_bytes(8'd5),
	.pattern({ 8'h20, 8'h00 , 8'hD0, 8'hC6 , 8'hC5 }),
	.needmatches(8'd1)
	) match_bytes_FE_0(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchFE_0)
);
match_bytes #(
	.num_bytes(8'd5),
	.pattern({ 8'h20, 8'hC3 , 8'hF8, 8'hA5 , 8'h82 }),
	.needmatches(8'd1)
	) match_bytes_FE_1(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchFE_1)
);
match_bytes #(
	.num_bytes(8'd5),
	.pattern({ 8'hD0, 8'hFB , 8'h20, 8'h73 , 8'hFE }),
	.needmatches(8'd1)
	) match_bytes_FE_2(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchFE_2)
);
match_bytes #(
	.num_bytes(8'd5),
	.pattern({ 8'h20, 8'h00 , 8'hF0, 8'h84 , 8'hD6 }),
	.needmatches(8'd1)
	) match_bytes_FE_3(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchFE_3)
);
/*



	// First check for *potential* F8
	uInt8 signature[2][3] = {
	  { 0x8D, 0xF9, 0x1F },  // STA $1FF9
	  { 0x8D, 0xF9, 0xFF }   // STA $FFF9
	};
	bool f8 = searchForBytes(image, size, signature[0], 3, 2) ||
			  searchForBytes(image, size, signature[1], 3, 2);


	else if(isProbablyFE(image, size) && !f8)
	  type = Bankswitch::Type::_FE;


bool CartDetector::isProbablyFE(const ByteBuffer& image, size_t size)
{
  // FE bankswitching is very weird, but always seems to include a
  // 'JSR $xxxx'
  // These signatures are attributed to the MESS project
  uInt8 signature[4][5] = {
	{ 0x20, 0x00, 0xD0, 0xC6, 0xC5 },  // JSR $D000; DEC $C5
	{ 0x20, 0xC3, 0xF8, 0xA5, 0x82 },  // JSR $F8C3; LDA $82
	{ 0xD0, 0xFB, 0x20, 0x73, 0xFE },  // BNE $FB; JSR $FE73
	{ 0x20, 0x00, 0xF0, 0x84, 0xD6 }   // JSR $F000; $84, $D6
  };
  for(uInt32 i = 0; i < 4; ++i)
	if(searchForBytes(image, size, signature[i], 5))
	  return true;

  return false;
}
*/

//------------------------------
// CV detector
//-------------------------------

wire hasMatchCV_0 , hasMatchCV_1;
wire hasMatchCV = hasMatchCV_0 | hasMatchCV_1;


match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h9D, 8'hFF , 8'hF3 }),
	.needmatches(8'd1)
	) match_bytes_CV_0(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchCV_0)
);
match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h99, 8'h00 , 8'hF4 }),
	.needmatches(8'd1)
	) match_bytes_CV_1(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchCV_1)
);
/*
bool CartDetector::isProbablyCV(const ByteBuffer& image, size_t size)
{
  // CV RAM access occurs at addresses $f3ff and $f400
  // These signatures are attributed to the MESS project
  uInt8 signature[2][3] = {
	{ 0x9D, 0xFF, 0xF3 },  // STA $F3FF.X
	{ 0x99, 0x00, 0xF4 }   // STA $F400.Y
  };
  if(searchForBytes(image, size, signature[0], 3))
	return true;
  else
	return searchForBytes(image, size, signature[1], 3);
}
*/

//------------------------------
// UA detector
//-------------------------------

wire hasMatchUA_0 , hasMatchUA_1 , hasMatchUA_2 , hasMatchUA_3 , hasMatchUA_4 , hasMatchUA_5 , hasMatchUA_6;
wire hasMatchUA = hasMatchUA_0 | hasMatchUA_1 | hasMatchUA_2 | hasMatchUA_3 | hasMatchUA_4 | hasMatchUA_5 | hasMatchUA_6;

match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'h40 , 8'h02 }),
	.needmatches(8'd1)
	) match_bytes_UA_0(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_0)
);

match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'h40 , 8'h02 }),
	.needmatches(8'd1)
	) match_bytes_UA_1(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_1)
);


match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hBD, 8'h1F , 8'h02 }),
	.needmatches(8'd1)
	) match_bytes_UA_2(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_2)
);

match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h2C, 8'hC0 , 8'h02 }),
	.needmatches(8'd1)
	) match_bytes_UA_3(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_3)
);

match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h8D, 8'hC0 , 8'h02 }),
	.needmatches(8'd1)
	) match_bytes_UA_4(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_4)
);

match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'hAD, 8'hC0 , 8'h02 }),
	.needmatches(8'd1)
	) match_bytes_UA_5(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_5)
);

match_bytes #(
	.num_bytes(8'd3),
	.pattern({ 8'h2C, 8'hC0 , 8'h0F }),
	.needmatches(8'd1)
	) match_bytes_UA_6(
	.addr(addr),
	.enable(enable),
	.clk(clk),
	.reset(reset),
	.data(data),
	.hasMatch(hasMatchUA_6)
);
/*
bool CartDetector::isProbablyUA(const ByteBuffer& image, size_t size)
{
  // UA cart bankswitching switches to bank 1 by accessing address 0x240
  // using 'STA $240' or 'LDA $240'
  // Similar Brazilian (Digivison) cart bankswitching switches to bank 1 by accessing address 0x2C0
  // using 'BIT $2C0', 'STA $2C0' or 'LDA $2C0'
  // Other Brazilian (Atari Mania) ROM's bankswitching switches to bank 1 by accessing address 0xFC0
  // using 'BIT $FA0', 'BIT $FC0' or 'STA $FA0'
  uInt8 signature[7][3] = {
    { 0x8D, 0x40, 0x02 },  // STA $240 (Funky Fish, Pleiades)
    { 0xAD, 0x40, 0x02 },  // LDA $240 (???)
    { 0xBD, 0x1F, 0x02 },  // LDA $21F,X (Gingerbread Man)
    { 0x2C, 0xC0, 0x02 },  // BIT $2C0 (Time Pilot)
    { 0x8D, 0xC0, 0x02 },  // STA $2C0 (Fathom, Vanguard)
    { 0xAD, 0xC0, 0x02 },  // LDA $2C0 (Mickey)
    { 0x2C, 0xC0, 0x0F }   // BIT $FC0 (H.E.R.O., Kung-Fu Master)
  };
  for(uInt32 i = 0; i < 7; ++i)
    if(searchForBytes(image, size, signature[i], 3))
      return true;

  return false;
}
*/

//------------------------------
// SC detector
//-------------------------------
//


/*
bool CartDetector::isProbablySC(const ByteBuffer& image, size_t size)
{
  // We assume a Superchip cart repeats the first 128 bytes for the second
  // 128 bytes in the RAM area, which is the first 256 bytes of each 4K bank
  const uInt8* ptr = image.get();
  while(size)
  {
	if(std::memcmp(ptr, ptr + 128, 128) != 0)
	  return false;

	ptr  += 4_KB;
	size -= 4_KB;
  }
  return true;
}
*/

// grab and save the CRC for the first 128 bytes
// each 4k check 128 bytes, and fail if CRC doesn't match
reg [31:0] sc_crc0,sc_crc1,sc_crc2;
reg has_sc;

// 80 - 100

always @(posedge clk) begin
	if (enable) begin
		if (addr < 16'h80) begin
			if (addr==0)
			begin
				sc_crc1<=0;
				has_sc<=0;
				sc_crc0<=nextCRC32_D8(data,32'b0);
			end
			else
				sc_crc0<=nextCRC32_D8(data,sc_crc0);
		end
		else if (addr >= 16'h80 && addr < 16'h100) begin
			sc_crc1<=nextCRC32_D8(data,sc_crc1);
		end
		else if (addr==16'h100) begin
			has_sc<= (sc_crc0==sc_crc1);
			sc_crc0<=0;
			sc_crc1<=0;
		end
		if (addr >= 16'h1000 && addr < 16'h1080) begin
			sc_crc0<=nextCRC32_D8(data,sc_crc0);
		end
		else if (addr >= 16'h1080 && addr < 16'h1100) begin
			sc_crc1<=nextCRC32_D8(data,sc_crc1);
		end
		else if (addr==16'h1100) begin
                        if (has_sc)
				has_sc<= (sc_crc0==sc_crc1);
		end
	end
end




////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1999-2008 Easics NV.
// This source file may be used and distributed without restriction
// provided that this copyright statement is not removed from the file
// and that any derivative work contains the original copyright notice
// and the associated disclaimer.
//
// THIS SOURCE FILE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Purpose : synthesizable CRC function
//   * polynomial: x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
//   * data width: 8
//
// Info : tools@easics.be
//        http://www.easics.com
////////////////////////////////////////////////////////////////////////////////
  // polynomial: x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
  // data width: 8
  // convention: the first serial bit is D[7]
  function [31:0] nextCRC32_D8;

	input [7:0] Data;
	input [31:0] crc;
	reg [7:0] d;
	reg [31:0] c;
	reg [31:0] newcrc;
  begin
	d = Data;
	c = crc;

	newcrc[0] = d[6] ^ d[0] ^ c[24] ^ c[30];
	newcrc[1] = d[7] ^ d[6] ^ d[1] ^ d[0] ^ c[24] ^ c[25] ^ c[30] ^ c[31];
	newcrc[2] = d[7] ^ d[6] ^ d[2] ^ d[1] ^ d[0] ^ c[24] ^ c[25] ^ c[26] ^ c[30] ^ c[31];
	newcrc[3] = d[7] ^ d[3] ^ d[2] ^ d[1] ^ c[25] ^ c[26] ^ c[27] ^ c[31];
	newcrc[4] = d[6] ^ d[4] ^ d[3] ^ d[2] ^ d[0] ^ c[24] ^ c[26] ^ c[27] ^ c[28] ^ c[30];
	newcrc[5] = d[7] ^ d[6] ^ d[5] ^ d[4] ^ d[3] ^ d[1] ^ d[0] ^ c[24] ^ c[25] ^ c[27] ^ c[28] ^ c[29] ^ c[30] ^ c[31];
	newcrc[6] = d[7] ^ d[6] ^ d[5] ^ d[4] ^ d[2] ^ d[1] ^ c[25] ^ c[26] ^ c[28] ^ c[29] ^ c[30] ^ c[31];
	newcrc[7] = d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[0] ^ c[24] ^ c[26] ^ c[27] ^ c[29] ^ c[31];
	newcrc[8] = d[4] ^ d[3] ^ d[1] ^ d[0] ^ c[0] ^ c[24] ^ c[25] ^ c[27] ^ c[28];
	newcrc[9] = d[5] ^ d[4] ^ d[2] ^ d[1] ^ c[1] ^ c[25] ^ c[26] ^ c[28] ^ c[29];
	newcrc[10] = d[5] ^ d[3] ^ d[2] ^ d[0] ^ c[2] ^ c[24] ^ c[26] ^ c[27] ^ c[29];
	newcrc[11] = d[4] ^ d[3] ^ d[1] ^ d[0] ^ c[3] ^ c[24] ^ c[25] ^ c[27] ^ c[28];
	newcrc[12] = d[6] ^ d[5] ^ d[4] ^ d[2] ^ d[1] ^ d[0] ^ c[4] ^ c[24] ^ c[25] ^ c[26] ^ c[28] ^ c[29] ^ c[30];
	newcrc[13] = d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[2] ^ d[1] ^ c[5] ^ c[25] ^ c[26] ^ c[27] ^ c[29] ^ c[30] ^ c[31];
	newcrc[14] = d[7] ^ d[6] ^ d[4] ^ d[3] ^ d[2] ^ c[6] ^ c[26] ^ c[27] ^ c[28] ^ c[30] ^ c[31];
	newcrc[15] = d[7] ^ d[5] ^ d[4] ^ d[3] ^ c[7] ^ c[27] ^ c[28] ^ c[29] ^ c[31];
	newcrc[16] = d[5] ^ d[4] ^ d[0] ^ c[8] ^ c[24] ^ c[28] ^ c[29];
	newcrc[17] = d[6] ^ d[5] ^ d[1] ^ c[9] ^ c[25] ^ c[29] ^ c[30];
	newcrc[18] = d[7] ^ d[6] ^ d[2] ^ c[10] ^ c[26] ^ c[30] ^ c[31];
	newcrc[19] = d[7] ^ d[3] ^ c[11] ^ c[27] ^ c[31];
	newcrc[20] = d[4] ^ c[12] ^ c[28];
	newcrc[21] = d[5] ^ c[13] ^ c[29];
	newcrc[22] = d[0] ^ c[14] ^ c[24];
	newcrc[23] = d[6] ^ d[1] ^ d[0] ^ c[15] ^ c[24] ^ c[25] ^ c[30];
	newcrc[24] = d[7] ^ d[2] ^ d[1] ^ c[16] ^ c[25] ^ c[26] ^ c[31];
	newcrc[25] = d[3] ^ d[2] ^ c[17] ^ c[26] ^ c[27];
	newcrc[26] = d[6] ^ d[4] ^ d[3] ^ d[0] ^ c[18] ^ c[24] ^ c[27] ^ c[28] ^ c[30];
	newcrc[27] = d[7] ^ d[5] ^ d[4] ^ d[1] ^ c[19] ^ c[25] ^ c[28] ^ c[29] ^ c[31];
	newcrc[28] = d[6] ^ d[5] ^ d[2] ^ c[20] ^ c[26] ^ c[29] ^ c[30];
	newcrc[29] = d[7] ^ d[6] ^ d[3] ^ c[21] ^ c[27] ^ c[30] ^ c[31];
	newcrc[30] = d[7] ^ d[4] ^ c[22] ^ c[28] ^ c[31];
	newcrc[31] = d[5] ^ c[23] ^ c[29];
	nextCRC32_D8 = newcrc;
  end
  endfunction

endmodule: detect2600

module match_bytes
(
	input clk,
	input reset,
	input  [15:0] addr,
	input  enable,
	input  [7:0] data,     // data in,
	output reg hasMatch
);

parameter [7:0] num_bytes;
parameter [(num_bytes*8)-1:0] pattern;
parameter [7:0] needmatches=8'b1;

reg [(num_bytes*8)-1:0] lastPattern;

reg [7:0] curMatch;

always @(posedge clk)
begin
	if (enable)
	begin
		// use address 0 as reset since reset is high during cart loads
		if (addr==16'b0)
		begin
			curMatch<=8'b0;
			hasMatch<=0;
			lastPattern<= {lastPattern[(num_bytes*8)-9:0],data};
		end
		else
		begin
			lastPattern<= {lastPattern[(num_bytes*8)-9:0],data};
			if (lastPattern == pattern)
			begin
					curMatch<=curMatch+8'b1;
					if (curMatch==(needmatches-8'b1))
						hasMatch<=1;
			end
		end
	end
	if (reset) begin
		curMatch <= 0;
		hasMatch <= 0;
		lastPattern <= '0;
	end
end

endmodule: match_bytes





