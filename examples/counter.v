module Counter(
  input wire clk,
  input wire reset,
  output wire[3:0] io_out
);
  wire[3:0] add15;
  reg[3:0] reg12; // v2 - counter.cpp(14)

  assign add15 = reg12 + 4'h1;
  always @ (posedge clk) begin
    reg12 <= reset ? 4'h0 : add15;
  end

  assign io_out = reg12;

endmodule
