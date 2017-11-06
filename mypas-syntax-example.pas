
var a, b, c: double;
    
begin 
	a:= 3.14159;
	b:= 2.71828;
	
	c := a * b * (a * c + b * c) / (a * b - (a + b));
	if a <= b then
		a := a + b
	else
		a := b	
end.

