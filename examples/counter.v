module Counter(
  input wire clk,
  input wire reset,
  output wire[3:0] io_out
);
  reg[3:0] reg7; // counter.cpp(14)
  wire[3:0] add14;

  always @ (posedge clk) begin
    reg7 <= reset ? 4'h2 : add14;
  end
  assign add14 = reg7 + 4'h1;

  assign io_out = reg7;

endmodule
