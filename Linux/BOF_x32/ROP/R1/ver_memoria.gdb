define print_mem
  set $i = 0
  set $addr = $esp 
  while ($i < 25)  
    #printf "0x%x\t0x%x: 0x", $addr, $addr
    printf "0x%x: 0x", $addr
    set $val1 = *(unsigned char *)$addr
    set $val2 = *(unsigned char *)($addr+1)
    set $val3 = *(unsigned char *)($addr+2)
    set $val4 = *(unsigned char *)($addr+3)
    printf "%02x%02x%02x%02x\n", $val4, $val3, $val2, $val1
    set $addr = $addr + 4
    set $i = $i + 1
  end
end

