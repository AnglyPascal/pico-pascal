var a: array 10 of integer;
var i: integer;

(* haha *)

begin
  i := 2; 
  a[0] := 1; 
  a[1] := 1;
  while i < 10 do
    a[i] := a[i-2] + a[i-1];
    i := i+1
  end;
  i := 0;
  while i < 10 do
    print a[i]; newline;
    i := i+1;
  end
end.
