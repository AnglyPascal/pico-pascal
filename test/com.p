proc sum(proc f(var i: integer;): integer; var n: integer;): integer;
  var m, s: integer;
  begin
    m := 0; s := 0;
    while m < n do 
      m := m + 1; 
      s := s + f(m)
    end;
    return s
  end;

proc sumpow(var n, k: integer;): integer;
  proc pow(var p: integer;): integer;
    var j, q: integer;
  begin
    j := 0; q := 1;
    while j < k do 
      j := j+1; q := q*p
    end;
    return q
  end;

begin
  return sum(pow, n)
end;

begin
  print sumpow(5, 4); newline
end.
