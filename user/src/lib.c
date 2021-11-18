

int main()
{
  panic("Cannot find main!");
}

// __attribute__((section("section_name")))，其作用是将作用的函数或数据放入指定名为"section_name"对应的段中

__attribute__((section(".text.entry"))) void _start()
{
  clear_bss();
  exit(main());
  panic("unreachable after sys_exit!");
}