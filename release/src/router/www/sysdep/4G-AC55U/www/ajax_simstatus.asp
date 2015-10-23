sim_state = '<% nvram_get("usb_modem_act_sim"); %>';
g3err_pin = '<% nvram_get("g3err_pin"); %>';
modem_signal = '<% nvram_get("usb_modem_act_signal"); %>';
modem_operation = '<% nvram_get("usb_modem_act_operation"); %>';
modem_isp = '<% nvram_get("modem_isp"); %>';
rx_bytes = parseFloat('<% nvram_get("modem_bytes_rx"); %>');
tx_bytes = parseFloat('<% nvram_get("modem_bytes_tx"); %>');
