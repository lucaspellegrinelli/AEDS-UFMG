program fribonacci;
n, a, b, c, i: integer
begin
  read(n);

  a := 0;
  b := 1;
  c := 0;
  i := 2;

  if n = 0 then
    write(0);

  while i <= n do
    c := a + b;
    a := b;
    b := c
  end;
  
  write(b)
end