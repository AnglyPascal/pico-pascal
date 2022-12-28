(* lab3/fac.p *)

proc fac(var i, j: integer; var b, c: boolean;): integer;
var k: integer;
  proc f();
  begin 
  end;

begin
  if i = 0 then
    return 1
  else
    return i * fac(i-1, j, b, c)
  end
end;

begin
  print fac(10, 0, false, false); newline
end.

(*<<
 3628800
>>*)
