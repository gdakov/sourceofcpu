//38x72, but on the inside a lot of pads are unused so far
`define ch0_ras [37][0]
`define ch0_cas [37][1]
`define ch0_rw [37][2]
`define ch0_addr [37][17:3]
//A side
`define ch0_data0 [37][35:18]
//B side
`define ch0_data1 [37][35:18]

`define ch2_ras [36][0]
`define ch2_cas [36][1]
`define ch2_rw [36][2]
`define ch2_addr [36][17:3]
//A side
`define ch2_data0 [36][35:18]
//B side
`define ch2_data1 [36][35:18]

`define ch1_ras [37][36]
`define ch1_cas [37][37]
`define ch1_rw [37][38]
`define ch1_addr [37][53:39]
//A side
`define ch1_data0 [37][71:54]
//B side
`define ch1_data1 [36][71:54]
`define ch3_ras [36][36]
`define ch3_cas [36][37]
`define ch3_rw [36][38]
`define ch3_addr [36][53:39]
//A side
`define ch3_data0 [36][71:54]
//B side
`define ch3_data1 [36][71:54]

//tr=transpose left (clockwise)
`define ch4_ras_tr [35][2]
`define ch4_cas_tr [35][3]
`define ch4_rw_tr [35][4]
`define ch4_addr_rt[35][19:5]
//A side
`define ch4_data_tr[35][37:20]
//B side
`define ch4_data_tr[35][37:20]
//tr=transpose left (clockwise)
`define ch5_ras_tr [34][2]
`define ch5_cas_tr [34][3]
`define ch5_rw_tr [34][4]
`define ch5_addr_tr[34][19:5]
//A side
`define ch5_data_tr[34][37:20]
//B side
`define ch5_data_tr[34][37:20]

//tl=transpose right (anti-clockwise)
`define ch6_ras_tl [0][2]
`define ch6_cas_tl [0][3]
`define ch6_rw_tl [0][4]
`define ch6_addr_rt[0][19:5]
//A side
`define ch6_data_tl[0][37:20]
//B side
`define ch6_data_tl[0][37:20]
//tl=tlanspose right (anti-clockwise)
`define ch7_ras_tl [1][2]
`define ch7_cas_tl [1][3]
`define ch7_rw_tl [1][4]
`define ch7_addr_tl[1][19:5]
//A side
`define ch7_data_tl[1][37:20]
//B side
`define ch7_data_tl[1][37:20]


`define serdes_in [0][69:36]
`define serdes_out [1][69:36]
//REPEATE many times
`define [0][35:29] GND;
`define [0][28:22] V12;
//END REPEATE
`define [0][21] clkin;
`define [1][21] clkin_inv;
`define [0][20] rst;
`define [1][20] rst_inv;
`define [0][2:19] chipset_in;
`define [1][2:19] chipset_out;
