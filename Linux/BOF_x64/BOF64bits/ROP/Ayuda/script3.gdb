define find_pop_rdx
  set $addr = 0x0000000000400000
  while $addr < 0x00007fffffffffff
    x/i $addr
    if ($_ == 'pop rdx')
      printf "Found pop rdx at: %p\n", $addr
    end
    set $addr = $addr + 1
  end
end

