# 2600 Detector

The original 2600 core didn't autodetect carts. Instead it used a wildcard in the config string, and it looked at the file extension to pick a mapper. This meant that each cartridge needed to be named correctly. 

The [Stella Cart Detector](https://github.com/stella-emu/stella/blob/916a2cdfff0a79ef39942bf12fce4974f6bc51ac/src/emucore/CartDetector.cxx) uses a bunch of heuristics to search through the cartridge for known opcodes to detect the cart type.

In C:

```C 

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


bool CartDetector::searchForBytes(const uInt8* image, size_t imagesize,
                                  const uInt8* signature, uInt32 sigsize,
                                  uInt32 minhits)
{
  uInt32 count = 0;

  for(uInt32 i = 0; i < imagesize - sigsize; ++i)
  {
    uInt32 j;

    for(j = 0; j < sigsize; ++j)
    {
      if(image[i + j] != signature[j])
        break;
    }
    if(j == sigsize)
    {
      if(++count == minhits)
        break;
      i += sigsize;  // skip past this signature 'window' entirely
    }
  }

  return (count == minhits);
}
```

in verilog, we can write a similar module, but it is going to look at a byte stream instead of reading through memory. We can do all the checks in parallel by instantiating a lot of matching modules.

we use parameters in the module to configure it and pass in the bytes we are looking for.

here is the module:

```verilog
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
```

# Testbench

Now that we have some code, we would like to see if it autodetects the cartridges correctly.  We can use verilator to load a cartridge and feed it to our detect routine. We will create a simple top that is called from verilator, and instantiates our 2600 detector. We put in a few lines of help so that the code will print out a comma delimited string, and set a done flag when it is finished. This makes things a bit simpler.

We can pass md5sum a list of files, and it will create md5 checksums and filenames. A quick copy/replace and we can turn it into a CSV file. We use a python program to read this file and a spreadsheet we found on the web to load and check each rom, and dump out the results.