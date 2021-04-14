
module video(

  input clk_vid,

  output hsync,
  output vsync,
  output hblank,
  output vblank,

  output [10:0] hpos,
  output [9:0] vpos

);

assign hpos = hcount;
assign vpos = vcount;

reg [10:0] hcount;
reg [9:0] vcount;


//https://www.improwis.com/tables/video.webt
//                                                                             pixel     front       back   front       back
//                                            Htotal Vtotal     hsync   vsync   clock     porch hsync porch  porch vsync porch
//    mode       name      res                pixels lines      kHz  pol pol     MHz       pix   pix   pix   lines lines lines
//a   arcade monitor        512x240@60.0       632    262      15.7199 - -       9.935        8    47   65      1    3   18        arcade/game modelines; fixed hsync freq arcade monitor

parameter HFP = 512;    // front porch
parameter HSP = HFP+47; // sync pulse
parameter HBP = HSP+65; // back porch
parameter HWL = HBP+8; // whole line
parameter VFP = 240;    // front porch
parameter VSP = VFP+3; // sync pulse
parameter VBP = VSP+18;  // back porch
parameter VWL = VBP+1; // whole line

assign hsync = ~((hcount >= HSP) && (hcount < HBP));
assign vsync = ~((vcount >= VSP) && (vcount < VBP));

assign hblank = hcount >= HFP;
assign vblank = vcount >= VFP;

always @(posedge clk_vid) begin
  hcount <= hcount + 11'd1;
  if (hcount == HWL) hcount <= 0;
end

always @(posedge clk_vid) begin
  if (hcount == HWL) begin
    if (vcount == VWL)
      vcount <= 0;
    else
      vcount <= vcount + 10'd1;
  end
end


endmodule