subroutine ex(a,b)
real a,b,c,d,e
c=a*b
e=c
if (c>0) then
  d=a*c
  c=e*d
  c=c+b
  b=c
else  
  e=c
  d=a*c
  b=e
endif
end
