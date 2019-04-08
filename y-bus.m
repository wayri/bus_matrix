clear
clc
val =0;
n1 = 0;
n2 = 0;
run = true;
ui = '0';
bam = zeros(3);


while(run)
val = input('input admittance value ->')
n1 = input('enter node 1 ->')
n2 = input('enter node 2 ->')

%check one node is zero condition or otherwise-
if (n1 == 0)
  bam(n2, n2) += val;
  

else if (n2 == 0)
   bam(n1, n1) += val;
 
 else 
   bam(n1, n2) -= val;
 end
 %------------------------------------------
 
 if ((n1 ~= 0 & n2 ~= 0) & (n1 ~= n2))
 bam(n1, n1) += val;
 bam(n2, n2) += val;
 bam(n2, n1) -= val;
 end
  
ui = input('to stop press "s"')
  if (ui == 100)  
   break
   end
end
end

disp('\n the resulting matrix is\n')
bam
