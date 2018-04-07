module Counter(
  input wire clk,
  input wire reset,
  output wire[3:0] io_out
);
  wire[3:0] add14;
  reg[3:0] reg7;

  assign add14 = reg7 + 4'h1;
  always @ (posedge clk) begin
    reg7 <= reset ? 4'h0 : add14;
  end

  assign io_out = reg7;

endmodule
