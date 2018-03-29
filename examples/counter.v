module Counter(
  input wire clk,
  input wire reset,
  output wire[3:0] io_out
);
  wire[3:0] add16;
  reg[3:0] reg10; // v2 - counter.cpp(14)

  assign add16 = reg10 + 4'h1;
  always @ (posedge clk) begin
    reg10 <= reset ? 4'h0 : add16;
  end

  assign io_out = reg10;

endmodule
